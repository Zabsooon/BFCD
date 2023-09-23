#include <utility>

namespace BFCD
{
    template<typename T>
    class Node
    {
    public:
        Node(char character, unsigned int frequency); // !Might not be usefull!
        Node(char character, unsigned int frequency, bool code);
        Node(char character, unsigned int frequency, bool code, Node<T>* leftNode, Node<T>* rightNode);
        Node(const Node<T>& node) = delete;
        Node(Node<T>&& node) noexcept;
        Node<T>& operator=(const Node<T>& node) = delete;
        Node<T>& operator=(Node<T>&& node) noexcept;

        [[nodiscard]] inline bool hasNext() const { return this->m_LeftNode != nullptr && this->m_RightNode != nullptr; }
        [[nodiscard]] inline bool hasLeft() const { return this->m_LeftNode != nullptr; }
        [[nodiscard]] inline bool hasRight() const { return this->m_RightNode != nullptr; }

        [[nodiscard]] inline char getCharacter() const { return this->m_Character; };
        [[nodiscard]] inline unsigned int getFrequency() const { return this->m_Frequency; };
        [[nodiscard]] inline unsigned int getCode() const { return this->m_Code; };

        inline Node<T>* getLeftNode() const { return this->m_LeftNode; };
        inline Node<T>* getRightNode() const { return this->m_RightNode; };
        inline void setLeftNode(Node<T>* node) { this->m_LeftNode = node; };
        inline void setRightNode(Node<T>* node) { this->m_RightNode = node; };
        void setBothNodes(Node<T>* leftNode, Node<T>* rightNode);

    private:
        T m_Character;
        unsigned int m_Frequency;
        bool m_Code;
        Node<T> *m_LeftNode;
        Node<T> *m_RightNode;
    };
} // namespace: BFCD