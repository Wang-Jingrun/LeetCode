/*
 * 513. 找树左下角的值		url: https://leetcode.cn/problems/find-bottom-left-tree-value/
 *
 * 题目描述：给定一个二叉树的 根节点 root，请找出该二叉树的 最底层 最左边 节点的值。
 * 假设二叉树中至少有一个节点。
 * */

#include <binary_tree.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution // 层序遍历
{
 public:
	int findBottomLeftValue(TreeNode* root)
	{
		if (root == nullptr) return 0;

		TreeNode* cur;
		TreeNode* result;
		queue<TreeNode*> queue;
		queue.push(root);

		while (!queue.empty())
		{
			int size = queue.size();

			result = queue.front();
			for (int i = 0; i < size; ++i)
			{
				cur = queue.front();
				queue.pop();

				if (cur->left != nullptr) queue.push(cur->left);
				if (cur->right != nullptr) queue.push(cur->right);
			}
		}

		return result->val;
	}
};

class Solution2 // 递归
{
 public:
	Solution2()
	{
		reset();
	}

	int findBottomLeftValue(TreeNode* root)
	{
		traversal(root, 0);
		int result = m_result;
		reset();
		return result;
	}

 private:
	void reset()
	{
		m_maxDepth = INT_MIN;
	}

	void traversal(TreeNode* cur, int depth)
	{
		if (cur->left == nullptr && cur->right == nullptr)
		{
			/* 因为左节点的优先级比右节点高，所以若最后一层有很多节点，
			 * 但是它们的深度都不大于第一个左节点。因此 结果就是第一个到达最深深度的节点
			 */
			if (depth > m_maxDepth)
			{
				m_maxDepth = depth;
				m_result = cur->val;
			}
			return;
		}

		if (cur->left != nullptr) traversal(cur->left, depth + 1);	// 隐藏着回溯
		if (cur->right != nullptr) traversal(cur->right, depth + 1);	// 隐藏着回溯
	}

 private:
	int m_maxDepth;
	int m_result;
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 1, 2, 3, 4, -1, 5, 6, -1, -1, 7 };
		BinaryTree tree(nums);
		cout << "exp1 (7): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << solution.findBottomLeftValue(tree.root()) << endl;
	}

	return 0;
}