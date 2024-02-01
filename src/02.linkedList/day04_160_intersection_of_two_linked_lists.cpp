/*
 * 160. 相交链表		url: https://leetcode.cn/problems/intersection-of-two-linked-lists/
 *
 * 题目描述：给你两个单链表的头节点 headA 和 headB ，请你找出并返回两个单链表相交的起始节点。
 * 如果两个链表没有交点，返回 null 。
 * */

#include <vector>
#include <stack>
#include <linked_list.h>
using namespace std;

class Solution
{
 public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
	{
		ListNode* result = nullptr;
		stack<ListNode*> listA;
		stack<ListNode*> listB;
		ListNode* curA = headA;
		ListNode* curB = headB;

		while (curA != nullptr)
		{
			listA.push(curA);
			curA = curA->next;
		}

		while (curB != nullptr)
		{
			listB.push(curB);
			curB = curB->next;
		}

		int len = listA.size() > listB.size() ? listA.size() : listB.size();

		while ((!listA.empty()) && (!listB.empty()))
		{
			if (listA.top() == listB.top())
				result = listA.top();
			listA.pop();
			listB.pop();
			len--;
		}

		return result;
	}
};

class Solution2
{
 public:
	ListNode* getIntersectionNode(ListNode* headA, ListNode* headB)
	{
		ListNode* curA = headA;
		ListNode* curB = headB;
		int lenA = 0, lenB = 0;

		while (curA != nullptr)
		{
			curA = curA->next;
			lenA++;
		}

		while (curB != nullptr)
		{
			curB = curB->next;
			lenB++;
		}

		curA = headA;
		curB = headB;

		// 让curA为最长链表的头，lenA为其长度
		if (lenB > lenA)
		{
			swap(lenA, lenB);
			swap(curA, curB);
		}

		// 求长度差
		int gap = lenA - lenB;
		// 让curA和curB在同一起点上（末尾位置对齐）
		while (gap--)
		{
			curA = curA->next;
		}

		// 遍历curA 和 curB，遇到相同则直接返回
		while (curA != nullptr)
		{
			// 因为是节点的内存相同，那么后面的节点自然也就相同
			if (curA == curB)
			{
				return curA;
			}
			curA = curA->next;
			curB = curB->next;
		}

		return nullptr;
	}
};

int main()
{
	Solution2 solution;

	{
		MyLinkedList linkedList1;
		linkedList1.addAtTail(4);
		linkedList1.addAtTail(1);

		MyLinkedList linkedList2;
		linkedList2.addAtTail(5);
		linkedList2.addAtTail(0);
		linkedList2.addAtTail(1);

		MyLinkedList linkedList3;
		linkedList3.addAtTail(8);
		linkedList3.addAtTail(4);
		linkedList3.addAtTail(5);

		linkedList1.addAtTail(linkedList3);
		linkedList2.addAtTail(linkedList3);

		cout << "exp1: " << endl;
		cout << "input: " << endl;
		linkedList1._printLinkedList();
		linkedList2._printLinkedList();
		cout << "output [8, 4, 5]: " << endl;
		MyLinkedList::printLinkedList_noHead(solution.getIntersectionNode(linkedList1.head()->next, linkedList2.head()->next));
	}
}
