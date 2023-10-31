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
        Reader& operator=(const Reader& reader);
        Reader& operator=(Reader&& reader) noexcept;
        Reader(const Reader& reader);
        Reader(Reader&& reader) noexcept;
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