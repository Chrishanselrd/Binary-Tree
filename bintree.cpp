#include "bintree.h"
#include <iostream>

//----------------------------------------------------------------------------
// operator<<
// overloaded <<: prints the binary tree
ostream &operator<<(ostream &out, const BinTree &bt) {
    bt.inorderHelper(bt.root, out);
    out << endl;
    return out;
}

void BinTree::inorderHelper(Node *curr, ostream &out) const {
    if (curr == nullptr) {
        return;
    }
    inorderHelper(curr->left, out);
    out << *(curr->data) << " ";
    inorderHelper(curr->right, out);
}

//----------------------------------------------------------------------------
// default constructor
// constructs a binary tree
BinTree::BinTree() { root = nullptr; }

//----------------------------------------------------------------------------
// copy constructor
// constructs a copy of a binary tree
BinTree::BinTree(const BinTree &bt) { root = copyHelper(bt.root); }

BinTree::Node *BinTree::copyHelper(Node *curr) {
    if (curr == nullptr) {
        return nullptr;
    }
    Node *newNode = new Node;
    newNode->data = new NodeData(*(curr->data));
    newNode->left = copyHelper(curr->left);
    newNode->right = copyHelper(curr->right);
    return newNode;
}

//----------------------------------------------------------------------------
// destructor
// frees up allocated memory
BinTree::~BinTree() { makeEmpty(); }

//----------------------------------------------------------------------------
// operator=
// Overloaded =: assigns a binary tree
BinTree &BinTree::operator=(const BinTree &bt) {
    if (this == &bt) {
        return *this;
    }
    makeEmpty();
    root = copyHelper(bt.root);
    return *this;
}

//----------------------------------------------------------------------------
// operator==
// Overloaded ==: current obj == parameter
bool BinTree::operator==(const BinTree &bt) const {
    return equalsHelper(root, bt.root);
}

bool BinTree::equalsHelper(const Node *ptr1, const Node *ptr2) const {
    if (ptr1 == nullptr && ptr2 == nullptr) {
        return true;
    }
    if (ptr1 == nullptr || ptr2 == nullptr) {
        return false;
    }
    if (*(ptr1->data) != *(ptr2->data)) {
        return false;
    }
    // recursively check the left and right subtrees
    return equalsHelper(ptr1->left, ptr2->left) &&
           equalsHelper(ptr1->right, ptr2->right);
}

//----------------------------------------------------------------------------
// operator!=
// Overloaded !=: current obj != parameter
bool BinTree::operator!=(const BinTree &bt) const { return !(*this == bt); }

//----------------------------------------------------------------------------
// retrive
// retrieve a NodeData* of a given object in the tree
bool BinTree::retrieve(const NodeData &nd, NodeData *&ndptr) const {
    return retrieveHelper(root, nd, ndptr);
}

bool BinTree::retrieveHelper(Node *curr, const NodeData &nd,
                             NodeData *&ndptr) const {
    if (curr == nullptr) {
        return false;
    }
    if (*(curr->data) == nd) {
        ndptr = curr->data;
        return true;
    }
    if (retrieveHelper(curr->left, nd, ndptr) ||
        retrieveHelper(curr->right, nd, ndptr)) {
        return true;
    }
    return false;
}

//----------------------------------------------------------------------------
// insert
// insert a node data
bool BinTree::insert(NodeData *dataptr) {
    if (dataptr == nullptr) {
        return false;
    }

    Node *ptr = new Node;
    ptr->data = dataptr;
    ptr->left = ptr->right = nullptr;

    if (isEmpty()) {
        root = ptr;
        return true;
    } else {
        Node *current = root;
        bool inserted = false;

        while (!inserted) {
            // if item is less than current item, insert in left subtree
            if (*ptr->data < *current->data) {
                if (current->left == nullptr) { // at leaf, insert left
                    current->left = ptr;
                    inserted = true;
                } else
                    current = current->left; // one step left
            }

            // if item is more than current item, insert in right subtree
            else if (*ptr->data > *current->data) {
                if (current->right == nullptr) { // at leaf, insert right
                    current->right = ptr;
                    inserted = true;
                } else
                    current = current->right; // one step right
            }

            // if item is equal to current item, free up memory
            else {
                delete ptr;
                ptr = nullptr;
                return false;
            }
        }
    }
    return true;
}

//----------------------------------------------------------------------------
// remove
// remove a NodeData*
bool BinTree::remove(const NodeData &target, NodeData *&ptr) {
    return removeHelper(root, target, ptr);
}

bool BinTree::removeHelper(Node *&current, const NodeData &target,
                           NodeData *&ptr) {
    if (current == nullptr) {
        return false;
    }

    // found item to remove
    if (target == *current->data) {
        deleteCurrent(current, ptr);
        return true;
    }
    if (target < *current->data) {
        return removeHelper(current->left, target, ptr);
    }

    // target >= *current->data
    return removeHelper(current->right, target, ptr);
}

void BinTree::deleteCurrent(Node *&current, NodeData *&ptr) {
    // current has no children
    if (current->left == nullptr && current->right == nullptr) {
        ptr = current->data;
        delete current;
        current = nullptr;
    }

    // current has only right child
    else if (current->left == nullptr) {
        Node *temp = current;
        current = current->right;
        ptr = temp->data;
        delete temp;
    }

    // current has only left child
    else if (current->right == nullptr) {
        Node *temp = current;
        current = current->left;
        ptr = temp->data;
        delete temp;
    }

    // current has two children
    else {
        ptr = current->data;
        current->data = findAndDeleteJustBigger(current->right);
    }
}

