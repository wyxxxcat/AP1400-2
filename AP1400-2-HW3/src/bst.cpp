#include "bst.h"
#include<iostream>
#include<iomanip>
BST& BST::operator=(const BST& bst) {
	auto bst2 = new BST(bst);
	this->~BST();
	root = bst2->root;
	return *this;
}
BST& BST::operator=(BST&& bst) {
	if (this != &bst) {
		this->~BST();
		this->root = new Node(bst.root->value, 0, 0);
		this->root->left = bst.root->left;
		this->root->right = bst.root->right;
		bst.root->left = nullptr;
		bst.root->right = nullptr;
	}
	return *this;
}
void copy(BST::Node* p1, BST::Node*& p2)
{
	if(p1)
	{
		p2 = new BST::Node(p1->value,nullptr,nullptr);
		copy(p1->left,p2->left);
		copy(p1->right,p2->right);
	}
}
BST::BST(BST&& bst_)
{
	this->root = new Node(bst_.root->value,nullptr,nullptr);
	this->root->left = bst_.root->left;
	this->root->right = bst_.root->right;
	bst_.root->right = nullptr;
	bst_.root->left = nullptr;
}
BST::BST(const BST& bst_)
{
	this->root = new Node(bst_.root->value,nullptr,nullptr);
	if(bst_.get_root())
	{
		copy(bst_.get_root(),this->get_root());
	}
}
BST::Node*& BST::get_root() const
{
	return this->root->left;
}
BST::BST(std::initializer_list<int> list)
{
	this->root = new Node(0,nullptr,nullptr);
	for(auto it : list)
	{
		add_node(it);
	}
}
void BST::bfs(std::function<void(Node*& node)> func)
{
	std::queue<Node*> q;
	q.push(get_root());
	while(!q.empty())
	{
		auto t = q.front();
		q.pop();
		func(t);
		if(t->left)
		{
			q.push(t->left);
		}
		if(t->right)
		{
			q.push(t->right);
		}
	}
}
size_t BST::length()
{
	std::vector<int> values;
 	this->bfs([&values](BST::Node*& node){values.push_back(node->value);});
	return values.size();
}
bool BST::add_node(int value)
{
	Node* r = get_root();
	Node* pre;
	if(!r)
	{
		this->root->left = new Node(value,nullptr,nullptr);
		this->root->value++;
		return true;
	}else
	{
		while (r)
		{
			pre = r;
			if (value < r->value)
			{
				r = r->left;
			}else if (value > r->value)
			{
				r = r->right;
			}else
			{
				return false;
			}
		}
		if (value < pre->value)
		{
			pre->left = new Node(value, nullptr, nullptr);
		}else if (value > pre->value)
		{
			pre->right = new Node(value, nullptr, nullptr);
		}else
		{
			return false;
		}
		this->root->value++;
		return true;
	}
	return 0;
}
BST::Node** BST::find_node(int value)
{
	if(get_root() == nullptr)
	{
		return nullptr;
	}
	if(get_root()->value == value)
	{
		return (&get_root());
	}
	std::queue<Node*> q;
	q.push(get_root());
	while(!q.empty())
	{
		Node* t = q.front();
		q.pop();
		if(t->left && t->left->value == value)
		{
			Node** p = &(t->left);
			return p;
		}else if(t->right && t->right->value == value)
		{
			Node** p = &(t->right);
			return p;
		}
		if(t->left != nullptr)
		{
			q.push(t->left);
		}
		if(t->right != nullptr)
		{
			q.push(t->right);
		}
	}
	return nullptr;
}
BST::Node** BST::find_parrent(int value)
{
	std::queue<Node*> q;
	q.push(get_root());
	while(!q.empty())
	{
		Node* t = q.front();
		q.pop();
		if(t->left && t->left->value == value)
		{
			return find_node(t->value);
		}
		if(t->right && t->right->value == value)
		{
			return find_node(t->value);
		}
		if(t->left)
		{
			q.push(t->left);
		}
		if(t->right)
		{
			q.push(t->right);
		}
	}
	return nullptr;
}
void inorder_traversal(BST::Node* root, std::vector<BST::Node*>& res)
{
	if (root)
	{
		inorder_traversal(root->right, res);
		res.push_back(root);
		inorder_traversal(root->left, res);
	}
	return;
}
BST::Node** BST::find_successor(int value)
{
	Node* r = get_root();
	if (r == nullptr)
		return nullptr;
	std::vector<BST::Node*> res;
	inorder_traversal(r, res);
	int i = 0;
	for (; i < res.size(); ++i)
	{
		if (res[i]->value == value) break;
	}
	return i + 1 < res.size() ? find_node(res[i + 1]->value) : nullptr;
}
static BST::Node* find_max(BST::Node* root)
{
	while (root && root->right)
	{
		root = root->right;
	}
	return root;
}
bool BST::delete_node(int value)
{
	Node* r = get_root();
	if(r == nullptr)
	{
		return false;
	}
	Node** isfind = find_node(value);
	if(isfind == nullptr)
	{
		return false;
	}
	Node* node = *isfind;
	bool ok = 0;
	if (node->left == nullptr && node->right == nullptr)
	{
		delete node;
		*isfind = nullptr;
		ok = 1;
	}else if(node->left == nullptr)
	{
		*isfind = node->right;
		delete node;
		ok = 1;
	}else if(node->right == nullptr)
	{
		*isfind = node->left;
		delete node;
		ok = 1;
	}else
	{
		Node* mx = find_max(node->left);
		auto pmx = find_parrent(mx->value);
		std::swap(mx->value, node->value);
		(*pmx)->right = nullptr;
		delete mx;
		ok = 1;
	}
	return ok;
}
BST::Node::Node(int value, Node* left, Node* right)
{
	this->value = value;
	this->left = left;
	this->right = right;
}
BST::Node::Node()
	: Node(0, nullptr, nullptr) {
}
BST::Node::Node(const Node& node)
{
	this->left = node.left;
	this->right = node.right;
	this->value = node.value;
}
std::ostream& operator<<(std::ostream& os, const BST::Node& node) {
	os << std::hex << &node << std::dec << "\t=> value:" << node.value
	   << "\tleft:" << std::left << std::setw(20) << std::hex << node.left << "\tright:" << node.right << std::dec;
	return os;
}
std::ostream& operator<<(std::ostream& os, const BST& bst) {
	std::cout << std::string(82, '*') << std::endl;
	std::queue<BST::Node*> q;
	q.push(bst.get_root());
	while (!q.empty()) {
		auto node = q.front();
		q.pop();
		std::cout << *node << std::endl;
		if (node->left)
			q.push(node->left);
		if (node->right)
			q.push(node->right);
	}
	std::cout << std::string(82, '*') << std::endl;
	return os;
}
bool operator<(const BST::Node& node,int a){
	return node.value < a;
}
bool operator<=(const BST::Node& node,int a){
	return node.value <= a;
}
bool operator>(const BST::Node& node,int a){
	return node.value > a;
}
bool operator>=(const BST::Node& node,int a){
	return node.value >= a;
}
bool operator==(const BST::Node& node,int a){
	return node.value == a;
}
auto operator<(int a,const BST::Node& node) ->bool{
	return node.value > a;
}
auto operator<=(int a,const BST::Node& node) ->bool{
	return node.value >= a;
}
auto operator>(int a,const BST::Node& node) ->bool{
	return node.value < a;
}
auto operator>=(int a,const BST::Node& node) ->bool{
	return node.value <= a;
}
auto operator==(int a,const BST::Node& node) ->bool{
	return node.value == a;
}
BST& operator++(BST& bst){
	bst.bfs([](BST::Node*& p){
		++(p->value);
	});
	return bst;
}
BST operator++(BST& bst,int)
{
	BST tmp(bst);
	++bst;
	return tmp;
}