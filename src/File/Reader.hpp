#pragma once

#include <memory>
#include <fstream>

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
        
        inline std::shared_ptr<File> getFile() const { return m_File; }
        void read();
        

    private:
        std::shared_ptr<File> m_File;
    };
} // namespace BFCD