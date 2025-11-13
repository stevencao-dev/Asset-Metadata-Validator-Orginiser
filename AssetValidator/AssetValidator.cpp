// AssetValidator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Logger.h"
#include "FileProcessor.h"
#include "Validator.h"

int main()
{
	std::cout << "Enter the asset path to validate: " << std::endl;
	std::string assetPath;
	std::getline(std::cin, assetPath);

	// Construct Validator explicitly to avoid most-vexing-parse
	Validator validator;
	FileProcessor fileProcessor(validator);

	fileProcessor.PrintDirectoryContents(assetPath);

	return 0;
}


