/*
 * 637. 二叉树的层平均值	url: https://leetcode.cn/problems/average-of-levels-in-binary-tree/
 *
 * 题目描述：给定一个非空二叉树的根节点 root , 以数组的形式返回每一层节点的平均值。与实际答案相差 10-5 以内的答案可以被接受。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	vector<double> averageOfLevels(TreeNode* root)
	{
		if (root == nullptr) return {};

		vector<double> result;
		double average;    // 记录每层的平均数
		int size;    // 记录每层节点数
		TreeNode* cur;
		queue<TreeNode*> queue;
		queue.push(root);

		while (!queue.empty())
		{
			average = 0;
			size = (int)queue.size();

			for (int i = size; i > 0; --i)
			{
				cur = queue.front();
				queue.pop();
				average += cur->val;

				if (cur->left != nullptr) queue.push(cur->left);
				if (cur->right != nullptr) queue.push(cur->right);
			}
			average /= size;
			result.push_back(average);
		}

		return result;
	}
};

int main()
{

	Solution solution;
	std::vector<int> nums;
	std::vector<double> result;

	{
		// -1 表示null节点
		nums = { 3, 9, 20, -1, -1, 15, 7 };
		BinaryTree tree(nums);
		cout << "exp1 ([3.00000,14.50000,11.00000]): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: ";
		result = solution.averageOfLevels(tree.root());
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