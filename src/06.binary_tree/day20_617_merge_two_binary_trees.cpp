/*
 * 617. 合并二叉树	url: https://leetcode.cn/problems/merge-two-binary-trees/
 *
 * 题目描述：给你两棵二叉树： root1 和 root2 。
 * 想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。
 * 你需要将这两棵树合并成一棵新二叉树。合并的规则是：如果两个节点重叠，那么将这两个节点的值
 * 相加作为合并后节点的新值；否则，不为 null 的节点将直接作为新二叉树的节点。
 * 返回合并后的二叉树。
 * 注意: 合并过程必须从两个树的根节点开始。
 * */

#include <binary_tree.h>
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2)
	{
		// 终止条件
		if (root1 == nullptr && root2 == nullptr) return nullptr;

		// 递归处理，分情况
		TreeNode* root = nullptr;
		if (root1 == nullptr)
		{
			root = new TreeNode(root2->val);
			root->left = mergeTrees(nullptr, root2->left);
			root->right = mergeTrees(nullptr, root2->right);
		}
		else if (root2 == nullptr)
		{
			root = new TreeNode(root1->val);
			root->left = mergeTrees(root1->left, nullptr);
			root->right = mergeTrees(root1->right, nullptr);
		}
		else
		{
			root = new TreeNode(root1->val + root2->val);
			root->left = mergeTrees(root1->left, root2->left);
			root->right = mergeTrees(root1->right, root2->right);
		}

		return root;
	}
};

int main()
{
	Solution solution;

	{
		// -1 表示null节点
		cout << "exp1 : " << endl;
		BinaryTree result_tree({ 3, 4, 5, 5, 4, -1, 7 });
		cout << "result tree: " << result_tree << endl;

		BinaryTree tree1({ 1, 3, 2, 5 });
		BinaryTree tree2({ 2, 1, 3, -1, 4, -1, 7 });
		BinaryTree output_tree(solution.mergeTrees(tree1.root(), tree2.root()));
		cout << "output tree: " << output_tree << endl;
	}

	return 0;
}