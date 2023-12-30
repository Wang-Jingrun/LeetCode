/*
 * 142. 环形链表 II	url: https://leetcode.cn/problems/linked-list-cycle-ii/
 *
 * 题目描述：给定一个链表的头节点 head ，返回链表开始入环的第一个节点。 如果链表无环，则返回 null。
 * 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，则链表中存在环。
 * 为了表示给定链表中的环，评测系统内部使用整数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
 * 如果 pos 是 -1，则在该链表中没有环。注意：pos 不作为参数进行传递，仅仅是为了标识链表的实际情况。不允许修改 链表。
 * */

#include <vector>
#include "day03_707_design_linked_list.h"

class Solution
{
 public:
	ListNode* detectCycle(ListNode* head)
	{
		auto fast = head;
		auto slow = head;

		while(fast != nullptr && fast->next!= nullptr)
		{
			fast = fast->next->next;
			slow = slow->next;

			if(fast == slow)
			{
				auto temp1 = head;
				auto temp2 = fast;

				while (temp1 != temp2)
				{
					temp1 = temp1->next;
					temp2 = temp2->next;
				}
				return temp1;
			}
		}

		return nullptr;
	}
};

class Solution2
{
 public:
	ListNode* detectCycle(ListNode* head)
	{
		auto cur = head;
		vector<ListNode*> list;

		while (cur != nullptr)
		{
			for (auto it : list)
			{
				if(cur == it)
				{
					return it;
				}
			}

			list.push_back(cur);
			cur = cur->next;
		}

		return nullptr;
	}
};

int main()
{
	Solution solution;

	{
		MyLinkedList linkedList1;
		linkedList1.addAtTail(3);
		linkedList1.addAtTail(2);
		linkedList1.addAtTail(0);
		linkedList1.addAtTail(4);
		linkedList1.makeLoop(1);

		cout << "exp1: " << endl;
		cout << "input: ";
		linkedList1._printLinkedList();
		cout << "output: ";
		// MyLinkedList 是带虚拟头节点实现的，因此传入传 next
		MyLinkedList::printLinkedList_noHead(solution.detectCycle(linkedList1.head()->next), 20);
	}

	{
		MyLinkedList linkedList1;
		linkedList1.addAtTail(1);
		linkedList1.addAtTail(2);
		linkedList1.makeLoop(0);

		cout << "exp1: " << endl;
		cout << "input: ";
		linkedList1._printLinkedList();
		cout << "output: ";
		// MyLinkedList 是带虚拟头节点实现的，因此传入传 next
		MyLinkedList::printLinkedList_noHead(solution.detectCycle(linkedList1.head()->next), 20);
	}
}
