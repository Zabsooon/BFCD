#include "Huffman.hpp"

using namespace BFCD;

// Public functions:
Huffman::Huffman()
{
    std::cout << "Construction of Huffman.\n";
    m_charCodes = std::unordered_map<char, std::string>();
    this->m_HuffmanTree = std::move(HuffmanTree<char>());
}

Huffman::Huffman(File* file)
{
    this->m_HuffmanTree = std::move(HuffmanTree<char>(file));
}

Huffman& Huffman::operator=(Huffman&& huffman) noexcept
{
    this->m_HuffmanTree = std::move(huffman.m_HuffmanTree);
    return *this;
}

Huffman::Huffman(Huffman&& huffman) noexcept
    : m_charCodes(std::move(huffman.m_charCodes)),
    m_HuffmanTree(std::move(huffman.m_HuffmanTree))
{}

Huffman::~Huffman()
{
    std::cout << "Destroying Huffman...\n";
    clearUMap(this->m_charCodes);
    std::cout << "Destroying after clearing UMap.\n";
}

template<typename T, typename U>
void Huffman::clearUMap(std::unordered_map<T, U> &umap)
{
    std::unordered_map<T, U> emptyMap;
    std::swap(umap, emptyMap);
    std::cout << "Clearing UMap\n";
}
