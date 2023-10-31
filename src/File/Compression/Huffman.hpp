#pragma once

#include <string>
#include <unordered_map>
#include <algorithm>

#include "../File.hpp"
#include "../Writer.hpp"
#include "../Reader.hpp"
#include "./DataStructure/HuffmanTree/HuffmanTree.hpp"

namespace BFCD
{
    class Huffman
    {
    public:
        Huffman();
        explicit Huffman(File* file);
        Huffman& operator=(const Huffman& huffman) = delete;
        Huffman& operator=(Huffman&& huffman) noexcept;
        Huffman(const Huffman& huffman) = delete;
        Huffman(Huffman&& huffman) noexcept;
        ~Huffman() = default;

        void compress();

    private:
        HuffmanTree<char> m_HuffmanTree;
        Reader m_Reader;
        Writer m_Writer;
    };
} // namespace: BFCD
