/*
 * 143. 重排链表		url: https://leetcode.cn/problems/reorder-list/
 *
 * 题目描述：给定一个单链表 L 的头节点 head ，单链表 L 表示为：
 * 		L0 → L1 → … → Ln - 1 → Ln
 * 请将其重新排列后变为：
 * 		L0 → Ln → L1 → Ln - 1 → L2 → Ln - 2 → …
 * 不能只是单纯的改变节点内部的值，而是需要实际的进行节点交换。
 * */

#include <vector>
#include <stack>
#include <linked_list.h>
using namespace std;

class Solution
{
 public:
	void reorderList(ListNode* head)
	{
		// 使用栈保存倒序的链表，同时统计链表长度
		stack<ListNode*> st;
		ListNode* cur = head;
		int size = 0;
		while (cur != nullptr)
		{
			++size;
			st.push(cur);
			cur = cur->next;
		}

		cur = head;
		for (int i = 0; i < size / 2; i++)
		{
			ListNode* temp = st.top();
			st.pop();

			// 插入操作
			temp->next = cur->next;
			cur->next = temp;

			// 获取下一次操作的节点
			cur = temp->next;
		}
		cur->next = nullptr; // 最后一个节点末尾置空
	}
};

class Solution2
{
 public:
	void reorderList(ListNode* head)
	{
		deque<ListNode*> que;
		ListNode* cur = head;
		if (cur == nullptr) return;

		while (cur->next != nullptr)
		{
			que.push_back(cur->next);
			cur = cur->next;
		}

		cur = head;
		int count = 0; // 计数，偶数去后面，奇数取前面
		ListNode* node;
		while (que.size())
		{
			if (count % 2 == 0)
			{
				node = que.back();
				que.pop_back();
			}
			else
			{
				node = que.front();
				que.pop_front();
			}
			count++;
			cur->next = node;
			cur = cur->next;
		}
		cur->next = nullptr; // 注意结尾
	}
};

class Solution3
{
 private:
	// 反转链表
	ListNode* reverseList(ListNode* head)
	{
		ListNode* temp; // 保存cur的下一个节点
		ListNode* cur = head;
		ListNode* pre = nullptr;
		while (cur)
		{
			temp = cur->next;  // 保存一下 cur的下一个节点，因为接下来要改变cur->next
			cur->next = pre; // 翻转操作
			// 更新pre 和 cur指针
			pre = cur;
			cur = temp;
		}
		return pre;
	}

 public:
	void reorderList(ListNode* head)
	{
		if (head == nullptr) return;
		// 使用快慢指针法，将链表分成长度均等的两个链表head1和head2
		// 如果总链表长度为奇数，则head1相对head2多一个节点
		ListNode* fast = head;
		ListNode* slow = head;
		while (fast && fast->next && fast->next->next)
		{
			fast = fast->next->next;
			slow = slow->next;
		}
		ListNode* head1 = head;
		ListNode* head2;
		head2 = slow->next;
		slow->next = nullptr;

		// 对head2进行翻转
		head2 = reverseList(head2);

		// 将head1和head2交替生成新的链表head
		ListNode* cur1 = head1;
		ListNode* cur2 = head2;
		ListNode* cur = head;
		cur1 = cur1->next;
		int count = 0; // 偶数取head2的元素，奇数取head1的元素
		while (cur1 && cur2)
		{
			if (count % 2 == 0)
			{
				cur->next = cur2;
				cur2 = cur2->next;
			}
			else
			{
				cur->next = cur1;
				cur1 = cur1->next;
			}
			count++;
			cur = cur->next;
		}
		if (cur2 != nullptr)
		{ // 处理结尾
			cur->next = cur2;
		}
		if (cur1 != nullptr)
		{
			cur->next = cur1;
		}
	}
};

int main()
{
	Solution solution;

	{
		MyLinkedList linkedList;
		linkedList.addAtTail(1);
		linkedList.addAtTail(2);
		linkedList.addAtTail(3);
		linkedList.addAtTail(4);

		cout << "exp1(1 4 3 2): " << endl;
		cout << "input: ";
		linkedList._printLinkedList();
		cout << "output: ";
		// MyLinkedList 是带虚拟头节点实现的，因此传入传 next
		solution.reorderList(linkedList.head()->next);
		linkedList._printLinkedList();
	}

	cout << endl;

	{
		MyLinkedList linkedList;
		linkedList.addAtTail(1);
		linkedList.addAtTail(2);
		linkedList.addAtTail(3);
		linkedList.addAtTail(4);
		linkedList.addAtTail(5);

		cout << "exp2(1 5 2 4 3): " << endl;
		cout << "input: ";
		linkedList._printLinkedList();
		cout << "output: ";
		// MyLinkedList 是带虚拟头节点实现的，因此传入传 next
		solution.reorderList(linkedList.head()->next);
		linkedList._printLinkedList();
	}
}
