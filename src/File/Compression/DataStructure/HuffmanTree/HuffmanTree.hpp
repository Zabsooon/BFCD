#include <queue>
#include <functional>

#include "Node.hpp"

namespace BFCD
{
    template<typename T>
    class HuffmanTree
    {
    public:
        HuffmanTree() = default;
        explicit HuffmanTree(Node<T>* topNode);  
        HuffmanTree(const HuffmanTree& huffmanTree);
        HuffmanTree(HuffmanTree&& huffmanTree) noexcept;
        HuffmanTree<T>& operator=(const HuffmanTree& huffmanTree) = delete;
        HuffmanTree<T>& operator=(HuffmanTree&& huffmanTree) noexcept;
        ~HuffmanTree();

    private:

        static std::pair<char, unsigned int> popMaximumOccurrence(std::unordered_map<char, unsigned int> &occurrences); // returns max occurence
        static std::pair<char, unsigned int> popMinimumOccurrence(std::unordered_map<char, unsigned int> &occurrences); // returns min occurence

        void buildHuffmanTree(std::unordered_map<char, unsigned int> occurrences);

        static void recursiveDestruction(Node<T> *topNode);
        static void clearQueue(std::queue<Node<T> *> &queue);

    private:
        Node<T> *m_TopNode;
        std::queue<Node<T>*> m_NodeQueue;
    };
} // namespace: BFCD

