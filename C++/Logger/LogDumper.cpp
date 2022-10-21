#include <iostream>
#include <vector>
#include <string>
#include <string.h>
#include <memory>
#include "Logger.h"
using namespace std;

int main(int argc, char *argv[]) {
  string appName = argv[1];
  Logger log = Logger(appName);
  shared_ptr<vector<LogMessage>> logs = log.Read_All();

  for (int i = 0; i < logs.get()->size(); i++) {
    cout << logs.get()->at(i).GetTimestamp() << ": "
         << logs.get()->at(i).GetMessage() << endl;
  }

  return 0;
}