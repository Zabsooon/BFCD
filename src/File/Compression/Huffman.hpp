#pragma once

#include <string>
#include <unordered_map>
#include <algorithm>

#include "../File.hpp"
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
        ~Huffman();

    private:
        template<typename T, typename U>
        static void clearUMap(std::unordered_map<T, U> &umap);

    private:
        std::unordered_map<char, std::string> m_charCodes;
        HuffmanTree<char> m_HuffmanTree;
    };
} // namespace: BFCD
