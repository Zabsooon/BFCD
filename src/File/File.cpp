#include "File.hpp"

using namespace BFCD;

File::File(const char* path)
    : m_Path(path)
{}

File::File(std::string path, std::string data, bytes size)
    : m_Path(path), m_Data(data), m_Size(size)
{}

File::File(const File& rhs)
    : m_Path(rhs.m_Path), m_Data(rhs.m_Data), m_Size(rhs.m_Size)
{}

// Copy assignment operator (takes an lvalue)
File& File::operator=(const File& rhs)
{
    this->m_Path = rhs.m_Path;
    this->m_Data = rhs.m_Data;
    this->m_Size = rhs.m_Size;
    return *this;
}

// Move assignment operator (takes an rvalue)
File& File::operator=(File&& rhs) noexcept
{
    this->m_Path = std::move(rhs.m_Path);
    this->m_Data = std::move(rhs.m_Data);
    this->m_Size = std::move(rhs.m_Size);
    return *this;
}

void File::print()
{
    std::cout << this->m_Path << std::endl;
    std::cout << this->m_Data << std::endl;
    std::cout << this->m_Size << std::endl;
}

void File::setSize()
{
    std::streampos begin, end;
    std::ifstream file(m_Path, std::ios::binary);
    begin = file.tellg();
    file.seekg(0, std::ios::end);
    end = file.tellg();
    file.close();
    m_Size = end - begin;
}