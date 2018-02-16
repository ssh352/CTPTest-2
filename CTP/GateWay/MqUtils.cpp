#include <stdarg.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

#include <stdint.h>
#include <amqp.h>
#include <amqp_framing.h>

#include "MqUtils.h"

void die(const char *fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  vfprintf(stderr, fmt, ap);
  va_end(ap);
  fprintf(stderr, "\n");
  exit(1);
}

void die_on_error(int x, char const *context)
{
  if (x < 0) {
    fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x));
    exit(1);
  }
}

bool die_on_amqp_error(amqp_rpc_reply_t x, char const *context)
{
  switch (x.reply_type) {
  case AMQP_RESPONSE_NORMAL:
    return true;

  case AMQP_RESPONSE_NONE:
    fprintf(stderr, "%s: missing RPC reply type!\n", context);
    break;

  case AMQP_RESPONSE_LIBRARY_EXCEPTION:
    fprintf(stderr, "%s: %s\n", context, amqp_error_string2(x.library_error));
    break;

  case AMQP_RESPONSE_SERVER_EXCEPTION:
    switch (x.reply.id) {
    case AMQP_CONNECTION_CLOSE_METHOD: {
      amqp_connection_close_t *m = (amqp_connection_close_t *)x.reply.decoded;
      fprintf(stderr, "%s: server connection error %uh, message: %.*s\n",
        context,
        m->reply_code,
        (int)m->reply_text.len, (char *)m->reply_text.bytes);
      break;
    }
    case AMQP_CHANNEL_CLOSE_METHOD: {
      amqp_channel_close_t *m = (amqp_channel_close_t *)x.reply.decoded;
      fprintf(stderr, "%s: server channel error %uh, message: %.*s\n",
        context,
        m->reply_code,
        (int)m->reply_text.len, (char *)m->reply_text.bytes);
      break;
    }
    default:
      fprintf(stderr, "%s: unknown server error, method id 0x%08X\n", context, x.reply.id);
      break;
    }
    break;
  }

  exit(1);
}

static void dump_row(long count, int numinrow, int *chs)
{
  int i;

  printf("%08lX:", count - numinrow);

  if (numinrow > 0) {
    for (i = 0; i < numinrow; i++) {
      if (i == 8) {
        printf(" :");
      }
      printf(" %02X", chs[i]);
    }
    for (i = numinrow; i < 16; i++) {
      if (i == 8) {
        printf(" :");
      }
      printf("   ");
    }
    printf("  ");
    for (i = 0; i < numinrow; i++) {
      if (isprint(chs[i])) {
        printf("%c", chs[i]);
      }
      else {
        printf(".");
      }
    }
  }
  printf("\n");
}

static int rows_eq(int *a, int *b)
{
  int i;

  for (i = 0; i < 16; i++)
    if (a[i] != b[i]) {
      return 0;
    }

  return 1;
}

void amqp_dump(void const *buffer, size_t len)
{
  unsigned char *buf = (unsigned char *)buffer;
  long count = 0;
  int numinrow = 0;
  int chs[16];
  int oldchs[16] = { 0 };
  int showed_dots = 0;
  size_t i;

  for (i = 0; i < len; i++) {
    int ch = buf[i];

    if (numinrow == 16) {
      int j;

      if (rows_eq(oldchs, chs)) {
        if (!showed_dots) {
          showed_dots = 1;
          printf("          .. .. .. .. .. .. .. .. : .. .. .. .. .. .. .. ..\n");
        }
      }
      else {
        showed_dots = 0;
        dump_row(count, numinrow, chs);
      }

      for (j = 0; j < 16; j++) {
        oldchs[j] = chs[j];
      }

      numinrow = 0;
    }

    count++;
    chs[numinrow++] = ch;
  }

  dump_row(count, numinrow, chs);

  if (numinrow != 0) {
    printf("%08lX:\n", count);
  }
}

//uint64_t now_microseconds(void)
//{
//  FILETIME ft;
//  GetSystemTimeAsFileTime(&ft);
//  return (((uint64_t)ft.dwHighDateTime << 32) | (uint64_t)ft.dwLowDateTime)
//    / 10;
//}
//
//void microsleep(int usec)
//{
//  Sleep(usec / 1000);
//}

int init_rabbitmq(amqp_connection_state_t &conn, string hostname, int port, string user, string passwd)
{
  conn = amqp_new_connection();
  amqp_socket_t *socket = amqp_tcp_socket_new(conn);
  if (!socket) {
    fprintf(stderr, "amqp_tcp_socket_new error");
    //LOG_ERROR << "RabbitMqConsumer amqp_tcp_socket_new error";
    return -1;
  }

  int status = amqp_socket_open(socket, hostname.c_str(), port);
  if (status) {
    fprintf(stderr, "amqp_socket_open error [%s] [%d]", hostname.c_str(), port);
    //LOG_ERROR << "RabbitMqConsumer opening TCP socket error";
    return -1;
  }
  amqp_rpc_reply_t tmp = amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, "guest", "guest");
  int res = die_on_amqp_error(tmp, "Logging in");//user.c_str(), passwd.c_str()), "Logging in");
  if (!res)
  {
    fprintf(stderr, "amqp_login error [%s]", user.c_str());
    return -1;
  }
  amqp_channel_open(conn, 1);
  res = die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");
  if (!res)
  {
    fprintf(stderr, "amqp_channel_open error ");
    return -1;
  }
  return 0;
}

