#include <iostream>
#include <string>
#include <string.h>
#include <vector>
#include <memory>
#include <unistd.h>
#include "Logger.h"

using namespace std;

int main(int argc, char *argv[]) {
  string appName = argv[0];
  Logger log = Logger(appName.substr(2, appName.length()));

  for (int i = 1; i < argc; i++) {
    cout << "Writing Message" << endl;
    log.Write(argv[i]);
    sleep(3);
  }

  return 0;
}