/*
 * 404. 左叶子之和	url: https://leetcode.cn/problems/sum-of-left-leaves/
 *
 * 题目描述：给定二叉树的根节点 root ，返回所有左叶子之和。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 private:
	int _sumOfLeftLeaves(TreeNode* cur, bool leftLeave)
	{
		if (cur->left == nullptr && cur->right == nullptr)
		{
			if (leftLeave)
				return cur->val;
			else
				return 0;
		}

		int leftSumOfLeftLeaves = 0, rightSumOfLeftLeaves = 0;
		if (cur->left != nullptr)
			leftSumOfLeftLeaves = _sumOfLeftLeaves(cur->left, true);

		if (cur->right != nullptr)
			rightSumOfLeftLeaves = _sumOfLeftLeaves(cur->right, false);

		return leftSumOfLeftLeaves + rightSumOfLeftLeaves;
	}

 public:
	int sumOfLeftLeaves(TreeNode* root)
	{
		if (root == nullptr) return 0;

		return _sumOfLeftLeaves(root, false);
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
		cout << "exp1 (24): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.sumOfLeftLeaves(tree.root()) << endl;
	}

	return 0;
}