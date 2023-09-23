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
std::pair<char, unsigned int> HuffmanTree<T>::popMaximumOccurrence(std::unordered_map<char, unsigned int> &occurrences)
{
    auto pr = std::max_element(occurrences.begin(),
                               occurrences.end(),
                               [&](const auto &x, const auto &y)
                               {
                                   return x.second < y.second;
                               });

    char ret_c = pr->first;
    unsigned int ret_v = pr->second;
    occurrences.erase(pr->first);

    return {ret_c, ret_v};
}

template<typename T>
std::pair<char, unsigned int> HuffmanTree<T>::popMinimumOccurrence(std::unordered_map<char, unsigned int> &occurrences)
{
    auto pr = std::min_element(occurrences.begin(),
                               occurrences.end(),
                               [&](const auto &x, const auto &y)
                               {
                                   return x.second < y.second;
                               });

    char ret_c = pr->first;
    unsigned int ret_v = pr->second;
    occurrences.erase(pr->first);

    return {ret_c, ret_v};
}

template<typename T>
void HuffmanTree<T>::buildHuffmanTree(std::unordered_map<char, unsigned int> occurrences)
{
    if(this->m_TopNode == nullptr)
        return;

    std::queue<Node<T>*> minQueue;

    while(!occurrences.empty())
    {
        std::pair<char, unsigned int> minElement = popMinimumOccurrence(occurrences);
        Node<T> *minNode{minElement.first, minElement.second};
        minQueue.push(minNode);
        this->m_NodeQueue.push(minNode); // add node to queue of all nodes
        if(minQueue.size() == 2)
        {
            Node<T> *a = minQueue.front();
            minQueue.pop();
            Node<T> *b = minQueue.front();
            minQueue.pop();

            Node<T> combineNode{0, (a->getFrequency() + b->getFrequency())};
            combineNode.setBothNodes(a, b);
            this->m_NodeQueue.push(combineNode);

            // now we have to add the combineNode to the pool of nodes
        }
    }

//    std::function<void(Node<T> *node)> recursiveTraversal;
//
//    recursiveTraversal = [&](Node<T> *node)
//    {
//        if(node->hasLeft())
//        {
//            this->m_NodeStack.push(node->getLeftNode());
//            recursiveTraversal(node->getLeftNode());
//        }
//        if(node->hasRight())
//        {
//            this->m_NodeStack.push(node->getRightNode());
//            recursiveTraversal(node->getLeftNode());
//        }
//    };
//
//    recursiveTraversal(this->m_TopNode);
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