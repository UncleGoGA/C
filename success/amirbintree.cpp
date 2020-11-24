#include <iostream>
#include "bintree.h"
#include <vector>

int main()
{
    tree *Tree = nullptr;
    std::vector<int> value;
    int semi;
    while (std::cin >> semi)
    {
        value.push_back(semi);
        //to kill cin just push smth char
    }
    for (size_t i = 0; i < value.size(); ++i)
    {
        Insertvalue(Tree, value.at(i));
    }
    TreeView3(Tree);
}