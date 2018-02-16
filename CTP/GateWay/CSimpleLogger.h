#ifndef __CSIMPLELOGGER_H__
#define __CSIMPLELOGGER_H__
#include <string>
using namespace std;
enum E_LogLevel { INFO, WARN, ERROR, OTHER };

class CSimpleLogger
{
public:
  CSimpleLogger();
  virtual ~CSimpleLogger();
public:

  static void WriteLog(E_LogLevel logLevel, const char * fmt, ...);

  static void Init(const char* fName, int fSize = 1024);

  static void EndLog();

  static CSimpleLogger* GetInstancePoint();


  string m_file_name;
  int m_file_size;

  char buffer[250];


  static CSimpleLogger *pLogger;

};
#endif // !__CSIMPLELOGGER_H__





