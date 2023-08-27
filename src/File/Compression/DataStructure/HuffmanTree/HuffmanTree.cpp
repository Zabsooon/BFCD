#include <unordered_map>
#include "HuffmanTree.hpp"

using namespace BFCD;

template<typename T>
HuffmanTree<T>::HuffmanTree(Node<T>* topNode)
    : m_TopNode(topNode)
{}

template<typename T>
HuffmanTree<T>::HuffmanTree(const HuffmanTree& huffmanTree)
    : m_TopNode(huffmanTree.m_TopNode),
    m_NodeQueue(huffmanTree.m_NodeQueue)
{}

template<typename T>
HuffmanTree<T>::HuffmanTree(HuffmanTree&& huffmanTree) noexcept
    : m_TopNode(std::move(huffmanTree.m_TopNode)),
    m_NodeQueue(std::move(huffmanTree.m_NodeQueue))
{}

template<typename T>
HuffmanTree<T>& HuffmanTree<T>::operator=(HuffmanTree<T>&& huffmanTree) noexcept
{
    this->m_TopNode = std::move(huffmanTree.m_TopNode);
    this->m_NodeQueue = std::move(huffmanTree.m_NodeQueue);
    return *this;
}

template<typename T>
HuffmanTree<T>::~HuffmanTree()
{
    recursiveDestruction(this->m_TopNode);
    clearQueue(this->m_NodeQueue);
}

template class BFCD::HuffmanTree<char>;

// private functions:

template<typename T>
void HuffmanTree<T>::buildHuffmanTree()
{

}

template<typename T>
void HuffmanTree<T>::recursiveDestruction(Node<T> *topNode)
{
    if(topNode)
    {
        recursiveDestruction(topNode->getLeftNode());
        recursiveDestruction(topNode->getRightNode());
    }
    delete topNode;
}

template<typename T>
void HuffmanTree<T>::clearQueue(std::queue<Node<T> *> &queue)
{
    std::queue<Node<T> *> emptyQueue;
    std::swap(queue, emptyQueue);
}