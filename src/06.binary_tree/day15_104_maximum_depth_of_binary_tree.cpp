/*
 * 104. 二叉树的最大深度	url: https://leetcode.cn/problems/maximum-depth-of-binary-tree/
 *
 * 题目描述：给定一个二叉树 root ，返回其最大深度。
 * 二叉树的 最大深度 是指从根节点到最远叶子节点的最长路径上的节点数。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	int maxDepth(TreeNode* root)
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
		cout << "exp1 (3): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.maxDepth(tree.root()) << endl;
	}

	return 0;
}