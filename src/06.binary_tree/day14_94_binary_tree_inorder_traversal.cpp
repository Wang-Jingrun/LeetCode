/*
 * 94. 二叉树的中序遍历	url: https://leetcode.cn/problems/binary-tree-inorder-traversal/
 *
 * 题目描述：给定一个二叉树的根节点 root ，返回 它的 中序 遍历 。
 * */

#include <binary_tree.h>
#include <vector>
#include <iostream>

using namespace std;

class Solution // 递归遍历
{
 public:
	void traversal(TreeNode* root, vector<int>& result)
	{
		if (root == nullptr) return;

		traversal(root->left, result);
		result.push_back(root->val);
		traversal(root->right, result);
	}

	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		traversal(root, result);
		return result;
	}
};

class Solution2 // 非递归遍历
{
 public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		if (root == nullptr) return {};

		vector<int> result;
		stack<TreeNode*> stack;
		TreeNode* cur = root;

		while (cur != nullptr || !stack.empty())
		{
			// 指针来访问节点，访问到最底层
			if (cur != nullptr)
			{
				// 将访问的节点放进栈
				stack.push(cur);
				cur = cur->left;            // 左
			}
				// 从栈里弹出的数据，就是要处理的数据（放进result数组里的数据）
			else
			{
				cur = stack.top();
				stack.pop();
				result.push_back(cur->val);    // 中
				cur = cur->right;            // 右
			}
		}

		return result;
	}
};

class Solution3
{
 public:
	vector<int> inorderTraversal(TreeNode* root)
	{
		vector<int> result;
		stack<TreeNode*> st;
		if (root != nullptr) st.push(root);
		while (!st.empty())
		{
			TreeNode* node = st.top();
			if (node != nullptr)
			{
				st.pop(); // 将该节点弹出，避免重复操作，下面再将右中左节点添加到栈中
				if (node->right) st.push(node->right);  // 添加右节点（空节点不入栈）
				st.push(node);                          // 添加中节点
				st.push(nullptr); // 中节点访问过，但是还没有处理，加入空节点做为标记。
				if (node->left) st.push(node->left);    // 添加左节点（空节点不入栈）
			}
			else
			{
				// 只有遇到空节点的时候，才将下一个节点放进结果集
				st.pop();           // 将空节点弹出
				node = st.top();    // 重新取出栈中元素
				st.pop();
				result.push_back(node->val); // 加入到结果集
			}
		}
		return result;
	}
};

int main()
{

	Solution2 solution;
	std::vector<int> nums;
	std::vector<int> result;

	{
		// -1 表示null节点
		nums = { 1, -1, 2, 3 };
		BinaryTree tree(nums);
		cout << "exp1 ([1,2,3]): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: [ ";
		result = solution.inorderTraversal(tree.root());
		for (auto num : result)
			cout << num << " ";
		cout << " ]" << endl;
	}

	return 0;
}