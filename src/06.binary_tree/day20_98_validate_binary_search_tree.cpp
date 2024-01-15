/*
 * 98. 验证二叉搜索树	url: https://leetcode.cn/problems/validate-binary-search-tree/
 *
 * 题目描述：给你一个二叉树的根节点 root ，判断其是否是一个有效的二叉搜索树。
 * 有效 二叉搜索树定义如下：
 * 		节点的左子树只包含 小于 当前节点的数。
 * 		节点的右子树只包含 大于 当前节点的数。
 * 		所有左子树和右子树自身必须也是二叉搜索树。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

// 直观法
class Solution
{
 private:
	vector<int> m_vec;

	void inorderTraversal(TreeNode* cur)
	{
		if (cur == nullptr) return;

		inorderTraversal(cur->left);
		m_vec.push_back(cur->val);
		inorderTraversal(cur->right);
	}

 public:
	bool isValidBST(TreeNode* root)
	{
		if (root == nullptr) return true;

		m_vec.clear();
		inorderTraversal(root);

		for (int i = 1; i < m_vec.size(); ++i)
		{
			if (m_vec[i] <= m_vec[i - 1])
			{
				return false;
			}
		}

		return true;
	}
};

class Solution2
{
 public:
	TreeNode* pre = nullptr; // 用来记录前一个节点
	bool isValidBST(TreeNode* root)
	{
		if (root == nullptr) return true;
		bool left = isValidBST(root->left);

		if (pre != nullptr && pre->val >= root->val) return false;
		pre = root; // 记录前一个节点

		bool right = isValidBST(root->right);
		return left && right;
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 2, 1, 3 };
		BinaryTree tree(nums);
		cout << "exp1 (true): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.isValidBST(tree.root()) << endl;
	}

	cout << endl;

	{
		// -1 表示null节点
		nums = { 5, 1, 4, -1, -1, 3, 6 };
		BinaryTree tree(nums);
		cout << "exp2 (false): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.isValidBST(tree.root()) << endl;
	}

	cout << endl;

	{
		// -1 表示null节点
		nums = { 5, 4, 6, -1, -1, 3, 7 };
		BinaryTree tree(nums);
		cout << "exp3 (false): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.isValidBST(tree.root()) << endl;
	}

	return 0;
}