#ifndef TREE_H
#define TREE_H

#include <iostream>
#include <vector>
#include <stdexcept>
#include <algorithm>

template <typename T>
class QuaternaryTree
{
private:
    struct Node
    {
        T value;
        std::vector<Node *> children;

        Node(T val) : value(val), children(4, nullptr) {}
    };

    Node *root;

    void destroyTree(Node *node)
    {
        if (!node)
            return;
        for (Node *child : node->children)
        {
            destroyTree(child);
        }
        delete node;
    }

    void printTree(Node *node, int depth = 0) const
    {
        if (!node)
            return;

        for (int i = 0; i < depth; i++)
        {
            std::cout << "  ";
        }
        std::cout << node->value << "\n";

        for (Node *child : node->children)
        {
            printTree(child, depth + 1);
        }
    }

public:
    QuaternaryTree() : root(nullptr) {}
    ~QuaternaryTree() { destroyTree(root); }

    void insert(const T &value, Node *parent = nullptr, int position = 0)
    {
        if (position < 0 || position > 3)
        {
            throw std::out_of_range("Position must be between 0 and 3");
        }
        if (!parent)
        {
            if (!root)
            {
                root = new Node(value);
            }
            else
            {
                throw std::runtime_error("Root already exists, specify parent");
            }
        }
        else
        {
            if (parent->children[position])
            {
                throw std::runtime_error("Position already occupied");
            }
            parent->children[position] = new Node(value);
        }
    }

    Node *getRoot() const
    {
        return root;
    }

    Node *getChild(Node *parent, int position) const
    {
        if (!parent)
        {
            throw std::invalid_argument("Parent node is null");
        }
        if (position < 0 || position > 3)
        {
            throw std::out_of_range("Position must be between 0 and 3");
        }
        return parent->children[position];
    }

    void print() const
    {
        printTree(root);
    }

    void sortStudentsByGrades(Node *groupNode)
    {
        if (!groupNode)
            return;

        std::sort(groupNode->children.begin(), groupNode->children.end(), [](Node *a, Node *b)
                  {
                      if (!a || !b)
                          return false;
                      return a->value < b->value; });
    }

    void sortSubjectsByType(Node *studentNode)
    {
        if (!studentNode)
            return;

        std::sort(studentNode->children.begin(), studentNode->children.end(), [](Node *a, Node *b)
                  {
                      if (!a || !b)
                          return false;
                      return a->value < b->value; });
    }
};

#endif