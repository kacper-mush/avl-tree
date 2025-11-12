#include "avl.h"

#include <sstream>

#include "avl_core.cpp"

using std::string;
using std::stringstream;

const string lb = u8"┌";
const string rb = u8"┐";
const string ln = u8"─";

enum CellInfo { ROOT, LCHILD, RCHILD, EMPTY, ALCHILD, ARCHILD };

struct Cell {
    CellInfo cellInfo;
    int value, size;

    Cell(CellInfo cellInfo, int value, int size)
        : cellInfo(cellInfo), value(value), size(size) {}
    Cell() : cellInfo(CellInfo::EMPTY), value(0), size(0) {};

    void setAbove(CellInfo ci) {
        cellInfo = (ci == LCHILD) ? ALCHILD : ARCHILD;
    }
};

string repString(const string& s, int n) {
    stringstream ss;
    for (int i = 0; i < n; i++) {
        ss << s;
    }
    return ss.str();
}

int getcol(int h) {
    if (h == 1) return 1;
    return getcol(h - 1) + getcol(h - 1) + 1;
}

int numDigits(int x) { return std::to_string(x).length(); }

void AVL::printTree(void** M, AVL::node* current, void* cellInfo, int col,
                    int row, int height) {
    if (current == NULL) return;

    CellInfo info = *(CellInfo*)cellInfo;
    ((Cell**)M)[row][col] = Cell(info, current->data, current->size);

    if (info != ROOT) {
        ((Cell**)M)[row - 1][col].setAbove(info);
    }

    delete (CellInfo*)cellInfo;

    printTree(M, current->left, new CellInfo(LCHILD),
              col - std::pow(2, height - 2), row + 1, height - 1);
    printTree(M, current->right, new CellInfo(RCHILD),
              col + std::pow(2, height - 2), row + 1, height - 1);
}

void AVL::TreePrinter(node* tree) {
    if (tree == NULL) {
        return;
    }
    int h = height(tree);
    int col = getcol(h);
    Cell** M = new Cell*[h];
    for (int i = 0; i < h; i++) {
        M[i] = new Cell[col];
    }
    printTree((void**)M, tree, new CellInfo(ROOT), col / 2, 0, h);

    int maxSizeField =
        numDigits(maxUtility(root)) + numDigits(root->height) + 1;
    string space = repString(" ", maxSizeField);
    string branch_horiz = repString(ln, maxSizeField);

    for (int i = 0; i < h; i++) {
        bool wasC = false;

        for (int j = 0; j < col; j++) {
            CellInfo cellInfo = M[i][j].cellInfo;
            if (cellInfo != LCHILD && cellInfo != RCHILD && cellInfo != ROOT) {
                if (!wasC) {
                    if (cellInfo == ALCHILD) {
                        cout << lb << branch_horiz;
                        wasC = true;
                    } else {
                        cout << space << " ";
                    }
                } else {
                    if (cellInfo == ARCHILD) {
                        int selfSize = numDigits(M[i + 1][j].value) +
                                       numDigits(M[i + 1][j].size) + 1;
                        int rightPad = maxSizeField - selfSize;
                        string spaceBeforeLast = repString(ln, selfSize - 1);
                        string rightSpace = repString(" ", rightPad);
                        cout << spaceBeforeLast << rb << rightSpace << ' ';
                        wasC = false;
                    } else {
                        cout << branch_horiz << ln;
                    }
                }
            } else {
                wasC = true;
                if (!findUtility(root, M[i][j].value)->right) {
                    wasC = false;
                }

                int selfSize =
                    numDigits(M[i][j].value) + numDigits(M[i][j].size) + 1;
                int rightPad = maxSizeField - selfSize;

                if (!wasC) {
                    string rightSpace = repString(" ", rightPad);
                    cout << M[i][j].value << ":" << M[i][j].size << rightSpace << " ";
                } else {
                    string rightSpace = repString(ln, rightPad);
                    cout << M[i][j].value << ":" << M[i][j].size <<  rightSpace << ln;
                }
            }
        }
        cout << "\n";
    }
    for (int i = 0; i < col; i++) {
        cout << branch_horiz << " ";
    }
    cout << "\n";

    for (int i = 0; i < h; i++) {
        delete[] M[i];
    }
    delete[] M;
}