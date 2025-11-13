#include "Validator.h"

#include <filesystem>
#include <iostream>

#include "Logger.h"

bool Validator::ValidatePath(const std::string& assetPath)
{
	namespace fs = std::filesystem;
	if (assetPath.empty())
	{
		Logger::Error("Asset path is empty.");
		return false;
	}
	// Not as clean however since this current version of the project is a CLI verison. This would handle arbitary user inputs and edge cases aswell as permission issues
	try
	{
		fs::path path(assetPath);
		if (fs::exists(path))
		{
			Logger::Info("Asset path is valid: " + path.string());
			return true;

		}
		else
		{
			Logger::Error("Asset path does not exist: " + path.string());
			return false;
		}
	}
	catch (const std::exception& e)
	{
		Logger::Error(std::string("Exception occurred while validating the path: ") + e.what());
		return false;
	}
}