NodeData *BinTree::findAndDeleteJustBigger(Node *&current) {
    if (current->left == nullptr) {
        NodeData *item = current->data;
        Node *junk = current;
        current = current->right;
        delete junk;
        return item;
    }
    return findAndDeleteJustBigger(current->left);
}

//----------------------------------------------------------------------------
// getSibling
// retrieve the NodeData sibling of a given object in the tree
// bool BinTree::getSibling(const NodeData &nd, NodeData &nd2) const {
//     Node *curr = root;
//     Node *parent = nullptr;
//     while (curr != nullptr) {
//         if (*(curr->data) == nd) {
//             if (parent != nullptr) {
//                 if (parent->left == curr) {
//                     nd2 = *(parent->right->data);
//                     return true;
//                 } else {
//                     nd2 = *(parent->left->data);
//                     return true;
//                 }
//             } else {
//                 return false;
//             }
//         }
//         parent = curr;
//         if (nd < *(curr->data)) {
//             curr = curr->left;
//         } else {
//             curr = curr->right;
//         }
//     }
//     return false;
// }

bool BinTree::getSibling(const NodeData &nd, NodeData &nd2) const {
    return getSiblingHelper(root, nullptr, nd, nd2);
}

bool BinTree::getSiblingHelper(Node *curr, Node *parent, const NodeData &nd,
                               NodeData &nd2) const {
    if (curr == nullptr) {
        return false;
    }

    if (*(curr->data) == nd) {
        if (parent != nullptr) {
            if (parent->left == curr) {
                nd2 = *(parent->right->data);
                return true;
            } else {
                nd2 = *(parent->left->data);
                return true;
            }
        } else {
            return false;
        }
    }

    bool found = getSiblingHelper(curr->left, curr, nd, nd2);
    if (!found) {
        found = getSiblingHelper(curr->right, curr, nd, nd2);
    }

    return found;
}

//----------------------------------------------------------------------------
// getParent
// retrieve the NodeData parent of a given object in the tree
bool BinTree::getParent(const NodeData &nd, NodeData &nd2) const {
    return getParentHelper(root, nullptr, nd, nd2);
}

bool BinTree::getParentHelper(Node *curr, Node *parent, const NodeData &nd,
                              NodeData &nd2) const {
    if (curr == nullptr) {
        return false;
    }

    if (*(curr->data) == nd) {
        if (parent != nullptr) {
            nd2 = *(parent->data);
            return true;
        } else {
            return false;
        }
    }

    bool found = getParentHelper(curr->left, curr, nd, nd2);
    if (!found) {
        found = getParentHelper(curr->right, curr, nd, nd2);
    }

    return found;
}

//----------------------------------------------------------------------------
// bstreeToArray
// fill an array of NodeData* by using an inorder traversal of the tree
void BinTree::bstreeToArray(NodeData *arr[]) {
    int i = 0;
    inorderHelper(root, arr, i);
    makeEmpty();
}

void BinTree::inorderHelper(Node *curr, NodeData *arr[], int &i) {
    if (curr == nullptr) {
        return;
    }
    inorderHelper(curr->left, arr, i);
    arr[i++] = curr->data;
    curr->data = nullptr;
    inorderHelper(curr->right, arr, i);
}

//----------------------------------------------------------------------------
// arrayToBSTree
// build a balanced BinTree from a sorted array of NodeData*
void BinTree::arrayToBSTree(NodeData *arr[]) {
    int n = 0;
    while (arr[n] != nullptr) {
        n++;
    }
    root = arrayToBSTreeHelper(arr, 0, n - 1);
}

BinTree::Node *BinTree::arrayToBSTreeHelper(NodeData *arr[], int start,
                                            int end) {
    if (start > end) {
        return nullptr;
    }
    int mid = (start + end) / 2;
    Node *curr = new Node();
    curr->data = arr[mid];
    curr->left = arrayToBSTreeHelper(arr, start, mid - 1);
    curr->right = arrayToBSTreeHelper(arr, mid + 1, end);
    return curr;
}

//----------------------------------------------------------------------------
// makeEmpty
// make the tree empty
void BinTree::makeEmpty() {
    makeEmptyHelper(root);
    root = nullptr;
}

void BinTree::makeEmptyHelper(Node *curr) {
    if (curr == nullptr) {
        return;
    }
    makeEmptyHelper(curr->left);
    makeEmptyHelper(curr->right);
    delete curr->data;
    curr->data = nullptr;
    delete curr;
    curr = nullptr;
}

//----------------------------------------------------------------------------
// isEmpty
// check if the tree is empty
bool BinTree::isEmpty() const { return root == nullptr; }

//----------------------------------------------------------------------------
// displaySideways
// display the tree sideways
void BinTree::displaySideways() const { sidewaysHelper(root, 0); }

void BinTree::sidewaysHelper(Node *current, int level) const {
    if (current != nullptr) {
        level++;
        sidewaysHelper(current->right, level);

        // indent for readability, same number of spaces per depth level
        for (int i = level; i >= 0; i--) {
            cout << "        ";
        }

        cout << *current->data << endl; // display information of object
        sidewaysHelper(current->left, level);
    }
}
