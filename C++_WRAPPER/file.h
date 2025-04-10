// Header inclusion
#include <cstdio>    // for C style i/o
#include <cstdarg>   // for printing variadic argument list
#include <iostream>  // for C++ style i/o
#include <string>    // for C++ style string
#include <stdexcept> // for exeption handling



// Enum class for seek origin
enum class SeekOrigin 
{
    Set = SEEK_SET,     // Beginning of file
    Current = SEEK_CUR, // Current position
    End = SEEK_END      // End of file
};



// Exception Handling Classes
// Costom Exception class for file opening error 
class error_opning_file : public std::runtime_error
{
    public:
        explicit error_opning_file(const std::string& s) : runtime_error(s) {}
};

// Costom  Exception class for bad file discriptor
class bad_file_discriptor : public std::runtime_error
{
    public:
        explicit bad_file_discriptor(const std::string& s) : runtime_error(s) {}
};



// Class File
class File
{
    private:
        FILE* m_fp;              // For storing file pointer
        std::string m_filename;  // for storing file name
        
        public:
        //==================== CONSTRUCTORS ====================
        /***
         * @brief   Open/Create file with provoided filename and mode.
         *
         * @details Open/Create file with provoided filename and mode and 
         *          stores file pointer in class's private variable member m_fp.
         * 
         * @param   filename: name of the file to open/create.
         * @param   mode: mode in which file should open/create.
         *
         * @throws  error_opning_file: If Unable to Create/Open file.
         */ 
        File(const std::string& filename, const std::string& mode) : m_fp(NULL), m_filename(filename)
        {
            if(!open(m_filename, mode))
            {
                std::string error_msg = "Error: Failed to open \"" + m_filename + "\" with mode \"" + mode + "\" Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw error_opning_file(error_msg);
            }
            else
            {
                std::cout << m_filename << " Opened Successfully with mode " << mode << std::endl;
            }    
        }

        /***
         * @brief   Create temporary file.
         *
         * @details If user have not provoided filename then this default construtor 
         *          creates temporary file with mode "wb+". Removes when closed or 
         *          programe gets terminated sucessfully.
         *
         * @throws error_opning_file: If Unable to create temporary file.
         */ 
        File()
        {
            m_fp = tmpfile();
            if(!m_fp)
            {
                std::string error_msg = "Error: Unable to create temporary file. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw error_opning_file(error_msg);
            }
            else
            {
                std::cout << "Temporary file Created Successfully with mode \"wb+\"" << std::endl;
            } 
        }



        //==================== DESTRUCTOR ====================
        /***
         * @brief   Closes opened/created file.
         *
         * @details Closes the opened/created file and clear the filename also.
         */ 
        ~File()
        {
            close();
            m_filename.clear();
        }



        //==================== FILE STATUS/ERROR DETECTION ====================
        /***
         * @brief   Checks file open status.
         *
         * @details Uses m_fp variable member of class to check file opening status.
         *          
         * @return  true if m_fp is not NULL otherwise false.
         */
        bool is_open() const
        {
            return m_fp != NULL;
        }

        /***
         * @brief   Checks any error indicator is active in file.
         *          
         * @return  true if any error indicator is active otherwise false
         */
        bool is_error()
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            int error = feof(m_fp);
            if(error != 0)
                return true;
                
            error = ferror(m_fp);
            if(error != 0)
                return true;

