#include "HuffmanTree.hpp"

using namespace BFCD;

template<typename T>
HuffmanTree<T>::HuffmanTree(File *file)
{
    this->m_TopNode = buildHuffmanTree(file);
    std::cout << "PRINTER: \n";
    recursivePrint(this->m_TopNode);
}

template<typename T>
HuffmanTree<T>::HuffmanTree(Node<T>* topNode)
    : m_TopNode(topNode)
{}

template<typename T>
HuffmanTree<T>::HuffmanTree(const HuffmanTree& huffmanTree)
    : m_TopNode(huffmanTree.m_TopNode)
{}

template<typename T>
HuffmanTree<T>::HuffmanTree(HuffmanTree&& huffmanTree) noexcept
    : m_TopNode(std::move(huffmanTree.m_TopNode))
{}

template<typename T>
HuffmanTree<T>& HuffmanTree<T>::operator=(HuffmanTree<T>&& huffmanTree) noexcept
{
    this->m_TopNode = std::move(huffmanTree.m_TopNode);
    return *this;
}

template<typename T>
HuffmanTree<T>::~HuffmanTree()
{
    recursiveDestruction(this->m_TopNode);
}

template class BFCD::HuffmanTree<char>;

// private functions:

template<typename T>
std::unordered_map<T, unsigned int>  HuffmanTree<T>::readOccurrences(File* file)
{

    std::unordered_map<char, unsigned int> occurrences;
    file->print();
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
Node<T>* HuffmanTree<T>::popMaximumNode(std::vector<Node<T>*> &nodeVector)
{
    unsigned int counter = 0;
    auto pr = std::max_element(nodeVector.begin(),
                                nodeVector.end(),
                                [&](const auto &x, const auto &y)
                                {
                                    counter++;
                                    return x->getFrequency() < y->getFrequency();
                                });
    nodeVector.erase(nodeVector.begin() + counter);
    return *pr;
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
    std::function<void(std::shared_ptr<Node<T>> node)> recursiveTraversal;
    std::vector<char> codeStackVec; // the only reason that we use vector instead of stack are iterators 
    codeStackVec.reserve(255);

    recursiveTraversal = [&](std::shared_ptr<Node<T>> node)
    {
        if(!node->hasNext())
        {
            auto countCode = [&](std::vector<char> &cStackVec)
            {
                std::string code;
                for(auto it = cStackVec.rbegin(); it != cStackVec.rend(); ++it)
                {
                    code += (*it);
                }
                return code;
            };
            charCodes[node->getCharacter()] = countCode(codeStackVec);
        }
        
        codeStackVec.emplace_back('0');
        recursiveTraversal(node->getLeftNode());
        codeStackVec.pop_back();
        
        codeStackVec.emplace_back('1');
        recursiveTraversal(node->getRightNode());
        codeStackVec.pop_back();
    };
    std::shared_ptr<Node<T>> topNode = this->m_TopNode;
    recursiveTraversal(topNode);
    
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
void HuffmanTree<T>::clearUMap(std::unordered_map<T, unsigned int> &umap)
{
    std::unordered_map<T, unsigned int> emptyUMap;
    std::swap(umap, emptyUMap);
}
