#pragma once

#include <queue>
#include <vector>
#include <unordered_map>
#include <functional>

#include "../../../File.hpp"
#include "Node.hpp"

namespace BFCD
{
    template<typename T>
    class HuffmanTree
    {
    public:
        HuffmanTree() = default;
        HuffmanTree(File *file);
        explicit HuffmanTree(std::shared_ptr<Node<T>> topNode);
        HuffmanTree(const HuffmanTree& huffmanTree);
        HuffmanTree(HuffmanTree&& huffmanTree) noexcept;
        HuffmanTree<T>& operator=(const HuffmanTree& huffmanTree) = delete;
        HuffmanTree<T>& operator=(HuffmanTree&& huffmanTree) noexcept;
        ~HuffmanTree();

    private:
	
	static std::unordered_map<T, unsigned int> readOccurrences(File* file); // returns occurrences of characters
        static std::vector<std::shared_ptr<Node<T>>> buildNodeVector(std::unordered_map<T, unsigned int> &occurrences);
        static std::shared_ptr<Node<T>> popMinimumNode(std::vector<std::shared_ptr<Node<T>>> &nodeVector);
        std::shared_ptr<Node<T>> buildHuffmanTree(File* file); // most likely to be used
        void buildHuffmanTree(std::unordered_map<char, unsigned int> &occurrences);
        std::unordered_map<T, std::string> generateCharCodes();
        void recursivePrint(std::shared_ptr<Node<T>> topNode);
        void printCharCodes(std::unordered_map<char, std::string> charCodes);

        static void recursiveDestruction(std::shared_ptr<Node<T>> topNode);
        static void clearQueue(std::queue<Node<T>> &queue);
        template<typename KeyType, typename ValueType>
        static void clearUMap(std::unordered_map<KeyType, ValueType> &umap);

    private:
        std::shared_ptr<Node<T>> m_TopNode;
        std::unordered_map<char, std::string> m_CharCodes;
    };
} // namespace: BFCD

