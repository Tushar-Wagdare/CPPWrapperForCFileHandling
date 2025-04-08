#include <cstdint>
#include <iostream>
#include <string>
#include <cstdarg>
#include <stdexcept>

// Enum class for seek origin
enum class SeekOrigin 
{
    Set = SEEK_SET,     // Beginning of file
    Current = SEEK_CUR, // Current position
    End = SEEK_END      // End of file
};



// Exception Handling Classes 
class error_opning_file : public std::runtime_error
{
    public:
        explicit error_opning_file(const std::string& s) : runtime_error(s) {}
};

class bad_file_discriptor : public std::runtime_error
{
    public:
        explicit bad_file_discriptor(const std::string& s) : runtime_error(s) {}
};



// Class File
class File
{
    private:
        FILE* m_fp;
        std::string m_filename;  
        
        public:
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

        // deleting copy constructor, copy assignment operator, move constructor, move asignment operator.
        File(const File&) = delete;
        File(const File&&) = delete;
        File& operator=(const File&) = delete;
        File& operator=(const File&&) = delete;

        File(const std::string& filename, const std::string& mode) : m_fp(NULL), m_filename(filename)
        {
            if(!open(m_filename, mode))
            {
                std::string error_msg = "Error: Failed to open \"" + m_filename + "\" with mode \"" + mode + "\" Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw error_opning_file(error_msg);
            }
                
            puts("File opening successfull...");
        }

        ~File()
        {
            close();
            m_filename.clear();
        }

        bool is_open() const
        {
            return m_fp != NULL;
        }

        bool open(const std::string& filename, const std::string& mode)
        {
            if(is_open())
            {
                close();
            }

            m_filename = filename;
            m_fp = fopen(m_filename.c_str(), mode.c_str());

            return m_fp != NULL;
        }

        void close()
        {
            if(m_fp)
            {
                fclose(m_fp);
                m_fp = NULL;
                puts("File closed successfully...");
            }
        }

        int read(void* ptr, size_t element_size, size_t element_count)
        {
            if(!is_open())
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            size_t items_readed = fread(ptr, element_size, element_count, m_fp);

            return items_readed;
        }

        int write(void* ptr, size_t element_size, size_t element_count)
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

        FILE* get_handle() const
        {
            return m_fp;
        }

        const std::string& get_filename() const 
        {
            return m_filename;
        }

        void clear_errors()
        {
            if(is_open())
            {
                clearerr(m_fp);
            }
        }

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

        int eof()
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return feof(m_fp);
        }

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

        char* getstring(char* string, int max_char)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            return fgets(string, max_char, m_fp);
        }

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

        bool printInFile(const char* format, ...)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            } 

            va_list ap;
            va_start(ap, format);
        
            vfprintf(m_fp, format, ap);
        
            va_end(ap);

            return true;
        }

        bool scanInFile(const char* format, ...)
        {
            if (!is_open()) 
            {
                std::string error_msg = "Error: Bad file discriptor. Line[" + std::to_string(__LINE__) +
                "], Function[" + __func__ + "], File[" + __FILE__ + "]";
                throw bad_file_discriptor(error_msg);
            }

            va_list ap;
            va_start(ap, format);
        
            vfscanf(m_fp, format, ap);
        
            va_end(ap);
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

        char* get_temp_name(char s[] = NULL)
        {
            return tmpnam(s);
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

