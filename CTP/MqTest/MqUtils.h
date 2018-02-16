#ifndef __MQUTILS_H__
#define __MQUTILS_H__
#include <amqp_tcp_socket.h>
#include <amqp.h>
#include <amqp_framing.h>


void die(const char *fmt, ...);
extern void die_on_error(int x, char const *context);
extern bool die_on_amqp_error(amqp_rpc_reply_t x, char const *context);
extern void amqp_dump(void const *buffer, size_t len);


#endif
