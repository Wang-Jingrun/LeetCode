/*
 * 199. 二叉树的右视图		url: https://leetcode.cn/problems/binary-tree-right-side-view/
 *
 * 题目描述：给定一个二叉树的 根节点 root，想象自己站在它的右侧，按照从顶部到底部的顺序，返回从右侧所能看到的节点值。
 * */

#include <binary_tree.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	vector<int> rightSideView(TreeNode* root)
	{
		if (root == nullptr) return {};

		vector<int> result;
		queue<TreeNode*> queue;
		TreeNode* node;
		queue.push(root);

		int size; // 存放每层的节点数

		while (!queue.empty())
		{
			size = queue.size();

			for (int i = size; i > 0; --i)
			{
				node = queue.front();
				queue.pop();

				if (node->left != nullptr) queue.push(node->left);
				if (node->right != nullptr) queue.push(node->right);
			}

			result.push_back(node->val);

		}

		return result;
	}
};

int main()
{

	Solution solution;
	std::vector<int> nums;
	std::vector<int> result;

	{
		// -1 表示null节点
		nums = { 1, 2, 3, 4 };
		BinaryTree tree(nums);
		cout << "exp1 ([1,3,4]): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: ";
		result = solution.rightSideView(tree.root());
		cout << "[ ";
		for (auto num : result)
		{
			cout << num << " ";
		}
		cout << "]" << endl;
	}

	cout << endl;

	return 0;
}