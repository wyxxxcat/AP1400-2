#ifndef BST_H
#define BST_H
#include<bits/stdc++.h>

class BST
{
public:
    class Node;
    BST& operator=(BST&& bst);
    BST& operator=(const BST& bst);
    BST(BST&& bst_);
    BST(const BST& bst_);
    BST(std::initializer_list<int>);
    Node*& get_root()const;
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
private:
    Node* root;
};
class BST::Node
{
public:
	Node(int value, Node* left, Node* right);
	Node();
	Node(const Node& node);
	int value = 0;
	Node* left = nullptr;
	Node* right = nullptr;
};
std::ostream& operator<<(std::ostream& os, const BST::Node& node);
std::ostream& operator<<(std::ostream& os,const BST& bst);
BST operator++(BST& bst,int);
BST& operator++(BST& bst);
bool operator<(const BST::Node& node,int a);
bool operator<=(const BST::Node& node,int a);
bool operator>(const BST::Node& node,int a);
bool operator>=(const BST::Node& node,int a);
bool operator==(const BST::Node& node,int a);
bool operator<(int a,const BST::Node& node);
bool operator<=(int a,const BST::Node& node);
bool operator>(int a,const BST::Node& node);
bool operator>=(int a,const BST::Node& node);
bool operator==(int a,const BST::Node& node);
#endif //BST_H