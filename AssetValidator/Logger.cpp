#include "Logger.h"
#include <iostream>

void Logger::Info(const std::string& message)
{
	std::cout << "\033[32m[INFO]:\033[0m " << message << std::endl;
}

void Logger::Error(const std::string& message)
{
	std::cout << "\033[31m[ERROR]:\033[0m " << message << std::endl;
}

void Logger::Warning(const std::string& message)
{
	std::cout << "\033[33m[WARNING]:\033[0m " << message << std::endl;
}

void Logger::Debug(const std::string& message)
{
	std::cout << "\033[36m[DEBUG]:\033[0m " << message << std::endl;
}
