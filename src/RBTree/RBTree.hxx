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

    // Enum for the colors.
    enum class Color { Red, Black };

    // Template with the data types (Key and value) and the comparator (from std) for the keys.
    template <typename KeyType, typename ValueType, typename Comparator = std::less<KeyType>>
    class RedBlackTree {
    private:
        // Struct node.
        struct Node {
            // Pointers to right and left sons, along with the parent node.
            Node* parent;
            Node* left;
            Node* right;
            Color color;
            KeyType key;
            ValueType value;

            // Explicit constructor. Initializes all fields.
            explicit Node(const KeyType& key, const ValueType& value, Node* parent = nullptr, Node* left = nullptr, 
            Node* right = nullptr, Color color = Color::Red)
            : parent(parent), left(left), right(right), color(color), key(key), value(value) 
            {}

            //DECLARE_RULE5(Iterator, default);

            // Copy const. Copies member from other to current. Parent, left, and right are checked before copying.
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

            // Copy with operator. Checks that they are different first. Copies the params. Deletes current pointers and asign the new ones if possible.
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

            // Destructor.
            ~Node() {
                delete left;
                delete right;
            }
        };

    private:
        // Root node.
        Node* root;

    public:
        // Constructor that initializes the root node to null.
        RedBlackTree() : root(nullptr) {}

        // Copy constructor for RedBlackTree.If other has a root it copies it.
        RedBlackTree(const RedBlackTree& other) : root(nullptr) {
            if (other.root)
                root = new Node(*other.root);
        }

        // Constructor for the class. Copies the root to current if they are different.
        RedBlackTree& operator=(const RedBlackTree& other) {
            if (this != &other) {
                delete root;
                root = nullptr;

                if (other.root)
                    root = new Node(*other.root);
            }
            return *this; // The node.
        }

        // Destructor of the class. Deletes node root.
        ~RedBlackTree() { delete root; }

        class Iterator {
        private:
            Node* node;

        public:
            // Constructor of Iterator. Initializes a node for the class.
            explicit Iterator(Node* node) : node(node) {}

            //DECLARE_RULE5(Iterator, default);

            // Comparer for two nodes.
            inline bool operator!=(const Iterator& other) const {
                return this->node != other.node;
            }

            // Const getter for node key.
            inline const KeyType& getKey() const {
                assert(this->node);
                return this->node->key;
            }

            // Getter for node key.
            inline KeyType& getKey() {
                assert(this->node);
                return this->node->key;
            }

            // Getter for node value.
            inline ValueType& getValue() {
                assert(this->node);
                return this->node->value;
            }

            // Const getter for node value.
            inline const ValueType& getValue() const {
                assert(this->node);
                return this->node->value;
            }

            // Calls findNextNode() to go to the next node.
            inline Iterator& operator++() {
                this->node = findNextNode(this->node);
                return *this;
            }
        };

        // Returns the root of the tree. Uses findMinimum func.
        Iterator begin() {
            return Iterator(findMinimum(this->root));
        }

        // Returns null.
        Iterator end() {
            return Iterator(nullptr);
        }

        // Inserts node. (with key and value). Creates a new node with insertImp() and then invokes fixInsert for the new node to apply
        // necessary changes.
        void insert(const KeyType& key, const ValueType& value = ValueType()) {
            Node* newNode = insertImp(key, value);
            fixInsert(newNode);
        }

        // Operator [] to find value by key. Creates a node with findNode(). If it exists returns node value, else, calls insert()
        // and returns findNode(key) value.
        ValueType& operator[](const KeyType& key) {
            Node* node = findNode(key);
            if (node) {
                return node->value;
            } else {
                insert(key);
                return findNode(key)->value;
            }
        }

        // Calls printInOrder with the root.
        void printInOrder() const {
            printInOrder(root);
        }

    private:
        // Helper functions. These are used above.

        // Find node with the key given. returns the node. Creates a node equal to the root. Also std comparator compare
        // and starts comparing until it returns node. (Compare is minor).
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

        // Goes to the left to find minimum node.
        /*
        Node* findMinimum(Node* node) const {
            if (node) {
                while (node->left) {
                    node = node->left;
                }
            }

            return node;
        }*/

        static Node* findMinimum(Node* subtree)
        {
            if(subtree)
            {
                while (subtree->left)
                {
                    subtree = subtree->left;
                }
                
            }
            return subtree;
        }

        // Goes to the right to find maximum node.
        Node* findMaximum(Node* node) const {
            if (node) {
                while (node->right) {
                    node = node->right;
                }
            }

            return node;
        }

        // Check for right node, if it exists, and applys findMinimum() to the node. If theres no right node,
        // creates a node parent. While parent exists and node equals the right node, node equals parent and
        // parent equals grand parent.
        /*
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
        }*/

        static Node* findNextNode(Node* current)
        {
            Node* original = current;
            if(current->right)
                return RedBlackTree::findMinimum(current->right);
            while(current->parent && current  == current->parent->right)
            {
                current = current->parent;
                if(current->parent == nullptr)
                    return nullptr;
            }
            if (current->parent && current == current->parent->left)
            {
                current = current->parent;
            }
            return current == original? nullptr : current;
        }

        Node* insertImp(const KeyType& key, const ValueType& value) {
            // Initializes two nodes, parent and node. A comparator compare.
            Node* parent = nullptr;
            Node* node = root;
            Comparator compare;

            // While theres node, parent equals node and starts comparing keys.
            while (node) {
                parent = node;
                if (compare(key, node->key)) {
                    node = node->left;
                } else if (compare(node->key, key)) {
                    node = node->right;
                } else {
                    // The key already exists, so update the value.
                    // The right thing to do would be to store a ventor to store as many as necessary.
                    node->value = value;
                    return node;
                }
            }

            // Creates new node with the given params. If no parent then its the root. After checking, it compares keys
            // to rearrange.
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

        // Called after insertion to fix the tree. Param node.
        void fixInsert(Node* node) {
            // Node exists, isnt root and current parents color is red.
            while (node && node != root && node->parent->color == Color::Red) {
                // if node parent equals node parent parent left, creates uncle right and checks if it exists
                // and if its red. if true, changes node parent to black, uncle to black, grand parent to red
                // and sets current to grand parent.
                if (node->parent == node->parent->parent->left) {
                    Node* uncle = node->parent->parent->right;
                    if (uncle && uncle->color == Color::Red) {
                        node->parent->color = Color::Black;
                        uncle->color = Color::Black;
                        node->parent->parent->color = Color::Red;
                        node = node->parent->parent;
                    // If the conditions are not met, checks if current is the right son, id true, changes node to parent
                    // and rotates left current.
                    // node parent is set to black, grand parent to red, and rotates right currents grand parent.
                    } else {
                        if (node == node->parent->right) {
                            node = node->parent;
                            rotateLeft(node);
                        }
                        node->parent->color = Color::Black;
                        node->parent->parent->color = Color::Red;
                        rotateRight(node->parent->parent);
                    }
                // If conditions are not met, creates uncle but with left node. The logic is the same as above but with
                // the opposite node.
                } else {
                    Node* uncle = node->parent->parent->left;
                    if (uncle && uncle->color == Color::Red) {
                        node->parent->color = Color::Black;
                        uncle->color = Color::Black;
                        node->parent->parent->color = Color::Red;
                        node = node->parent->parent;
                    } else {
                        // In this case checks if its left son of parent. Rotates right.
                        if (node == node->parent->left) {
                            node = node->parent;
                            rotateRight(node);
                        }
                        node->parent->color = Color::Black;
                        node->parent->parent->color = Color::Red;
                        rotateLeft(node->parent->parent); // Rotate left.
                    }
                }
            }
            // changes root color to black.
            root->color = Color::Black;
        }

        // Rotations to fix and balance the tree. Algorithms from the internet.

        // Rotate left.
        void rotateLeft(Node* node) {
            // If theres no node or right son return.
            if (!node || !node->right) {
                return;
            }

            // Create a pivot which is the right of current. Right = left. If the pivot has left, 
            // the parent of left of pivot = current.
            Node* pivot = node->right;
            node->right = pivot->left;
            if (pivot->left) {
                pivot->left->parent = node;
            }
            // assign the node parent to pivot parent. If node has no parent, he is the root.
            pivot->parent = node->parent;
            if (!node->parent) {
                root = pivot;
            // If current node is left, turn to pivot. Else, turn right node to pivot.
            } else if (node == node->parent->left) {
                node->parent->left = pivot;
            } else {
                node->parent->right = pivot;
            }
            // pivot left = current. Current parent = pivot.
            pivot->left = node;
            node->parent = pivot;
        }

        // Rotate right.
        void rotateRight(Node* node) {
            // If theres no node or left son return.
            if (!node || !node->left) {
                return;
            }

            // Create a pivot which is the left of current. left = right. If the pivot has right, 
            // the parent of right of pivot = current.
            Node* pivot = node->left;
            node->left = pivot->right;
            if (pivot->right) {
                pivot->right->parent = node;
            }
            // assign the node parent to pivot parent. If node has no parent, he is the root.
            pivot->parent = node->parent;
            if (!node->parent) {
                root = pivot;
            // If current node is left, turn to pivot. Else, turn right node to pivot.
            } else if (node == node->parent->left) {
                node->parent->left = pivot;
            } else {
                node->parent->right = pivot;
            }
            // pivot right = current. Current parent = pivot.
            pivot->right = node;
            node->parent = pivot;
        }

        // Recursive function that prints the tree in order based on the keys. Prints the values.
        // It goes from left to right (which are the keys minor to mayor) and when there are no more nodes it starts going back.
        void printInOrder(Node* node) const {
            if (node) {
                printInOrder(node->left);
                std::cout << node->key << ": " << node->value << std::endl;
                printInOrder(node->right);
            }
        }
    };
}