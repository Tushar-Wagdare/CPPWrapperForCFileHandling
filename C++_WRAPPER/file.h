#ifndef _FILE_H
#define _FILE_H

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
// Custom Exception class for file opening error 
class error_opning_file : public std::runtime_error
{
    public:
        explicit error_opning_file(const std::string& s) : runtime_error(s) {}
};

// Custom  Exception class for bad file discriptor
class bad_file_discriptor : public std::runtime_error
{
    public:
        explicit bad_file_discriptor(const std::string& s) : runtime_error(s) {}
};



//==================== File Class ====================
class File
{
    private:
        FILE* m_fp;              // For storing file pointer
        std::string m_filename;  // for storing file name
        
        public:
        //==================== CONSTRUCTORS ====================
        /***
        * @brief       Open/Create file with provided filename and mode.
        *
        * @details     Open/Create file with provided filename and mode and 
        *              stores file pointer in class's private variable member m_fp.
        * 
        * @param[in]   filename: name of the file to open/create.
        * @param[in]   mode: mode in which file should open/create.
        *
        * @throws      error_opning_file: If Unable to Create/Open file.
        */ 
        File(const std::string& filename, const std::string& mode) : m_fp(NULL), m_filename(filename)
        {
            if(!open(m_filename, mode))
            {
                
                std::string error_msg = "Error: Failed to open \"" + m_filename + "\" with mode \"" + mode +
                                        "\" - Reason: " + strerror(errno) + 
                                        ". Line[" + std::to_string(__LINE__) + "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw error_opning_file(error_msg);
                
            }   
        }

