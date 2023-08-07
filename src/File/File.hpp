#pragma once

#include <iostream>
#include <fstream>

namespace BFCD
{
    class File 
    {
    public:
        typedef size_t bytes;
        friend class Reader;

        File(const char* path);
        File(std::string path, std::string data = "", bytes size = 0);
        File(const File& rhs);
        File(File&& file) = default;
        File& operator=(const File& rhs);
        File& operator=(File&& rhs) noexcept;
        void print();

        inline std::string getPath() const { return m_Path; }
        
    private:

        void setSize();
        
    private:
        std::string m_Path;
        std::string m_Data{ "" };
        bytes m_Size{ 0 };
    };
} // namespace BFCD 