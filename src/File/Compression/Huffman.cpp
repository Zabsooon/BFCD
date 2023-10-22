#include "Huffman.hpp"

using namespace BFCD;

// Public functions:
Huffman::Huffman()
{
    std::cout << "Construction of Huffman.\n";
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
    : m_HuffmanTree(std::move(huffman.m_HuffmanTree))
{}

