/*
 * 515. 在每个树行中找最大值	url: https://leetcode.cn/problems/find-largest-value-in-each-tree-row/
 *
 * 题目描述：给定一棵二叉树的根节点 root ，请找出该二叉树中每一层的最大值。
 * */

#include <binary_tree.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	vector<int> largestValues(TreeNode* root)
	{
		if (root == nullptr) return {};

		vector<int> result;
		int size;
		int layer_max = INT_MIN;

		TreeNode* cur;
		queue<TreeNode*> queue;
		queue.push(root);
		while (!queue.empty())
		{
			size = (int)queue.size();

			for (int i = size; i > 0; --i)
			{
				cur = queue.front();
				queue.pop();
				layer_max = cur->val > layer_max ? cur->val : layer_max;

				if (cur->left != nullptr) queue.push(cur->left);
				if (cur->right != nullptr) queue.push(cur->right);
			}
			result.push_back(layer_max);
			layer_max = INT_MIN;
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
		nums = { 1, 3, 2, 5, 3, -1, 9 };
		BinaryTree tree(nums);
		cout << "exp1 ([1,3,9]): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: ";
		result = solution.largestValues(tree.root());
		cout << "[ ";
		for (auto it : result)
		{
			cout << it << " ";
		}
		cout << "]" << endl;
	}

	cout << endl;

	return 0;
}