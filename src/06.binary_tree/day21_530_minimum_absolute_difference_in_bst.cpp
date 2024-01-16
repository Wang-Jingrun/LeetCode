/*
 * 530. 二叉搜索树的最小绝对差		url: https://leetcode.cn/problems/minimum-absolute-difference-in-bst/
 *
 * 题目描述：给你一个二叉搜索树的根节点 root ，返回
 * 树中任意两不同节点值之间的最小差值 。差值是一个正数，
 * 其数值等于两值之差的绝对值。
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include "binary_tree.h"

using namespace std;

// 先中序遍历，然后取遍历符合条件的结果
class Solution
{
 private:
	vector<int> m_vec;

	void traversal(TreeNode* cur)
	{
		if (cur == nullptr) return;

		traversal(cur->left);
		m_vec.push_back(cur->val);
		traversal(cur->right);
	}

 public:
	int getMinimumDifference(TreeNode* root)
	{
		m_vec.clear();
		traversal(root);

		int result = INT_MAX;
		for (int i = 0; i < m_vec.size() - 1; ++i)
		{
			result = min(result, m_vec[i + 1] - m_vec[i]);
		}

		return result;
	}
};

class Solution2
{
 private:
	TreeNode* pre = nullptr;
	int result = INT_MAX;

	void traversal(TreeNode* cur)
	{
		if (cur == nullptr) return;

		// 左
		traversal(cur->left);

		// 中
		if(pre!= nullptr)
		{
			result = min(result, cur->val - pre->val);
		}
		pre = cur;

		// 右
		traversal(cur->right);
	}

 public:
	int getMinimumDifference(TreeNode* root)
	{
		pre = nullptr;
		result = INT_MAX;
		traversal(root);
		return result;
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 4, 2, 6, 1, 3 };
		BinaryTree tree(nums);
		cout << "exp1 (1): " << endl;

		cout << "result: " << solution.getMinimumDifference(tree.root()) << endl;
	}

	{
		// -1 表示null节点
		nums = { 543, 384, 652, -1, 445, -1, 699 };
		BinaryTree tree(nums);
		cout << "exp2 (47): " << endl;

		cout << "result: " << solution.getMinimumDifference(tree.root()) << endl;
	}

	return 0;
}