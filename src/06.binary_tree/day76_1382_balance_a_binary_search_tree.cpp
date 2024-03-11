/*
 * 1382. 将二叉搜索树变平衡		url: https://leetcode.cn/problems/balance-a-binary-search-tree/
 *
 * 题目描述：给你一棵二叉搜索树，请你返回一棵 平衡后 的二叉搜索树，
 * 新生成的树应该与原来的树有着相同的节点值。如果有多种构造方法，
 * 请你返回任意一种。
 *
 * 如果一棵二叉搜索树中，每个节点的两棵子树高度差不超过 1 ，我们就
 * 称这棵二叉搜索树是 平衡的 。
 * */

#include <binary_tree.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 private:
	vector<int> nums;
	void traversal(TreeNode* node)
	{
		if (node == nullptr) return;
		traversal(node->left);
		nums.push_back(node->val);
		traversal(node->right);
	}

	TreeNode* nums2tree(int start, int end)
	{
		if (start >= end) return nullptr;

		if (end - start == 1) return new TreeNode(nums[start]);

		int mid = (end + start) / 2;
		auto node = new TreeNode(nums[mid]);
		node->left = nums2tree(start, mid);
		node->right = nums2tree(mid + 1, end);
		return node;
	}

 public:
	TreeNode* balanceBST(TreeNode* root)
	{
		nums.clear();
		traversal(root);
		if (nums.size() <= 1) return root;

		return nums2tree(0, nums.size());
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		BinaryTree tree({ 1, -1, 2, -1, 3, -1, 4 });
		cout << "exp1: " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: ";
		BinaryTree out_tree(solution.balanceBST(tree.root()));
		cout << out_tree << endl;
	}

	{
		// -1 表示null节点
		BinaryTree tree({ 14, 9, 16, 2, 13 });
		cout << "exp2: " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: ";
		BinaryTree out_tree(solution.balanceBST(tree.root()));
		cout << out_tree << endl;
	}

	return 0;
}