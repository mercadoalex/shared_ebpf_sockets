# eBPF Sockets Lab

## Overview
The eBPF Sockets Lab is a project designed to demonstrate the use of eBPF (Extended Berkeley Packet Filter) for socket filtering. This lab provides a hands-on experience in writing and loading eBPF programs that can filter network packets based on specific criteria. 

## Project Structure
The project consists of the following files:

- `src/main.c`: The entry point of the application that initializes and loads the eBPF program.
- `src/ebpf_program.c`: Contains the eBPF program code for packet filtering.
- `src/helpers.h`: Header file with utility functions and definitions for the eBPF program.
- `Makefile`: Build instructions for compiling the eBPF program and linking necessary libraries.
- `README.md`: Documentation for the project.
- `.gitignore`: Specifies files and directories to be ignored by Git.

## Prerequisites
To build and run this project, you need the following:
- A Linux environment with kernel support for eBPF.
- The LLVM and Clang toolchain installed.
- The `libbpf` library for loading eBPF programs.

## Setup Instructions
1. **Clone the repository:**
   ```
   git clone <repository-url>
   cd ebpf-sockets-lab
   ```

2. **Install dependencies:**
   Ensure you have the required tools installed. You can install them using your package manager. For example, on Ubuntu:
   ```
   sudo apt-get install clang llvm libelf-dev gcc make
   ```

3. **Build the project:**
   Run the following command in the project root directory:
   ```
   make
   ```

4. **Run the eBPF program:**
   After building, you can run the program using:
   ```
   sudo ./main
   ```

## Usage
Once the program is running, it will start filtering packets based on the criteria defined in the eBPF program. You can modify the filtering logic in `src/ebpf_program.c` to suit your needs.

## Contributing
Contributions are welcome! If you have suggestions or improvements, feel free to open an issue or submit a pull request.

## License
This project is licensed under the MIT License. See the LICENSE file for more details.

## Author
Alejandro Mercado Peña