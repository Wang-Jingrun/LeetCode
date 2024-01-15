/*
 * 700. 二叉搜索树中的搜索	url: https://leetcode.cn/problems/search-in-a-binary-search-tree/
 *
 * 题目描述：给定二叉搜索树（BST）的根节点 root 和一个整数值 val。
 * 你需要在 BST 中找到节点值等于 val 的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 null 。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	TreeNode* searchBST(TreeNode* root, int val)
	{
		if (root == nullptr || root->val == val) return root;
		if (root->val < val) return searchBST(root->right, val);
		if (root->val > val) return searchBST(root->left, val);
		return nullptr;
	}
};

class Solution2
{
 public:
	TreeNode* searchBST(TreeNode* root, int val)
	{
		while (root != nullptr)
		{
			if (root->val > val) root = root->left;
			else if (root->val < val) root = root->right;
			else return root;
		}
		return nullptr;
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		BinaryTree tree({ 4, 2, 7, 1, 3 });
		cout << "exp1 : " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: ";
		BinaryTree result_tree(solution.searchBST(tree.root(), 2));
		cout << result_tree << endl;;
	}

	return 0;
}