        /***
        * @brief   Create temporary file.
        *
        * @details If user have not provided filename then this default construtor 
        *          creates temporary file with mode "wb+". Removes when closed or 
        *          programe gets terminated sucessfully.
        *
        * @throws  error_opning_file: If Unable to create temporary file.
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
        }



        //==================== DESTRUCTOR ====================
        /***
        * @brief   Closes opened/created file.
        *
        * @details Closes the opened/created file and clear the filename also.
        */ 
        ~File() noexcept
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
        bool is_error() const
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }
                
            return ferror(m_fp) != 0;
        }

        /***
        * @brief   Checks for end of file.
        *          
        * @return  true if end of file occured otherwise false.
        */
        bool is_eof() const
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
        void clear_errors() 
        {
            if(is_open())
            {
                clearerr(m_fp);
            }
        }



        //==================== HELPER FUNCTIONS ====================
        /***
        * @brief       Helper function to open file
        *
        * @details     First checks file is opened if yes then closes previously opened file
        *              and opens/create new file with given mode and stores the file pointer
        *              in private variable member m_fp.
        * 
        * @param[in]   filename:name of the file to open/create 
        * @param[in]   mode:mode in which file is opened/created. 
        * 
        * @return      if file opened successfully then return true otherwise false. 
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
            }
        }



        //==================== FILE OPERATIONS ====================
        /***
        * @brief        Reads number of items(element_count) in file to buffer.
        *
        * @details      First check file is opened or not if opened then performs 
        *               read operation otherwise throws exception.
        * 
        * @param[out]   ptr: buffer to store read items
        * @param[in]    element_size: size of each element in bytes.
        * @param[in]    element_count: number of element to read.
        * 
        * @return       number of items read.
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
        * @brief       Writes number of items(element_count) in file from buffer.
        *
        * @details     First check file is opened or not if opened then performs 
        *              write operation otherwise throws exception.
        * 
        * @param[in]   ptr: buffer to read data.
        * @param[in]   element_size: size of each element in bytes.
        * @param[in]   element_count: number of element to write from buffer.
        * 
        * @return      number of items written.
        */
        size_t write(const void* ptr, size_t element_size, size_t element_count) 
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
        * @brief        Creates temporary filename.
        * 
        * @param[out]   s: if provided then generated file name will stored is s.
        * 
        * @return       pointer to the internal static array.
        * 
        * @deprecated   this function is unsafe and deprecated so commenting out to prevent any harm..
        */
        // char* get_temp_name(char s[] = NULL)
        // {
        //     return tmpnam(s);
        // }

        /***
        * @brief   Read next character from file.
        * 
        * @return  return read character or EOF for end of file or any error.
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
        * @brief       Writes character.
        * 
        * @param[in]   c: Writes character c in file.
        * 
        * @return      return character written or EOF for end of file or any error.
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
        * @brief        Reads next input line from file.
        * 
        * @param[out]   string: read string will stored in string param.
        * @param[in]    max_char: if given then atmost max_char-1 will be read otherwise 63 characters will be read
        * 
        * @return       returns read line or EOF for end of file or any error.
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
        * @brief       Writes string in file.
        * 
        * @param[in]   string: write give 'string' in file.
        * 
        * @return      returns true on success or false on end of file or any error.
        */
        bool putstring(const char* string) 
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return fputs(string, m_fp) != EOF;
        }

        /***
        * @brief       Prints formatted input in the file.
        * 
        * @param[in]   format: format of the input string.
        * @param[in]   ...: Variadic argument list.
        * 
        * @return      returns true if number of charactors written in file is positive otherwise false.
        */
        bool printInFile(const char* format, ...) const
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
        * @brief       Scans file
        * 
        * @param[in]   format: format of the arguments.
        * @param[in]   ...: Variadic argument list which stores scanned items.
        * 
        * @return      returns false if EOF occured otherwise true.
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

        /***
        * @brief       reopens file with given mode.
        * 
        * @param[in]   mode: mode to change while reopening file.
        * 
        * @return      returns true on successfull reopening of the file otherwise throws exception.
        */
        bool reopen(const std::string& mode) 
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
                std::string error_msg = "Error: Failed to reopen \"" + m_filename + "\" with mode \"" + mode +
                                        "\" - Reason: " + strerror(errno) + 
                                        ". Line[" + std::to_string(__LINE__) + "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                    throw error_opning_file(error_msg);
            }

            return true;
        }

        /***
        * @brief   Flushes any buffered output before next statement.
        * 
        * @details Ensures that the data is read or written completely.
        * 
        * @return  true on success otherwise false.
        */
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
        /***
        * @brief   To get file handle.
        * 
        * @details Used to get file handle of type FILE*.
        * 
        * @return  returns file handle.
        */
        FILE* get_handle() const
        {
            return m_fp;
        }

        /***
        * @brief   To get file name.
        * 
        * @details Used to get filename associated with the class object.
        * 
        * @return  returns file name
        */
        const std::string& get_filename() const 
        {
            return m_filename;
        }

        

        //==================== FILE POSITIONING ====================
        /***
        * @brief       Used to set file pointer.
        * 
        * @param[in]   offset: number of bytes to shift file pointer.
        * @param[in]   origin: from where shifting of file pointer will be done.
        *                  allowable mode: Set(from origin), Current(from current position of file pointer) 
        *                  or End(from end of the file).
        * 
        * @return      returns true on success otherwise false.
        */
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
    
        /***
        * @brief   To get current position of file pointer.
        * 
        * @return  return byte offset from file's base address to current position of file pointer.
        */
        long tell() const
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return ftell(m_fp);
        }
    
        /***
        * @brief   Sets file pointer to begining.
        */
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

        /***
        * @brief        Records current file position.
        * 
        * @param[out]   pos: stores current file position in fpos_t data types variable.
        * 
        * @return       return true on success otherwise false.
        */
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

        /***
        * @brief       Sets previously Recorded file position.
        * 
        * @param[in]   pos: Priviously recorded file position
        * 
        * @return      return true on success otherwise false.
        */
        bool set_pos(const fpos_t* pos) 
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


#endif  // _FILE_H
