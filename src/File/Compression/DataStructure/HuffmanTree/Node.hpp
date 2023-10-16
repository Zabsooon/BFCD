#pragma once

#include <utility>
#include <memory>

namespace BFCD
{
    template<typename T>
    class Node
    {
    public:
        Node();
        Node(char character = 0, unsigned int frequency = 0, std::shared_ptr<Node<T>> leftNode = nullptr, std::shared_ptr<Node<T>> rightNode = nullptr);
        Node(const Node<T>& node);
        Node(Node<T>&& node) noexcept;
        Node(std::shared_ptr<Node<T>>& node);
        Node<T>& operator=(const Node<T>& node);
        Node<T>& operator=(Node<T>&& node) noexcept;

        [[nodiscard]] inline bool hasNext() const { return this->m_LeftNode != nullptr && this->m_RightNode != nullptr; }
        [[nodiscard]] inline bool hasLeft() const { return this->m_LeftNode != nullptr; }
        [[nodiscard]] inline bool hasRight() const { return this->m_RightNode != nullptr; }

        [[nodiscard]] inline char getCharacter() const { return this->m_Character; };
        [[nodiscard]] inline unsigned int getFrequency() const { return this->m_Frequency; };

        [[nodiscard]] inline std::shared_ptr<Node<T>> getLeftNode() const { return this->m_LeftNode; };
        [[nodiscard]] inline std::shared_ptr<Node<T>> getRightNode() const { return this->m_RightNode; };
        inline void setLeftNode(std::shared_ptr<Node<T>> node) { this->m_LeftNode = node; };
        inline void setRightNode(std::shared_ptr<Node<T>> node) { this->m_RightNode = node; };
        void setBothNodes(std::shared_ptr<Node<T>> leftNode, std::shared_ptr<Node<T>> rightNode);

    private:
        T m_Character;
        unsigned int m_Frequency;
        std::shared_ptr<Node<T>> m_LeftNode;
        std::shared_ptr<Node<T>> m_RightNode;
    };
} // namespace: BFCD
