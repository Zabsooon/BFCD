#include "HuffmanTree.hpp"

using namespace BFCD;

template<typename T>
HuffmanTree<T>::HuffmanTree(File *file)
{
    this->m_TopNode = buildHuffmanTree(file);
    this->m_CharCodes = generateCharCodes();
}

template<typename T>
HuffmanTree<T>::HuffmanTree(std::shared_ptr<Node<T>> topNode)
    : m_TopNode(topNode)
{}

template<typename T>
HuffmanTree<T>::HuffmanTree(const HuffmanTree& huffmanTree)
    : m_TopNode(huffmanTree.m_TopNode),
    m_CharCodes(huffmanTree.m_CharCodes)
{}

template<typename T>
HuffmanTree<T>::HuffmanTree(HuffmanTree&& huffmanTree) noexcept
    : m_TopNode(std::move(huffmanTree.m_TopNode)),
    m_CharCodes(std::move(huffmanTree.m_CharCodes))
{}

template<typename T>
HuffmanTree<T>& HuffmanTree<T>::operator=(HuffmanTree<T>&& huffmanTree) noexcept
{
    this->m_TopNode = std::move(huffmanTree.m_TopNode);
    this->m_CharCodes = std::move(huffmanTree.m_CharCodes);
    return *this;
}

template<typename T>
HuffmanTree<T>::~HuffmanTree()
{
    recursiveDestruction(this->m_TopNode);
    std::cout << "Pre clear \n";
    clearUMap(m_CharCodes);
    std::cout << "Post clear \n";
}

template class BFCD::HuffmanTree<char>;

// private functions:

template<typename T>
std::unordered_map<T, unsigned int>  HuffmanTree<T>::readOccurrences(File* file)
{
    std::unordered_map<char, unsigned int> occurrences;
    for(char c : file->getData())   
        occurrences[c]++;
    return occurrences;
}

template<typename T>
std::vector<std::shared_ptr<Node<T>>> HuffmanTree<T>::buildNodeVector(std::unordered_map<T, unsigned int> &occurrences)
{
    std::vector<std::shared_ptr<Node<T>>> nodeVector;
    nodeVector.reserve(occurrences.size());
    for(auto it = occurrences.begin(); it != occurrences.end(); it++)
    {
        std::shared_ptr<Node<T>> node = std::make_shared<Node<T>>((*it).first, (*it).second, nullptr, nullptr);
        nodeVector.emplace_back(node);
    }

    return nodeVector;
}

template<typename T>
std::shared_ptr<Node<T>> HuffmanTree<T>::popMinimumNode(std::vector<std::shared_ptr<Node<T>>> &nodeVector)
{
    auto getMinimumElement = [&](std::vector<std::shared_ptr<Node<T>>> &nVector)
    {
        std::shared_ptr<Node<T>> smallestNode = *nVector.begin();
        auto nodeIt = nVector.begin();
        for(auto it = nVector.begin(); it != nVector.end(); it++)
        {
            if((*it)->getFrequency() < smallestNode->getFrequency())
            {
                nodeIt = it;
                smallestNode = *it;
            }
        }
        nodeVector.erase(nodeIt);
        return smallestNode;
    };
    std::shared_ptr<Node<T>> minNode = getMinimumElement(nodeVector);
    return minNode;
}

template<typename T>
std::shared_ptr<Node<T>> HuffmanTree<T>::buildHuffmanTree(File* file)
{
    std::unordered_map<T, unsigned int> occurrences = readOccurrences(file);
    std::vector<std::shared_ptr<Node<T>>> nodeVector = buildNodeVector(occurrences);

    while(nodeVector.size() > 1)
    {
        std::shared_ptr<Node<T>> minNodeLeft = popMinimumNode(nodeVector);
        std::shared_ptr<Node<T>> minNodeRight = popMinimumNode(nodeVector);
        std::shared_ptr<Node<T>> combinedNode = std::make_shared<Node<T>>('\0',
                            minNodeLeft->getFrequency() + minNodeRight->getFrequency(),
                            minNodeLeft,
                            minNodeRight);
        nodeVector.emplace_back(combinedNode);
    }
    return popMinimumNode(nodeVector);
}

template<typename T>
void HuffmanTree<T>::buildHuffmanTree(std::unordered_map<char, unsigned int> &occurrences)
{
    std::vector<std::shared_ptr<Node<T>>> nodeVector = buildNodeVector(occurrences);
    
    while(nodeVector.size() > 1)
    {
        std::shared_ptr<Node<T>> minNodeLeft = popMinimumNode(nodeVector);
        std::shared_ptr<Node<T>> minNodeRight = popMinimumNode(nodeVector);
        std::shared_ptr<Node<T>> combinedNode = std::make_shared<Node<T>>(0,
                            minNodeLeft->getFrequency() + minNodeRight->getFrequency(),
                            minNodeLeft,
                            minNodeRight);
        
        nodeVector.emplace_back(combinedNode);
    }

    this->m_TopNode = popMinimumNode(nodeVector);
}

template<typename T>
std::unordered_map<T, std::string> HuffmanTree<T>::generateCharCodes()
{
    std::unordered_map<T, std::string> charCodes;
    std::function<void(std::shared_ptr<Node<T>> node, const std::string& code)> recursiveTraversal;

    charCodes.reserve(256);

    recursiveTraversal = [&](std::shared_ptr<Node<T>> node, const std::string& code)
    {
        if(!node->hasNext())
        {
            charCodes[node->getCharacter()] = code;
        }
        if(node->getLeftNode())
        {
            recursiveTraversal(node->getLeftNode(), code + "0");
        }
        if(node->getRightNode())
        {
            recursiveTraversal(node->getRightNode(), code + "1");
        }
    };

    std::shared_ptr<Node<T>> topNode = this->m_TopNode;
    recursiveTraversal(topNode, "");

    return charCodes;
}

template<typename T>
void HuffmanTree<T>::recursivePrint(std::shared_ptr<Node<T>> topNode)
{
    if(topNode == nullptr)
        return;

    std::cout << "------- NEXT --------\n";
    std::cout << "Node character: " << topNode->getCharacter() << ", frequency: " << topNode->getFrequency() << "\n";
    std::cout << "Node left: " << topNode->hasLeft() << " , node right: " << topNode->hasRight() << "\n";

    if(topNode->hasNext())
    {
        recursivePrint(topNode->getLeftNode());
        recursivePrint(topNode->getRightNode());
    }
}

template<typename T>
void HuffmanTree<T>::printCharCodes(std::unordered_map<char, std::string> charCodes)
{
    for(auto [Key, Value] : charCodes)
    {
        std::cout << "Key: " << Key << ", Value: " << Value << "\n";
    }
}

template<typename T>
void HuffmanTree<T>::recursiveDestruction(std::shared_ptr<Node<T>> topNode)
{
    if(topNode == nullptr)
        return;

    if(topNode->hasNext())
    {
        recursiveDestruction(topNode->getLeftNode());
        recursiveDestruction(topNode->getRightNode());
    }
    // delete topNode;
}

template<typename T>
void HuffmanTree<T>::clearQueue(std::queue<Node<T>> &queue)
{
    std::queue<Node<T>> emptyQueue;
    std::swap(queue, emptyQueue);
}

template<typename T>
template<typename KeyType, typename ValueType>
void HuffmanTree<T>::clearUMap(std::unordered_map<KeyType, ValueType> &umap)
{
    std::unordered_map<KeyType, ValueType> emptyUMap;
    std::swap(umap, emptyUMap);
}
