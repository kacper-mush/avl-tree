#include "avl.h"

class AVL::node {
   public:
    int data;     // store data in AVL
    node* left;   // point to left node
    node* right;  // point to right node
    int height;   // the maximum path from specified node to leaves
    int size;     // how many node in the tree
    node(int value)
        : data(value), left(NULL), right(NULL), height(1), size(1) {}
};

int AVL::size(node* current) {
    if (current == NULL) return 0;
    return current->size;
}

void AVL::updateSize(node* current) {
    if (current != NULL) {
        current->size = size(current->left) + size(current->right) + 1;
    }
}

// to return height of node
int AVL::height(node* current) {
    if (current == NULL) return 0;
    return current->height;
}

void AVL::updateHeight(node* current) {
    if (current != NULL) {
        current->height =
            1 + max(height(current->left), height(current->right));
    }
}

// function to calculate the maximum value from specified node
int AVL::maxUtility(node* current) {
    if (current->right == NULL)
        return current->data;
    else
        return maxUtility(current->right);
}

int AVL::balance(node* current) {
    return height(current->left) - height(current->right);
}

// right rotation if not balanced in the left
AVL::node* AVL::rightRotation(node* topMost) {
    node* middle = topMost->left;
    topMost->left = middle->right;
    middle->right = topMost;
    // Middle is now on top, first update the lower node
    updateHeight(topMost);
    updateHeight(middle);
    updateSize(topMost);
    updateSize(middle);
    return middle;
}

// left rotation if not balanced in the right
AVL::node* AVL::leftRotation(node* topMost) {
    node* middle = topMost->right;
    topMost->right = middle->left;
    middle->left = topMost;
    // Middle is now on top, first update the lower node
    updateHeight(topMost);
    updateHeight(middle);
    updateSize(topMost);
    updateSize(middle);
    return middle;
}

void AVL::deleteUtility(node* current) {
    if (current != NULL) {
        deleteUtility(current->left);
        deleteUtility(current->right);
        delete current;
    }
}

// to add node in the AVL Tree with balanced result
AVL::node* AVL::insertUtility(node* current, int value) {
    // if AVL Tree is empty
    if (current == NULL) {
        node* new_node = new node(value);
        return new_node;
    }
    // if AVL Tree is not empty
    if (value < current->data) {
        // go to the last left
        current->left = insertUtility(current->left, value);
    } else if (value > current->data) {
        // go to the last right
        current->right = insertUtility(current->right, value);
    }

    updateHeight(current);
    updateSize(current);
    return fixBalance(current);
}

// to remove node from the AVL Tree with balanced result
AVL::node* AVL::removeUtility(node* current, int value) {
    // if AVL Tree is empty
    if (current == NULL) {
        return NULL;
    }

    // if AVL Tree is not empty
    if (value < current->data) {
        // go to the last left
        current->left = removeUtility(current->left, value);
    } else if (value > current->data) {
        // go to the last right
        current->right = removeUtility(current->right, value);
    } else {
        // After finding the value
        if (current->left == NULL && current->right == NULL) {
            // if the is leaf
            delete current;
            return NULL;
        } else if (current->left != NULL && current->right != NULL) {
            // if the node has 2 children
            int max = maxUtility(current->left);
            current->data = max;
            current->left = removeUtility(current->left, max);
        } else {
            if (current->left != NULL) {
                current->data = current->left->data;
                current->left = removeUtility(current->left, current->data);
            } else {
                current->data = current->right->data;
                current->right = removeUtility(current->right, current->data);
            }
        }
    }

    updateHeight(current);
    updateSize(current);
    return fixBalance(current);
}

AVL::node* AVL::fixBalance(node* current) {
    // if not balanced in the left side
    if (balance(current) > 1) {
        if (balance(current->left) < 0) {
            /* Left Right Case
                     5
                    /
                   3
                    \
                     4
            */
            current->left = leftRotation(current->left);
            return rightRotation(current);
        } else {
            /* Left Left Case
                     5
                    /
                   3
                  /
                 2
            */
            return rightRotation(current);
        }
    }
    // if not balanced in the right side
    else if (balance(current) < -1) {
        if (balance(current->right) > 0) {
            /* Right Left Case
                  5
                   \
                    7
                   /
                  6
            */
            current->right = rightRotation(current->right);
            return leftRotation(current);
        } else {
            /* Right Right Case
                   5
                    \
                     6
                      \
                       7
            */
            return leftRotation(current);
        }
    }
    return current;
}

AVL::node* AVL::findUtility(node* current, int value) {
    if (current == NULL) {
        return NULL;
    }
    if (value < current->data) {
        return findUtility(current->left, value);
    }
    if (value > current->data) {
        return findUtility(current->right, value);
    }
    return current;
}

bool AVL::_isBalanced(node* current) {
    if (current == NULL) {
        return true;
    }
    bool isBalanced = balance(current) <= 1 && balance(current) >= -1;
    return _isBalanced(current->left) && _isBalanced(current->right) &&
           isBalanced;
}