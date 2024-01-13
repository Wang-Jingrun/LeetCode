/*
 * 105. 从前序与中序遍历序列构造二叉树	url: https://leetcode.cn/problems/construct-binary-tree-from-preorder-and-inorder-traversal/
 *
 * 题目描述：给定两个整数数组 preorder 和 inorder ，
 * 其中 preorder 是二叉树的先序遍历， inorder 是同一
 * 棵树的中序遍历，请构造二叉树并返回其根节点。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder)
	{
		// 空节点返回
		if (preorder.empty()) return nullptr;

		// 根节点为先序遍历的第一个节点
		int rootValue = preorder.front();
		auto root = new TreeNode(rootValue);
		if (preorder.size() == 1) return root;    // 叶子节点返回

		// 寻找中序遍历的分割点
		int index = 0;
		for (; index < inorder.size(); ++index)
		{
			if (inorder[index] == rootValue) break;
		}

		// 分割中序，左开有闭
		auto leftInorder = vector<int>(inorder.begin(), inorder.begin() + index);
		auto rightInorder = vector<int>(inorder.begin() + index + 1, inorder.end());

		// 分割前序，左开有闭
		auto leftPreorder = vector<int>(preorder.begin() + 1, preorder.begin() + 1 + leftInorder.size());
		auto rightPreorder = vector<int>(preorder.begin() + 1 + leftInorder.size(), preorder.end());

		// 递归处理
		root->left = buildTree(leftPreorder, leftInorder);
		root->right = buildTree(rightPreorder, rightInorder);

		return root;
	}
};

int main()
{
	Solution solution;
	vector<int> inorder;
	vector<int> preorder;

	{
		// -1 表示null节点
		preorder = { 3, 9, 20, 15, 7 };
		inorder = { 9, 3, 15, 20, 7 };
		BinaryTree tree({ 3, 9, 20, -1, -1, 15, 7 });
		cout << "exp1 : " << endl;
		cout << "result tree: " << tree << endl;

		cout << "result: ";
		BinaryTree result_tree(solution.buildTree(preorder, inorder));
		cout << result_tree << endl;;
	}

	return 0;
}