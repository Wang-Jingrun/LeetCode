/*
 * 707. 设计链表	url: https://leetcode.cn/problems/design-linked-list/
 * */

#include "linked_list.h"
using namespace std;

/**
 * Your MyLinkedList object will be instantiated and called as such:
 * MyLinkedList* obj = new MyLinkedList();
 * int param_1 = obj->get(index);
 * obj->addAtHead(val);
 * obj->addAtTail(val);
 * obj->addAtIndex(index,val);
 * obj->deleteAtIndex(index);
 */
int main()
{
	{
		cout << "exp1: " << endl;
		auto* linkedList = new MyLinkedList();
		linkedList->addAtHead(1);
		linkedList->_printLinkedList();

		linkedList->addAtTail(3);
		linkedList->_printLinkedList();

		linkedList->addAtIndex(1, 2);
		linkedList->_printLinkedList();

		cout << "get(1): " << linkedList->get(1) << endl;

		linkedList->deleteAtIndex(0);
		linkedList->_printLinkedList();

		cout << "get(0): " << linkedList->get(0) << endl;
	}

	{
		cout << "exp2: " << endl;
		auto* linkedList2 = new MyLinkedList();
		linkedList2->addAtIndex(0, 10);
		linkedList2->_printLinkedList();

		linkedList2->addAtIndex(0, 20);
		linkedList2->_printLinkedList();

		linkedList2->addAtIndex(1, 30);
		linkedList2->_printLinkedList();

		cout << "get(0): " << linkedList2->get(0) << endl;
	}
}