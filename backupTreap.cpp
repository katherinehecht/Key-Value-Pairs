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
//static void rotate_r(Node *);
static bool isHeap(Node *);
static void rotate_tree(Node *, Node *, std::string);

// Methods ---------------------------------------------------------------------

void TreapMap::insert(const std::string &key, const std::string &value) {
    std::cout << "Called Insert" << std::endl;
    if (root == nullptr)
    {
        Entry a(key, value);
        root = new Node{a, get_random(), nullptr, nullptr};
    }
    else
    {
        Node * c = insert_r(root, key, value);
  /*      if (c->right != nullptr)
        {
            if (c->priority < c->right->priority)
                Node* d = rotate_left(c); 
        }
        if (c->left != nullptr)
        {
            if (c->priority < c->left->priority)
                Node* d = rotate_right(c); 
        }*/
        while (!isHeap(root))
        {
            std::cout << "in while loop" << std::endl;
            rotate_root();
            std::cout << "after rotate root" << std::endl;
            if (isHeap(root))
                break;
            rotate_tree(root->left, root, "left");
            std::cout << "after rotate tree left" << std::endl;
            if (isHeap(root))
                break;
            rotate_tree(root->right, root, "right");
            std::cout << "after rotate tree right" << std::endl;
        }
    }  
    std::cout << "Leaving insert" << std::endl;
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

void TreapMap::rotate_root()
{
    if (root->left != nullptr)
    {
        if (root->priority <= root->left->priority)
            root = rotate_right(root);
    }
    else if (root->right != nullptr)
    {
        if (root->priority <= root->right->priority)
            root = rotate_left(root);
    }
}



// Internal Functions ----------------------------------------------------------
Node *insert_r(Node *node, const std::string &key, const std::string &value) {
    if (key == node->entry.first)
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
    }
    return node;
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

static bool isHeap(Node *a)
{
    if (a == nullptr)
        return true;
    if ((a->left == nullptr) && (a->right == nullptr))
        return true;
    if (a->left != nullptr)
    {
        if (a->left->entry.first >= a->entry.first)
            return false;
    }    
    if (a->right != nullptr)
    {
        if (a->right->entry.first >= a->entry.first)
            return false;
    }
    return isHeap(a->left) && isHeap(a->right);
}

static void rotate_tree(Node * child, Node * parent, std::string c)
{
    if (parent == nullptr)
        return;
    if (child == nullptr)
        return;
    int cVal = child->priority;
    if (c == "left")
    {
        if (cVal <= child->left->priority)
            parent->left = rotate_right(child);
        
        else if (cVal <= child->right->priority)
            parent->left = rotate_left(child);
    }
    else if (c == "right") 
    {
        if (cVal <= child->right->priority)
            parent->right = rotate_left(child);
        else if (cVal <= child->left->priority)
            parent->right = rotate_right(child);
    }
    rotate_tree(child->left, child, "left");
    rotate_tree(child->right, child, "right");

}

// vim: set sts=4 sw=4 ts=8 expandtab ft=cpp:
