#pragma once

#include <cassert>
#include <iostream>

#define DECLARE_RULE5(Class, Action) \
    Class(const Class& other) = Action; \
    Class(Class&& other) = Action; \
    Class& operator=(const Class& other) = Action; \
    Class& operator=(Class&& other) = Action

#define DISABLE_COPY(Class) \
    DECLARE_RULE5(Class, delete);

namespace ecci {

    enum class Color {
        Red,
        Black
    };

    template <typename KeyType, typename ValueType, typename Comparator = std::less<KeyType>>
    class RedBlackTree {
    private:
        struct Node {
            Node* parent;
            Node* left;
            Node* right;
            Color color;
            KeyType key;
            ValueType value;

            explicit Node(const KeyType& key, const ValueType& value, Node* parent = nullptr,
                          Node* left = nullptr, Node* right = nullptr, Color color = Color::Red)
                : parent(parent),
                  left(left),
                  right(right),
                  color(color),
                  key(key),
                  value(value) {}

            DECLARE_RULE5(Node, delete);
            ~Node() {
                delete left;
                delete right;
            }
        };

    private:
        Node* root;

    public:
        RedBlackTree() : root(nullptr) {}
        ~RedBlackTree() { delete root; }

        class Iterator {
        private:
            Node* node;

        public:
            explicit Iterator(Node* node) : node(node) {}
            DECLARE_RULE5(Iterator, default);

            inline bool operator!=(const Iterator& other) const {
                return this->node != other.node;
            }

            inline const KeyType& getKey() const {
                assert(this->node);
                return this->node->key;
            }

            inline KeyType& getKey() {
                assert(this->node);
                return this->node->key;
            }

            inline ValueType& getValue() {
                assert(this->node);
                return this->node->value;
            }

            inline const ValueType& getValue() const {
                assert(this->node);
                return this->node->value;
            }

            inline Iterator& operator++() {
                this->node = findNextNode(this->node);
                return *this;
            }
        };

        Iterator begin() {
            return Iterator(findMinimum(this->root));
        }

        Iterator end() {
            return Iterator(nullptr);
        }

        void insert(const KeyType& key, const ValueType& value = ValueType()) {
            Node* newNode = insertImpl(key, value);
            fixInsertion(newNode);
        }

        ValueType& operator[](const KeyType& key) {
            Node* node = insertImpl(key);
            return node->value;
        }

        void printInOrder() const {
            printInOrder(root);
        }

    private:
        Node* insertImpl(const KeyType& key, const ValueType& value = ValueType()) {
            if (root == nullptr) {
                root = createNode(key, value, nullptr, nullptr, nullptr, Color::Black);
                return root;
            } else {
                Comparator comparator;
                Node* current = root;
                Node* parent = nullptr;

                while (current != nullptr) {
                    parent = current;

                    if (comparator(key, current->key))
                        current = current->left;
                    else if (comparator(current->key, key))
                        current = current->right;
                    else
                        return current;  // Node with the same key already exists
                }

                Node* newNode = createNode(key, value, parent, nullptr, nullptr, Color::Red);
                if (comparator(key, parent->key))
                    parent->left = newNode;
                else
                    parent->right = newNode;

                return newNode;
            }
        }

        Node* createNode(const KeyType& key, const ValueType& value, Node* parent, Node* left, Node* right,
                         Color color) {
            Node* newNode = new Node(key, value, parent, left, right, color);
            if (newNode == nullptr)
                throw std::runtime_error("RedBlackTree: No memory to create node");

            return newNode;
        }

        void fixInsertion(Node* newNode) {
            while (newNode->parent && newNode->parent->color == Color::Red) {
                if (newNode->parent == newNode->parent->parent->left) {
                    Node* uncle = newNode->parent->parent->right;

                    if (uncle && uncle->color == Color::Red) {
                        newNode->parent->color = Color::Black;
                        uncle->color = Color::Black;
                        newNode->parent->parent->color = Color::Red;
                        newNode = newNode->parent->parent;
                    } else {
                        if (newNode == newNode->parent->right) {
                            newNode = newNode->parent;
                            rotateLeft(newNode);
                        }

                        newNode->parent->color = Color::Black;
                        newNode->parent->parent->color = Color::Red;
                        rotateRight(newNode->parent->parent);
                    }
                } else {
                    Node* uncle = newNode->parent->parent->left;

                    if (uncle && uncle->color == Color::Red) {
                        newNode->parent->color = Color::Black;
                        uncle->color = Color::Black;
                        newNode->parent->parent->color = Color::Red;
                        newNode = newNode->parent->parent;
                    } else {
                        if (newNode == newNode->parent->left) {
                            newNode = newNode->parent;
                            rotateRight(newNode);
                        }

                        newNode->parent->color = Color::Black;
                        newNode->parent->parent->color = Color::Red;
                        rotateLeft(newNode->parent->parent);
                    }
                }
            }

            root->color = Color::Black;
        }

        void rotateLeft(Node* node) {
            Node* pivot = node->right;
            node->right = pivot->left;

            if (pivot->left != nullptr)
                pivot->left->parent = node;

            pivot->parent = node->parent;

            if (node->parent == nullptr)
                root = pivot;
            else if (node == node->parent->left)
                node->parent->left = pivot;
            else
                node->parent->right = pivot;

            pivot->left = node;
            node->parent = pivot;
        }

        void rotateRight(Node* node) {
            Node* pivot = node->left;
            node->left = pivot->right;

            if (pivot->right != nullptr)
                pivot->right->parent = node;

            pivot->parent = node->parent;

            if (node->parent == nullptr)
                root = pivot;
            else if (node == node->parent->right)
                node->parent->right = pivot;
            else
                node->parent->left = pivot;

            pivot->right = node;
            node->parent = pivot;
        }

        Node* findMinimum(Node* subtree) {
            if (subtree == nullptr)
                return nullptr;

            while (subtree->left != nullptr)
                subtree = subtree->left;

            return subtree;
        }

        Node* findNextNode(Node* current) {
            if (current->right != nullptr)
                return findMinimum(current->right);

            Node* parent = current->parent;

            while (parent != nullptr && current == parent->right) {
                current = parent;
                parent = parent->parent;
            }

            return parent;
        }

        void printInOrder(Node* node) const {
            if (node == nullptr)
                return;

            printInOrder(node->left);
            std::cout << node->key << ": " << node->value << std::endl;
            printInOrder(node->right);
        }
    };
}