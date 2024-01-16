/*
 * 501. 二叉搜索树中的众数		url: https://leetcode.cn/problems/find-mode-in-binary-search-tree/
 *
 * 题目描述：给你一个含重复值的二叉搜索树（BST）的根节点 root ，
 * 找出并返回 BST 中的所有 众数（即，出现频率最高的元素）。
 * 如果树中有不止一个众数，可以按 任意顺序 返回。
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include "binary_tree.h"

using namespace std;

class Solution
{
 private:
	TreeNode* pre = nullptr;
	vector<int> result;
	int max_count = 0;
	int count = 0;

	void traversal(TreeNode* cur)
	{
		if (cur == nullptr) return;

		// 左
		traversal(cur->left);

		// 中
		if (pre == nullptr) count++;
		else
		{
			if (cur->val == pre->val) count++;
			else count = 1;
		}

		if (count > max_count)
		{
			result.clear();
			result.push_back(cur->val);
			max_count = count;
		}
		else if (count == max_count)
		{
			result.push_back(cur->val);
		}
		pre = cur;

		// 右
		traversal(cur->right);
	}

 public:
	vector<int> findMode(TreeNode* root)
	{
		pre = nullptr;
		result.clear();
		max_count = 0;
		count = 0;

		traversal(root);
		return result;
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		BinaryTree tree({ 1, -1, 2 });
		cout << "exp1 ([1, 2]): " << endl;
		auto result = solution.findMode(tree.root());
		cout << "result: [ ";
		for (auto num : result)
		{
			cout << num << " ";
		}
		cout << "]" << endl;
	}

	return 0;
}