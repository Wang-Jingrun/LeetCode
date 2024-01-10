/*
 * 102. 二叉树的层序遍历	url: https://leetcode.cn/problems/binary-tree-level-order-traversal/
 *
 * 题目描述：给你二叉树的根节点 root ，返回其节点值的 层序遍历。
 * （即逐层地，从左到右访问所有节点）。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	vector<vector<int>> levelOrder(TreeNode* root)
	{
		if (root == nullptr) return {};

		vector<vector<int>> result;
		vector<int> layers;
		queue<TreeNode*> queue;
		queue.push(root);
		int size;	// 通过 size 记录每层的节点数

		while (!queue.empty())
		{
			size = queue.size();

			for (int i = size; i > 0; --i)
			{
				auto node = queue.front();
				queue.pop();

				layers.push_back(node->val);
				if (node->left != nullptr) queue.push(node->left);
				if (node->right != nullptr) queue.push(node->right);
			}
			result.push_back(layers);
			layers.clear();
		}

		return result;
	}
};

int main()
{
	Solution solution;
	std::vector<int> nums;
	std::vector<vector<int>> result;

	{
		// -1 表示null节点
		nums = { 3, 9, 20, -1, -1, 15, 7 };
		BinaryTree tree(nums);
		cout << "exp1 ([[3],[9,20],[15,7]]): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: ";
		result = solution.levelOrder(tree.root());
		cout << "[";
		for (auto its : result)
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

	cout << endl;

	{
		// -1 表示null节点
		nums = { 1, 2, -1, 3, -1, 4, -1, 5 };
		BinaryTree tree(nums);
		cout << "exp2 ([[1],[2],[3],[4],[5]]): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: ";
		result = solution.levelOrder(tree.root());
		cout << "[";
		for (auto its : result)
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