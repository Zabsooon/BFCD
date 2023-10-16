#pragma once

#include <memory>
#include <fstream>
#include <string>

#include "File.hpp"

namespace BFCD
{
    class Reader
    {
    public:
        Reader& operator=(const Reader&) = delete;
        Reader& operator=(Reader&&) = delete;
        Reader(const Reader&) = delete;
        Reader(Reader&&) = delete;
        Reader(const File& file);
        Reader(File&& file);
        Reader(std::string path);
        Reader(std::shared_ptr<File> file);
        
        inline std::shared_ptr<File> getFile() const { return m_File; }
        bool readData(); // returns true if file data was read successfully
        bool readData(File* file); // returns true if file data was read successfully

    private:
        std::shared_ptr<File> m_File;
    };
} // namespace BFCD