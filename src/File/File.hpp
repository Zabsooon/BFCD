#pragma once

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

namespace BFCD
{
    class File 
    {
    public:
        typedef size_t bytes;
        friend class Reader;

        explicit File(const char* path);
        explicit File(std::string path, std::vector<char> data, bytes size = 0);
        File(const File& rhs);
        File(File&& file) = default;
        File& operator=(const File& rhs);
        File& operator=(File&& rhs) noexcept;
        void print();

        [[nodiscard]] inline std::string getPath() const { return m_Path; }
        [[nodiscard]] inline std::vector<char> getData() const { return m_Data; }
        
        void setPath(std::string path) { this->m_Path = path; }
        void setData(std::vector<char> data) { this->m_Data = data; }
        void setData(const char* data); // make std::vector<char>       ! needs m_Size !

    private:
        void setSize();
        
    private:
        std::string m_Path;
        std::vector<char> m_Data;
        bytes m_Size{ 0 };
    };
} // namespace BFCD 