/*
 * 206. 反转链表	url: https://leetcode.cn/problems/reverse-linked-list/
 * */

#include "day03_707_design_linked_list.h"

class Solution
{
 public:
	ListNode* reverseList(ListNode* head)
	{
		ListNode* pre = nullptr;    // 反转后旧头节点的前一个节点是 nullptr
		ListNode* cur = head->next;
		ListNode* temp = nullptr;

		while (cur != nullptr)
		{
			// temp 是为了存放 cur 的下一个节点，以防 cur->next 被替换后丢失
			temp = cur->next;
			cur->next = pre;
			pre = cur;
			cur = temp;
		}

		return pre;
	}
};

class Solution2	// 递归解法
{
 public:
	ListNode* reverse(ListNode* pre, ListNode* cur)
	{
		if (cur == nullptr)
		{
			return pre;
		}
		ListNode* temp = cur->next;
		cur->next = pre;
		return reverse(cur, temp);
	}

	ListNode* reverseList(ListNode* head)
	{
		return reverse(nullptr, head);
	}
};

int main()
{
	Solution solution;

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
		cout << "output: ";
		MyLinkedList::printLinkedList_noHead(solution.reverseList(linkedList1.head()));
	}

	{
		MyLinkedList linkedList2;
		linkedList2.addAtTail(1);
		linkedList2.addAtTail(2);

		cout << "exp2: " << endl;
		cout << "input: ";
		linkedList2._printLinkedList();
		cout << "output: ";
		MyLinkedList::printLinkedList_noHead(solution.reverseList(linkedList2.head()));
	}
}
