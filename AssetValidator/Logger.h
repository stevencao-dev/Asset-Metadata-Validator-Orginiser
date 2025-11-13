#pragma once
#include <string>
#include <optional>

class Logger
{
public:
	static void Info(const std::string& message);
	static void Error(const std::string& message);
	static void Debug(const std::string& message);
};

