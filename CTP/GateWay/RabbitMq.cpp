#include "RabbitMq.h"
#include "MqUtils.h"
#include<chrono>

using namespace std;
using namespace std::chrono;
#define CURR_STIME_POINT duration_cast<chrono::seconds>(system_clock::now().time_since_epoch()).count()



int RabbitMq::init()
{
  int res = init_consumer(recv1Connection_, hostName_, port_, user_, passwd_, recv1QueueName_, exchange_, bindingkey1_);
  if (res) {
    //Ê§°Ü
  }
  res = init_consumer(recv2Connection_, hostName_, port_, user_, passwd_, recv2QueueName_, exchange_, bindingkey2_);
  if (res) {
    //Ê§°Ü
  }


  props_._flags = AMQP_BASIC_CONTENT_TYPE_FLAG | AMQP_BASIC_DELIVERY_MODE_FLAG;
  props_.content_type = amqp_cstring_bytes("text/plain");
  props_.delivery_mode = 2; /* persistent delivery mode */
                            //0,1,0 auto ack 0,0,0 no auto ack

  res = init_publish(send1Connection_, hostName_, port_, user_, passwd_);
  if (res) {
    //Ê§°Ü
  }

  res = init_publish(send2Connection_, hostName_, port_, user_, passwd_);
  if (res) {
    //Ê§°Ü
  }
  return 0;
}

void RabbitMq::run()
{
  string msg;
  while (true) {
    try
    {
      bool ret = recvQueue1();
      if (ret) {
        lastRecvTime_ = CURR_STIME_POINT;
      }
      while (recv1Msg_->dequeue(msg)) {
        //sendMsg1(msg.c_str());
      }
      ret = recvQueue2();
      while (recv2Msg_->dequeue(msg)) {
        //sendMsg1(msg.c_str());
      }
    }
    catch (std::exception &ex)
    {
      //LOG_ERROR << "exception:" << ex.what();
      //sendTimeOut();
    }
    catch (...)
    {
      //LOG_ERROR << "exception";
      //sendTimeOut();
    }
    return;
  }
}

int RabbitMq::recvQueue1()
{
  static int count = 0;
  amqp_envelope_t envelope;
  amqp_maybe_release_buffers(recv1Connection_);
  amqp_rpc_reply_t ret = amqp_consume_message(recv1Connection_, &envelope, &tval_, 0);
  int res = die_on_amqp_error(ret, "consume receive message");
  if (!res)
  {
    return -1;
  }
  //handleJsonMessage(envelope.message.body.bytes, envelope.message.body.len);
  handleQueue1(envelope.message.body.bytes, envelope.message.body.len);

  return 0;
}

int RabbitMq::recvQueue2()
{
  static int count = 0;
  amqp_envelope_t envelope;
  amqp_maybe_release_buffers(recv2Connection_);
  amqp_rpc_reply_t ret = amqp_consume_message(recv2Connection_, &envelope, &tval_, 0);
  int res = die_on_amqp_error(ret, "consume receive message");
  if (!res)
  {
    return -1;
  }
  //handleQueue1(envelope.message.body.bytes, envelope.message.body.len);
  return 0;
}

int RabbitMq::handleQueue1(void * body, unsigned int len)
{
  rapidjson::Document doc;
  doc.Parse(static_cast<const char *>(body), len);
  if (doc.HasParseError())
  {
    char buff[1024];
    memcpy(buff, body, len < 1023 ? len : 1023);
    string buffer = "consumer json parse error: ";
    buffer = buffer + buff;
    //LOG_THROW(buffer.c_str());
    //·¢ËÍ
  }

  std::map<std::string, setMethod> mapMeth;
  for (rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr) {
    recv1Msg_->enqueue(itr->value.GetString());
    //if (strcmp(itr->name.GetString(), "Title") == 0) {
    //  recv1Msg->enqueue(itr->value.GetString());
    //}
  }

  return 0;
}

int RabbitMq::handleQueue2(void * body, unsigned int len)
{
  rapidjson::Document doc;
  doc.Parse(static_cast<const char *>(body), len);
  if (doc.HasParseError())
  {
    char buff[1024];
    memcpy(buff, body, len < 1023 ? len : 1023);
    string buffer = "consumer json parse error: ";
    buffer = buffer + buff;
    //LOG_THROW(buffer.c_str());
    //·¢ËÍ
  }

  std::map<std::string, setMethod> mapMeth;
  for (rapidjson::Value::ConstMemberIterator itr = doc.MemberBegin(); itr != doc.MemberEnd(); ++itr) {
    recv1Msg_->enqueue(itr->value.GetString());
    //if (strcmp(itr->name.GetString(), "Title") == 0) {
    //  recv1Msg->enqueue(itr->value.GetString());
    //}
  }

  return 0;
}

int RabbitMq::sendMsg1(const char * msg)
{
  int res = amqp_basic_publish(send1Connection_,
    1,
    amqp_cstring_bytes(""),
    amqp_cstring_bytes(send1QueueName_.c_str()),
    0,
    0,
    &props_,
    amqp_cstring_bytes(msg));
  if (res < 0)
  {
    string buffer = "publish error: ";
    buffer = buffer + amqp_error_string2(res);
    //LOG_THROW(buffer.c_str());
  }
  fprintf(stdout, "send message\n");
  return 0;
}

int RabbitMq::sendMsg2(const char * msg)
{
  int res = amqp_basic_publish(send2Connection_,
    1,
    amqp_cstring_bytes(""),
    amqp_cstring_bytes(send2QueueName_.c_str()),
    0,
    0,
    &props_,
    amqp_cstring_bytes(msg));
  if (res < 0)
  {
    string buffer = "publish error: ";
    buffer = buffer + amqp_error_string2(res);
    //LOG_THROW(buffer.c_str());
  }
  return 0;
}



