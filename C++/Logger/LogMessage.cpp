#include "LogMessage.h"

using namespace std;

LogMessage::LogMessage(string message, string timestamp)
    : _message_text{message}, _timestamp_text{timestamp} {}

LogMessage::~LogMessage() {}
/*
GetMessage
Get The Message from the database

*/
string LogMessage::GetMessage() { return _message_text; }
/*
GetTimestamp
Get The Timestamp from the database

*/
string LogMessage::GetTimestamp() { return _timestamp_text; }