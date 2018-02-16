#ifndef __INIHELPER_H__
#define __INIHELPER_H__

#include <memory>
#include <vector>

class IniItem
{
public:
  IniItem(char *name, char *value);
  virtual ~IniItem(void);

  char *getName(void);
  char *getValue(void);

private:
  char name_[20];
  char value_[500];

};
class IniHelper
{
public:
  IniHelper(const char *iniFilename);
  virtual ~IniHelper(void);

  virtual char *getItem(const char *name);
private:
  typedef std::vector< std::shared_ptr<IniItem>> ItemVec;
  ItemVec items_;
};

class is_equal
{
public:
  is_equal(const char* name)
  {
    memset(name_, 0, sizeof(name_));
    memcpy(name_, name, sizeof(name_));
  }

  bool operator() (std::shared_ptr<IniItem> &item) const
  {
    if (strcmp(item->getName(), name_) == 0)
    {
      return true;
    }
    else
    {
      return false;
    }
  }

private:
  char name_[20];
};

#endif // !__READINI_H__
