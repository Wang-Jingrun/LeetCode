/*
 * 429. N 叉树的层序遍历	url: https://leetcode.cn/problems/n-ary-tree-level-order-traversal/
 *
 * 题目描述：给定一个 N 叉树，返回其节点值的层序遍历。（即从左到右，逐层遍历）。
 * 树的序列化输入是用层序遍历，每组子节点都由 null 值分隔。
 * */

#include "n_ary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	vector<vector<int>> levelOrder(Node* root)
	{
		if (root == nullptr) return {};

		vector<vector<int>> result;
		vector<int> nodes; // 记录每次节点值
		int size; // 记录每次节点数

		Node* cur;
		queue<Node*> queue;
		queue.push(root);
		while (!queue.empty())
		{
			size = queue.size();

			for (int i = size; i > 0; --i)
			{
				cur = queue.front();
				queue.pop();
				nodes.push_back(cur->val);

				for (auto item : cur->children)
				{
					if (item != nullptr)
						queue.push(item);
				}
			}
			result.push_back(nodes);
			nodes.clear();
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
		nums = { 1,-1,2,3,4,5,-1,-1,6,7,-1,8,-1,9,10,-1,-1,11,-1,12,-1,13,-1,-1,14 };
		NAryTree tree(nums);
		cout << "exp1 ([";
		result = tree.levelOrder();
		for (auto its : result)
		{
			cout << "[ ";
			for (auto it : its)
			{
				cout << it << " ";
			}
			cout << "]";
		}
		cout << "])" << endl;

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