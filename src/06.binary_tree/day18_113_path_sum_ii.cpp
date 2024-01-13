/*
 * 113. 路径总和 II	url: https://leetcode.cn/problems/path-sum-ii/
 *
 * 题目描述：给你二叉树的根节点 root 和一个整数目标和 targetSum ，
 * 找出所有 从根节点到叶子节点 路径总和等于给定目标和的路径。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 private:
	void getPath(TreeNode* cur, vector<int>& path, vector<vector<int>>& paths)
	{
		path.push_back(cur->val);

		if (cur->left == nullptr && cur->right == nullptr)
		{
			paths.push_back(path);
			return;
		}

		if (cur->left != nullptr)
		{
			getPath(cur->left, path, paths);
			path.pop_back();
		}

		if (cur->right != nullptr)
		{
			getPath(cur->right, path, paths);
			path.pop_back();
		}
	}

 public:
	vector<vector<int>> pathSum(TreeNode* root, int targetSum)
	{
		if (root == nullptr) return {};

		vector<int> path;
		vector<vector<int>> paths;
		getPath(root, path, paths);

		for (auto itm = paths.begin(); itm != paths.end();)
		{
			int sum = 0;
			for (auto num : *itm)
			{
				sum += num;
			}
			if (sum != targetSum)
				itm = paths.erase(itm);
			else
				++itm;
		}

		return paths;
	}
};

class Solution2
{
 private:
	void getPath(TreeNode* cur, int count, vector<int>& path, vector<vector<int>>& paths)
	{
		// 中
		path.push_back(cur->val);

		// 是叶子节点，且值符合条件
		if (cur->left == nullptr && cur->right == nullptr && count == 0)
		{
			paths.push_back(path);
			return;
		}

		// 是叶子节点，但其值不符合条件
		if (cur->left == nullptr && cur->right == nullptr)
		{
			return;
		}

		// 左
		if (cur->left != nullptr)
		{
			getPath(cur->left, count - cur->left->val, path, paths);
			path.pop_back();
		}

		// 左
		if (cur->right != nullptr)
		{
			getPath(cur->right, count - cur->right->val, path, paths);
			path.pop_back();
		}
	}

 public:
	vector<vector<int>> pathSum(TreeNode* root, int targetSum)
	{
		if(root == nullptr) return {};

		vector<vector<int>> result;
		vector<int> path;
		getPath(root, targetSum - root->val, path, result);
		return result;
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 5, 4, 8, 11, -1, 13, 4, 7, 2, -1, -1, 5, 1 };
		BinaryTree tree(nums);
		cout << "exp1 ([[5,4,11,2],[5,8,4,5]]): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: ";
		auto result = solution.pathSum(tree.root(), 22);
		cout << "[";
		for (const auto& its : result)
		{
			cout << "[ ";
			for (auto it : its)
			{
				cout << it << " ";
			}
			cout << "]";
		}
		cout << "]" << endl;
	}

	return 0;
}