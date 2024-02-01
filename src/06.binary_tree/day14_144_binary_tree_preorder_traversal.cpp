/*
 * 144. 二叉树的前序遍历	url: https://leetcode.cn/problems/binary-tree-preorder-traversal/
 *
 * 题目描述：给你二叉树的根节点 root ，返回它节点值的 前序 遍历。
 * */

#include <binary_tree.h>
using namespace std;

class Solution // 递归遍历
{
 public:
	void traversal(TreeNode* root, vector<int>& result)
	{
		if (root == nullptr) return;

		result.push_back(root->val);
		traversal(root->left, result);
		traversal(root->right, result);
	}

	vector<int> preorderTraversal(TreeNode* root)
	{
		vector<int> result;
		traversal(root, result);
		return result;
	}
};

class Solution2 // 非递归遍历
{
 public:
	vector<int> preorderTraversal(TreeNode* root)
	{
		if (root == nullptr) return {};

		vector<int> result;
		stack<TreeNode*> stack;
		TreeNode* cur;

		stack.push(root);
		while (!stack.empty())
		{
			cur = stack.top();    // 中
			stack.pop();
			result.push_back(cur->val);
			if (cur->right != nullptr) stack.push(cur->right);    // 右（空节点不入栈）
			if (cur->left != nullptr) stack.push(cur->left);    // 左（空节点不入栈）
		}

		return result;
	}
};

class Solution3
{
 public:
	vector<int> preorderTraversal(TreeNode* root)
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
				if (node->left) st.push(node->left);    // 添加左节点（空节点不入栈）
				st.push(node);                          // 添加中节点
				st.push(nullptr); // 中节点访问过，但是还没有处理，加入空节点做为标记。
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

	Solution3 solution;
	std::vector<int> nums;
	std::vector<int> result;

	{
		// -1 表示null节点
		nums = { 1, -1, 2, 3 };
		BinaryTree tree(nums);
		cout << "exp1 ([1,2,3]): " << endl;
		cout << "input tree: " << tree << endl;

		cout << "result: [ ";
		result = solution.preorderTraversal(tree.root());
		for (auto num : result)
			cout << num << " ";
		cout << " ]" << endl;
	}

	return 0;
}