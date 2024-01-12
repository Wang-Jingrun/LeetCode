/*
 * 257. 二叉树的所有路径	url: https://leetcode.cn/problems/binary-tree-paths/
 *
 * 题目描述：给你一个二叉树的根节点 root ，按 任意顺序 ，返回所有从根节点到叶子节点的路径。
 * 叶子节点 是指没有子节点的节点。
 * */

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	void getPath(TreeNode* cur, vector<int>& path, vector<string>& result)
	{
		// 写在这里，因为最后一个节点也要加入到path中
		// 因为结束条件不同了，相当于提早结束了
		path.push_back(cur->val);

		// 处理到叶子节点就开始结束逻辑
		if (cur->left == nullptr && cur->right == nullptr)
		{
			string sPath;

			// 将 path 里记录的路径转化为 string 格式
			for (int i = 0; i < path.size() - 1; ++i)
			{
				sPath += to_string(path[i]);
				sPath += "->";
			}
			sPath += to_string(path[path.size() - 1]); // 记录最后一个节点，即叶子节点
			result.push_back(sPath); // 收集一个路径
			return;
		}

		// 左
		if (cur->left)
		{
			getPath(cur->left, path, result);
			path.pop_back(); // 回溯
		}

		// 右
		if (cur->right)
		{
			getPath(cur->right, path, result);
			path.pop_back(); // 回溯
		}
	}

	vector<string> binaryTreePaths(TreeNode* root)
	{
		vector<string> result;
		vector<int> path;
		if (root == nullptr) return result;
		getPath(root, path, result);
		return result;
	}
};

class Solution2
{
 private:

	// 回溯隐藏在 string path 中，每次拷贝传值
	void traversal(TreeNode* cur, string path, vector<string>& result)
	{
		path += to_string(cur->val); // 中
		if (cur->left == nullptr && cur->right == nullptr)
		{
			result.push_back(path);
			return;
		}
		if (cur->left) {
			path += "->";
			traversal(cur->left, path, result); // 左
		}
		if (cur->right) {
			path += "->";
			traversal(cur->right, path, result); // 右
		}
	}

 public:
	vector<string> binaryTreePaths(TreeNode* root)
	{
		vector<string> result;
		string path;
		if (root == nullptr) return result;
		traversal(root, path, result);
		return result;

	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		// -1 表示null节点
		nums = { 1, 2, 3, -1, 5 };
		BinaryTree tree(nums);
		cout << R"(exp1 (["1->2->5","1->3"]): )" << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: " << endl;
		auto result = solution.binaryTreePaths(tree.root());
		for (auto& it : result)
		{
			cout << it << endl;
		}
	}

	return 0;
}