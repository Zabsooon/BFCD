#include "FileHandler.hpp"

using namespace BFCD;

FileHandler::FileHandler()
    : m_File(nullptr)
{}

FileHandler::FileHandler(const std::string& filePath)
    : m_File(std::make_shared<File>(filePath))
{
    readData();
}

FileHandler::FileHandler(FileHandler& fileHandler)
{
    if(fileHandler.m_File)
    {
        fileHandler.m_File = std::make_shared<File>(std::move(*fileHandler.m_File));
    }
    else
        m_File = nullptr;
}

FileHandler::FileHandler(FileHandler&& fileHandler) noexcept
{
    m_File = std::move(fileHandler.m_File);
}

bool FileHandler::saveData(std::string& data)
{
    std::ofstream fs(this->m_File->getPath(), std::ios::trunc);

    if(!fs)
    {
        std::cout << "Could not write to the file!\n";
        return false;
    }

    std::string newData;
    for(char c : this->m_File->getData())
        newData += c;

    fs << newData;
    fs.close();
    return true;
}

bool FileHandler::readData()
{
    std::ifstream fs(this->m_File->getPath());

    if(!fs)
    {
        std::cout << "Could not open the file!\n";
        return false;
    }

    std::stringstream buffer;
    buffer << fs.rdbuf();
    fs.close();
    this->m_File->setData(buffer.str().c_str());
    return true;
}
