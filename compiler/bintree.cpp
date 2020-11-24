#include "../bintree.h"

class BinTree{
    tree* root, *cur, *prev;
    size_t size;
    BinTree(){
        root = cur = prev = nullptr;
        size = 0;
    }
    BinTree(BinTree& Bin){
        size = Bin.size;
        root = Bin.root;
        //smth root.left && root.right copy
    }
    ~BinTree(){
        deltree(root, root->value);
        delete root;
        delete cur;
        delete prev;
    }
};