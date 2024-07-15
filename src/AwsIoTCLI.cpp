#include "AwsIoTCLI.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <unistd.h>
#include   "json.hpp" // Include a JSON library like nlohmann/json for handling JSON

using json = nlohmann::json;

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

    certificateArn = extractValue(response, "certificateArn");
    certificateId = extractValue(response, "certificateId");
}

std::string AwsIoTCLI::extractValue(const std::string& jsonString, const std::string& key) {
    std::size_t keyPos = jsonString.find("\"" + key + "\"");
    if (keyPos != std::string::npos) {
        std::size_t valueStart = jsonString.find("\"", keyPos + key.length() + 2);
        std::size_t valueEnd = jsonString.find("\"", valueStart + 1);
        return jsonString.substr(valueStart + 1, valueEnd - valueStart - 1);
    }
    return "";
}

void AwsIoTCLI::createThing(const std::string& thingName, const std::string& policyName) {
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
   /*
         std::string createPolicyCommand =
		"aws iot create-policy --policy-name " + policyName +
		" --policy-document file://policy.json";

    executeCommand(createPolicyCommand);
   */

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

void AwsIoTCLI::createMultipleThings(const std::vector<std::string>& thingNames, const std::string& policyName) {
    for (const auto& thingName : thingNames) {
        createThing(thingName, policyName);
    }
}

std::vector<std::string> AwsIoTCLI::readDeviceNamesFromJson(const std::string& jsonFileName) {
    std::ifstream jsonFile(workingDirectory + "/" + jsonFileName);
    if (!jsonFile.is_open()) {
        std::cerr << "Error opening JSON file.\n";
        std::exit(EXIT_FAILURE);
    }

    json jsonData;
    jsonFile >> jsonData;
    jsonFile.close();

    std::vector<std::string> deviceNames;
    for (const auto& item : jsonData) {
        deviceNames.push_back(item.at("device name"));
    }

    return deviceNames;
}