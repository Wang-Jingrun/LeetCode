/*
 * 234. 回文链表		url: https://leetcode.cn/problems/palindrome-linked-list/
 *
 * 题目描述：给你一个单链表的头节点 head ，请你判断该链表是否为回文链表。如果是，返回 true ；否则，返回 false 。
 * */

#include <vector>
#include <stack>
#include <linked_list.h>
using namespace std;

class Solution
{
 public:
	bool isPalindrome(ListNode* head)
	{
		vector<int> vec;
		ListNode* cur = head;
		while (cur != nullptr)
		{
			vec.push_back(cur->val);
			cur = cur->next;
		}

		for (int left = 0, right = vec.size() - 1; left <= right; left++, right--)
		{
			if (vec[left] != vec[right]) return false;
		}
		return true;
	}
};

class Solution2
{
 private:
	ListNode* reverseList(ListNode* head)
	{
		if (head == nullptr || head->next == nullptr) return head;

		ListNode* cur = head;
		ListNode* pre = head->next;
		cur->next = nullptr;
		while (pre != nullptr)
		{
			ListNode* temp = pre->next;
			pre->next = cur;
			cur = pre;
			pre = temp;
		}
		return cur;
	}

 public:
	bool isPalindrome(ListNode* head)
	{
		if (head == nullptr || head->next == nullptr) return true;

		// 分割链表
		ListNode* slow = head; // 慢指针，找到链表中间分位置，作为分割
		ListNode* fast = head;
		ListNode* pre; // 记录慢指针的前一个节点，用来分割链表
		while (fast != nullptr && fast->next != nullptr)
		{
			pre = slow;
			slow = slow->next;
			fast = fast->next->next;
		}
		pre->next = nullptr; // 分割链表

		ListNode* cur1 = reverseList(slow); // 反转后半部分，总链表长度如果是奇数，cur2比cur1多一个节点
		ListNode* cur2 = head; // 前半部分
		while (cur1 != nullptr && cur2 != nullptr)
		{
			if (cur1->val != cur2->val) return false;

			cur1 = cur1->next;
			cur2 = cur2->next;
		}
		return true;
	}
};

int main()
{
	Solution2 solution;

	{
		MyLinkedList linkedList;
		linkedList.addAtTail(1);
		linkedList.addAtTail(2);
		linkedList.addAtTail(2);
		linkedList.addAtTail(1);

		cout << "exp1(true): " << endl;
		cout << "input: ";
		linkedList._printLinkedList();
		cout << "output: " << solution.isPalindrome(linkedList.head()->next) << endl;
	}

	cout << endl;

	{
		MyLinkedList linkedList;
		linkedList.addAtTail(1);
		linkedList.addAtTail(2);

		cout << "exp2(false): " << endl;
		cout << "input: ";
		linkedList._printLinkedList();
		cout << "output: " << solution.isPalindrome(linkedList.head()->next) << endl;
	}
}
