/*
 * 538. 把二叉搜索树转换为累加树	url: https://leetcode.cn/problems/convert-bst-to-greater-tree/
 *
 * 题目描述：给出二叉 搜索 树的根节点，该树的节点值各不相同，请你将其转换为累加树（Greater Sum Tree），
 * 使每个节点 node 的新值等于原树中大于或等于 node.val 的值之和。
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include <binary_tree.h>

using namespace std;

class Solution
{
 private:
	int sum = 0;
	void traversal(TreeNode* cur)
	{
		if (cur == nullptr) return;

		// 右
		traversal(cur->right);

		// 中
		sum += cur->val;
		cur->val = sum;

		// 左
		traversal(cur->left);
	}

 public:
	TreeNode* convertBST(TreeNode* root)
	{
		sum = 0;
		// 采用右中左遍历，即从大到小
		traversal(root);
		return root;
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		cout << "exp1 (2): " << endl;
		BinaryTree result({ 30, 36, 21, 36, 35, 26, 15, -1, -1, -1, 33, -1, -1, -1, 8 });
		cout << "result: " << result << endl;

		BinaryTree input({ 4, 1, 6, 0, 2, 5, 7, -1, -1, -1, 3, -1, -1, -1, 8 });
		solution.convertBST(input.root());
		cout << "output: " << input << endl;
	}

	return 0;
}