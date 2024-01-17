/*
 * 235. 二叉搜索树的最近公共祖先		url: https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-search-tree/
 *
 * 题目描述：给定一个二叉搜索树, 找到该树中两个指定节点的最近公共祖先。
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include "binary_tree.h"

using namespace std;

class Solution // 利用搜索二叉树的性质
{
 public:
	TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q)
	{
		if (root == nullptr) return nullptr;

		// p 和 q 都在 root 的左子树
		if (root->val > p->val && root->val > q->val)
		{
			auto left = lowestCommonAncestor(root->left, p, q);
			if (left != nullptr) return left;
		}

		// p 和 q 都在 root 的右子树
		if (root->val < p->val && root->val < q->val)
		{
			auto right = lowestCommonAncestor(root->right, p, q);
			if (right != nullptr) return right;
		}

		// root 的值在 p 和 q 之间，即所求的节点
		return root;
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		BinaryTree tree({ 6, 2, 8, 0, 4, 7, 9, -1, -1, 3, 5 });
		cout << "exp1 (6): " << endl;

		cout << "result: " << solution.lowestCommonAncestor(tree.root(), tree.root()->left, tree.root()->right)->val
			 << endl;
	}

	return 0;
}