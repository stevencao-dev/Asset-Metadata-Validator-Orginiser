#pragma once
#include <string>
#include "Validator.h"
class FileProcessor
{
public:
	FileProcessor() {};
	~FileProcessor() {};

	void PrintDirectoryContents(const std::string& directoryPath);
	void ExportToCSV(const std::string& directoryPath, std::string& exportCSVPath);
	void CompareWithCSV(const std::string& directoryPath, const std::string& csvPath);

private:

	std::string ResolvePathExtension(std::string& path);
};

