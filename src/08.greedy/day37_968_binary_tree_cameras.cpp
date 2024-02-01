/*
 * 968. 监控二叉树		url: https://leetcode.cn/problems/binary-tree-cameras/
 *
 * 题目描述：给定一个二叉树，我们在树的节点上安装摄像头。
 * 节点上的每个摄影头都可以监视其父对象、自身及其直接子对象。
 * 计算监控树的所有节点所需的最小摄像头数量。
 * */

#include <iostream>
#include <binary_tree.h>
using namespace std;

class Solution
{
 private:
	int result;
	int traversal(TreeNode* cur)
	{
		if (cur == NULL) return 2;
		int left = traversal(cur->left);    // 左
		int right = traversal(cur->right);  // 右
		if (left == 2 && right == 2) return 0;
		else if (left == 0 || right == 0)
		{
			result++;
			return 1;
		}
		else return 2;
	}
 public:
	int minCameraCover(TreeNode* root)
	{
		result = 0;
		if (traversal(root) == 0)
		{ // root 无覆盖
			result++;
		}
		return result;
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		BinaryTree tree({ 0, 0, -1, 0, -1, 0, -1, -1, 0 });
		cout << "exp1 (2): " << endl;
		cout << "input tree: " << tree << endl;
		cout << "result: " << solution.minCameraCover(tree.root()) << endl;
	}
}
