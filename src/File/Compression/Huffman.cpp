#include "Huffman.hpp"

using namespace BFCD;

// Public functions:
Huffman::Huffman()
{
    this->m_Occurrences = std::move(std::unordered_map<char, unsigned int>());
    this->m_HuffmanTree = std::move(HuffmanTree<char>());
}

Huffman::Huffman(File* file)
{
    setOccurrences(file);
    this->m_HuffmanTree = std::move(HuffmanTree<char>());
}

Huffman& Huffman::operator=(Huffman&& huffman) noexcept
{
    this->m_Occurrences = std::move(huffman.m_Occurrences);
    this->m_HuffmanTree = std::move(huffman.m_HuffmanTree);
    return *this;
}

Huffman::Huffman(Huffman&& huffman) noexcept
    : m_Occurrences(std::move(huffman.m_Occurrences)),
    m_HuffmanTree(std::move(huffman.m_HuffmanTree))
{}

Huffman::~Huffman()
{
    cleanOccurences(this->m_Occurrences);
}

// Private functions:

void Huffman::setOccurrences(File* file)
{
    this->m_Occurrences = std::unordered_map<char, unsigned int>();
    std::string data = file->getData();

    for(char c : data)
    {
        auto found = std::find_if(
            m_Occurrences.begin(),
            m_Occurrences.end(),
            [&c](const auto& p){ return p.second == c; });
        if(found != m_Occurrences.end())
        {
            m_Occurrences.at(c)++;
        }
        else
        {
            m_Occurrences.insert(std::make_pair(c, 1));
        }
    }
}

void Huffman::cleanOccurences(std::unordered_map<char, unsigned int>& occurences)
{
    std::unordered_map<char, unsigned int> emptyOccurences;
    std::swap(occurences, emptyOccurences);
}
