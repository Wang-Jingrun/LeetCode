/*
 * 337. 打家劫舍 III		url: https://leetcode.cn/problems/house-robber-iii/
 *
 * 题目描述：小偷又发现了一个新的可行窃的地区。这个地区只有一个入口，我们称之为 root 。
 * 除了 root 之外，每栋房子有且只有一个“父“房子与之相连。一番侦察之后，聪明的小偷意识
 * 到“这个地方的所有房屋的排列类似于一棵二叉树”。 如果 两个直接相连的房子在同一天晚上被打劫 ，房屋将自动报警。
 * 给定二叉树的 root 。返回 在不触动警报的情况下 ，小偷能够盗取的最高金额 。
 * */

#include <iostream>
#include <vector>
#include <binary_tree.h>
using namespace std;

class Solution
{
 public:
	// 0: 使用本节点，1: 不使用本节点
	vector<int> traversal(TreeNode* node)
	{
		if (node == nullptr) return { 0, 0 };

		// 后序遍历
		vector<int> leftdp = traversal(node->left); // 左
		vector<int> rightdp = traversal(node->right); // 右

		// 中
		int val1 = node->val + leftdp[1] + rightdp[1];	// 使用本节点
		int val2 = max(leftdp[0], leftdp[1]) + max(rightdp[0], rightdp[1]); // 不使用本节点

		return { val1, val2 };
	}

	int rob(TreeNode* root)
	{
		vector<int> result = traversal(root);
		return max(result[0], result[1]);
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		auto tree = BinaryTree({ 2, 1, 3, -1, 4 });
		cout << "exp1 (7): " << endl;
		cout << "input tree:" << tree << endl;
		cout << "result: " << solution.rob(tree.root()) << endl;
	}
}
