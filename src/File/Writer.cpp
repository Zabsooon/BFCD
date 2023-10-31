#include "Writer.hpp"

using namespace BFCD;

Writer& Writer::operator=(const Writer& writer)
{
    this->m_File = writer.m_File;
    return *this;
}

Writer& Writer::operator=(Writer&& writer) noexcept
{
    this->m_File = writer.m_File;
    return *this;
}

Writer::Writer(const Writer& writer)
    : m_File(writer.m_File)
{}

Writer::Writer(Writer&& writer) noexcept
    : m_File(std::move(writer.m_File))
{}

Writer::Writer(const File& file)
    : m_File(std::make_shared<File>(file))
{}

Writer::Writer(File&& file)
    : m_File(std::make_shared<File>(std::move(file)))
{}

Writer::Writer(std::string path)
{
    m_File->setPath(path);
    m_File->setSize();
}

Writer::Writer(std::shared_ptr<File> file)
    : m_File(file)
{}

bool Writer::saveData(std::string data)
{
    std::ofstream fs(this->m_File->getPath(), std::ios::trunc);

    if(!fs)
    {
        std::cout << "Could not write to the file!\n";
        return false;
    }

    std::string data;
    for(char c : this->m_File->getData())
        data += c;

    fs << data;
    fs.close();
    return true;
}
