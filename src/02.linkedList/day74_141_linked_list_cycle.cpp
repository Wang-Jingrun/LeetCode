/*
 * 141. 环形链表		url: https://leetcode.cn/problems/linked-list-cycle/
 *
 * 题目描述：给你一个链表的头节点 head ，判断链表中是否有环。
 *
 * 如果链表中有某个节点，可以通过连续跟踪 next 指针再次到达，
 * 则链表中存在环。 为了表示给定链表中的环，评测系统内部使用整
 * 数 pos 来表示链表尾连接到链表中的位置（索引从 0 开始）。
 * 注意：pos 不作为参数进行传递 。仅仅是为了标识链表的实际情况。
 *
 * 如果链表中存在环 ，则返回 true 。 否则，返回 false 。
 * */

#include <vector>
#include <stack>
#include <linked_list.h>
using namespace std;

class Solution
{
 public:
	bool hasCycle(ListNode* head)
	{
		ListNode* slow = head;
		ListNode* fast = head;

		while (fast != nullptr && fast->next != nullptr)
		{
			slow = slow->next;
			fast = fast->next->next;

			if (slow == fast) return true;
		}
		return false;
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
		linkedList1.addAtTail(-4);
		linkedList1.makeLoop(1);

		cout << "exp1(true): " << endl;
		cout << "output: " << solution.hasCycle(linkedList1.head()->next) << endl;
	}

	cout << endl;

	{
		MyLinkedList linkedList;
		linkedList.addAtTail(1);
		linkedList.addAtTail(2);

		cout << "exp2(false): " << endl;
		cout << "output: " << solution.hasCycle(linkedList.head()->next) << endl;
	}
}
