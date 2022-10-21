#ifndef LOGMESSAGE_H
#define LOGMESSAGE_H

#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <memory>

using namespace std;

class LogMessage {
private:
  const string _message_text;
  const string _timestamp_text;

public:
  LogMessage(string message_text, string timestamp_text);
  ~LogMessage();
  string GetMessage();
  string GetTimestamp();
};

#endif