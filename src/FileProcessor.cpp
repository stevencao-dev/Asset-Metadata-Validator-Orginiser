#include "FileProcessor.h"
#include <fstream>
#include <sstream>
#include <filesystem>
#include <iostream>
#include <chrono>
#include <unordered_set>
#include "Logger.h"

void FileProcessor::PrintDirectoryContents(const std::string& directoryPath)
{
	auto dir = Validator::ValidatePath(directoryPath);
	if (!dir) return;

	// Declaring in the loop is fine too as modern compilers optimize it well. Only tiny optimisation gains here.
	std::string fileName;
	for (const auto& entry :std::filesystem::recursive_directory_iterator(*dir))
	{
		if (entry.is_regular_file())
		{
			fileName = entry.path().filename().string();
			Logger::Info(fileName);
		}
	}
}

void FileProcessor::ExportToCSV(const std::string& directoryPath, std::string& exportCSVPath)
{
	if (!Validator::ValidatePath(directoryPath))
	{
		// logging already exists in ValidatePath
		return;
	}
	
	namespace fs = std::filesystem;
	exportCSVPath = ResolvePathExtension(exportCSVPath);
	std::ofstream csvFile(exportCSVPath);

	if (!csvFile.is_open())
	{
		Logger::Error("Failed to open CSV file for writing: " + exportCSVPath);
		return;
	}

	// If I was to expand this project out, this would be moved to a config file under "CSV headers"
	csvFile << "\"File Name\",\"Path\",\"File Size (bytes)\",\"Last Changed\",\"Extension\"\n";

	try 
	{
		for(const auto& entry : fs::recursive_directory_iterator(directoryPath))
		{
			if (entry.is_regular_file())
			{
				auto cftime = std::chrono::clock_cast<std::chrono::system_clock>(
					fs::last_write_time(entry)
				);
				auto roundedTime = std::chrono::floor<std::chrono::seconds>(cftime);
				csvFile << "\"" << entry.path().filename().string() << "\","
					<< "\"" << entry.path().string() << "\","
					<< "\"" << entry.file_size() << "\","
					<< "\"" << std::format("{:%d-%m-%Y %H:%M:%S}", roundedTime) << "\","
					<< "\"" << entry.path().extension().string() << "\"\n";
			}
		}
		Logger::Info("CSV export successful: ");
	}
	catch (std::exception& e)
	{
		Logger::Error(std::string("Exception occurred while exporting to CSV: ") + e.what());
		return;
	}
	
}

void FileProcessor::CompareWithCSV(const std::string& directoryPath, const std::string& csvPath)
{
	auto dir = Validator::ValidatePath(directoryPath);
	if (!dir) return;

	auto csv = Validator::ValidatePath(csvPath);
	if(!csv) return;
	
	std::ifstream csvFile(*csv);
	if (!csvFile.is_open())
	{
		Logger::Error("Failed to open CSV file for reading: " + csvPath);
		return;
	}
	std::unordered_set <std::string> csvEntries;
	std::string line;
	if(!std::getline(csvFile, line))
	{ 
		return;
	}
	// Read each line
	while (std::getline(csvFile, line))
	{
		std::stringstream ss(line);
		std::string cell;

		// Get the first cell (column)
		if (std::getline(ss, cell, ','))
		{
			// Remove quotes if present
			if (!cell.empty() && cell.front() == '"' && cell.back() == '"')
				cell = cell.substr(1, cell.size() - 2);

			csvEntries.insert(cell);
		}
	}

	std::unordered_set <std::string> fileNamesInDirectory;
	try 
	{
		for (const auto& entry : std::filesystem::recursive_directory_iterator(*dir))
		{
			if (entry.is_regular_file())
			{
				fileNamesInDirectory.insert(entry.path().filename().string());
			}
		}
	}
	catch (std::exception& e)
	{
		Logger::Error(std::string("Exception occurred while reading directory: ") + e.what());
		return;
	}

	// Compare CSV entries with directory files - O(n + m) complexity
	for (const auto& csvFileName : csvEntries)
	{
		if (fileNamesInDirectory.find(csvFileName) == fileNamesInDirectory.end())
		{
			Logger::Info("Missing from Directory: " + csvFileName);
		}
	}
	for (const auto& dirFileName : fileNamesInDirectory)
	{
		if (csvEntries.find(dirFileName) == csvEntries.end())
		{
			Logger::Info("Missing from CSV: " + dirFileName);
		}
	}
}

std::string FileProcessor::ResolvePathExtension(std::string& path)
{
	using namespace std::chrono; 
	namespace fs = std::filesystem;

	auto now = system_clock::now();
	auto localtime = zoned_time(current_zone(), now);
	std::string timestamp = std::format("{:%d-%m-%Y_%H-%M-%S}", localtime);

	fs::path directory(path);
	fs::path fileName = "export_" + timestamp + ".csv";
	fs::path fullPath = directory.empty() ? fileName : directory / fileName;

	if (!directory.empty())
		fs::create_directories(directory);

	if (directory.empty())
		Logger::Warning("Export CSV path is empty. CSV will be stored in Working Directory");
	
	return fullPath.string();
}

