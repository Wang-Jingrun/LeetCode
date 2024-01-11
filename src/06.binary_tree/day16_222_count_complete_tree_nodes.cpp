/*
 * 222. 完全二叉树的节点个数	url: https://leetcode.cn/problems/count-complete-tree-nodes/
 *
 * 题目描述：给你一棵 完全二叉树 的根节点 root ，求出该树的节点个数。
 * 完全二叉树 的定义如下：在完全二叉树中，除了最底层节点可能没填满外，
 * 其余每层节点数都达到最大值，并且最下面一层的节点都集中在该层最左边的若干位置。
 * 若最底层为第 h 层，则该层包含 1~ 2h 个节点。
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include "binary_tree.h"

using namespace std;

class Solution
{
 private:
	int getNodesNum(TreeNode* cur)
	{
		if (cur == nullptr) return 0;
		int leftNum = getNodesNum(cur->left);        // 左
		int rightNum = getNodesNum(cur->right);        // 右
		int treeNum = leftNum + rightNum + 1;            // 中
		return treeNum;
	}
 public:
	int countNodes(TreeNode* root)
	{
		return getNodesNum(root);
	}
};

class Solution2
{
 public:
	int countNodes(TreeNode* root)
	{
		if (root == nullptr) return 0;
		TreeNode* left = root->left;
		TreeNode* right = root->right;
		int leftDepth = 0, rightDepth = 0; // 这里初始为0是有目的的，为了下面求指数方便
		while (left)
		{  // 求左子树深度
			left = left->left;
			leftDepth++;
		}
		while (right)
		{ // 求右子树深度
			right = right->right;
			rightDepth++;
		}
		if (leftDepth == rightDepth)
		{
			return (2 << leftDepth) - 1; // 注意(2<<1) 相当于2^2，所以leftDepth初始为0
		}
		return countNodes(root->left) + countNodes(root->right) + 1;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 1, 2, 3, 4, 5, 6 };
		BinaryTree tree(nums);
		cout << "exp1 (6): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.countNodes(tree.root()) << endl;
	}

	return 0;
}