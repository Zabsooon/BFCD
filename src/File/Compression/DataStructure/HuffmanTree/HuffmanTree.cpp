#include "HuffmanTree.hpp"

using namespace BFCD;

template<typename T>
HuffmanTree<T>::HuffmanTree(File *file)
{
    std::cout << "Construction of HuffmanTree\n";
    this->m_TopNode = std::make_shared<Node<T>>(buildHuffmanTree(file));
    std::cout << "Construction of HuffmanTree after building\n";
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
    std::cout << "Destruction HuffmanTree\n";
    recursiveDestruction(this->m_TopNode);
    std::cout << "Destruction HuffmanTree after recursive destruct\n";
}

template class BFCD::HuffmanTree<char>;

// private functions:

template<typename T>
std::unordered_map<T, unsigned int>  HuffmanTree<T>::readOccurrences(File* file)
{

    std::unordered_map<char, unsigned int> occurrences;
    std::cout << "Read occurrences: before filling occurrences\n";
    file->print();
    for(char c : file->getData())   
        occurrences[c]++;
    std::cout << "Read occurrences: before returning occurrences\n";
    return occurrences;
}

template<typename T>
std::vector<Node<T>> HuffmanTree<T>::buildNodeVector(std::unordered_map<T, unsigned int> &occurrences)
{
    std::vector<Node<T>> nodeVector;
    std::cout << "Build Node Vector: before reserving size\n";
    nodeVector.reserve(occurrences.size());
    std::cout << "Build Node Vector: before loop\n";
    for(auto it = occurrences.begin(); it != occurrences.end(); it++)
    {
        std::cout << "Build Node Vector: inside loop before creating node\n";
        Node<T> node(it->first, it->second);
        std::cout << "Build Node Vector: inside loop before emplace_back()\n";
        nodeVector.emplace_back(node);
    }
    std::cout << "Build Node Vector: before returning nodeVector\n";
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
Node<T> HuffmanTree<T>::popMinimumNode(std::vector<Node<T>> &nodeVector)
{
    unsigned int counter = 0;
    std::cout << "Inside PopMinimumNode: Before declaring getMinimum Element\n";
    auto getMinimumElement = [&](std::vector<Node<T>> &nVector)
    {
        std::cout << "nVector.size(): " << nVector.size() << "\n";
        std::cout << "Before assigning smallestNode";
        Node<T> smallestNode = *nVector.begin();
        std::cout << "Character: " << smallestNode.getCharacter() << ", frequency: " << smallestNode.getFrequency() << "\n";
        std::cout << "Before nVector loop";
        for(auto it = nVector.begin(); it != nVector.end(); it++, counter++)
        {
            std::cout << "inside loop\n";
            if((*it).getFrequency() < smallestNode.getFrequency())
            {
                std::cout << "(*it)'s character: " << (*it).getCharacter() << "(*it)" << (*it).getFrequency() << "\n";
                smallestNode = *it;
            }
            std::cout << "nodeVector.at(" << counter << ") character:" << nodeVector.at(counter).getCharacter() << ", frequency: " << nodeVector.at(counter).getFrequency() << "\n";
            std::cout << "nodeVector iterator character: " << (*it).getCharacter() << ", frequency: " << (*it).getFrequency() << "\n";
        }
        std::cout << "popMinimumNode: before return smallestNode\n";
        nodeVector.erase(nodeVector.begin() + counter);
        return smallestNode;
    };
    std::cout << "popMinmumNode: before getMinimumElement call\n";
    Node<T> minNode = getMinimumElement(nodeVector);
    std::cout << "popMinimumNode: before return minNode\n";
    return minNode;
}

template<typename T>
Node<T> HuffmanTree<T>::buildHuffmanTree(File* file)
{
    std::cout << "1\n";
    std::unordered_map<T, unsigned int> occurrences = readOccurrences(file);
    std::cout << "1\n";
    std::vector<Node<T>> nodeVector = buildNodeVector(occurrences);
    std::cout << "1\n";

    while(nodeVector.size() > 1)
    {
        std::cout << "2\n";
        std::cout << "NodeVector size: " << nodeVector.size() << "\n";
        Node<T> minNodeLeft = popMinimumNode(nodeVector);
        std::cout << "MinNodeLeft character: " << minNodeLeft.getCharacter() << ", occurrences:" << minNodeLeft.getFrequency() << "\n";
        Node<T> minNodeRight = popMinimumNode(nodeVector);
        std::cout << "MinNodeRight character: " << minNodeRight.getCharacter() << ", occurrences:" << minNodeRight.getFrequency() << "\n";
        std::shared_ptr<Node<T>> combinedNode = std::make_shared<Node<T>>(0,
                            minNodeLeft.getFrequency() + minNodeRight.getFrequency(),
                            std::make_shared<Node<T>>(minNodeLeft),
                            std::make_shared<Node<T>>(minNodeRight));
        std::cout << "CombinedNode character: " << combinedNode->getCharacter() << ", occurrences: " << combinedNode->getFrequency() << "\n";
        nodeVector.emplace_back(combinedNode);
        std::cout << "After emplace_back\n";
    }
    std::cout << "3\n";
    return popMinimumNode(nodeVector);
}

template<typename T>
void HuffmanTree<T>::buildHuffmanTree(std::unordered_map<char, unsigned int> &occurrences)
{
    std::vector<Node<T>> nodeVector = buildNodeVector(occurrences);
    
    while(nodeVector.size() > 1)
    {
        Node<T> minNodeLeft = popMinimumNode(nodeVector);
        Node<T> minNodeRight = popMinimumNode(nodeVector);
        Node<T> combinedNode(0,
                            minNodeLeft.getFrequency() + minNodeRight.getFrequency(),
                            std::make_shared<Node<T>>(minNodeLeft),
                            std::make_shared<Node<T>>(minNodeRight));
        
        nodeVector.emplace_back(combinedNode);
    }

    this->m_TopNode = std::make_unique<Node<T>>(popMinimumNode(nodeVector));
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
