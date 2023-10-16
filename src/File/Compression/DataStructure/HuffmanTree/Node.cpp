#include "Node.hpp"

using namespace BFCD;

template<typename T>
Node<T>::Node()
    : m_Character(0),
    m_Frequency(0),
    m_LeftNode(nullptr),
    m_RightNode(nullptr)
{}

template<typename T>
Node<T>::Node(char character, unsigned int frequency, std::shared_ptr<Node<T>> leftNode, std::shared_ptr<Node<T>> rightNode)
    : m_Character(character),
    m_Frequency(frequency),
    m_LeftNode(leftNode),
    m_RightNode(rightNode)
{}

template<typename T>
Node<T>::Node(const Node<T>& node)
    : m_Character(node.m_Character),
    m_Frequency(node.m_Frequency),
    m_LeftNode(node.m_LeftNode),
    m_RightNode(node.m_RightNode)
{}

template<typename T>
Node<T>::Node(Node&& node) noexcept
    : m_Character(std::move(node.m_Character)),
    m_Frequency(std::move(node.m_Frequency)),
    m_LeftNode(std::move(node.m_LeftNode)),
    m_RightNode(std::move(node.m_RightNode))
{}

template<typename T>
Node<T>::Node(std::shared_ptr<Node<T>>& node)
{
    this->m_Character = node->getCharacter();
    this->m_Frequency = node->getFrequency();
    this->m_LeftNode = node->getLeftNode();
    this->m_RightNode = node->getRightNode();
}

template<typename T>
Node<T>& Node<T>::operator=(const Node<T>& node)
{
    this->m_Character = node.getCharacter();
    this->m_Frequency = node.getFrequency();
    this->m_LeftNode = node.getLeftNode();
    this->m_RightNode = node.getRightNode();
    return *this;
}

template<typename T>
Node<T>& Node<T>::operator=(Node<T>&& node) noexcept
{
    this->m_Character = std::move(node.m_Character);
    this->m_Frequency = std::move(node.m_Frequency);
    this->m_LeftNode = std::move(node.m_LeftNode);
    this->m_RightNode = std::move(node.m_RightNode);
    return *this;
}

template<typename T>
void Node<T>::setBothNodes(std::shared_ptr<Node<T>> leftNode, std::shared_ptr<Node<T>> rightNode)
{
    this->m_LeftNode = leftNode;
    this->m_RightNode = rightNode;
}

template class BFCD::Node<char>;
