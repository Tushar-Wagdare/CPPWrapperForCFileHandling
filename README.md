C Style File  Handling Wrapped In C++ Class

A C++ RAII (Resource Acquisition Is Initialization) wrapper class for standard C file I/O functions. This project provides a safer and more object-oriented way to handle C-style `FILE*` resources in C++ applications.

The primary goal is to prevent resource leaks by automatically closing the file handle when the wrapper object goes out of scope, leveraging C++ destructors.

# Features

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

# Repository Structure

*   `C++_WRAPPER/`: Contains the core C++ wrapper code.
    *   `file.h`: Header file defining the `File` class.
    *   `sample_use.cpp`: Example usage for the `File` class.
    *   `test_cases_part_1.cpp`: Test case part one of `File` class.
    *   `test_cases_part_2.cpp`: Test case part two of `File` class.
*   `C_STYLE/`: Contains various example C programs demonstrating raw `<cstdio>` usage (likely for reference or comparison).
  
# Test Case Outputs
## Part one

```cpp
C:\Users\tusha\Desktop\CPPWrapperForCFileHandling\C++_WRAPPER>cl /EHsc /Fe:app.exe test_cases_part_1.cpp
Microsoft (R) C/C++ Optimizing Compiler Version 19.42.34435 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

test_cases_part_1.cpp
Microsoft (R) Incremental Linker Version 14.42.34435.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:app.exe 
test_cases_part_1.obj 

C:\Users\tusha\Desktop\CPPWrapperForCFileHandling\C++_WRAPPER>app.exe
--- Running File Class Tests ---

Testing Constructors & Destructor (RAII)...
Constructors & Destructor Test Passed.

Testing Status & Error Handling...
Status & Error Handling Test Passed.

Testing Binary I/O (read/write)...
Binary I/O Test Passed.

Testing Text I/O (getchar/putchar/getstring/putstring/printInFile/scanInFile)...
Text I/O Test Passed.

Testing File Positioning (seek/tell/rewind/get_pos/set_pos)...
File Positioning Test Passed.

Testing reopen...
reopen Test Passed.

Testing Exception Handling...
  Caught expected open error: Error: Failed to open "no_such_file_here.txt" with mode "r" -
  Reason: No such file or directory.
  Line[67], Function[File], File[C:\Users\tusha\Desktop\CPPWrapperForCFileHandling\C++_WRAPPER\file.h]

  Caught expected bad descriptor error: Error: Bad file discriptor.
  Line[308], Function[putchar], File[C:\Users\tusha\Desktop\CPPWrapperForCFileHandling\C++_WRAPPER\file.h]

Exception Handling Test Passed.

--- All File Class Tests Passed Successfully! ---

C:\Users\tusha\Desktop\CPPWrapperForCFileHandling\C++_WRAPPER>
```

## Part Two

```cpp
C:\Users\tusha\Desktop\CPPWrapperForCFileHandling\C++_WRAPPER>cl /EHsc /Fe:app.exe test_cases_part_2.cpp 
Microsoft (R) C/C++ Optimizing Compiler Version 19.42.34435 for x64
Copyright (C) Microsoft Corporation.  All rights reserved.

test_cases_part_2.cpp
Microsoft (R) Incremental Linker Version 14.42.34435.0
Copyright (C) Microsoft Corporation.  All rights reserved.

/out:app.exe
test_cases_part_2.obj

C:\Users\tusha\Desktop\CPPWrapperForCFileHandling\C++_WRAPPER>app.exe
=============== IN test_case_1() ===============
Just opening and closing file
=============== OUT test_case_1() ===============

=============== IN test_case_2() ===============
Creating and writing binary file
Writing binary data successfull...
=============== OUT test_case_2() ===============

=============== IN test_case_3() ===============
Reading binary file
Reading binary data successfull...
10 20 30 40 50
=============== OUT test_case_3() ===============

=============== IN test_case_4() ===============
File Positioning: seek, tell, rewind, getpos, setpos
File pointer befour seek call: 0
File pointer after seek call: 8
Storing file position in fpos_t...
Reading array(10, 20, 30, 40, 50) from 30
File pointer after read call: 20
Reading binary data from 30 successfull...
30 40 50
File pointer after rewind call: 0
Reading array upto 3rd item after rewind
File pointer after read call: 12
Reading binary data upto 3rd item successfull...
10 20 30
Restoring file position using fpos_t...
File pointer after set_pos call: 8
=============== OUT test_case_4() ===============

=============== IN test_case_5() ===============
File Operation, getchar, putchar, getstring and putstring
getchar output: T
getchar output: U
getchar output: S
getchar output: H
getchar output: A
getchar output: R
getchar output:

getchar output: H
getchar output: e
getchar output: l
getchar output: l
getchar output: o
getchar output:

getchar output: P
getchar output: u
getchar output: t
getchar output: s
getchar output: t
getchar output: r
getchar output: i
getchar output: n
getchar output: g
getchar output:
getchar output: d
getchar output: e
getchar output: m
getchar output: o
getchar output:

getchar output: T
getchar output: e
getchar output: s
getchar output: t
getchar output:
getchar output: c
getchar output: a
getchar output: s
getchar output: e
getchar output:
getchar output: 5
getchar output:

getstring output: TUSHAR
getstring output: Hello
getstring output: Putstring demo
getstring output: Test case 5
=============== OUT test_case_5() ===============


C:\Users\tusha\Desktop\CPPWrapperForCFileHandling\C++_WRAPPER>

```




# Getting Started

1.  **Clone the repository:**
    ```bash
    git clone https://github.com/Tushar-Wagdare/CPPWrapperForCFileHandling
    cd CPPWrapperForCFileHandling
    ```
2.  **Locate the code:** The main wrapper class `File` is defined in `C++_WRAPPER/file.h`.

# Usage

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
