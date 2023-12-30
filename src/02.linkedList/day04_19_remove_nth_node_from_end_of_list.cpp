/*
 * 19. 删除链表的倒数第 N 个结点	url: https://leetcode.cn/problems/remove-nth-node-from-end-of-list/
 *
 * 题目描述：给你一个链表，删除链表的倒数第 n 个结点，并且返回链表的头结点。
 * */

#include <vector>
#include "day03_707_design_linked_list.h"

class Solution
{
 public:
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		// 有虚拟头节点
		vector<ListNode*> list;
		ListNode* cur = head;

		// 遍历一遍链表，同时存储其节点信息
		while(cur!= nullptr)
		{
			list.push_back(cur);
			cur=cur->next;
		}

		// 找到倒数第 n 个节点的前一个节点
		if(list.size() == 1)
		{
			delete head;
			return nullptr;
		}
		else if(list.size() == n)
		{
			auto temp = head;
			head = head->next;
			delete temp;
			return head;
		}
		else
		{
			cur = list[list.size() - n - 1];
		}
		auto temp = cur->next;
		cur->next = cur->next->next;
		delete temp;

		return head;
	}
};

class Solution2
{
 public:
	// 快慢指针法
	ListNode* removeNthFromEnd(ListNode* head, int n)
	{
		// 有虚拟头节点
		auto vHead = new ListNode(0, head);
		auto fast = vHead;
		auto slow = vHead;

		n++;    // 需要 slow 指向被删除的前一个节点
		while (n--)
		{
			fast = fast->next;
		}

		// 遍历到 fast 指向 nullptr，此时 slow 正好是被删除的前一个节点
		while (fast != nullptr)
		{
			slow = slow->next;
			fast = fast->next;
		}

		// 删除节点
		fast = slow->next;
		slow->next = slow->next->next;
		delete fast;

		// 删除虚拟头节点
		head = vHead->next;
		delete vHead;
		return head;
	}
};

int main()
{
	Solution2 solution;

	{
		MyLinkedList linkedList1;
		linkedList1.addAtTail(1);
		linkedList1.addAtTail(2);
		linkedList1.addAtTail(3);
		linkedList1.addAtTail(4);
		linkedList1.addAtTail(5);

		cout << "exp1: " << endl;
		cout << "input: ";
		linkedList1._printLinkedList();
		cout << "output [1, 2, 3, 5]: ";
		// MyLinkedList 是带虚拟头节点实现的，因此传入传 next
		MyLinkedList::printLinkedList_noHead(solution.removeNthFromEnd(linkedList1.head()->next, 2), linkedList1.size() - 1);
	}

	{
		MyLinkedList linkedList2;
		linkedList2.addAtTail(1);
		linkedList2.addAtTail(2);

		cout << "exp2: " << endl;
		cout << "input: ";
		linkedList2._printLinkedList();
		cout << "output [1]: ";
		// MyLinkedList 是带虚拟头节点实现的，因此传入传 next
		MyLinkedList::printLinkedList_noHead(solution.removeNthFromEnd(linkedList2.head()->next, 1), linkedList2.size() - 1);
	}

	{
		MyLinkedList linkedList3;
		linkedList3.addAtTail(1);
		linkedList3.addAtTail(2);

		cout << "exp3: " << endl;
		cout << "input: ";
		linkedList3._printLinkedList();
		cout << "output [2]: ";
		// MyLinkedList 是带虚拟头节点实现的，因此传入传 next
		MyLinkedList::printLinkedList_noHead(solution.removeNthFromEnd(linkedList3.head()->next, 2), linkedList3.size() - 1);
	}
}
