#include "n_ary_tree.h"

NAryTree::NAryTree() : m_root(nullptr)
{
}

NAryTree::NAryTree(const std::vector<int>& nums) : m_root(nullptr)
{
	*this = nums;
}

NAryTree::~NAryTree()
{
	clear(m_root);
}

void NAryTree::clear(Node* root)
{
	if (root != nullptr)
	{
		for (auto it : root->children)
		{
			clear(it);
		}
	}

	delete root;
	root = nullptr;
}

NAryTree& NAryTree::operator=(const std::vector<int>& nums)
{
	clear(m_root);

	// -1 表示空节点
	if (nums.empty() || nums[0] == -1) return *this;

	m_root = new Node(nums[0]);
	std::queue<Node*> nodes;
	nodes.push(m_root);

	int i = 2;
	while ((!nodes.empty()) && i < nums.size())
	{
		Node* current = nodes.front();
		nodes.pop();

		while (i < nums.size() && nums[i] != -1)
		{
			current->children.push_back(new Node(nums[i]));
			nodes.push(current->children.back());
			i++;
		}
		i++;
	}
	return *this;
}

Node* NAryTree::root()
{
	return m_root;
}

bool NAryTree::isEmpty()
{
	return m_root == nullptr;
}

// 层序遍历
std::vector<std::vector<int>> NAryTree::levelOrder()
{
	if (m_root == nullptr) return {};

	std::vector<std::vector<int>> result;
	std::vector<int> nodes; // 记录每次节点值
	int size; // 记录每次节点数

	Node* cur;
	std::queue<Node*> queue;
	queue.push(m_root);
	while (!queue.empty())
	{
		size = queue.size();

		for (int i = size; i > 0; --i)
		{
			cur = queue.front();
			queue.pop();
			nodes.push_back(cur->val);

			for (auto item : cur->children)
			{
				if (item != nullptr)
					queue.push(item);
			}
		}
		result.push_back(nodes);
		nodes.clear();
	}
	return result;
}

