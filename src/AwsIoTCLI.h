#pragma once

#include <string>

class AwsIoTCLI {
public:
    AwsIoTCLI(const std::string& workingDirectory);

    void createThing(const std::string& thingName);
    void listThings();

private:
    std::string workingDirectory;

    void setWorkingDirectory();
    void executeCommand(const std::string& command, bool printOutput = true);
    void readResponseFile(const std::string& responseFilePath, std::string& certificateArn, std::string& certificateId);
    std::string extractValue(const std::string& jsonString, const std::string& key);
};
