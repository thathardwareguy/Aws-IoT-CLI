# AWS IoT CLI

This is a simple Command Line Interface (CLI) for managing things using AWS IoT. It allows you to create things, list things, and perform other operations related to AWS IoT.

## Prerequisites

Before you begin, make sure you have the following installed on your system:

- [CMake](https://cmake.org/download/) (minimum version 3.5)
- [Ninja](https://ninja-build.org/) (or any other build system supported by CMake)
- C++ compiler with C++11 support

## Building and Running

Follow these steps to build and run the AWS IoT CLI:

1. **Clone the Repository:**

    ```bash
    git clone https://github.com/yourusername/awsiotcli.git
    cd awsiotcli
    ```

2. **Create a Build Directory:**

    ```bash
    mkdir build
    cd build
    ```

3. **Generate Build Files:**

    ```bash
    cmake -G Ninja ..
    ```

4. **Compile using Ninja:**

    ```bash
    ninja
    ```

5. **Run the AWS IoT CLI:**

    ```bash
    ./awsiotcli
    ```

### Running on Windows

If you are on Windows, you can run the AWS IoT CLI using one of the following methods:

- **Bash on Windows (WSL):**
    - Install [Windows Subsystem for Linux (WSL)](https://docs.microsoft.com/en-us/windows/wsl/install)
    - Launch your preferred Linux distribution from the Start menu
    - Follow the Linux instructions above

- **Ubuntu for Windows:**
    - Install [Ubuntu for Windows](https://ubuntu.com/tutorials/ubuntu-on-windows#1-overview)
    - Launch Ubuntu from the Start menu
    - Follow the Linux instructions above

## Usage

Once the CLI is running, you will see a menu with options to perform various operations related to AWS IoT. Follow the on-screen prompts to interact with the CLI.

## Contributing

If you'd like to contribute to this project, feel free to fork the repository and create a pull request.

## License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.
