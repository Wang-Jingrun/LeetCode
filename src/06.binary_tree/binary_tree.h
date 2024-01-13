#pragma once
#include <vector>
#include <queue>
#include <stack>
#include <iostream>
#include <sstream>

// Definition for a binary tree node.
struct TreeNode
{
	int val;
	TreeNode* left;
	TreeNode* right;
	TreeNode() : val(0), left(nullptr), right(nullptr) {}
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
	TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

class BinaryTree
{
 public:
	BinaryTree();
	BinaryTree(TreeNode* root);
	BinaryTree(const std::vector<int>& nums); // -1 表示空节点
	~BinaryTree();

	void clear(TreeNode* root);

	// todo 拷贝构造，拷贝复制
	BinaryTree& operator=(const std::vector<int>& nums);

	TreeNode* root();
	bool isEmpty();

	// 层序遍历
	std::vector<std::vector<int>> levelOrder();

	// 递归遍历二叉树，返回树的内容的字符串形式
	std::string str(TreeNode* root) const;

	// 重载 << 运算符，输出二叉树内容的字符串形式
	friend std::ostream& operator<<(std::ostream& os, const BinaryTree& tree)
	{
		os << tree.str(tree.m_root);
		return os;
	}

 private:
	TreeNode* m_root;
};