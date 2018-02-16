#include "CSimpleLogger.h"
#include <stdarg.h>
#include <time.h>

CSimpleLogger *CSimpleLogger::pLogger = NULL;


CSimpleLogger::CSimpleLogger()
{

}

CSimpleLogger::~CSimpleLogger()
{

}

CSimpleLogger* CSimpleLogger::GetInstancePoint()
{
  if (pLogger == NULL)
  {
    pLogger = new CSimpleLogger();
  }
  return pLogger;
}

void CSimpleLogger::Init(const char* fName, int fSize)
{
  CSimpleLogger* p = GetInstancePoint();
  p->m_file_name = fName;
  p->m_file_size = fSize;

}


void CSimpleLogger::EndLog()
{

  //quit thread
  CSimpleLogger* p = GetInstancePoint();
  delete p;
  //dbgout("end log\n");
}

void CSimpleLogger::WriteLog(E_LogLevel logLevel, const char * fmt, ...)
{

  CSimpleLogger* p = GetInstancePoint();

  string str;
  //struct tm *ptm;
  time_t now = time(NULL);
  struct tm *ptm=localtime(&now);
  char buf[25];
  strftime(buf, 25, "%Y%m%d %X\t", ptm);

  if (logLevel == INFO)
  {
    str = str + "INFO\t" + buf;
  }
  else if (logLevel == WARN)
  {
    str = str + "WARN\t" + buf;
  }
  else if (logLevel = ERROR)
  {
    str = str + "ERROR\t" + buf;
  }


  int t = 0;
  va_list ap;
  va_start(ap, fmt);
  t = vsnprintf(p->buffer, 250, fmt, ap);
  va_end(ap);

  //write log
  FILE *pf;
  pf = fopen(p->m_file_name.c_str(), "a+");
  if (pf)
  {
    fprintf(pf, "%s\n", (str + p->buffer).c_str());
    fclose(pf);
  }
  struct stat st;
  if (stat(p->m_file_name.c_str(), &st) == 0)
  {
    if ((st.st_size) > p->m_file_size)
    {
      rename(p->m_file_name.c_str(), (p->m_file_name + ".bak").c_str());
    }

  }

}

