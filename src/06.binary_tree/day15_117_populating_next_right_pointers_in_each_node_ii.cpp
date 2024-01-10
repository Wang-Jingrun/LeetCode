/*
 * 117. 填充每个节点的下一个右侧节点指针 II	url: https://leetcode.cn/problems/populating-next-right-pointers-in-each-node-ii/
 *
 * 题目描述：给定一个二叉树 ，填充它的每个 next 指针，让这个指针指向其下一个右侧节点。
 * 如果找不到下一个右侧节点，则将 next 指针设置为 NULL 。
 * 初始状态下，所有 next 指针都被设置为 NULL 。
 * */
// 二叉树定义如下：
struct Node
{
	int val;
	Node* left;
	Node* right;
	Node* next;
};

#include "binary_tree.h"
#include <vector>
#include <iostream>
#include <algorithm>

using namespace std;

class Solution
{
 public:
	Node* connect(Node* root)
	{
		if (root == nullptr) return nullptr;

		vector<int> result;
		int size;

		Node* cur;
		queue<Node*> queue;
		queue.push(root);
		while (!queue.empty())
		{
			size = (int)queue.size();

			for (int i = size; i > 0; --i)
			{
				cur = queue.front();
				queue.pop();
				cur->next = queue.front();	// next 指针指向下一个节点

				if (cur->left != nullptr) queue.push(cur->left);
				if (cur->right != nullptr) queue.push(cur->right);
			}
			cur->next = nullptr;	// 每层的最后一个节点的 next 指针指向nullptr
		}
		return root;
	}
};

int main()
{


	return 0;
}