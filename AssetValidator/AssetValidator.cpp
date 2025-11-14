// AssetValidator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Logger.h"
#include "FileProcessor.h"
#include "Validator.h"

void pause()
{
	std::cout << "Press Enter to return to menu...";
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int main()
{
	// Construct Validator explicitly to avoid most-vexing-parse
	Validator validator;
	FileProcessor fileProcessor(validator);
	while (true) {
		system("cls");

		std::cout << "\n=== Asset Tool Menu ===\n";
		std::cout << "1. Validate a path\n";
		std::cout << "2. List files in directory\n";
		std::cout << "3. Exit\n";
		std::cout << "Choose an option: ";

		std::string input;
		std::getline(std::cin, input);
		int choice = std::stoi(input);

		switch (choice)
		{
		case 1:
		{
			system("cls");
			std::cout << "Enter the asset path to validate: " << std::endl;
			std::string assetPath;
			std::getline(std::cin, assetPath);
			validator.ValidatePath(assetPath);
			pause();
			break;
		}
		case 2:
		{
			system("cls");
			std::cout << "Enter the directory path to display: " << std::endl;
			std::string assetPath;
			std::getline(std::cin, assetPath);
			fileProcessor.PrintDirectoryContents(assetPath);
			pause();
			break;
		}
		case 3:
		{
			pause();
			break;
		}
		case 4:
		{
			std::cout << "Exit Application" << std::endl;
			return 0;
		}
		default:
			std::cout << "Invalid choice. Please try again.\n";
			continue;
		}
	}
	return 0;
}


