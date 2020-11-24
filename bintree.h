#ifndef _CREATE_SYSTEM_H
#define _CREATE_SYSTEM_H

#include <iostream>

struct list
{
	std::string inf;
	bool checked;
	size_t count;
	list* next;
	~list(){
		delete next;
	}
};

bool NilList(list*& root) {
	return (root == nullptr ? true : false);
}

void InsertList(list*& root, std::string x)
{ 
	if(root->inf == x){
		root->count++;
	}
	else if (root == nullptr)
	{
		list* el = new list;
		el->inf = x;
		el->next = nullptr;
		root = el;
	}
	else
		InsertList(root->next, x);
}

void FindList(list*& root, std::string x, list*& cur, list*& prev)
{
	cur = root;
	prev = nullptr;
	while (cur != nullptr && cur->inf != x)
	{
		prev = cur;
		cur = cur->next;
	}
	if (cur == nullptr)
		prev = nullptr;
}


void printm(list* array, int size) {
	while (array != nullptr) {
		std::cout << array->inf;
		array = array->next;
	}
	std::cout << std::endl;
}

void DeleteDoplers(list*& root)
{
	while (true) {
		if (root->inf == root->next->inf) {
			root = root->next;
			continue;
		}
		else {
			break;
		}
	}
	list* cur1 = root;

	while (cur1 != nullptr)
	{
		list* cur2 = cur1->next;
		list* prev = cur1;
		while (cur2 != nullptr)
		{
			if (cur2->inf == cur1->inf)
				prev->next = cur2->next;
			else
				prev = cur2;
			cur2 = cur2->next;
		}
		cur1 = cur1->next;
	}
}

void bubble_sort_list(list* root){
    list *t, *m, *a, *b;
    for(bool go = true; go; ){
        go = false;
        a  = t = root;
        b  = root->next;
 
        while(b != NULL){
            if(a->inf < b->inf){
                if(t == a)
                    root = b;
                else
                    t->next = b;
 
                a->next = b->next;
                b->next = a;
 
                m  = a, a = b, b = m;
                go = true;
            }
            t = a;
            a = a->next;
            b = b->next;
        }
    }
}

// template<typename value>
// struct tree{
// 	value val;
// 	tree* left, *right;
// 	tree(){
// 		val = 0;
// 		left = right = nullptr;
// 	}
// 	tree(value insert){
// 		val = insert;
// 		left = right = nullptr;
// 	}
// 	tree(tree& root){
// 		val = root.val;

// 	}
// }

struct tree {
	int value;
	tree* left = nullptr, * right = nullptr;
	~tree(){
		delete left;
		delete right;
	}
};

bool NilTree(tree* root)
{
	return (root == nullptr ? true : false);
}

void Insertvalue(tree*& root, int value) {
	if (root == nullptr) {
		tree* new_root = new tree;
		new_root->value = value;
		new_root->left = new_root->right = nullptr;
		root = new_root;
	}
	else {
		tree* cur = root, * previous = nullptr;
		while (cur != nullptr) {
			previous = cur;
			if (value > cur->value) {
				cur = cur->right;
			}
			else{
				cur = cur->left;
			}
		}
		tree* new_root = new tree;
		new_root->value = value;
		new_root->left = new_root->right = nullptr;
		//if (value > cur->value) {
		//	cur->right = new_root;
		//}
		//
		if (value > previous->value) {
			previous->right = new_root;
		}
		else {
			previous->left = new_root;
		}
	}
}

void findtree(tree*& root, int value, tree*& cur, tree*& prev) { //by the cur we took back pointer on interested leaf
	cur = root;
	while (cur != nullptr) {
		if (cur->value == value) {
			break;
		}
		prev = cur;
		value > cur->value ? cur = cur->right : cur = cur->left;
	}

	if (cur == nullptr) {
		prev = nullptr;
	}
}

void postOrderTravers(tree* root, size_t& count) {
	if (root != nullptr) {
		count++;
		postOrderTravers(root->left, count);
		postOrderTravers(root->right, count);
	}
}

void deltree(tree*& root, int value) {
	tree* cur, * prev = nullptr;
	findtree(root, value, cur, prev);
	if (cur != nullptr) {
		if (cur == root) {
			if (cur->left == nullptr && cur->right == nullptr) {
				cur = nullptr;
				std::cout << "currently deleted" << std::endl;
			}
			if (cur->left != nullptr && cur->right == nullptr) {
				cur = cur->left;
				std::cout << "currently deleted" << std::endl;
			}
			if (cur->left == nullptr && cur->right != nullptr) {
				cur = cur->right;
				std::cout << "currently deleted" << std::endl;
			}
			if (cur->left != nullptr && cur->right != nullptr) {
				tree* new_cur = cur, * new_prev = new_cur->right;
				while (new_prev->left != nullptr) {
					new_cur = new_prev;
					new_prev = new_prev->left;
				}
				cur->value = new_cur->value;
				new_prev->left = nullptr;
				std::cout << "currently deleted" << std::endl;
			}
		}
		else {
			if (cur->left == nullptr && cur->right == nullptr) {
				prev->left == cur ? prev->left = nullptr : prev->right = nullptr;
				std::cout << "currently deleted" << std::endl;
			}
			if (cur->left != nullptr && cur->right == nullptr) {
				prev->left = cur->left;
				std::cout << "currently deleted" << std::endl;
			}
			if (cur->left == nullptr && cur->right != nullptr) {
				prev->right = cur->right;
				std::cout << "currently deleted" << std::endl;
			}
			if (cur->left != nullptr && cur->right != nullptr) {
				tree* new_cur = cur, * new_prev = new_cur->right;
				while (new_prev->left != nullptr) {
					new_cur = new_prev;
					new_prev = new_prev->left;
				}
				cur->value = new_cur->value;
				new_prev->left = nullptr;
				std::cout << "currently deleted" << std::endl;
			}
		}
	}
	else {
		std::cout << "cant delete" << std::endl;
	}
}

void del_subtree(tree*& root, int value, char volume) {
	tree* cur, * prev;
	findtree(root, value, cur, prev);
	if (cur != nullptr) {
		volume == 'L' ? cur->left = nullptr : cur->right = nullptr;
		std::cout << "currently deleted" << std::endl;
	}
	else {
		std::cout << "cant delete" << std::endl;
	}
}

void TreeView1(tree*& root)
{
	if (root != nullptr)
	{
		std::cout << root->value << " ";
		TreeView1(root->left);
		TreeView1(root->right);
	}
}

void TreeView2(tree*& root)
{
	if (root != nullptr)
	{
		TreeView2(root->left);
		std::cout << root->value << " ";
		TreeView2(root->right);
	}
}

void TreeView3(tree*& root)
{
	if (root != nullptr)
	{
		TreeView3(root->left);
		TreeView3(root->right);
		std::cout << root->value << " ";
	}
}

#endif // !_CREATE_SYSTEM_H
