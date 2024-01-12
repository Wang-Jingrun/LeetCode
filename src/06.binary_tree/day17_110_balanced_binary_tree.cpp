/*
 * 110. 平衡二叉树	url: https://leetcode.cn/problems/balanced-binary-tree/
 *
 * 题目描述：给定一个二叉树，判断它是否是高度平衡的二叉树。
 * 本题中，一棵高度平衡二叉树定义为：
 * 		一个二叉树每个节点 的左右两个子树的高度差的绝对值不超过 1 。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	int getHeight(TreeNode* node)
	{
		if (node == nullptr) return 0;

		int leftHeight = getHeight(node->left);
		if (leftHeight == -1) return -1;

		int rightHeight = getHeight(node->right);
		if (rightHeight == -1) return -1;

		int result;
		if (abs(leftHeight - rightHeight) > 1)
			// 如果当前传入节点为根节点的二叉树已经不是二叉平衡树了，还返回高度的话就没有意义了。
			// 因此返回 -1 作为标记
			result = -1;
		else
			result = max(leftHeight, rightHeight) + 1;
		return result;
	}

	bool isBalanced(TreeNode* root)
	{
		return getHeight(root) != -1;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 1, 2, 2, 3, 3, -1, -1, 4, 4 };
		BinaryTree tree(nums);
		cout << "exp1 (false): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.isBalanced(tree.root()) << endl;
	}

	{
		// -1 表示null节点
		nums = { 3, 9, 20, -1, -1, 15, 7 };
		BinaryTree tree(nums);
		cout << "exp2 (true): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.isBalanced(tree.root()) << endl;
	}

	{
		// -1 表示null节点
		nums = { 1, 2, 2, 3, -1, -1, 3, 4, -1, -1, 4 };
		BinaryTree tree(nums);
		cout << "exp3 (false): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.isBalanced(tree.root()) << endl;
	}

	return 0;
}