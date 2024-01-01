
#include "AwsIoTCLI.h"
#include <iostream>
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <unistd.h>

AwsIoTCLI::AwsIoTCLI(const std::string& workingDirectory) : workingDirectory(workingDirectory) {}

void AwsIoTCLI::setWorkingDirectory() {
    if (chdir(workingDirectory.c_str()) != 0) {
        std::cerr << "Error setting working directory.\n";
        std::exit(EXIT_FAILURE);
    }
}

void AwsIoTCLI::executeCommand(const std::string& command, bool printOutput) {
    setWorkingDirectory();

    int result = std::system(command.c_str());

    if (result != 0) {
        std::cerr << "Error executing command: " << command << "\n";
        std::exit(EXIT_FAILURE);
    }
}

void AwsIoTCLI::readResponseFile(const std::string& responseFilePath, std::string& certificateArn, std::string& certificateId) {
    std::ifstream responseFile(responseFilePath);
    if (!responseFile.is_open()) {
        std::cerr << "Error reading certificate and keys response.\n";
        std::exit(EXIT_FAILURE);
    }

    std::stringstream responseStream;
    responseStream << responseFile.rdbuf();
    responseFile.close();

    std::string response = responseStream.str();

    std::istringstream iss(response);
    std::string line;

    while (std::getline(iss, line)) {
        size_t arnPos = line.find("certificateArn");
        if (arnPos != std::string::npos) {
            size_t start = line.find('"', arnPos);
            size_t end = line.rfind('"', arnPos);
            certificateArn = line.substr(start, end - start);

            // Check if the certificateArn starts with double quotes, remove them
            if (!certificateArn.empty() && certificateArn.front() == '"') {
                certificateArn = certificateArn.substr(1, certificateArn.size() - 1);
            }

            // Remove trailing comma, if present
            size_t lastCharPos = certificateArn.find_last_not_of(", \t\n\r\f\v");
            if (lastCharPos != std::string::npos) {
                certificateArn.erase(lastCharPos + 1);
            }
        } else if (line.find("certificateId") != std::string::npos) {
            size_t idPos = line.find('"');
            size_t start = idPos + 1;
            size_t end = line.rfind('"');
            certificateId = line.substr(start, end - start);

            // Check if the certificateId starts with double quotes, remove them
            if (!certificateId.empty() && certificateId.front() == '"') {
                certificateId = certificateId.substr(1, certificateId.size() - 1);
            }

            // Remove trailing comma, if present
            size_t lastCharPos = certificateId.find_last_not_of(", \t\n\r\f\v");
            if (lastCharPos != std::string::npos) {
                certificateId.erase(lastCharPos + 1);
            }
        }
    }
}


void AwsIoTCLI::createThing(const std::string& thingName) {
    std::string createThingCommand = "aws iot create-thing --thing-name " + thingName;
    executeCommand(createThingCommand);

    std::string createKeysCommand =
        "aws iot create-keys-and-certificate --set-as-active"
        " --public-key-outfile " + thingName + ".public.key"
        " --private-key-outfile " + thingName + ".private.key"
        " --certificate-pem-outfile " + thingName + ".certificate.pem > " + workingDirectory + "create_cert_and_keys_response";

    executeCommand(createKeysCommand);
    std::string certificateArn, certificateId;
    readResponseFile(workingDirectory + "create_cert_and_keys_response", certificateArn, certificateId);

    std::cout << "Certificate ARN: " << certificateArn << "\n";
    std::cout << "Certificate ID: " << certificateId << "\n";

    std::string policyName = thingName + "_Policy";
    std::string createPolicyCommand =
		"aws iot create-policy --policy-name " + policyName +
		" --policy-document file://policy.json";

    executeCommand(createPolicyCommand);

    std::string attachPolicyCommand =
        "aws iot attach-policy --policy-name " + policyName +
        " --target " + certificateArn;

    executeCommand(attachPolicyCommand);

    std::string attachThingCommand =
        "aws iot attach-thing-principal --thing-name " + thingName +
        " --principal " + certificateArn;

    executeCommand(attachThingCommand);

    std::cout << "Thing created successfully.\n";
}

void AwsIoTCLI::listThings() {
    std::string command = "aws iot list-things";
    executeCommand(command);
}