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
	FileProcessor fileProcessor;
	while (true) {
		system("cls");

		std::cout << "\n=== Asset Tool Menu ===\n";
		std::cout << "1. Validate a path\n";
		std::cout << "2. List files in directory\n";
		std::cout << "3. Export assets in directory into CSV\n";
		std::cout << "4. Compare directory with CSV\n";
		std::cout << "5. Exit\n";
		std::cout << "Choose an option: ";

		std::string input;
		std::getline(std::cin, input);
		if (input.empty()) continue;

		int choice = std::stoi(input);

		switch (choice)
		{
			system("cls");
		case 1:
		{
			std::cout << "Enter the asset path to validate: " << std::endl;
			std::string assetPath;
			std::getline(std::cin, assetPath);
			Validator::ValidatePath(assetPath);
			pause();
			break;
		}
		case 2:
		{
			std::cout << "Enter the directory path to display: " << std::endl;
			std::string dirPath;
			std::getline(std::cin, dirPath);
			fileProcessor.PrintDirectoryContents(dirPath);
			pause();
			break;
		}
		case 3:
		{
			std::cout << "Enter the directory path to export: " << std::endl;
			std::string dirPath;
			std::getline(std::cin, dirPath);
			std::cout << "Where do you want to save it: " << std::endl;
			std::string exportPath;
			std::getline(std::cin, exportPath);
			fileProcessor.ExportToCSV(dirPath, exportPath);
			pause();
			break;
		}
		case 4:
		{
			std::cout << "Enter the directory path to comapre: " << std::endl;
			std::string dirPath;
			std::getline(std::cin, dirPath);
			std::cout << "Enter CSV Path: " << std::endl;
			std::string csvPath;
			std::getline(std::cin, csvPath);
			fileProcessor.CompareWithCSV(dirPath, csvPath);
			pause();
			break;
		}
		case 5:
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