int init_consumer(amqp_connection_state_t & conn, std::string hostname, int port, std::string user, std::string passwd, std::string queuename, std::string exchange, std::string bindingkey)
{
  conn = amqp_new_connection();
  amqp_socket_t *socket = amqp_tcp_socket_new(conn);
  if (!socket) {
    fprintf(stderr, "amqp_tcp_socket_new error");
    //LOG_ERROR << "RabbitMqConsumer amqp_tcp_socket_new error";
    return -1;
  }

  int status = amqp_socket_open(socket, hostname.c_str(), port);
  if (status) {
    fprintf(stderr, "amqp_socket_open error [%s] [%d]", hostname.c_str(), port);
    //LOG_ERROR << "RabbitMqConsumer opening TCP socket error";
    return -1;
  }
  amqp_rpc_reply_t tmp = amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, user.c_str(), passwd.c_str());
  int res = die_on_amqp_error(tmp, "Logging in");
  if (!res)
  {
    fprintf(stderr, "amqp_login error [%s]", user.c_str());

    return -1;
  }

  amqp_channel_open(conn, 1);
  res = die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");
  if (!res)
  {
    fprintf(stderr, "amqp_channel_open error ");
    return -1;
  }

  {
    amqp_queue_declare_ok_t *r = amqp_queue_declare(conn, 1, amqp_cstring_bytes(queuename.c_str()), 0, 0, 0, 1,
      amqp_empty_table);
    res = die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring queue");
    if (!res) {
      fprintf(stderr, "amqp_queue_declare error [%s]", queuename.c_str());
      return -1;
    }
  }

  amqp_queue_bind(conn, 1, amqp_cstring_bytes(queuename.c_str()), amqp_cstring_bytes(exchange.c_str()), amqp_cstring_bytes(bindingkey.c_str()), amqp_empty_table);
  res = die_on_amqp_error(amqp_get_rpc_reply(conn), "Binding queue");
  if (!res)
  {
    fprintf(stderr, "amqp_queue_bind error ");
    return -1;
  }

  amqp_basic_consume(conn, 1, amqp_cstring_bytes(queuename.c_str()), amqp_empty_bytes, 0, 1, 0, amqp_empty_table);
  res = die_on_amqp_error(amqp_get_rpc_reply(conn), "Consuming");
  if (!res)
  {
    fprintf(stderr, "amqp_basic_consume error ");
    return -1;
  }

  return 0;
}

int init_publish(amqp_connection_state_t & conn, std::string hostname, int port, std::string user, std::string passwd)
{
  conn = amqp_new_connection();
  amqp_socket_t *socket = amqp_tcp_socket_new(conn);
  if (!socket) {
    fprintf(stderr, "amqp_tcp_socket_new error");
    //LOG_ERROR << "RabbitMqConsumer amqp_tcp_socket_new error";
    return -1;
  }

  int status = amqp_socket_open(socket, hostname.c_str(), port);
  if (status) {
    fprintf(stderr, "amqp_socket_open error [%s] [%d]", hostname.c_str(), port);
    //LOG_ERROR << "RabbitMqConsumer opening TCP socket error";
    return -1;
  }
  amqp_rpc_reply_t tmp = amqp_login(conn, "/", 0, 131072, 0, AMQP_SASL_METHOD_PLAIN, user.c_str(), passwd.c_str());
  int res = die_on_amqp_error(tmp, "Logging in");
  if (!res)
  {
    fprintf(stderr, "amqp_login error [%s]", user.c_str());

    return -1;
  }

  amqp_channel_open(conn, 1);
  res = die_on_amqp_error(amqp_get_rpc_reply(conn), "Opening channel");
  if (!res)
  {
    fprintf(stderr, "amqp_channel_open error ");
    return -1;
  }

  return 0;
}

int queue_declare(amqp_connection_state_t &conn, std::string queuename, bool purge)
{
  int res = 0;
  if (purge)
  {
    amqp_queue_purge(conn, 1, amqp_cstring_bytes(queuename.c_str()));
    res = die_on_amqp_error(amqp_get_rpc_reply(conn), "Clearing jet queue");
    if (res)
    {
      fprintf(stderr, "amqp_queue_purge error [%s]", queuename.c_str());
      return -1;
    }
  }

  amqp_queue_declare(conn, 1, amqp_cstring_bytes(queuename.c_str()), 0, 1, 0, 0, amqp_empty_table);
  res = die_on_amqp_error(amqp_get_rpc_reply(conn), "Declaring jet queue");
  if (res)
  {
    fprintf(stderr, "amqp_queue_declare error [%s]", queuename.c_str());
    return -1;
  }

  return 0;
}
