#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <string>
#include <vector>
#include <sqlite3.h>
#include <memory>
#include <string.h>

using namespace std;

#include "Utlis.h"
#include "LogMessage.h"

class Logger {
private:
  const string _appName;
  sqlite3 *_dbObject;

  int makeTable();

public:
  Logger(string appName);

  ~Logger();

  int Write(const string &message_text);

  shared_ptr<vector<LogMessage>> Read_All();
  bool CheckError(char **err);
  void CheckPreparation(int code, int status);
  bool CheckOK(int code);
};
#endif
