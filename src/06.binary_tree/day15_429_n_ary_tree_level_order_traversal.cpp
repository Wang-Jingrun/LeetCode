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
	// todo n叉树

	return 0;
}