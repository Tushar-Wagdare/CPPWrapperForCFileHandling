#include <iostream>
#include <stdexcept>
#include <vector>
#include "file.h" // Adjust path as needed


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