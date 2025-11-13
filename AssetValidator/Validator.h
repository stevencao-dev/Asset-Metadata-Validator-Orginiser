#pragma once
#include <string>
class Validator
{
public:
	Validator() {};
	~Validator() {};

	bool ValidatePath(const std::string& assetPath);

};

