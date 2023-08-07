#include "Reader.hpp"

using namespace BFCD;

Reader::Reader(std::string path)
{
    m_File->m_Path = path;
    m_File->setSize();
}

Reader::Reader(const File& file)
    : m_File(std::make_shared<File>(file))
{}

Reader::Reader(File&& file)
    : m_File(std::make_shared<File>(std::move(file)))
{}

void Reader::read()
{
    std::ifstream file = std::ifstream(m_File->m_Path);
    if(file.is_open())
    {
        std::string line;
        while(std::getline(file, line))
        {
            m_File->m_Data.append(line);
            
        }
        file.close();
    }
    else
    {
        std::cout << "Could not open the file!" << std::endl;
    }
}