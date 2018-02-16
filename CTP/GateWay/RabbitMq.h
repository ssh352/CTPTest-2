#ifndef __RABBITMA_H__
#define __RABBITMA_H__
#include <string>
#include <amqp.h>
//#include <winnt.h>
//#define __memory_barrier() MemoryBarrier()

using namespace std;



size_t const cache_line_size = 64;

template<typename T>
T load_consume(T const* addr)
{

  // hardware fence is implicit on x86 
  T v = *const_cast<T const volatile*>(addr);
  //__memory_barrier(); // compiler fence 
  return v;
}

template<typename T>
void store_release(T* addr, T v)
{
  // hardware fence is implicit on x86 
  //__memory_barrier(); // compiler fence
  *const_cast<T volatile*>(addr) = v;
}

template<typename T>
class spsc_queue
{
public:

  spsc_queue()
  {
    node* n = new node;
    n->next_ = 0;
    tail_ = head_ = first_ = tail_copy_ = n;
  }

  ~spsc_queue()
  {
    node* n = first_;
    do
    {
      node* next = n->next_;
      delete n;
      n = next;
    } while (n);
  }

  void enqueue(T v)
  {
    node* n = alloc_node();
    n->next_ = 0;
    n->value_ = v;
    store_release(&head_->next_, n);
    head_ = n;
  }

  // returns 'false' if queue is empty 
  bool dequeue(T& v)
  {
    if (load_consume(&tail_->next_))
    {
      v = tail_->next_->value_;
      store_release(&tail_, tail_->next_);
      return true;
    }
    else
    {
      return false;
    }
  }

private:
  // internal node structure 
  struct node
  {
    node* next_;
    T value_;
  };

  // consumer part 
  // accessed mainly by consumer, infrequently be producer 

  node* tail_; // tail of the queue  
               // delimiter between consumer part and producer part, 
               // so that they situated on different cache lines 
  char cache_line_pad_[cache_line_size];

  // producer part 
  // accessed only by producer 
  node* head_; // head of the queue 
  node* first_; // last unused node (tail of node cache) 
  node* tail_copy_; // helper (points somewhere between first_ and tail_) 

  node* alloc_node()
  {
    // first tries to allocate node from internal node cache, 
    // if attempt fails, allocates node via ::operator new() 

    if (first_ != tail_copy_)
    {
      node* n = first_;
      first_ = first_->next_;
      return n;
    }

    tail_copy_ = load_consume(&tail_);
    if (first_ != tail_copy_)
    {
      node* n = first_;
      first_ = first_->next_;
      return n;
    }

    node* n = new node;
    return n;
  }

  //spsc_queue(spsc_queue const&);
  //spsc_queue& operator = (spsc_queue const&);
};
typedef spsc_queue<string>* MessageCache;

struct timeval {
  long    tv_sec;         /* seconds */
  long    tv_usec;        /* and microseconds */
};

class RabbitMq
{
public:
  RabbitMq(string hostName, int port, string user, string passwd, string send1QueueName, string send2QueueName, MessageCache recv1Msg, MessageCache recv2Msg) :
    hostName_(hostName),
    port_(port),
    user_(user),
    passwd_(passwd),
    send1QueueName_(send1QueueName),
    send2QueueName_(send2QueueName),
    recv1Msg_(recv1Msg),
    recv2Msg_(recv2Msg)
  {

  }

  int init();

  void run();
  struct timeval tval_;

  amqp_connection_state_t recv1Connection_;
  amqp_connection_state_t recv2Connection_;

  amqp_connection_state_t send1Connection_;
  amqp_connection_state_t send2Connection_;

  int recvQueue1();
  int recvQueue2();


  int handleQueue1(void *body, unsigned int len);
  int handleQueue2(void *body, unsigned int len);

  int sendMsg1(const char *msg);
  int sendMsg2(const char *msg);

private:
  MessageCache recv1Msg_;
  MessageCache recv2Msg_;

  string send1QueueName_;
  string send2QueueName_;

  string recv1QueueName_;
  string recv2QueueName_;

  amqp_socket_t *socket_;
  amqp_basic_properties_t props_;

  int64_t  lastRecvTime_;
  int64_t  lastSendTime_;

  string hostName_;
  int port_;
  string user_;
  string passwd_;
  string exchange_ = "amq.direct";
  string bindingkey1_ = "send1";
  string bindingkey2_ = "send2";
};
#endif // !__RABBITMA_H__



