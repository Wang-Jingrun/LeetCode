/*
 * 232. 用栈实现队列	url: https://leetcode.cn/problems/implement-queue-using-stacks/
 *
 * 题目描述：请你仅使用两个栈实现先入先出队列。队列应当支持一般队列支持的所有操作（push、pop、peek、empty）
 * */

#include <iostream>
#include <stack>
using namespace std;

// 我的解法，过于复杂
// 应当只需要 in2out 这一过程，保证每次 in2out 之前出栈为空即可
class MyQueue
{
 public:
	MyQueue()
	{
		m_stackIn = new stack<int>();
		m_stackOut = new stack<int>();
	}

	~MyQueue()
	{
		if (m_stackIn != nullptr)
		{
			delete m_stackIn;
			m_stackIn = nullptr;
		}

		if (m_stackOut != nullptr)
		{
			delete m_stackOut;
			m_stackOut = nullptr;
		}
	}

	void push(int x)
	{
		out2in();
		m_stackIn->push(x);
	}

	int pop()
	{
		in2out();
		int temp = m_stackOut->top();
		m_stackOut->pop();
		return temp;
	}

	int peek()
	{
		in2out();
		return m_stackOut->top();
	}

	bool empty()
	{
		return (m_stackOut->empty() && m_stackIn->empty());
	}

	void in2out()
	{
		while (!m_stackIn->empty())
		{
			m_stackOut->push(m_stackIn->top());
			m_stackIn->pop();
		}
	}

	void out2in()
	{
		while (!m_stackOut->empty())
		{
			m_stackIn->push(m_stackOut->top());
			m_stackOut->pop();
		}
	}

 private:
	stack<int>* m_stackIn;
	stack<int>* m_stackOut;
};

class MyQueue2
{
 public:
	MyQueue2()
	{
		m_stackIn = new stack<int>();
		m_stackOut = new stack<int>();
	}

	~MyQueue2()
	{
		if (m_stackIn != nullptr)
		{
			delete m_stackIn;
			m_stackIn = nullptr;
		}

		if (m_stackOut != nullptr)
		{
			delete m_stackOut;
			m_stackOut = nullptr;
		}
	}

	void push(int x)
	{
		m_stackIn->push(x);
	}

	int pop()
	{
		// 只有当出栈为空的时候，再从入栈里导入数据（导入入栈全部数据）
		if(m_stackOut->empty())
			in2out();

		int temp = m_stackOut->top();
		m_stackOut->pop();
		return temp;
	}

	int peek()
	{
		int temp = this->pop(); // 直接使用已有的pop函数
		m_stackOut->push(temp); // 因为pop函数弹出了元素res，所以再添加回去
		return temp;
	}

	bool empty()
	{
		return (m_stackOut->empty() && m_stackIn->empty());
	}

	void in2out()
	{
		while (!m_stackIn->empty())
		{
			m_stackOut->push(m_stackIn->top());
			m_stackIn->pop();
		}
	}

 private:
	stack<int>* m_stackIn;
	stack<int>* m_stackOut;
};

/**
 * Your MyQueue object will be instantiated and called as such:
 * MyQueue* obj = new MyQueue();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->peek();
 * bool param_4 = obj->empty();
 */

int main()
{
	MyQueue obj = MyQueue();
	obj.push(1);
	obj.push(2);
	obj.peek();
	obj.pop();
	cout << obj.empty() << endl;
}