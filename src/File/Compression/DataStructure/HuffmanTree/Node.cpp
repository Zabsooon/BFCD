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
Node<T>::Node(char character, unsigned int frequency, Node* leftNode, Node* rightNode)
    : m_Character(character),
    m_Frequency(frequency),
    m_LeftNode(leftNode),
    m_RightNode(rightNode)
{}

template<typename T>
Node<T>::Node(Node&& node) noexcept
    : m_Character(std::move(node.m_Character)),
    m_Frequency(std::move(node.m_Frequency)),
    m_LeftNode(std::move(node.m_LeftNode)),
    m_RightNode(std::move(node.m_RightNode))
{}

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
void Node<T>::setBothNodes(Node<T>* leftNode, Node<T>* rightNode)
{
    this->m_LeftNode = leftNode;
    this->m_RightNode = rightNode;
}

template class BFCD::Node<char>;
