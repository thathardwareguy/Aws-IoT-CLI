#pragma once

#include <string>
#include <vector>

class AwsIoTCLI {
public:
    AwsIoTCLI(const std::string& workingDirectory);

    void createThing(const std::string& thingName, const std::string& policyName);
    void listThings();
    void createMultipleThings(const std::vector<std::string>& thingNames, const std::string& policyName);

    std::vector<std::string> readDeviceNamesFromJson(const std::string& jsonFileName);

private:
    std::string workingDirectory;

    void setWorkingDirectory();
    void executeCommand(const std::string& command, bool printOutput = true);
    void readResponseFile(const std::string& responseFilePath, std::string& certificateArn, std::string& certificateId);
    std::string extractValue(const std::string& jsonString, const std::string& key);
};
