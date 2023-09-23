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
        void setOccurrences(File* file);

        static void cleanOccurrences(std::unordered_map<char, unsigned int>& occurrences);

    private:
        std::unordered_map<char, unsigned int> m_Occurrences;
        HuffmanTree<char> m_HuffmanTree;
    };
} // namespace: BFCD
