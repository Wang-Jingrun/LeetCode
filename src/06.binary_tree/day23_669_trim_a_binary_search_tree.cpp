/*
 * 669. 修剪二叉搜索树		url: https://leetcode.cn/problems/trim-a-binary-search-tree/
 *
 * 题目描述：给你二叉搜索树的根节点 root ，同时给定最小边界low 和最大边界 high。
 * 通过修剪二叉搜索树，使得所有节点的值在[low, high]中。修剪树 不应该 改变保留在
 * 树中的元素的相对结构 (即，如果没有被移除，原有的父代子代关系都应当保留)。
 * 可以证明，存在 唯一的答案 。所以结果应当返回修剪好的二叉搜索树的新的根节点。
 * 注意，根节点可能会根据给定的边界发生改变。
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include <binary_tree.h>

using namespace std;

class Solution
{
 public:
	TreeNode* trimBST(TreeNode* root, int low, int high)
	{
		if (root == nullptr) return nullptr;
		if (root->val < low)
		{
			TreeNode* rightTrimmed = trimBST(root->right, low, high);	// 寻找符合区间[low, high]的节点
			//delete root; // 释放删除的节点内存
			return rightTrimmed;
		}
		if (root->val > high)
		{
			TreeNode* leftTrimmed = trimBST(root->left, low, high);	// 寻找符合区间[low, high]的节点
			//delete root; // 释放删除的节点内存
			return leftTrimmed;
		}
		root->left = trimBST(root->left, low, high);	// root->left接入符合条件的左孩子
		root->right = trimBST(root->right, low, high);	// root->right接入符合条件的右孩子
		return root;
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		BinaryTree tree({ 1, -1, 2 });
		cout << "exp1 (2): " << endl;

		// 根节点可能被删除，需要重新赋值根节点
		tree.root(solution.trimBST(tree.root(), 2, 4));

		cout << "output: " << tree << endl;
	}

// 报错可能得原因类似下面
//	auto root = new TreeNode(100);
//	auto temp = root;
//	delete temp;
//
//	if (root != nullptr)
//	{
//		delete root;
//		root == nullptr;
//	}

	return 0;
}