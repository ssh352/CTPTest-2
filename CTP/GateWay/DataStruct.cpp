#include "DataStruct.h"

int char2int(const char **ps)
{
  int n = 0;
  for (; **ps && **ps >= '0' && **ps <= '9'; ++*ps)
    n = n * 10 + **ps - '0';
  return n;
}