            return false;
        }

        /***
         * @brief   Checks for end of file.
         *          
         * @return  true if end of file occured otherwise false.
         */
        bool is_eof()
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return feof(m_fp) != 0;
        }

        /***
         * @brief   Clears active error flags to perform further operations.
         */
        void claer_errors()
        {
            if(is_open())
            {
                clearerr(m_fp);
            }
        }



        //==================== HELPER FUNCTIONS ====================
        /***
         * @brief   Helper function to open file
         *
         * @details First checks file is opened if yes then closes priviosly opned file
         *          and opens/create new file with given mode and stores the file pointer
         *          in private variable member m_fp.
         * 
         * @param   filename:name of the file to open/create 
         * @param   mode:mode in which file is opened/created. 
         * 
         * @return  if file opened successfully then return true otherwise false. 
         */
        bool open(const std::string& filename, const std::string& mode)
        {
            if(is_open())
            {
                close();
            }

            m_filename = filename; // assign input filename to class variable member m_filename
            m_fp = fopen(m_filename.c_str(), mode.c_str()); // perform fopen operation

            return m_fp != NULL;
        }

        /***
         * @brief   Helper function to close file
         *
         * @details Checks if file is opened, if true then closes file and assign
         *          NULL to file pointer variable.
         */
        void close()
        {
            if(m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
                std::cout << "\"" << m_filename << "\"" << " closed successfully..." << std::endl;
            }
        }



        //==================== FILE OPERATIONS ====================
        /***
         * @brief   Reads number of items(element_count) in file to buffer.
         *
         * @details First check file is opened or not if opened then performs 
         *          read operation otherwise throws exception.
         * 
         * @param   ptr: buffer to store readed items
         * @param   element_size: size of each element in bytes.
         * @param   element_count: number of element to read.
         * 
         * @return  number of items readed.
         */
        size_t read(void* ptr, size_t element_size, size_t element_count)
        {
            if(!is_open())
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            // perform read operation
            size_t items_readed = fread(ptr, element_size, element_count, m_fp);

            return items_readed; 
        }

        /***
         * @brief   Writes number of items(element_count) in file from buffer.
         *
         * @details First check file is opened or not if opened then performs 
         *          write operation otherwise throws exception.
         * 
         * @param   ptr: buffer to read data.
         * @param   element_size: size of each element in bytes.
         * @param   element_count: number of element to write from buffer.
         * 
         * @return  number of items written.
         */
        size_t write(void* ptr, size_t element_size, size_t element_count)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            size_t items_written = fwrite(ptr, element_size, element_count, m_fp);

            return items_written;
        }

        /***
         * @brief   Creates temporary filename.
         * 
         * @param   s: if provoided then generated file name will stored is s.
         * 
         * @return  pointer to the internal static array.
         */
        char* get_temp_name(char s[] = NULL)
        {
            return tmpnam(s);
        }

        /***
         * @brief   Read next charactor from file.
         * 
         * @return  return readed charactor or EOF for end of file or any error.
         */
        int getchar()
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return fgetc(m_fp);
        }

         /***
         * @brief   Writes charactor.
         * 
         * @param   c: Writes charactor c in file.
         * 
         * @return  return charactor written or EOF for end of file or any error.
         */
        int putchar(char c)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return fputc(c, m_fp);
        }

         /***
         * @brief   Reads next input line from file.
         * 
         * @param   string: readed string will stored in string param.
         * @param   max_char: if given then atmost max_char-1 will be readed otherwise 63 charactors will be readed
         * 
         * @return  returns readed line or EOF for end of file or any error.
         */
        char* getstring(char* string, int max_char = 64)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return fgets(string, max_char, m_fp);
        }

        /***
         * @brief   Writes string in file.
         * 
         * @param   string: write give 'string' in file.
         * 
         * @return  returns 0 on success or or EOF for end of file or any error.
         */
        int putstring(char* string)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return fputs(string, m_fp);
        }

        /***
         * @brief   Prints formatted input in the file.
         * 
         * @param   format: format of the input string.
         * @param   ...: Variadic argument list.
         * 
         * @return  returns true if number charactors writtened in file is positive otherwise false.
         */
        bool printInFile(const char* format, ...)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            } 

            // create variadic argument list
            va_list ap;
            va_start(ap, format); // initialise it with first unknown argument
        
            int ret_val = vfprintf(m_fp, format, ap); // perform print in file operation
        
            // close the variadic argument list
            va_end(ap);

            if(ret_val < 0)
            {
                return false;
            }
            else
            {
                return true;
            }
        }

         /***
         * @brief   Prints formatted input in the file.
         * 
         * @param   format: format of the input string.
         * @param   ...: Variadic argument list.
         * 
         * @return  returns number charactors writtened in file or nagative number on error.
         */
        bool scanInFile(const char* format, ...)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            // create variadic argument list
            va_list ap;
            va_start(ap, format); // initialise it with first unknown argument
        
            int ret_val = vfscanf(m_fp, format, ap); // perform scan in file operation
        
            // close the variadic argument list
            va_end(ap);

            // check for error or end of file
            if(ret_val != EOF)
            {
                return true;
            }
            else
            {
                return false;
            }
        }

        bool reopen(std::string& mode)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }
            
            m_fp = freopen(m_filename.c_str(), mode.c_str(), m_fp);
            if(m_fp == NULL)
            {
                std::string error_msg = "Error: Failed to open \"" + m_filename + "\" with mode \"" + mode + "\" Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw error_opning_file(error_msg);
            }

            return true;
        }

        bool flush()  
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return fflush(m_fp) == 0;
        }



        //==================== GETTER FUNCTIONS ====================
        FILE* get_handle() const
        {
            return m_fp;
        }

        const std::string& get_filename() const 
        {
            return m_filename;
        }

        

        //==================== FILE POSITIONING ====================
        bool seek(long offset, SeekOrigin origin)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return fseek(m_fp, offset, static_cast<int>(origin)) == 0;
        }
    
        long tell() 
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return ftell(m_fp);
        }
    
        void rewind()
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg); 
            }

            ::rewind(m_fp); 
        }

        bool get_pos(fpos_t* pos)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return fgetpos(m_fp, pos) == 0;
        }

        bool set_pos(fpos_t* pos)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return fsetpos(m_fp, pos) == 0;
        }    
};

