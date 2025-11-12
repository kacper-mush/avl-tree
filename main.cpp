#include <random>
#include <vector>

#include "avl.h"

using std::vector;

int main(int argc, char **argv) {
    if (argc != 2) {
        return 1;
    }

    // RNG for random node values
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, 100);

    int max = atoi(argv[1]);

    vector<int> values(max);
    std::uniform_int_distribution<> indexes(0, max - 1);
    for (int i = 0; i < max; i++) {
        values[i] = distrib(gen);
    }

    AVL avl;
    for (int val : values) {
        avl.insert(val);
        if (!avl.checkAVL()) {
            return 1;
        }
    }

    for (int i = 0; i < max / 2; i++) {
        avl.remove(values[indexes(gen)]);
        if (!avl.checkAVL()) {
            return 1;
        }
    }
    avl.print2D();
    return 0;
}