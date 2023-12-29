/*
 * 203. 移除链表元素	url: https://leetcode.cn/problems/remove-linked-list-elements/
 * */

#include "day03_707_design_linked_list.h"

class Solution
{
 public:
	ListNode* removeElements(ListNode* head, int val)
	{
		// 创建一个头节点, 其值无用，便于进行删除操作
		ListNode* hd = new ListNode(0, head);
		ListNode* front = hd;
		ListNode* current = head;
		while (current != nullptr)
		{
			// 删除节点
			if (current->val == val)
			{
				front->next = current->next;
				delete current;    // 释放需要删除的节点的内存
				current = front->next;
			}
			else
			{
				front = current;
				current = current->next;
			}
		}

		head = hd->next;
		delete hd; // 释放创建的虚拟头节点的内存
		return head;
	}
};

class Solution2
{
 public:
	ListNode* removeElements(ListNode* head, int val)
	{
		ListNode* temp = nullptr;
		while (head != nullptr && head->val == val)
		{
			temp = head;
			head = head->next;
			delete temp;
		}

		ListNode* current = head;
		while (current != nullptr && current->next != nullptr)
		{
			// 删除节点
			if (current->next->val == val)
			{
				temp = current->next;
				current->next = current->next->next;
				delete temp;    // 释放需要删除的节点的内存
			}
			else
			{
				current = current->next;
			}
		}

		return head;
	}
};

int main()
{
	Solution solution;

	{
		MyLinkedList linkedList1;
		linkedList1.addAtTail(1);
		linkedList1.addAtTail(2);
		linkedList1.addAtTail(6);
		linkedList1.addAtTail(3);
		linkedList1.addAtTail(4);
		linkedList1.addAtTail(5);
		linkedList1.addAtTail(6);

		cout << "exp1, remove val = 6: " << endl;
		cout << "input: ";
		linkedList1._printLinkedList();
		cout << "output: ";
		MyLinkedList::printLinkedList(solution.removeElements(linkedList1.head(), 6));
	}

	{
		MyLinkedList linkedList2;
		linkedList2.addAtTail(7);
		linkedList2.addAtTail(7);
		linkedList2.addAtTail(7);
		linkedList2.addAtTail(7);

		cout << "exp2, remove val = 7: " << endl;
		cout << "input: ";
		linkedList2._printLinkedList();
		cout << "output: ";
		MyLinkedList::printLinkedList(solution.removeElements(linkedList2.head(), 7));
	}
}