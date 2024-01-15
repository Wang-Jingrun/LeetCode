/*
 * 654. 最大二叉树	url: https://leetcode.cn/problems/maximum-binary-tree/
 *
 * 题目描述：给定一个不重复的整数数组 nums 。 最大二叉树 可以用下面的算法从 nums 递归地构建:
 * 创建一个根节点，其值为 nums 中的最大值。
 * 递归地在最大值 左边 的 子数组前缀上 构建左子树。
 * 递归地在最大值 右边 的 子数组后缀上 构建右子树。
 * 返回 nums 构建的 最大二叉树 。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	int getMaxIndex(vector<int>& nums)
	{
		int max_index = 0;
		for (int i = 1; i < nums.size(); ++i)
		{
			if (nums[i] > nums[max_index]) max_index = i;
		}
		return max_index;
	}

	TreeNode* constructMaximumBinaryTree(vector<int>& nums)
	{
		// 空节点返回
		if (nums.empty()) return nullptr;

		// 获取根节点
		int rootIndex = getMaxIndex(nums);
		auto root = new TreeNode(nums[rootIndex]);
		if (nums.size() == 1) return root; // 叶子节点

		// 分割左区间，左开右闭
		vector<int> leftNums(nums.begin(), nums.begin() + rootIndex);

		// 分割右区间，左开右闭
		vector<int> rightNums(nums.begin() + rootIndex + 1, nums.end());

		// 递归处理
		root->left = constructMaximumBinaryTree(leftNums);
		root->right = constructMaximumBinaryTree(rightNums);

		return root;
	}
};

class Solution2    // 优化版
{
 private:
	// 左闭右开
	TreeNode* traversal(vector<int>& nums, int left, int right)
	{
		// 空节点返回
		if (left >= right) return nullptr;

		// 寻找最大节点
		int max_index = left;
		for (int i = left + 1; i < right; ++i)
		{
			if (nums[i] > nums[max_index]) max_index = i;
		}
		auto root = new TreeNode(nums[max_index]);
		if (left == right + 1) return root;    // 叶子节点返回

		// 分割左区间
		root->left = traversal(nums, left, max_index);

		// 分割右区间
		root->right = traversal(nums, max_index + 1, right);

		return root;
	}

 public:
	TreeNode* constructMaximumBinaryTree(vector<int>& nums)
	{
		return traversal(nums, 0, nums.size());
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 3, 2, 1, 6, 0, 5 };
		BinaryTree tree({ 6, 3, 5, -1, 2, 0, -1, -1, 1 });
		cout << "exp1 : " << endl;
		cout << "result tree: " << tree << endl;

		cout << "result: ";
		BinaryTree result_tree(solution.constructMaximumBinaryTree(nums));
		cout << result_tree << endl;;
	}

	return 0;
}