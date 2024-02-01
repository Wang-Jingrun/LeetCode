/*
 * 559. N 叉树的最大深度	url: https://leetcode.cn/problems/maximum-depth-of-n-ary-tree/
 *
 * 题目描述：给定一个 N 叉树，找到其最大深度。
 * 最大深度是指从根节点到最远叶子节点的最长路径上的节点总数。
 * N 叉树输入按层序遍历序列化表示，每组子节点由空值分隔。
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include <n_ary_tree.h>

using namespace std;

class Solution
{
 public:
	int getDepth(Node* node)
	{
		if (node == nullptr) return 0;

		int depth = 0;
		for (auto it : node->children)
		{
			int temp = getDepth(it);
			if (temp > depth) depth = temp;
		}

		// 加1是因为算上当前中间节点
		return depth + 1;
	}

	int maxDepth(Node* root)
	{
		return getDepth(root);
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 1, -1, 2, 3, 4, 5, -1, -1, 6, 7, -1, 8, -1, 9, 10, -1, -1, 11, -1, 12, -1, 13, -1, -1, 14 };
		NAryTree tree(nums);
		cout << "exp1 (5): " << endl;

		cout << "result: " << solution.maxDepth(tree.root()) << endl;
	}

	return 0;
}