/*
 * 100. 相同的树		url: https://leetcode.cn/problems/same-tree/
 *
 * 题目描述：给你两棵二叉树的根节点 p 和 q ，编写一个函数来检验这两棵树是否相同。
 *
 * 如果两个树在结构上相同，并且节点具有相同的值，则认为它们是相同的。
 * */

#include <binary_tree.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	bool isSameTree(TreeNode* p, TreeNode* q)
	{
		if (p == nullptr && q == nullptr)
			return true;
		else if (p == nullptr && q != nullptr)
			return false;
		else if (p != nullptr && q == nullptr)
			return false;
		else if (p->val == q->val)
		{
			return isSameTree(p->right, q->right) && isSameTree(p->left, q->left);
		}
		else
			return false;
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		BinaryTree tree1({ 0, 5 });
		BinaryTree tree2({ 0, 8 });
		cout << "exp1 (false): " << endl;
		cout << "input tree1: " << tree1 << endl;
		cout << "input tree2: " << tree2 << endl;

		cout << "result: ";
		cout << solution.isSameTree(tree1.root(), tree2.root()) << endl;
	}

	return 0;
}