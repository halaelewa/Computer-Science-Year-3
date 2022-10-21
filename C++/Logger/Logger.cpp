#include "Logger.h"

using namespace std;

const char *PATH{"./Database.db"};

/*
the logger constructor
here the logger is constructed

@param appName :string The name of the app that is using the Logger class to
log messages.
*/
Logger::Logger(string appName) : _appName{appName} {

  if (!CheckOK(sqlite3_open(PATH, &_dbObject))) {
    cout << "Connection successfully opened. Table: " + appName + '\n';
  }
  if (makeTable() == -1) {
    throw "Error, cannot establish a connection with the database.";
  }
}

/*
Logger Destructor
To End the Database Connection safely
*/
Logger::~Logger() {
  sqlite3_close(_dbObject);
  cout << "Connection successfully closed.\n";
}

/*
Logger::Write
Writing messages to The Database Logs Table
@param message_text : const string& The message to be written.
*/
int Logger::Write(const string &message_text) {
  string timestamp = TimeNow();
  string query = "INSERT INTO " + _appName + " VALUES " + "(\"" + timestamp +
                 "\", \"" + message_text + "\");";
  char **error = nullptr;
  sqlite3_exec(_dbObject, query.data(), nullptr, nullptr, error);
  if (CheckError(error)) {
    return -1;
  }
  return 0;
}

/*
Logger::ReadAll
returns a list for all the messages that stored in the database
@return shared_ptr<vector<LogMessage>>: represents the log messages vector from the database.
*/
shared_ptr<vector<LogMessage>> Logger::Read_All() {
  string sqlQuery = "SELECT * from " + _appName;
  sqlite3_stmt *queryObject;
  CheckPreparation(sqlite3_prepare_v2(_dbObject, sqlQuery.data(),
                                      sqlQuery.length() + 1, &queryObject,
                                      nullptr),
                   0);
  int steps = sqlite3_step(queryObject);
  auto logs = make_shared<vector<LogMessage>>();
  while (steps != SQLITE_DONE) {
    CheckPreparation(steps, 1);
    string timestamp = (const char *)sqlite3_column_text(queryObject, 0);
    string message = (const char *)sqlite3_column_text(queryObject, 1);
    logs->push_back(LogMessage{message, timestamp});
    steps = sqlite3_step(queryObject);
  }
  sqlite3_finalize(queryObject);
  return logs;
}

/*
private Logger::makeTable
Creates a table in the database.

@return int : 0 if successful, -1 otherwise
*/
int Logger::makeTable() {
  string tableStatus =
      "CREATE TABLE IF NOT EXISTS " + _appName+
      "(Timestamp varchar(255) NOT NULL, Message varchar(255) NOT NULL);";
  char **error = nullptr;
  sqlite3_exec(_dbObject, tableStatus.data(), nullptr, 0, error);
  if (CheckError(error)) {
    return -1;
  }
  return 0;
}

bool Logger::CheckError(char **err) {
  if (err) {
    cerr << "DB ERROR..." << err << endl;
    sqlite3_free(err);
    err = nullptr;
    return true;
  }
  return false;
}

void Logger::CheckPreparation(int code, int status) {
  if (status == 0) {
    if (SQLITE_OK != code) {
      throw "Failed to Make SQL statement.";
    }
  } else {
    if (SQLITE_ERROR == code || SQLITE_MISUSE == code) {
      throw "Error code: " + code;
    }
  }

  return;
}

bool Logger::CheckOK(int code) {
  if (SQLITE_OK != code) {
    throw "Database could not be opened.";
  }
  return false;
}