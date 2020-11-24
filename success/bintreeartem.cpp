#include <iostream>
#include <vector>
#include <string>

struct tree
{
    std::string value;
    tree *left = nullptr, *right = nullptr;
    ~tree()
    {
        delete left;
        delete right;
    }
};

bool NilTree(tree *root)
{
    return (root == nullptr ? true : false);
}

void Insertvalue(tree *&root, std::string value)
{
    if (root == nullptr)
    {
        tree *new_root = new tree;
        new_root->value = value;
        new_root->left = new_root->right = nullptr;
        root = new_root;
    }
    else
    {
        tree *cur = root, *previous = nullptr;
        while (cur != nullptr)
        {
            previous = cur;
            if (value > cur->value)
            {
                cur = cur->right;
            }
            else
            {
                cur = cur->left;
            }
        }
        tree *new_root = new tree;
        new_root->value = value;
        new_root->left = new_root->right = nullptr;
        //if (value > cur->value) {
        //	cur->right = new_root;
        //}
        //
        if (value > previous->value)
        {
            previous->right = new_root;
        }
        else
        {
            previous->left = new_root;
        }
    }
}

void findtree(tree *&root, std::string value, tree *&cur, tree *&prev)
{ //by the cur we took back pointer on interested leaf
    if(value[value.size() - 1] == '\n'){
        value.pop_back();
    }
    cur = root;
    while (cur != nullptr)
    {
        if (cur->value == value)
        {
            break;
        }
        prev = cur;
        value > cur->value ? cur = cur->right : cur = cur->left;
    }

    if (cur == nullptr)
    {
        prev = nullptr;
    }
}

void postOrderTravers(tree *root, size_t &count)
{
    if (root != nullptr)
    {
        count++;
        postOrderTravers(root->left, count);
        postOrderTravers(root->right, count);
    }
}

void deltree(tree *&root, std::string value)
{
    tree *cur, *prev = nullptr;
    findtree(root, value, cur, prev);
    if (cur != nullptr)
    {
        if (cur == root)
        {
            if (cur->left == nullptr && cur->right == nullptr)
            {
                cur = nullptr;
                std::cout << "currently deleted" << std::endl;
            }
            if (cur->left != nullptr && cur->right == nullptr)
            {
                cur = cur->left;
                std::cout << "currently deleted" << std::endl;
            }
            if (cur->left == nullptr && cur->right != nullptr)
            {
                cur = cur->right;
                std::cout << "currently deleted" << std::endl;
            }
            if (cur->left != nullptr && cur->right != nullptr)
            {
                tree *new_cur = cur, *new_prev = new_cur->right;
                while (new_prev->left != nullptr)
                {
                    new_cur = new_prev;
                    new_prev = new_prev->left;
                }
                cur->value = new_cur->value;
                new_prev->left = nullptr;
                std::cout << "currently deleted" << std::endl;
            }
        }
        else
        {
            if (cur->left == nullptr && cur->right == nullptr)
            {
                prev->left == cur ? prev->left = nullptr : prev->right = nullptr;
                std::cout << "currently deleted" << std::endl;
            }
            if (cur->left != nullptr && cur->right == nullptr)
            {
                prev->left = cur->left;
                std::cout << "currently deleted" << std::endl;
            }
            if (cur->left == nullptr && cur->right != nullptr)
            {
                prev->right = cur->right;
                std::cout << "currently deleted" << std::endl;
            }
            if (cur->left != nullptr && cur->right != nullptr)
            {
                tree *new_cur = cur, *new_prev = new_cur->right;
                while (new_prev->left != nullptr)
                {
                    new_cur = new_prev;
                    new_prev = new_prev->left;
                }
                cur->value = new_cur->value;
                new_prev->left = nullptr;
                std::cout << "currently deleted" << std::endl;
            }
        }
    }
    else
    {
        std::cout << "cant delete" << std::endl;
    }
}

void del_subtree(tree *&root, std::string value, char volume)
{
    tree *cur, *prev;
    findtree(root, value, cur, prev);
    if (cur != nullptr)
    {
        volume == 'L' ? cur->left = nullptr : cur->right = nullptr;
        std::cout << "currently deleted" << std::endl;
    }
    else
    {
        std::cout << "cant delete" << std::endl;
    }
}

void TreeView1(tree *&root)
{
    if (root != nullptr)
    {
        std::cout << root->value << " ";
        TreeView1(root->left);
        TreeView1(root->right);
    }
}

void TreeView2(tree *&root)
{
    if (root != nullptr)
    {
        TreeView2(root->left);
        std::cout << root->value << " ";
        TreeView2(root->right);
    }
}

void TreeView3(tree *&root)
{
    if (root != nullptr)
    {
        TreeView3(root->left);
        TreeView3(root->right);
        std::cout << root->value << " ";
    }
}

bool is_open(char *argv[])
{
    FILE *fa = fopen(argv[1], "r"), *fb = fopen(argv[2], "r");
    if (!fa && !fb)
    {
        return true;
    }
    return false;
}

inline char *substr(char *str, size_t pos, size_t n)
{
    char *newstr = new char[n];
    for (size_t i = pos, k = 0; k < n; ++k, ++i)
    {
        newstr[k] = str[i];
    }
    return newstr;
}

void alg(char *argv[])
{
    FILE *fb, *fa;
    char *semi = new char[300];
    fa = fopen(argv[1], "r");
    fb = fopen(argv[2], "r");
    std::vector<std::string> str_a;
    std::vector<std::string> str_b;
    while (!feof(fa))
    {
        fgets(semi, 300, fa);
        str_a.push_back(semi);
    }
    while (!feof(fb))
    {
        fgets(semi, 300, fb);
        str_b.push_back(semi);
    }
    fclose(fa);
    fclose(fb);
    tree *tree_b = nullptr, *cur, *prev;
    //    for(size_t i = 0; i < str_a.size(); ++i){
    //        Insertvalue(tree_a,str_a[i]);
    //    }
    FILE *out = fopen("out.txt", "w");
    std::string semi_str;
    for (size_t i = 0; i < str_b.size(); ++i)
    {
        semi_str = str_b[i];
        if (semi_str[semi_str.size() - 1] == '\n')
        {
            semi_str.pop_back();
        }
        Insertvalue(tree_b, semi_str);
    }
    for (size_t i = 0; i < str_a.size(); ++i)
    {
        semi_str = str_a[i];
        if (semi_str[semi_str.size() - 1] == '\n')
        {
            semi_str.pop_back();
        }
        findtree(tree_b, str_a[i], cur, prev);
        if (cur == nullptr)
        {
            fprintf(out,semi_str.c_str());
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        printf("Invalid params");
        exit(0);
    }
    alg(argv);

    return 0;
}
