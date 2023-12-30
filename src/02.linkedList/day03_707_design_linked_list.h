/*
 * 707. 设计链表	url: https://leetcode.cn/problems/design-linked-list/
 * */

#pragma once
#include <iostream>
using namespace std;

// Definition for singly-linked list.
struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr)
	{
	}
	ListNode(int x) : val(x), next(nullptr)
	{
	}
	ListNode(int x, ListNode* next) : val(x), next(next)
	{
	}
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
			// 使用 size 辅助析构，防止链表中有环
			while ((m_head != nullptr) && (m_size <= 0))
			{
				temp = m_head;
				m_head = m_head->next;
				delete temp;
				m_size--;
			}
			m_head = nullptr;
			temp = nullptr;
			m_size = 0;
		}
	}

	ListNode* head()
	{
		return m_head;
	}

	int size()
	{
		return m_size;
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

	void addAtTail(MyLinkedList& list)
	{
		ListNode* current = m_head;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = list.head()->next;
		m_size += list.size();
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

	void makeLoop(int index)
	{
		// 使链表的尾部连接到下标为 index 的节点
		if (index < 0 || index > m_size)
		{
			// 下标越界，直接返回
			return;
		}

		// 获取下标为 index 的节点
		ListNode* current = m_head;
		while (index--)
		{
			current = current->next;
		}
		auto temp = current->next;

		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = temp;
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
		int count = 0;
		auto cur = m_head;
		while (cur->next != nullptr)
		{
			if (count >= m_size)
			{
				cout << "loop val: " << cur->next->val << " ";
				break;
			}

			cout << cur->next->val << " ";
			cur = cur->next;
			count++;
		}
		cout << endl;
	}

	static void printLinkedList(ListNode* head, int max_len)
	{
		int count = 0;
		auto cur = head;
		while (cur->next != nullptr)
		{
			if (count >= max_len)
				break;

			cout << cur->next->val << " ";
			cur = cur->next;
			count++;
		}
		cout << endl;
	}

	static void printLinkedList(ListNode* head)
	{
		printLinkedList(head, INT_MAX);
	}

	static void printLinkedList_noHead(ListNode* head)
	{
		if (head == nullptr)
			return;

		cout << head->val << " ";
		printLinkedList(head, INT_MAX);
	}

	static void printLinkedList_noHead(ListNode* head, int max_len)
	{
		if (head == nullptr)
			return;

		cout << head->val << " ";
		printLinkedList(head, max_len);
	}

 private:
	ListNode* m_head;
	int m_size;
};