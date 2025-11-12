#ifndef AVL_H
#define AVL_H
#include <cmath>
#include <iostream>
#include <queue>

using std::cout;
using std::max;

class AVL {
    class node;
    node* root = NULL;  // in the first time before adding in AVL Tree

    int maxUtility(node* current);
    int size(node* current);
    int balance(node* current);
    int height(node* current);
    void updateSize(node* current);
    void updateHeight(node* current);
    node* rightRotation(node* current);
    node* leftRotation(node* current);
    node* fixBalance(node* current);
    void deleteUtility(node* current);
    node* insertUtility(node* current, int value);
    node* removeUtility(node* current, int value);
    node* findUtility(node* current, int value);
    void TreePrinter(node* tree);
    void printTree(void** M, AVL::node* current, void* cellInfo, int col, int row, int height);
    bool _isBalanced(node* current);


   public:
    // these Function will Appear in main when use object
    void insert(int value) { root = insertUtility(root, value); }
    void remove(int value) { root = removeUtility(root, value); }
    void print2D() { TreePrinter(root); }
    bool find(int value) { return findUtility(root, value) != NULL; }
    bool checkAVL() { return _isBalanced(root); }
    ~AVL() { deleteUtility(root); }
};

#endif