#pragma once
#include <cassert>
#include <iostream>

#define DECLARE_RULE5(Class, Action)\
    Class(const Class& other) = Action;\
    Class(Class&& other) = Action;\
    Class& operator= (const Class& other) = Action;\
    Class& operator= (Class&& other) = Action

#define DISABLE_COPY(Class)\
    DECLARE_RULE5(Class, delete);

namespace ecci 
{
    template <typename DataType>
    struct Less
    {
        inline bool operator()(const DataType& value1, const DataType& value2)
        {
            return value1 < value2;
        }
    };
    template <typename DataType>
    struct Greater
    {
        inline bool operator()(const DataType& value1, const DataType& value2)
        {
            return value1 > value2;
        }
    };    
    
    template <typename KeyType, typename ValueType, typename Comparator = Less<KeyType>>
    class Map
    {
        DISABLE_COPY(Map);
      private:
        struct Node
        {
          public:
            Node* parent;
            KeyType key;
            ValueType value;
            Node* left;
            Node* right;
            explicit Node(const KeyType& key, const ValueType & value = ValueType()
                , Node* parent = nullptr, Node* left = nullptr, Node* right = nullptr)
                : parent(parent)
                , key(key)
                , value(value)
                , left(left)
                , right(right)
            {                
            }
            DECLARE_RULE5(Node, delete);
            ~Node()
            {
                delete this->left;
                delete this->right;
            }

        };
      private:
        size_t count;
        Node* root;
      public:
        Map()
            : count(0)
            , root(nullptr)
        {            
        }
        ~Map()
        {
            delete this->root;
        }
      public:
        inline bool isEmpty()const {return this->root == nullptr;}
        inline size_t getCount()const {return this->count;}

      public:
        void insert(const KeyType& key, const ValueType& value = ValueType())
        {
            this->insertImpl(key, value);
        }
        ValueType& operator[] (const KeyType key){
            Node* node = this->insertImpl(key);
            return node->value;
        }

        class Iterator
        {            
          private:
            Node* node;
          public:
            explicit Iterator(Node* node) 
                : node(node)
            {                
            }
            DECLARE_RULE5(Iterator, default);
            inline bool operator != (const Iterator& other) const 
            {
                return this->node != other.node;
            }
            inline const KeyType& getKey() const
            {
                assert(this->node);
                return this->node->key;
            }
            inline KeyType& getKey()
            {
                assert(this->node);
                return this->node->key;
            }
            inline ValueType& getValue()
            {
                assert(this->node);
                return this->node->value;
            }
            inline const ValueType& getValue()const
            {
                assert(this->node);
                return this->node->value;
            }
            inline Iterator& operator ++()
            {
                this->node = Map::findNextNode(this->node);
                return *this;
            }
        };
        Iterator begin()
        {
            return Iterator(this->findMinimum(this->root));
        }
        Iterator end()
        {
            return Iterator(nullptr);
        }
        Node* insertImpl(const KeyType& key, const ValueType& value = ValueType())
        {
            if(this->isEmpty())
            {
                return this->root = this->createNode(key, value);
            }
            else
            {
                Comparator comparator;
                Node* current = this->root; 
                while(true)
                {  
                    if(comparator(key, current->key))
                    {
                        if(current->left == nullptr)
                            return current->left = this->createNode(key, value, current);
                        else
                         current = current->left;
                    }
                    else if(comparator(current->key, key))
                    {
                        if(current->right == nullptr)
                            return current->right = this->createNode(key, value, current);
                        else
                         current = current->right;
                    }
                    else
                        return current;
                }
            }
        }
        Node* createNode(const KeyType& key, const ValueType& value = ValueType(), Node* parent = nullptr)
        {
            Node* newNode = new Node(key, value, parent);
            if(newNode == nullptr)
                throw std::runtime_error("map: no memory to create node");
            ++ this->count;
            return newNode;
        }
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
        static Node* findNextNode(Node* current)
        {
            Node* original = current;
            if(current->right)
                return Map::findMinimum(current->right);
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
    };
}