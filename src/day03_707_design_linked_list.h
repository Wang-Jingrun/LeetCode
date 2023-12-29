/*
 * 707. 设计链表	url: https://leetcode.cn/problems/design-linked-list/
 * */

#pragma once
#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode {
	int val;
	ListNode *next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class MyLinkedList
{
 public:
	MyLinkedList() : m_size(0)
	{
		m_head = new ListNode(0, nullptr);
	}

	// 析构函数，释放所有节点的内存
	~MyLinkedList()
	{
		if (m_head != nullptr)
		{
			ListNode* temp = nullptr;
			while (m_head != nullptr)
			{
				temp = m_head;
				m_head = m_head->next;
				delete temp;
			}
			m_head = nullptr;
			temp = nullptr;
			m_size = 0;
		}
	}

	int get(int index)
	{
		// 下标越界，直接返回 -1
		if (index < 0 || index >= m_size)
		{
			return -1;
		}

		// 下标为 index，即向后移动 index 次
		ListNode* current = m_head->next;
		while (index--)
		{
			current = current->next;
		}
		return current->val;
	}

	void addAtHead(int val)
	{
		// 头节点直接插入
		auto* node = new ListNode(val, m_head->next);
		m_head->next = node;
		m_size++;
	}

	void addAtTail(int val)
	{
		ListNode* current = m_head;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new ListNode(val, nullptr);
		m_size++;
	}

	void addAtIndex(int index, int val)
	{
		if (index < 0 || index > m_size)
		{
			// 下标越界，直接返回
			return;
		}

		// 遍历到插入位置的前一个位置
		ListNode* current = m_head;
		while (index--)
		{
			current = current->next;
		}

		auto node = new ListNode(val, current->next);
		current->next = node;
		m_size++;
	}

	void deleteAtIndex(int index)
	{
		if (index < 0 || index > m_size)
		{
			// 下标越界，直接返回
			return;
		}

		// 遍历到删除位置的前一个位置
		ListNode* current = m_head;
		while (index--)
		{
			current = current->next;
		}
		auto temp = current->next;
		current->next = current->next->next;
		delete temp;
		m_size--;
	}

	void _printLinkedList()
	{
		auto cur = m_head;
		while (cur->next != nullptr)
		{
			cout << cur->next->val << " ";
			cur = cur->next;
		}
		cout << endl;
	}

	ListNode* head()
	{
		return m_head;
	}

	static void printLinkedList(ListNode* head)
	{
		auto cur = head;
		while (cur->next != nullptr)
		{
			cout << cur->next->val << " ";
			cur = cur->next;
		}
		cout << endl;
	}

	static void printLinkedList_noHead(ListNode* head)
	{
		cout << head->val << " ";
		auto cur = head;
		while (cur->next != nullptr)
		{
			cout << cur->next->val << " ";
			cur = cur->next;
		}
		cout << endl;
	}

 private:
	ListNode* m_head;
	int m_size;
};

class MyLinkedList2
{
 public:
	MyLinkedList2() : m_head(nullptr), m_size(0) {}

	~MyLinkedList2()    // 析构函数，释放所有节点的内存
	{
		if (m_head != nullptr)
		{
			ListNode* temp = nullptr;
			while (m_head != nullptr)
			{
				temp = m_head;
				m_head = m_head->next;
				delete temp;
			}
			m_head = nullptr;
			m_size = 0;
		}
	}

	int get(int index)
	{
		// 下标越界，直接返回 -1
		if (index < 0 || index >= m_size)
		{
			return -1;
		}

		// 下标为 index，即向后移动 index 次
		ListNode* current = m_head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->val;
	}

	void addAtHead(int val)
	{
		// 头节点直接插入
		ListNode* node = new ListNode(val, m_head);
		m_head = node;
		m_size++;
	}

	void addAtTail(int val)
	{
		// 头节点为空，相当于从头节点插入
		if (m_head == nullptr)
		{
			addAtHead(val);
			return;
		}

		// 头节点非空，遍历到 nullptr 前一个节点，方便插入
		ListNode* current = m_head;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new ListNode(val, nullptr);
		m_size++;
	}

	void addAtIndex(int index, int val)
	{
		if (index < 0 || index > m_size)
		{
			// 下标越界，直接返回
			return;
		}
		else if (index == m_size)
		{
			// 下标为 size，相当于尾部插入
			addAtTail(val);
			return;
		}
		else if (index == 0)
		{
			// 下标为 0，相当于头部插入
			addAtHead(val);
			return;
		}

		// 遍历到插入位置的前一个位置
		ListNode* current = m_head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->next;
		}

		auto node = new ListNode(val, current->next);
		current->next = node;
		m_size++;
	}

	void deleteAtIndex(int index)
	{
		if (index < 0 || index >= m_size)
		{
			// 下标越界，直接返回
			return;
		}

		// 下标为 0，删除头节点，需要特殊处理
		if (index == 0)
		{
			auto temp = m_head;
			m_head = m_head->next;
			delete temp;
			m_size--;
			return;
		}

		// 遍历到删除位置的前一个位置
		ListNode* current = m_head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->next;
		}
		auto temp = current->next;
		current->next = current->next->next;
		delete temp;
		m_size--;
	}

 private:
	ListNode* m_head;
	int m_size;
};