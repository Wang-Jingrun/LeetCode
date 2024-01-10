/*
 * 111. 二叉树的最小深度	url: https://leetcode.cn/problems/minimum-depth-of-binary-tree/
 *
 * 题目描述：给定一个二叉树，找出其最小深度。
 * 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	int minDepth(TreeNode* root)
	{
		if (root == nullptr) return 0;

		int size;
		int depth = 0;
		TreeNode* cur;
		queue<TreeNode*> queue;
		queue.push(root);

		while (!queue.empty())
		{
			size = queue.size();

			for (int i = size; i > 0; --i)
			{
				cur = queue.front();
				queue.pop();

				// 第一个出现的叶子节点就在最小深度的那层
				if (cur->right == nullptr && cur->left == nullptr)
					return depth + 1;

				if (cur->left != nullptr) queue.push(cur->left);
				if (cur->right != nullptr) queue.push(cur->right);
			}
			++depth;
		}
		return depth;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 3, 9, 20, -1, -1, 15, 7 };
		BinaryTree tree(nums);
		cout << "exp1 (2): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.minDepth(tree.root()) << endl;
	}

	{
		// -1 表示null节点
		nums = { 1, 2, 3, 4, 5 };
		BinaryTree tree(nums);
		cout << "exp2 (2): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.minDepth(tree.root()) << endl;
	}

	return 0;
}