#include "FileProcessor.h"
#include <fstream>
#include <filesystem>
#include <iostream>

#include "Logger.h"

void FileProcessor::ReadFile(const std::string& filePath)
{
	std::ifstream file(filePath);
	if (!file.is_open())
	{
		std::cerr << "Failed to open file: " << filePath << std::endl;
		return;
	}
}

void FileProcessor::PrintDirectoryContents(const std::string& directoryPath)
{
	if (!m_Validator.ValidatePath(directoryPath))
	{
		// logging already exists in ValidatePath
		return;
	}
	std::string fileName;
	for (const auto& entry :std::filesystem::recursive_directory_iterator(directoryPath))
	{
		if (entry.is_regular_file())
		{
			fileName = entry.path().filename().string();
			Logger::Info(fileName);
		}
	}
}
