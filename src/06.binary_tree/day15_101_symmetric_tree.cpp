/*
 * 101. 对称二叉树	url: https://leetcode.cn/problems/symmetric-tree/
 *
 * 题目描述：给你一个二叉树的根节点 root ， 检查它是否轴对称。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	void _isSymmetric(TreeNode* left, TreeNode* right, bool& flag)
	{
		// 首先排除空节点的情况
		if ((left == nullptr) && (right == nullptr))
			return;
		else if (left == nullptr)
		{
			flag = false;
			return;
		}
		else if (right == nullptr)
		{
			flag = false;
			return;
		}
		// 排除了空节点，再排除数值不相同的情况
		else if (left->val != right->val)
		{
			flag = false;
			return;
		}

		// 此时就是：左右节点都不为空，且数值相同的情况
		// 此时才做递归，做下一层的判断
		_isSymmetric(left->right, right->left, flag);
		_isSymmetric(left->left, right->right, flag);
	}

	bool isSymmetric(TreeNode* root)
	{
		if (root == nullptr) return false;

		bool flag = true;
		_isSymmetric(root->left, root->right, flag);
		return flag;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 1, 2, 2, 3, 4, 4, 3 };
		BinaryTree tree(nums);
		cout << "exp1 (true): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.isSymmetric(tree.root()) << endl;
	}

	cout << endl;

	{
		// -1 表示null节点
		nums = { 1, 2, 2, -1, 3, -1, 3 };
		BinaryTree tree(nums);
		cout << "exp2 (false): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.isSymmetric(tree.root()) << endl;
	}

	return 0;
}