/*
 * 225. 用队列实现栈	url: https://leetcode.cn/problems/implement-stack-using-queues/
 *
 * 题目描述：请你仅使用两个队列实现一个后入先出（LIFO）的栈，并支持普通栈的全部四种操作（push、top、pop 和 empty）。
 * */

#include <iostream>
#include <queue>
using namespace std;

class MyStack
{
 public:
	MyStack()
	{
		m_queue = new queue<int>();
	}

	~MyStack()
	{
		if (m_queue != nullptr)
		{
			delete m_queue;
			m_queue = nullptr;
		}
	}

	void push(int x)
	{
		m_queue->push(x);

		// 执行 size - 1 次
		for (int i = 0; i < m_queue->size() - 1; ++i)
		{
			elementCycle();
		}
	}

	int pop()
	{
		int temp = m_queue->front();
		m_queue->pop();
		return temp;
	}

	int top()
	{
		return m_queue->front();
	}

	bool empty()
	{
		return m_queue->empty();
	}

	void elementCycle()
	{
		m_queue->push(m_queue->front());
		m_queue->pop();
	}

 private:
	queue<int>* m_queue;
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */

int main()
{
	MyStack obj = MyStack();
	obj.push(1);
	obj.push(2);
	obj.push(3);
	obj.top();
}