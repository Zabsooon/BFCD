#include "Node.hpp"

using namespace BFCD;

template<typename T>
Node<T>::Node(char character, unsigned int frequency, bool code)
    : m_Character(character),
    m_Frequency(frequency),
    m_Code(code),
    m_LeftNode(nullptr),
    m_RightNode(nullptr)
{}

template<typename T>
Node<T>::Node(char character, unsigned int frequency, bool code, Node* leftNode, Node* rightNode)
    : m_Character(character),
    m_Frequency(frequency),
    m_Code(code),
    m_LeftNode(leftNode),
    m_RightNode(rightNode)
{}

template<typename T>
Node<T>::Node(Node&& node) noexcept
    : m_Character(std::move(node.m_Character)),
    m_Frequency(std::move(node.m_Frequency)),
    m_Code(std::move(node.m_Code)),
    m_LeftNode(std::move(node.m_LeftNode)),
    m_RightNode(std::move(node.m_RightNode))
{}

template<typename T>
Node<T>& Node<T>::operator=(Node<T>&& node) noexcept
{
    this->m_Character = std::move(node.m_Character);
    this->m_Frequency = std::move(node.m_Frequency);
    this->m_Code = std::move(node.m_Code);
    this->m_LeftNode = std::move(node.m_LeftNode);
    this->m_RightNode = std::move(node.m_RightNode);
}