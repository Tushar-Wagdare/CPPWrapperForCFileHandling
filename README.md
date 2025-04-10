C Style File  Handling Wrapped In C++ Class

A C++ RAII (Resource Acquisition Is Initialization) wrapper class for standard C file I/O functions (`<cstdio>`). This project provides a safer and more object-oriented way to handle C-style `FILE*` resources in C++ applications.

The primary goal is to prevent resource leaks by automatically closing the file handle when the wrapper object goes out of scope, leveraging C++ destructors.

## Features

*   **RAII:** Automatic `fclose()` via destructor ensures files are closed even if exceptions occur.
*   **Object-Oriented Interface:** Provides methods like `open()`, `read()`, `write()`, `seek()`, etc., on a `File` object.
*   **Resource Safety:** Copy constructor/assignment and move constructor/assignment are deleted to prevent accidental mismanagement of the underlying `FILE*`.
*   **Comprehensive Function Wrapping:** Wraps most common `<cstdio>` functions, including:
    *   File Operations: `fopen`, `fclose`, `freopen`, `fflush`, `tmpfile`
    *   I/O: `fread`, `fwrite`, `fgetc`, `fputc`, `fgets`, `fputs`, `vfprintf`, `vfscanf`
    *   Positioning: `fseek`, `ftell`, `fgetpos`, `fsetpos`, `rewind`
    *   Error Handling: `feof`, `ferror`, `clearerr`
*   **Custom Exceptions:** Defines `error_opning_file` and `bad_file_discriptor` for specific error handling.
*   **Type-Safe Seeking:** Uses `enum class SeekOrigin` for clarity (`SeekOrigin::Set`, `SeekOrigin::Current`, `SeekOrigin::End`).

## Repository Structure

*   `C++_WRAPPER/`: Contains the core C++ wrapper code.
    *   `file.h`: Header file defining the `File` class.
    *   `use_file.cpp`: Example usage and test cases for the `File` class.
*   `C_STYLE/`: Contains various example C programs demonstrating raw `<cstdio>` usage (likely for reference or comparison).
*   `TestCasesOutput/`: Contains screenshots, presumably showing the output of the test cases in `use_file.cpp`.
  
## Test Case Outputs
Test Case 1-3 Output:
![alt text](TestCasesOutput/Screenshot%202025-04-08%20194247.png)

Test Case 4 Output:
![alt text](TestCasesOutput/Screenshot%202025-04-08%20194303.png)

Test Case 5 Output:
![alt text](TestCasesOutput/Screenshot%202025-04-08%20194324.png)




## Getting Started

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/Tushar-Wagdare/CPPWrapperForCFileHandling
    cd CPPWrapperForCFileHandling
    ```
2.  **Locate the code:** The main wrapper class `File` is defined in `C++_WRAPPER/file.h`.

## Usage

Include `file.h` in your C++ project. You can then create and use `File` objects. It's recommended to use stack allocation for automatic RAII benefits.

```cpp
#include "C++_WRAPPER/file.h" // Adjust path as needed
#include <iostream>
#include <stdexcept>
#include <vector>

int main() {
    try {
        // --- Example: Writing to a binary file ---
        std::cout << "Creating and writing to test.bin..." << std::endl;
        { // Inner scope for RAII demonstration
            File writer("test.bin", "wb"); // Create/truncate, binary write mode

            int data_out[] = { 1, 2, 3, 4, 5 };
            size_t count = sizeof(data_out) / sizeof(data_out[0]);

            size_t written = writer.write(data_out, sizeof(int), count);
            if (written != count) {
                std::cerr << "Warning: Could not write all items!" << std::endl;
                // Check writer.is_error() for more details if needed
            } else {
                std::cout << "Successfully wrote " << written << " integers." << std::endl;
            }
            // writer goes out of scope here, ~File() is called, closing the file.
        } // File is guaranteed to be closed here

        // --- Example: Reading from the binary file ---
        std::cout << "\nReading from test.bin..." << std::endl;
        {
            File reader("test.bin", "rb"); // Read-only, binary mode
            std::vector<int> data_in(5);

            size_t read_count = reader.read(data_in.data(), sizeof(int), data_in.size());
            std::cout << "Successfully read " << read_count << " integers: ";
            for (size_t i = 0; i < read_count; ++i) {
                std::cout << data_in[i] << " ";
            }
            std::cout << std::endl;
            // Check reader.eof() if read_count < data_in.size()
        } // File is guaranteed to be closed here

    } catch (const error_opning_file& e) {
        std::cerr << "File Opening Error: " << e.what() << std::endl;
        return 1;
    } catch (const bad_file_discriptor& e) {
        std::cerr << "File Operation Error: " << e.what() << std::endl;
        return 1;
    } catch (const std::exception& e) {
        std::cerr << "Standard Error: " << e.what() << std::endl;
        return 1;
    } catch (...) {
        std::cerr << "An unknown error occurred." << std::endl;
        return 1;
    }

    return 0;
}
