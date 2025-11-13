#pragma once
#include <string>
#include "Validator.h"
class FileProcessor
{
public:
	FileProcessor(Validator validator): m_Validator(validator) {};
	~FileProcessor() {};

	void ReadFile(const std::string& filePath);
	void PrintDirectoryContents(const std::string& directoryPath);

private:
	Validator& m_Validator;
};

