#pragma once
#include <utility>
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>

// Definition for a Node.
class Node {
 public:
	int val;
	std::vector<Node*> children;

	Node() : val(0) {}
	Node(int _val) : val(_val) {}
	Node(int _val, std::vector<Node*> _children) : val(_val), children(std::move(_children)) {}
};

class NAryTree
{
 public:
	NAryTree();
	NAryTree(const std::vector<int>& nums); // -1 表示空节点
	~NAryTree();

	void clear(Node* root);

	// todo 拷贝构造，拷贝复制
	NAryTree& operator=(const std::vector<int>& nums);

	Node* root();
	bool isEmpty();

	// 层序遍历
	std::vector<std::vector<int>> levelOrder();

 private:
	Node* m_root;
};