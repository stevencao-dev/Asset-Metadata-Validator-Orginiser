#pragma once
#include <string>
#include <filesystem>
class Validator
{
public:

	static std::optional<std::filesystem::path> ValidatePath(const std::string& assetPath);

};

