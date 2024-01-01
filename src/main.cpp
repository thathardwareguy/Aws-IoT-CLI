#include "AwsIoTCLI.h"
#include <iostream>

int main() {
    std::string workingDirectory;
    std::cout << "Welcome to AWS IoT CLI v1.0.0!\n";
    std::cout << "Enter the absolute path of the working directory: ";
    std::getline(std::cin, workingDirectory);

    AwsIoTCLI awsIoTCLI(workingDirectory);

    while (true) {
        std::cout << "AWS IoT CLI Menu:\n";
		std::cout << "1. Create Thing\n";
		std::cout << "2. List Things\n";
		std::cout << "3. Describe Thing Group\n";
		std::cout << "4. Create Thing Group\n";
		std::cout << "5. Attach Thing Principal\n";
		std::cout << "6. Describe Thing\n";
		std::cout << "7. Delete Thing\n";
		std::cout << "8. List Policies\n";
		std::cout << "9. Create Thing Type\n";
		std::cout << "10. Update Thing\n";
		std::cout << "11. Exit\n";
		std::cout << "Enter your choice (1-11): ";

        int choice;
        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1:
                {
                    std::string thingName;
                    std::cout << "Enter the name of the thing to be created: ";
                    std::getline(std::cin, thingName);
                    awsIoTCLI.createThing(thingName);
                }
                break;
            case 2:
                awsIoTCLI.listThings();
                break;
            case 3:
                std::cout << "Exiting program.\n";
                return 0;
            default:
                std::cerr << "Invalid choice. Please enter a number between 1 and 11.\n";
        }
    }

    return 0;
}
