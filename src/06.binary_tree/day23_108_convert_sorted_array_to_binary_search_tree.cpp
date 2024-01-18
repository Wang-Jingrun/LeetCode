/*
 * 108. 将有序数组转换为二叉搜索树		url: https://leetcode.cn/problems/convert-sorted-array-to-binary-search-tree/
 *
 * 题目描述：给你一个整数数组 nums ，其中元素已经按 升序 排列，请你将其转换为一棵 高度平衡 二叉搜索树。
 * 高度平衡 二叉树是一棵满足「每个节点的左右两个子树的高度差的绝对值不超过 1 」的二叉树。
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include "binary_tree.h"

using namespace std;

class Solution
{
 private:
	TreeNode* traversal(vector<int>& nums, int left, int right)
	{
		if (left >= right) return nullptr;

		int mid = (left + right) / 2;
		auto root = new TreeNode(nums[mid]);

		root->left = traversal(nums, left, mid);
		root->right = traversal(nums, mid + 1, right);

		return root;
	}

 public:
	// 左闭右开，不断取中间节点
	TreeNode* sortedArrayToBST(vector<int>& nums)
	{
		return traversal(nums, 0, nums.size());
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		// -1 表示null节点
		cout << "exp1: " << endl;
		BinaryTree result1({ 0, -3, 9, -10, -1, 5 });
		cout << "result1: " << result1 << endl;
		BinaryTree result2({ 0, -10, 5, -1, -3, -1, 9 });
		cout << "result2: " << result2 << endl;

		nums = { -10, -3, 0, 5, 9 };
		BinaryTree tree(solution.sortedArrayToBST(nums));
		cout << "output: " << tree << endl;
	}

	return 0;
}