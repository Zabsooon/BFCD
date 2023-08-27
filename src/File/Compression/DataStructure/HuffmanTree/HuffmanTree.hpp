#include <queue>

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

        static void buildHuffmanTree();

        static void recursiveDestruction(Node<T> *topNode);
        static void clearQueue(std::queue<Node<T> *> &queue);

    private:
        Node<T> *m_TopNode;
        std::queue<Node<T>*> m_NodeQueue;
    };
} // namespace: BFCD

