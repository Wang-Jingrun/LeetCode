/*
 * 111. 二叉树的最小深度	url: https://leetcode.cn/problems/minimum-depth-of-binary-tree/
 *
 * 题目描述：给定一个二叉树，找出其最小深度。
 * 最小深度是从根节点到最近叶子节点的最短路径上的节点数量。
 * */

#include <binary_tree.h>
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

class Solution2	// 递归法
{
 public:
	int getDepth(TreeNode* node)
	{
		int depth = 0;

		if (node == nullptr) return 0;
		int leftDepth = getDepth(node->left);
		int rightDepth = getDepth(node->right);

		// 左右孩子都为空的节点才是叶子节点！
		// 计算的左右子树深度都为 0 才表示最小深度为 0，否则是非叶子节点
		// 也就是 左右深度只有一个 0 并不代表最小深度为 0，直接 min 会出错
		if (leftDepth == 0) depth = rightDepth;
		else if (rightDepth == 0) depth = leftDepth;
		else depth = min(leftDepth, rightDepth);

		return depth + 1;
	}

	int minDepth(TreeNode* root)
	{
		return getDepth(root);
	}
};

int main()
{
	Solution2 solution;
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

	{
		// -1 表示null节点
		nums = { 2, -1, 3, -1, 4, -1, 5, -1, 6 };
		BinaryTree tree(nums);
		cout << "exp3 (5): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.minDepth(tree.root()) << endl;
	}

	return 0;
}