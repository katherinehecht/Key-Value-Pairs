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
/*    if (root == nullptr)
    {
        Entry a(key, value);
        root = new Node{a, get_random(), nullptr, nullptr};
    }
    else*/
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
    deleteNode(root);
}

// Internal Functions ----------------------------------------------------------
Node *insert_r(Node *node, const std::string &key, const std::string &value) {

    if (node == nullptr)
    {
        Entry a(key, value);
        node = new Node{a, get_random(), nullptr, nullptr};
        return node;
    }

    if (key == node->entry.first)
        node->entry.second = value;

    else if (key <= node->entry.first)
    {
        node->left = insert_r(node->left, key, value);
        if (node->priority < node->left->priority)
            node = rotate_right(node);
    }
    else
    {
        node->right = insert_r(node->right, key, value);
        if (node->priority < node->right->priority)
            node = rotate_left(node);
    }
    return node;


/*  if (key == node->entry.first)
    {
        node->entry.second = value;
    }
    
    else if (key <= node->entry.first)
    {
        if (node->left == nullptr)
        {
            Entry a(key, value);
            Node *b = new Node{a, 0, nullptr, nullptr};
            node->left = b;
        }
        else
            node = insert_r(node->left, key, value);
//        if (node->left->priority > node->priority)
//            node = rotate_right(node);
    }
    else 
    {
        if (node->right == nullptr)
        {
            Entry a(key, value);
            Node *b = new Node{a, 0, nullptr, nullptr};
            node->right = b;
        }
        else
            node = insert_r(node->right, key, value);
//        if (node->right->priority > node->priority)
//            node = rotate_left(node);
    }
    return node;*/
}

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
