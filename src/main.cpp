#include "AwsIoTCLI.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <limits>
#include   "json.hpp"
#include <fstream>

using json = nlohmann::json;

int main() {
    std::string workingDirectory;
    std::cout << "Welcome to AWS IoT CLI v1.1.0!\n";
    std::cout << "Enter the absolute path of the working directory: ";
    std::getline(std::cin, workingDirectory);

    AwsIoTCLI awsIoTCLI(workingDirectory);

    while (true) {
        std::cout << "AWS IoT CLI Menu:\n";
        std::cout << "(1) Create Thing\n";
        std::cout << "(2) List Things\n";
        std::cout << "(3) Create Multiple Things\n"; // New menu option
        std::cout << "(11) Exit\n";
        std::cout << "Enter your choice (1-11): ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter a number between 1 and 11.\n";
            continue;
        }

        std::cin.ignore();

        switch (choice) {
            case 1:
                {
                    std::string thingName;
                    std::cout << "Enter the name of the thing to be created: ";
                    std::getline(std::cin, thingName);
                    std::string policyName;
                    std::cout << "Enter the name of the policy JSON file: ";
                    std::getline(std::cin, policyName);
                    awsIoTCLI.createThing(thingName, policyName);
                }
                break;
            case 2:
                awsIoTCLI.listThings();
                break;
                    case 3:
                {
                    int numThings;
                    std::cout << "Enter the number of things to be created: ";
                    std::cin >> numThings;
                    std::cin.ignore();

                    std::string jsonFileName;
                    std::cout << "Enter the name of the JSON file containing the device names: ";
                    std::getline(std::cin, jsonFileName);

                    std::string policyName;
                    std::cout << "Enter the name of the policy JSON file: ";
                    std::getline(std::cin, policyName);

                    std::vector<std::string> thingNames = awsIoTCLI.readDeviceNamesFromJson(jsonFileName);
                    if (thingNames.size() < numThings) {
                        std::cerr << "Not enough device names in the JSON file.\n";
                        break;
                    }

                    awsIoTCLI.createMultipleThings({thingNames.begin(), thingNames.begin() + numThings}, policyName);
                }
                break;
            case 11:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cerr << "Invalid choice. Please enter a number between 1 and 11.\n";
        }

        std::this_thread::sleep_for(std::chrono::seconds(2));
    }

    return 0;
}