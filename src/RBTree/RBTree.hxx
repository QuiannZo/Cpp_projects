#pragma once

#include <cassert>
#include <iostream>

/*
#define DECLARE_RULE5(Class, Action) \
    Class(const Class& other) = Action; \
    Class(Class&& other) = Action; \
    Class& operator=(const Class& other) = Action; \
    Class& operator=(Class&& other) = Action

#define DISABLE_COPY(Class) \
    DECLARE_RULE5(Class, delete);

#define ENABLE_COPY(Class) \
    DECLARE_RULE5(Class, default);*/

// El constructor por default de las copias no sirve porque se requiere copiar los campos, entonces se hizo manual.
// No pude hacerlo con macros. 

namespace ecci {

    enum class Color { Red, Black };

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

            explicit Node(const KeyType& key, const ValueType& value, Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr, Color color = Color::Red)
            : parent(parent), left(left), right(right), color(color), key(key), value(value) 
            {}

            //DECLARE_RULE5(Iterator, default);

            Node(const Node& other) : parent(nullptr), left(nullptr), right(nullptr), color(other.color), key(other.key), value(other.value) {
                if (other.left)
                    left = new Node(*other.left);
                if (other.right)
                    right = new Node(*other.right);
                if (left)
                    left->parent = this;
                if (right)
                    right->parent = this;
            }

            Node& operator=(const Node& other) {
                if (this != &other) {
                    color = other.color;
                    key = other.key;
                    value = other.value;

                    delete left;
                    delete right;

                    left = nullptr;
                    right = nullptr;

                    if (other.left)
                        left = new Node(*other.left);
                    if (other.right)
                        right = new Node(*other.right);

                    if (left)
                        left->parent = this;
                    if (right)
                        right->parent = this;
                }
                return *this;
            }

            ~Node() {
                delete left;
                delete right;
            }
        };

    private:
        Node* root;

    public:
        RedBlackTree() : root(nullptr) {}

        RedBlackTree(const RedBlackTree& other) : root(nullptr) {
            if (other.root)
                root = new Node(*other.root);
        }

        RedBlackTree& operator=(const RedBlackTree& other) {
            if (this != &other) {
                delete root;
                root = nullptr;

                if (other.root)
                    root = new Node(*other.root);
            }
            return *this;
        }

        ~RedBlackTree() { delete root; }

        class Iterator {
        private:
            Node* node;

        public:
            explicit Iterator(Node* node) : node(node) {}

            //DECLARE_RULE5(Iterator, default);

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
            Node* node = findNode(key);
            if (node) {
                return node->value;
            } else {
                insert(key);
                return findNode(key)->value;
            }
        }

        void printInOrder() const {
            printInOrder(root);
        }

    private:
        // Helper functions

        Node* findNode(const KeyType& key) const {
            Node* node = root;
            Comparator compare;

            while (node) {
                if (compare(key, node->key)) {
                    node = node->left;
                } else if (compare(node->key, key)) {
                    node = node->right;
                } else {
                    return node;
                }
            }

            return nullptr;
        }

        Node* findMinimum(Node* node) const {
            if (node) {
                while (node->left) {
                    node = node->left;
                }
            }

            return node;
        }

        Node* findMaximum(Node* node) const {
            if (node) {
                while (node->right) {
                    node = node->right;
                }
            }

            return node;
        }

        Node* findNextNode(Node* node) const {
            if (node) {
                if (node->right) {
                    return findMinimum(node->right);
                } else {
                    Node* parent = node->parent;
                    while (parent && node == parent->right) {
                        node = parent;
                        parent = parent->parent;
                    }
                    return parent;
                }
            }

            return nullptr;
        }

        Node* insertImpl(const KeyType& key, const ValueType& value) {
            Node* parent = nullptr;
            Node* node = root;
            Comparator compare;

            while (node) {
                parent = node;
                if (compare(key, node->key)) {
                    node = node->left;
                } else if (compare(node->key, key)) {
                    node = node->right;
                } else {
                    // The key already exists, so update the value.
                    node->value = value;
                    return node;
                }
            }

            Node* newNode = new Node(key, value, parent);
            if (!parent) {
                root = newNode;
            } else if (compare(key, parent->key)) {
                parent->left = newNode;
            } else {
                parent->right = newNode;
            }

            return newNode;
        }

        void fixInsertion(Node* node) {
            while (node && node != root && node->parent->color == Color::Red) {
                if (node->parent == node->parent->parent->left) {
                    Node* uncle = node->parent->parent->right;
                    if (uncle && uncle->color == Color::Red) {
                        node->parent->color = Color::Black;
                        uncle->color = Color::Black;
                        node->parent->parent->color = Color::Red;
                        node = node->parent->parent;
                    } else {
                        if (node == node->parent->right) {
                            node = node->parent;
                            rotateLeft(node);
                        }
                        node->parent->color = Color::Black;
                        node->parent->parent->color = Color::Red;
                        rotateRight(node->parent->parent);
                    }
                } else {
                    Node* uncle = node->parent->parent->left;
                    if (uncle && uncle->color == Color::Red) {
                        node->parent->color = Color::Black;
                        uncle->color = Color::Black;
                        node->parent->parent->color = Color::Red;
                        node = node->parent->parent;
                    } else {
                        if (node == node->parent->left) {
                            node = node->parent;
                            rotateRight(node);
                        }
                        node->parent->color = Color::Black;
                        node->parent->parent->color = Color::Red;
                        rotateLeft(node->parent->parent);
                    }
                }
            }

            root->color = Color::Black;
        }

        void rotateLeft(Node* node) {
            if (!node || !node->right) {
                return;
            }

            Node* pivot = node->right;
            node->right = pivot->left;
            if (pivot->left) {
                pivot->left->parent = node;
            }
            pivot->parent = node->parent;
            if (!node->parent) {
                root = pivot;
            } else if (node == node->parent->left) {
                node->parent->left = pivot;
            } else {
                node->parent->right = pivot;
            }
            pivot->left = node;
            node->parent = pivot;
        }

        void rotateRight(Node* node) {
            if (!node || !node->left) {
                return;
            }

            Node* pivot = node->left;
            node->left = pivot->right;
            if (pivot->right) {
                pivot->right->parent = node;
            }
            pivot->parent = node->parent;
            if (!node->parent) {
                root = pivot;
            } else if (node == node->parent->left) {
                node->parent->left = pivot;
            } else {
                node->parent->right = pivot;
            }
            pivot->right = node;
            node->parent = pivot;
        }

        void printInOrder(Node* node) const {
            if (node) {
                printInOrder(node->left);
                std::cout << node->key << ": " << node->value << std::endl;
                printInOrder(node->right);
            }
        }
    };
}