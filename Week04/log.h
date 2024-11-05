#pragma once
#include <iostream>
#include <vector>

//enum , Enumeration
enum LogType {
	LOG_DEFAULT, //0
	LOG_WARNING, //1
	LOG_ERROR    //2
};

struct LogEntry {
	LogType Type;
	std::string Message;
};


class Log {
public:
	static std::vector<LogEntry> LogEntries;
	static void LogMessage(LogType Type, std::string Message);
	static void PrintLog(LogEntry& Entry);
};