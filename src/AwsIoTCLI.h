
#pragma once

#include <string>

class AwsIoTCLI {
public:
    AwsIoTCLI(const std::string& workingDirectory);

    void createThing(const std::string& thingName);
    void listThings();

private:
    std::string workingDirectory;
    std::string responseFilePath;

    void setWorkingDirectory();
    void executeCommand(const std::string& command, bool printOutput = true);
    void readResponseFile(const std::string& responseFilePath, std::string& certificateArn, std::string& certificateId);
};
