#include "File.hpp"

using namespace BFCD;

File::File(const char* path)
    : m_Path(path)
{
    setSize();
}

File::File(std::string path, std::vector<char> data, bytes size)
    : m_Path(path), m_Data(data), m_Size(size)
{}

File::File(const File& rhs)
    : m_Path(rhs.m_Path), m_Size(rhs.m_Size)
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
    auto printData = [&](std::vector<char> data)
    {
        for(char c : data)
            std::cout << c;
        std::cout << std::endl;
    };
    printData(this->m_Data);
    std::cout << this->m_Size << std::endl;
}

void File::setData(const char* data)
{
    std::vector<char> dataVec;
    dataVec.reserve(this->m_Size);
    for(int i = 0; i < this->m_Size; ++i)
    {
        dataVec.emplace_back(*(data + i));
    }

    std::swap(this->m_Data, dataVec);
}

// private members

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