/*
 * 236. 二叉树的最近公共祖先		url: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/
 *
 * 题目描述：给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include <binary_tree.h>

using namespace std;

class Solution
{
 public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
	{
		if (root == q || root == p || root == nullptr) return root;

		TreeNode* left = lowestCommonAncestor(root->left, p, q);
		TreeNode* right = lowestCommonAncestor(root->right, p, q);

		if (left != nullptr && right != nullptr) return root;
		if (left == nullptr && right != nullptr) return right;
		else if (left != nullptr && right == nullptr) return left;
		else
		{ //  (left == NULL && right == NULL)
			return nullptr;
		}

	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		BinaryTree tree({ 3, 5, 1, 6, 2, 0, 8, -1, -1, 7, 4 });
		cout << "exp1 (3): " << endl;

		cout << "result: " << solution.lowestCommonAncestor(tree.root(), tree.root()->left, tree.root()->right)->val
			 << endl;
	}

	return 0;
}