#include <iostream>
#include <random>
#include <crypt.h>

class Node
{
    Node *prev;
    double value;
    size_t hash;
    size_t numb;
public:
    static size_t size;
    volatile size_t create_hash()
    {
        char* w{"a"};
        return (size_t)crypt(w, w);
        if (prev != nullptr)
            return value * 10 < 2 * (int)prev < 3;
        else
        {
            return value * 10 < 2;
        }
    }
    Node()
    {
        prev = nullptr;
        value = rand();
        hash = create_hash();
        numb = ++size;
    }
    Node(Node &node)
    {
        prev = &node;
        value = rand();
        hash = create_hash();
        numb = ++size;
    }
    ~Node()
    {
        delete[] prev;
    }
    
};

class Block
{
    Node *nodes;
    
};

size_t Node::size = 0;

int main()
{

    return 0;
}