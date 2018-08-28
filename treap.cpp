//Katherine Hecht, Julia Hughes, Richard Stefanik
// treap.cpp: Treap Map

#include "map.h"

#include <climits>
#include <random>

// Prototypes ------------------------------------------------------------------

static Node *insert_r(Node *node, const std::string &key, const std::string &value);
extern Node *search_r(Node *node, const std::string &key);
extern void dump_r(Node *node, std::ostream &os, DumpFlag flag);
extern void deleteNode(Node *);
static Node *rotate_right(Node *p);
static Node *rotate_left(Node *p);
static int get_random();

// Methods ---------------------------------------------------------------------

void TreapMap::insert(const std::string &key, const std::string &value) {
    root  = insert_r(root, key, value);
}

const Entry TreapMap::search(const std::string &key) {
    return search_r(root, key) == nullptr ? NONE : search_r(root, key)->entry;
}

void TreapMap::dump(std::ostream &os, DumpFlag flag) {
    dump_r(root, os, flag);
}

TreapMap::~TreapMap()
{
    //deleteNode function found in bst.cpp
    deleteNode(root);
}

// Internal Functions ----------------------------------------------------------
// Insert recursively, making sure to main both the bst and heap properties.
Node *insert_r(Node *node, const std::string &key, const std::string &value) {

    if (node == nullptr)
    {
        Entry a(key, value);
        node = new Node{a, get_random(), nullptr, nullptr};
        return node;
    }

    //Key found, so update its value
    if (key == node->entry.first)
        node->entry.second = value;

    //Insert into left subtree
    else if (key <= node->entry.first)
    {
        node->left = insert_r(node->left, key, value);
        //After finished inserting, check if priorities still maintain
        //heap proerty.  If not, perform right rotation.
        if (node->priority < node->left->priority)
            node = rotate_right(node);
    }
    //Insert into right subtree
    else if (key > node->entry.first)
    {
        node->right = insert_r(node->right, key, value);
        //After finished inserting, check if priorities still maintain
        //heap proerty.  If not, perform left rotation.
        if (node->priority < node->right->priority)
            node = rotate_left(node);
    }
    return node;
}

/*      Rotate Right
//     p             c
//    / \           / \
//   c   T3  -->   T1  p
//  / \               / \
// T1  T2            T2  T3 */

Node *rotate_right(Node *p) {
    if (p == nullptr)
        return nullptr;
    else
    {
        Node * c = p->left;
        if (c != nullptr)
        {
            Node * T2 = c->right;
            c->right = p;
            p->left = T2;
        }
        return c;
    }
    return nullptr;
}

/*      Rotate Left
//     p             c
//    / \           / \
//   T1  c  -->    p   T3
//      / \       / \
//     T2  T3   T1  T2    */

Node *rotate_left(Node *p) {
    if (p == nullptr)
        return nullptr;
    else
    {
        Node * c = p->right;
        if (c != nullptr)
        {
            Node * T2 = c->left;
            c->left = p;
            p->right = T2;
        }
        return c;
    }

    return nullptr;
}

int get_random() {
    std :: random_device rd;
    std :: default_random_engine g(rd());
    std :: uniform_int_distribution <>  d( 1 , INT_MAX );
    return d(g);
}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
