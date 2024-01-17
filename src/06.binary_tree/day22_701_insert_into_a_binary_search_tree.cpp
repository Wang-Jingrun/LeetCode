/*
 * 701. 二叉搜索树中的插入操作		url: https://leetcode.cn/problems/insert-into-a-binary-search-tree/
 *
 * 题目描述：给定二叉搜索树（BST）的根节点 root 和要插入树中的值 value ，
 * 将值插入二叉搜索树。 返回插入后二叉搜索树的根节点。 输入数据 保证 ，新值
 * 和原始二叉搜索树中的任意节点值都不同。
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include "binary_tree.h"

using namespace std;

class Solution
{
 private:
	void traversal(TreeNode* cur, int val)
	{
		if(cur->left == nullptr && cur->val > val)
		{
			cur->left = new TreeNode(val);
			return;
		}
		else if(cur->right == nullptr && cur->val < val)
		{
			cur->right = new TreeNode(val);
			return;
		}


		if (cur->left != nullptr && cur->val > val)
		{
			traversal(cur->left, val);
		}

		if (cur->right != nullptr && cur->val < val)
		{
			traversal(cur->right, val);
		}
	}

 public:
	TreeNode* insertIntoBST(TreeNode* root, int val)
	{
		if (root == nullptr) return new TreeNode(val);

		traversal(root, val);
		return root;
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点

		BinaryTree result_tree({ 5, 4, 14, -1, -1, 10, 77, -1, -1, -1, 95 });
		cout << "exp1: " << endl;
		cout << "result: " << result_tree << endl;

		BinaryTree tree({ 5, -1, 14, 10, 77, -1, -1, -1, 95, -1, -1 });
		solution.insertIntoBST(tree.root(), 4);

		cout << "result: " << tree << endl;
	}

	return 0;
}