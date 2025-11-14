#include "Validator.h"

#include <filesystem>
#include <iostream>

#include "Logger.h"

std::optional<std::filesystem::path> Validator::ValidatePath(const std::string& assetPath)
{
	namespace fs = std::filesystem;
	if (assetPath.empty())
	{
		Logger::Error("Asset path is empty.");
		return std::nullopt;
	}
	// Handles edge case with Windows Copy as Path
	std::string pathStr(assetPath);
	if (pathStr.front() == '"' && pathStr.back() == '"')
		pathStr = pathStr.substr(1, pathStr.size() - 2);

	// Not as clean however since this current version of the project is a CLI verison. This would handle arbitary user inputs and edge cases aswell as permission issues
	try
	{
		fs::path path = fs::absolute(pathStr);
		if (fs::exists(path))
		{
			Logger::Info("Asset path is valid: " + path.string());
			return path;
		}
		else
		{
			Logger::Error("Asset path does not exist: " + path.string());
			return std::nullopt;
		}
	}
	catch (const std::exception& e)
	{
		Logger::Error(std::string("Exception occurred while validating the path: ") + e.what());
		return std::nullopt;
	}
}
