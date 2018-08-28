// Katherine Hecht, Julia Hughes, Richard Stefanik
// bst.cpp: BST Map

#include "map.h"

#include <stdexcept>

// Prototypes ------------------------------------------------------------------

Node *insert_r(Node *node, const std::string &key, const std::string &value);
Node *search_r(Node *node, const std::string &key);
void    dump_r(Node *node, std::ostream &os, DumpFlag flag);
void deleteNode(Node *);

// Methods ---------------------------------------------------------------------

void BSTMap::insert(const std::string &key, const std::string &value) {
    //If nothing is in the tree, make this entry the root
    if (root == nullptr)
    {
        Entry a(key, value);
        root = new Node{a, 0, nullptr, nullptr};
    }
    else
        Node * c = insert_r(root, key, value);
//   dump(std::cout, DUMP_KEY_VALUE); 
}

const Entry BSTMap::search(const std::string &key) {
    return search_r(root, key) == nullptr ? NONE : search_r(root, key)->entry;
}

void BSTMap::dump(std::ostream &os, DumpFlag flag) {
    dump_r(root, os, flag);
}

BSTMap::~BSTMap()
{
    deleteNode(root);
}

// Internal Functions ----------------------------------------------------------
void deleteNode(Node * a)
{
    //Delete parent, then delete its left child and right child
    if (a == nullptr)
        return;
    Node * left = a->left;
    Node * right = a->right;
    delete a;

    deleteNode(left);
    deleteNode(right);
}


//Insertion using the properties of a bst to make process quicker
Node *insert_r(Node *node, const std::string &key, const std::string &value) {
    //Key found in the bst, so update its value
    if (key == node->entry.first)
    {
        node->entry.second = value;
    }
    

    //Go down left subtree
    else if (key <= node->entry.first)
    {
        if (node->left == nullptr)
        {
            Entry a(key, value);
            node->left = new Node{a, 0, nullptr, nullptr};
        }
        else
            node = insert_r(node->left, key, value);
    }
    //Go down right subtree
    else 
    {
        if (node->right == nullptr)
        {
            Entry a(key, value);
            node->right = new Node{a, 0, nullptr, nullptr};
        }
        else
            node = insert_r(node->right, key, value);
    }
    return node;
}

//Binary search to find given key
Node *search_r(Node *node, const std::string &key) {
    if (node == nullptr)
        return nullptr;
    //Key found
    if (node->entry.first == key)
        return node;
    //Search left subtree
    else if (key <= node->entry.first)
        return search_r(node->left, key);
    //Search right subtree
    else
        return search_r(node->right, key);

    return nullptr;
}

void dump_r(Node *node, std::ostream &os, DumpFlag flag) {
    //In order traversal
    if (node == nullptr)
        return;

    dump_r(node->left, os, flag);
   
    switch (flag) {
        case DUMP_KEY:          os << node->entry.first  << std::endl; break;
        case DUMP_VALUE:        os << node->entry.second << std::endl; break;
        case DUMP_KEY_VALUE:    os << node->entry.first  << "\t" << node->entry.second << std::endl; break;
        case DUMP_VALUE_KEY:    os << node->entry.second << "\t" << node->entry.first  << std::endl; break;
    }

    dump_r(node->right, os, flag);
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
