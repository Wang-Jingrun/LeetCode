/*
 * 226. 翻转二叉树	url: https://leetcode.cn/problems/invert-binary-tree/
 *
 * 题目描述：给你一棵二叉树的根节点 root ，翻转这棵二叉树，并返回其根节点。（左子树右子树互换）
 * */

#include <binary_tree.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution    // 层序遍历+翻转
{
 public:
	TreeNode* invertTree(TreeNode* root)
	{
		if (root == nullptr) return nullptr;

		int size;
		TreeNode* cur;
		queue<TreeNode*> queue;
		queue.push(root);
		while (!queue.empty())
		{
			size = queue.size();

			for (int i = size; i > 0; --i)
			{
				cur = queue.front();
				queue.pop();
				swap(cur->left, cur->right);
				if (cur->left != nullptr) queue.push(cur->left);
				if (cur->right != nullptr) queue.push(cur->right);
			}
			size = 0;
		}
		return root;
	}
};

class Solution2    // 前序遍历+翻转
{
 public:
	TreeNode* invertTree(TreeNode* root)
	{
		if (root == nullptr) return root;
		swap(root->left, root->right);  // 中
		invertTree(root->left);         // 左
		invertTree(root->right);        // 右
		return root;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 4, 2, 7, 1, 3, 6, 9 };
		BinaryTree tree(nums);
		cout << "exp1 ([4,7,2,9,6,3,1]): " << endl;
		cout << "input tree: " << tree << endl;

		solution.invertTree(tree.root());
		auto result = tree.levelOrder();
		cout << "result: [ ";
		for (auto& items : result)
		{
			for (auto it : items)
			{
				cout << it << " ";
			}
		}
		cout << "]" << endl;
	}

	return 0;
}