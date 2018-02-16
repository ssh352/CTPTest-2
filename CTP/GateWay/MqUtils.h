#ifndef __MQUTILS_H__
#define __MQUTILS_H__
#include "DataStruct.h"
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>

void die(const char *fmt, ...);
extern void die_on_error(int x, char const *context);
extern bool die_on_amqp_error(amqp_rpc_reply_t x, char const *context);

extern void amqp_dump(void const *buffer, size_t len);

//extern uint64_t now_microseconds(void);
//extern void microsleep(int usec);

extern int init_rabbitmq(amqp_connection_state_t &conn, std::string hostname, int port, std::string user, std::string passwd);

extern int init_consumer(amqp_connection_state_t &conn, std::string hostname, int port, std::string user, std::string passwd, std::string queuename, std::string exchange, std::string bindingkey);
extern int init_publish(amqp_connection_state_t &conn, std::string hostname, int port, std::string user, std::string passwd);
#endif // !__MQUTILS_H__


