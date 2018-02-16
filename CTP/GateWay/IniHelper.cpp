#include "IniHelper.h"
#include <assert.h>
#include <stdio.h>
#include <algorithm>


IniItem::IniItem(char *name, char *value)
{
  assert(strlen(name) < 30);
  assert(strlen(value) < 255);
  memcpy(name_, name, sizeof(name_) - 1);
  memcpy(value_, value, sizeof(value_) - 1);
}

IniItem::~IniItem(void)
{
}

char *IniItem::getName(void)
{
  return name_;
}

char *IniItem::getValue(void)
{
  return value_;
}

IniHelper::IniHelper(const char *filePath)
{
  FILE *iniFile;
  char *pLast = NULL;

  const int BUF_SIZE = 1024;
  char buffer[BUF_SIZE];

  iniFile = fopen(filePath, "rt");

  if (iniFile == NULL)
  {
    return;
  }

  while (fgets(buffer, BUF_SIZE, iniFile) != NULL)
  {
    char *name, *value;
    if (strtok_s(buffer, "\n\r", &pLast) == NULL)
      continue;
    if (buffer[0] == '#')
      continue;
    name = strtok_s(buffer, "\n\r=", &pLast);
    value = strtok_s(NULL, "\n\r", &pLast);
    if (name == NULL)
    {
      continue;
    }
    items_.push_back(std::shared_ptr<IniItem>(new  IniItem(name, value)));
  }
  fclose(iniFile);
}

char *IniHelper::getItem(const char *name)
{
  ItemVec::iterator it = std::find_if(items_.begin(), items_.end(), is_equal(name));
  if (it != items_.end())
  {
    return (*it)->getValue();
  }
  return nullptr;
}


IniHelper::~IniHelper()
{
}
