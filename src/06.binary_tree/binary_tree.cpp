#include "binary_tree.h"

BinaryTree::BinaryTree() : m_root(nullptr)
{
}

BinaryTree::~BinaryTree()
{
	_destroy(m_root);
}

BinaryTree::BinaryTree(std::vector<int>& nums) : m_root(nullptr)
{
	// -1 表示空节点
	if (nums.empty() || nums[0] == -1)
		return;

	m_root = new TreeNode(nums[0]);
	std::queue<TreeNode*> nodes;
	nodes.push(m_root);

	int i = 1;
	while (!nodes.empty() && i < nums.size())
	{
		TreeNode* current = nodes.front();
		nodes.pop();

		// 左子节点
		if (i < nums.size() && nums[i] != -1)
		{
			current->left = new TreeNode(nums[i]);
			nodes.push(current->left);
		}

		++i;

		// 右子节点
		if (i < nums.size() && nums[i] != -1)
		{
			current->right = new TreeNode(nums[i]);
			nodes.push(current->right);
		}

		++i;
	}
}

TreeNode* BinaryTree::root()
{
	return m_root;
}

bool BinaryTree::isEmpty()
{
	return m_root == nullptr;
}

std::vector<std::vector<int>> BinaryTree::levelOrder()
{
	if (m_root == nullptr) return {};

	std::vector<std::vector<int>> result;
	std::vector<int> layers;
	std::queue<TreeNode*> queue;
	queue.push(m_root);
	int size;    // 通过 size 记录每层的节点数

	while (!queue.empty())
	{
		size = queue.size();

		for (int i = size; i > 0; --i)
		{
			auto node = queue.front();
			queue.pop();

			layers.push_back(node->val);
			if (node->left != nullptr) queue.push(node->left);
			if (node->right != nullptr) queue.push(node->right);
		}
		result.push_back(layers);
		layers.clear();
	}

	return result;
}

// 递归遍历二叉树，返回树的内容的字符串形式
std::string BinaryTree::str(TreeNode* root) const
{
	if (root == nullptr) return "";

	std::stringstream ss;
	ss << root->val;

	if (root->left != nullptr || root->right != nullptr)
	{
		ss << " (";
		ss << str(root->left);
		ss << ", ";
		ss << str(root->right);
		ss << ")";
	}

	return ss.str();
}

void BinaryTree::_destroy(TreeNode* root)
{
	if (root != nullptr)
	{
		_destroy(root->left);
		_destroy(root->right);
		// std::cout << "delete:" << root->val << " ";
		delete root;
		root = nullptr;
	}
}
