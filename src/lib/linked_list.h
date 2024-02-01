#pragma once
#include <iostream>


// Definition for singly-linked list.
struct ListNode
{
	int val;
	ListNode* next;
	ListNode() : val(0), next(nullptr) {}
	ListNode(int x) : val(x), next(nullptr) {}
	ListNode(int x, ListNode* next) : val(x), next(next) {}
};

class MyLinkedList
{
 public:
	MyLinkedList();
	~MyLinkedList();

	// todo 拷贝构造，拷贝复制

	ListNode* head();
	int size();

	int get(int index);

	void addAtHead(int val);
	void addAtTail(int val);
	void addAtTail(MyLinkedList& list);
	void addAtIndex(int index, int val);

	void makeLoop(int index);

	void deleteAtIndex(int index);

	void _printLinkedList();
	static void printLinkedList(ListNode* head, int max_len);
	static void printLinkedList(ListNode* head);
	static void printLinkedList_noHead(ListNode* head);
	static void printLinkedList_noHead(ListNode* head, int max_len);

 private:
	ListNode* m_head;
	int m_size;
};
