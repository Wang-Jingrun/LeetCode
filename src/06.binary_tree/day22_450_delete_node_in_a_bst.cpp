/*
 * 450. 删除二叉搜索树中的节点		url: https://leetcode.cn/problems/delete-node-in-a-bst/
 *
 * 题目描述：给定一个二叉搜索树的根节点 root 和一个值 key，
 * 删除二叉搜索树中的 key 对应的节点，并保证二叉搜索树的性质不变。
 * 返回二叉搜索树（有可能被更新）的根节点的引用。
 * */
#include <vector>
#include <iostream>
#include <algorithm>
#include <binary_tree.h>

using namespace std;

class Solution
{
 private:
	TreeNode* traversal(TreeNode* cur, int key)
	{
		// 没有找到要删除的节点，直接返回
		if (cur == nullptr) return nullptr;

		// 找到节点进行删除
		if (cur->val == key)
		{
			// 是叶子节点，直接删除
			if (cur->left == nullptr && cur->right == nullptr)
			{
				delete cur;
				return nullptr;
			}

			// 有一个子节点，用子节点接替该节点的位置
			if (cur->left != nullptr && cur->right == nullptr)
			{
				auto temp = cur->left;
				delete cur;
				return temp;
			}
			else if (cur->left == nullptr && cur->right != nullptr)
			{
				auto temp = cur->right;
				delete cur;
				return temp;
			}

			// 左右子树都不为空
			auto min_right_node = cur->right;
			while (min_right_node->left != nullptr)
			{
				min_right_node = min_right_node->left;
			}
			min_right_node->left = cur->left;
			auto temp = cur->right;
			delete cur;
			return temp;
		}

		// 向左子树查找
		if (cur->val > key)
		{
			cur->left = traversal(cur->left, key);
		}

		// 向右子树查找
		if (cur->val < key)
		{
			cur->right = traversal(cur->right, key);
		}

		return cur;
	}

 public:
	TreeNode* deleteNode(TreeNode* root, int key)
	{
		return traversal(root, key);
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		BinaryTree tree({ 6, 2, 8, 0, 4, 7, 9, -1, -1, 3, 5 });
		cout << "exp1 (6): " << endl;

		cout << "result: " << solution.lowestCommonAncestor(tree.root(), tree.root()->left, tree.root()->right)->val
			 << endl;
	}

	return 0;
}