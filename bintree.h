#ifndef BINTREE_H
#define BINTREE_H
#include "nodedata.h"
#include <iostream>
#include <string>
using namespace std;

//---------------------------------------------------------------------------
// BinTree:  One BinTree object holds 3 nodes that forms a binary tree. It
// has a node pointing to a NodeData object that holds data. It also 2 other
// nodes that has pointers to the left and right.
//
// Implementation and assumptions:
//   -- the data will be stored in a different object
//   -- the data must be acces via the pointer on the node
//   -- most functions requires a recursive helper function to traverse the
//      binary tree
//   -- The binary tree should be traversed inorder

class BinTree {

    // overloaded <<: prints the binary tree
    friend ostream &operator<<(ostream &out, const BinTree &bt);

  private:
    struct Node {
        NodeData *data; // pointer to data object
        Node *left;     // left subtree pointer
        Node *right;    // right subtree pointer
    };
    Node *root; // root of the tree

    // Helper functions
    void inorderHelper(Node *curr, ostream &out) const;
    void inorderHelper(Node *curr, NodeData *arr[], int &i);
    void makeEmptyHelper(Node *curr);
    Node *copyHelper(Node *curr);
    bool equalsHelper(const Node *curr1, const Node *curr2) const;
    Node *arrayToBSTreeHelper(NodeData *arr[], int start, int end);
    bool retrieveHelper(Node *curr, const NodeData &nd, NodeData *&ndptr) const;
    bool removeHelper(Node *&current, const NodeData &target, NodeData *&ptr);
    void deleteCurrent(Node *&current, NodeData *&ptr);
    NodeData *findAndDeleteJustBigger(Node *&current);
    void sidewaysHelper(Node *current, int level) const;
    bool getSiblingHelper(Node *curr, Node *parent, const NodeData &nd,
                          NodeData &nd2) const;
    bool getParentHelper(Node *curr, Node *parent, const NodeData &nd,
                         NodeData &nd2) const;

  public:
    // default constructor, creates an empty tree
    BinTree();

    // copy constructor
    BinTree(const BinTree &bt);

    // destructor, calls makeEmpty()
    ~BinTree();

    // assignment operator
    BinTree &operator=(const BinTree &bt);

    // boolean comparison operators
    bool operator==(const BinTree &bt) const;
    bool operator!=(const BinTree &bt) const;

    // retrive a nodeData
    bool retrieve(const NodeData &nd, NodeData *&ndptr) const;

    // insert node data
    bool insert(NodeData *dataptr);

    // remove a NodeData*
    bool remove(const NodeData &target, NodeData *&ptr);

    // retrieve the NodeData sibling of a given object in the tree
    bool getSibling(const NodeData &nd, NodeData &nd2) const;

    // retrieve the NodeData parent of a given object in the tree
    bool getParent(const NodeData &nd, NodeData &nd2) const;

    // fill an array of NodeData* by using an inorder traversal of the tree
    void bstreeToArray(NodeData *[]);

    // build a balanced BinTree from a sorted array of NodeData*
    void arrayToBSTree(NodeData *[]);

    // make the tree empty
    void makeEmpty();

    // check if the tree is empty
    bool isEmpty() const;

    // display the tree sideways
    void displaySideways() const;
};

#endif