/*
 * 24. 两两交换链表中的节点		url: https://leetcode.cn/problems/swap-nodes-in-pairs/
 *
 * 题目描述：给你一个链表，两两交换其中相邻的节点，并返回交换后链表的头节点。
 * 你必须在不修改节点内部的值的情况下完成本题（即，只能进行节点交换）。
 * */

#include <linked_list.h>
using namespace std;

class Solution
{
 public:
	ListNode* swapPairs(ListNode* head)
	{
		// 无虚拟头节点版本
		ListNode* vHead = new ListNode(0, head);
		ListNode* pre = vHead;
		ListNode* cur;
		ListNode* next1;
		ListNode* next2;
		while (pre->next != nullptr && pre->next->next != nullptr)
		{
			// 保存后面的节点，防止指针修改后无法访问到
			cur = pre->next;
			next1 = pre->next->next;
			next2 = next1->next;

			pre->next = next1;    // 步骤一
			next1->next = cur;    // 步骤二
			cur->next = next2;    // 步骤三

			pre = pre->next->next;
		}
		head = vHead->next;
		delete vHead;
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
		linkedList1.addAtTail(3);
		linkedList1.addAtTail(4);

		cout << "exp1: " << endl;
		cout << "input: ";
		linkedList1._printLinkedList();
		cout << "output: ";
		// MyLinkedList 是带虚拟头节点实现的，因此传入传 next
		MyLinkedList::printLinkedList_noHead(solution.swapPairs(linkedList1.head()->next));
	}

	{
		MyLinkedList linkedList2;
		linkedList2.addAtTail(1);

		cout << "exp2: " << endl;
		cout << "input: ";
		linkedList2._printLinkedList();
		cout << "output: ";
		// MyLinkedList 是带虚拟头节点实现的，因此传入传 next
		MyLinkedList::printLinkedList_noHead(solution.swapPairs(linkedList2.head()->next));
	}
}
