#include "linked_list.h"

MyLinkedList::MyLinkedList() : m_size(0)
{
	m_head = new ListNode(0, nullptr);
}

// 析构函数，释放所有节点的内存
MyLinkedList::~MyLinkedList()
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

ListNode* MyLinkedList::head()
{
	return m_head;
}

int MyLinkedList::size()
{
	return m_size;
}

int MyLinkedList::get(int index)
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

void MyLinkedList::addAtHead(int val)
{
	// 头节点直接插入
	auto* node = new ListNode(val, m_head->next);
	m_head->next = node;
	m_size++;
}

void MyLinkedList::addAtTail(int val)
{
	ListNode* current = m_head;
	while (current->next != nullptr)
	{
		current = current->next;
	}
	current->next = new ListNode(val, nullptr);
	m_size++;
}

void MyLinkedList::addAtTail(MyLinkedList& list)
{
	ListNode* current = m_head;
	while (current->next != nullptr)
	{
		current = current->next;
	}
	current->next = list.head()->next;
	m_size += list.size();
}

void MyLinkedList::addAtIndex(int index, int val)
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

void MyLinkedList::makeLoop(int index)
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

void MyLinkedList::deleteAtIndex(int index)
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

void MyLinkedList::_printLinkedList()
{
	int count = 0;
	auto cur = m_head;
	while (cur->next != nullptr)
	{
		if (count >= m_size)
		{
			std::cout << "loop val: " << cur->next->val << " ";
			break;
		}

		std::cout << cur->next->val << " ";
		cur = cur->next;
		count++;
	}
	std::cout << std::endl;
}

void MyLinkedList::printLinkedList(ListNode* head, int max_len)
{
	int count = 0;
	auto cur = head;
	while (cur->next != nullptr)
	{
		if (count >= max_len)
			break;

		std::cout << cur->next->val << " ";
		cur = cur->next;
		count++;
	}
	std::cout << std::endl;
}

void MyLinkedList::printLinkedList(ListNode* head)
{
	printLinkedList(head, INT_MAX);
}

void MyLinkedList::printLinkedList_noHead(ListNode* head)
{
	if (head == nullptr)
		return;

	std::cout << head->val << " ";
	printLinkedList(head, INT_MAX);
}

void MyLinkedList::printLinkedList_noHead(ListNode* head, int max_len)
{
	if (head == nullptr)
		return;

	std::cout << head->val << " ";
	printLinkedList(head, max_len);
}