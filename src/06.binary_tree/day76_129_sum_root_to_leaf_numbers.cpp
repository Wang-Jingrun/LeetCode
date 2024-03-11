/*
 * 129. 求根节点到叶节点数字之和		url: https://leetcode.cn/problems/sum-root-to-leaf-numbers/
 *
 * 题目描述：给你一个二叉树的根节点 root ，树中每个节点都存放有一个 0 到 9 之间的数字。
 * 		每条从根节点到叶节点的路径都代表一个数字：
 * 例如，从根节点到叶节点的路径 1 -> 2 -> 3 表示数字 123 。
 * 计算从根节点到叶节点生成的 所有数字之和 。
 *
 * */

#include <binary_tree.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 private:
	int result = 0;
	void getPathSum(TreeNode* node, int sum)
	{
		if (node->left == nullptr && node->right == nullptr)
		{
			result += sum * 10 + node->val;
			return;
		}

		if (node->left != nullptr) getPathSum(node->left, sum * 10 + node->val);
		if (node->right != nullptr) getPathSum(node->right, sum * 10 + node->val);
	}

 public:
	int sumNumbers(TreeNode* root)
	{
		result = 0;
		if (root == nullptr) return result;
		getPathSum(root, 0);
		return result;
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		BinaryTree tree({ 4, 9, 0, 5, 1 });
		cout << "exp1 (1026): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: ";
		cout << solution.sumNumbers(tree.root()) << endl;
	}

	return 0;
}