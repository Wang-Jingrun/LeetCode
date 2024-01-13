/*
 * 106. 从中序与后序遍历序列构造二叉树	url: https://leetcode.cn/problems/construct-binary-tree-from-inorder-and-postorder-traversal/
 *
 * 题目描述：给定两个整数数组 inorder 和 postorder ，
 * 其中 inorder 是二叉树的中序遍历， postorder 是同一
 * 棵树的后序遍历，请你构造并返回这颗 二叉树
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder)
	{
		// 后序数组为 0，空节点
		if (postorder.empty()) return nullptr;

		// 后序数组最后一个元素为节点元素
		int rootValue = postorder.back();
		auto root = new TreeNode(rootValue);
		if (postorder.size() == 1) return root;

		// 寻找中序数组切割点
		int index = 0;
		for (; index < inorder.size(); index++)
		{
			if (inorder[index] == rootValue) break;
		}

		// 切中序数组
		// 左闭右开区间：[0, delimiterIndex)
		auto leftInorder = vector<int>(inorder.begin(), inorder.begin() + index);
		// [delimiterIndex + 1, end)
		auto rightInorder = vector<int>(inorder.begin() + index + 1, inorder.end());

		// 切后序数组
		// 依然左闭右开，注意这里使用了左中序数组大小作为切割点
		// [0, leftInorder.size)
		auto leftPostorder = vector<int>(postorder.begin(), postorder.begin() + leftInorder.size());
		// [leftInorder.size(), end-1)，end-1 即最后一个值，为中序节点
		auto rightPostorder = vector<int>(postorder.begin() + leftInorder.size(), postorder.end() - 1);

		// 递归处理左区间和后区间
		root->left = buildTree(leftInorder, leftPostorder);
		root->right = buildTree(rightInorder, rightPostorder);

		return root;
	}
};

int main()
{
	Solution solution;
	vector<int> inorder;
	vector<int> postorder;

	{
		// -1 表示null节点
		inorder = { 9, 3, 15, 20, 7 };
		postorder = { 9, 15, 7, 20, 3 };
		BinaryTree tree({ 3, 9, 20, -1, -1, 15, 7 });
		cout << "exp1 : " << endl;
		cout << "result tree: " << tree << endl;

		cout << "result: ";
		BinaryTree result_tree(solution.buildTree(inorder, postorder));
		cout << result_tree << endl;;
	}

	{
		// -1 表示null节点
		inorder = { 1, 2 };
		postorder = { 2, 1 };
		BinaryTree tree({ 1, -1, 2 });
		cout << "exp1 : " << endl;
		cout << "result tree: " << tree << endl;

		cout << "result: ";
		BinaryTree result_tree(solution.buildTree(inorder, postorder));
		cout << result_tree << endl;;
	}

	return 0;
}