/*
 * 112. 路径总和	url: https://leetcode.cn/problems/path-sum/
 *
 * 题目描述：给你二叉树的根节点 root 和一个表示目标和的整数 targetSum 。
 * 判断该树中是否存在 根节点到叶子节点 的路径，这条路径上所有节点值相加等于
 * 目标和 targetSum 。如果存在，返回 true ；否则，返回 false 。
 * 叶子节点 是指没有子节点的节点。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 private:
	void getPathSum(TreeNode* cur, int sum, vector<int>& sums)
	{
		if (cur->left == nullptr && cur->right == nullptr)
		{
			sum += cur->val;
			sums.push_back(sum);
		}

		if (cur->left != nullptr) getPathSum(cur->left, sum + cur->val, sums);
		if (cur->right != nullptr) getPathSum(cur->right, sum + cur->val, sums);

		sum += cur->val;
	}

 public:
	bool hasPathSum(TreeNode* root, int targetSum)
	{
		if (root == nullptr) return false;

		int sum = 0;
		vector<int> sums;
		getPathSum(root, sum, sums);

		for (auto it : sums)
		{
			if (it == targetSum)
				return true;
		}

		return false;
	}
};

class Solution2
{
 private:
	// count 用于记录当前的和（还差多少满足条件）
	bool traversal(TreeNode* cur, int count)
	{
		// 叶子节点且满足和
		if (cur->left == nullptr && cur->right == nullptr && count == 0) return true;

		// 叶子节点但不满足和
		if (cur->left == nullptr && cur->right == nullptr) return false;

		// 左
		if (cur->left != nullptr)
		{
			// count - cur->left->val 隐含回溯
			if (traversal(cur->left, count - cur->left->val))
				return true;
		}

		// 右
		if (cur->right != nullptr)
		{
			// count - cur->right->val 隐含回溯
			if (traversal(cur->right, count - cur->right->val)) return true;
		}

		return false;
	}

 public:
	bool hasPathSum(TreeNode* root, int targetSum)
	{
		if (root == nullptr) return false;

		return traversal(root, targetSum - root->val);
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, -1, 1 };
		BinaryTree tree(nums);
		cout << "exp1 (true): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: ";
		cout << solution.hasPathSum(tree.root(), 22) << endl;
	}

	return 0;
}