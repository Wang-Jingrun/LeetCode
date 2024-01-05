## Day03: 链表part01

### 链表理论基础
[文章讲解](https://programmercarl.com/%E9%93%BE%E8%A1%A8%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80.html#%E9%93%BE%E8%A1%A8%E7%9A%84%E7%B1%BB%E5%9E%8B)

#### 单链表：

每一个节点由两部分组成，一个是数据域一个是指针域（存放指向下一个节点的指针），最后一个节点的指针域指向null。

![20200806194529815](./imgs/20200806194529815.png)

#### 双链表：

每一个节点有两个指针域，一个指向下一个节点，一个指向上一个节点。双链表既可以向前查询也可以向后查询。

![20200806194559317](imgs/20200806194559317.png)

#### 循环链表：

链表首尾相连。循环链表可以用来解决约瑟夫环问题。

![20200806194629603](imgs/20200806194629603.png)

#### 链表的存储方式：

链表中的节点在内存中不是连续分布的 ，而是散乱分布在内存中的某地址上，分配机制取决于操作系统的内存管理。

#### 链表的定义：

```C++
// Definition for singly-linked list.
struct ListNode {
  int val;
  ListNode *next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode *next) : val(x), next(next) {}
};
```

#### 删除节点：

C++里最好是再手动释放删除的节点，释放这块内存。其他语言例如Java、Python，就有自己的内存回收机制，就不用自己手动释放了。

![20200806195114541-20230310121459257](imgs/20200806195114541-20230310121459257.png)

#### 添加节点：

![20200806195134331-20230310121503147](imgs/20200806195134331-20230310121503147.png)

#### 性能分析：

![20200806195200276](imgs/20200806195200276.png)

### 203. 移除链表元素

[LeetCode](https://leetcode.cn/problems/remove-linked-list-elements/)  [文章讲解](https://programmercarl.com/0203.%E7%A7%BB%E9%99%A4%E9%93%BE%E8%A1%A8%E5%85%83%E7%B4%A0.html)  [视频讲解](https://www.bilibili.com/video/BV18B4y1s7R9/)

#### 题目描述：

给你一个链表的头节点 `head` 和一个整数 `val` ，请你删除链表中所有满足 `Node.val == val` 的节点，并返回 **新的头节点** 。

示例 1： 输入：head = [1,2,6,3,4,5,6], val = 6 输出：[1,2,3,4,5]

示例 2： 输入：head = [], val = 1 输出：[]

示例 3： 输入：head = [7,7,7,7], val = 7 输出：[]

#### 我的解法（设置虚拟头结点）：

由于涉及到删除元素需要两个指针，一个指向被删除的前一个节点（用于删除节点），一个指向需要删除的节点（进行遍历寻找为 `val` 的节点）。如果需要删除头节点的话，由于头节点没有前一个节点，因此我想到创建一个虚拟节点来进行删除操作。不要忘记清除创建的虚拟头节点和要删除的节点的内存。

```C++
class Solution
{
 public:
	ListNode* removeElements(ListNode* head, int val)
	{
		// 创建一个头节点, 其值无用，便于进行删除操作
		ListNode* hd = new ListNode(0, head);
		ListNode* front = hd;
		ListNode* current = head;
		while (current != nullptr)
		{
			// 删除节点
			if (current->val == val)
			{
				front->next = current->next;
				delete current;    // 释放需要删除的节点的内存
				current = front->next;
			}
			else
			{
				front = current;
				current = current->next;
			}
		}

		head = hd->next;
		delete hd; // 释放创建的虚拟头节点的内存
		return head;
	}
};
```

#### 直接使用原来的链表来进行移除节点操作：

由于头节点没有前一个节点，将头结点向后移动一位就相当于删除其元素，因此移除头结点和移除其他节点的操作需要分开情况处理。

循环的条件不要忘记加上判断本节点是否为 `nullptr` 的情况。

```C++
class Solution2
{
 public:
	ListNode* removeElements(ListNode* head, int val)
	{
		ListNode* temp = nullptr;
        // 直到头节点不是要删除的节点
		while (head != nullptr && head->val == val)
		{
			temp = head;
			head = head->next;
			delete temp;
		}

		ListNode* current = head;
		while (current != nullptr && current->next != nullptr)
		{
			// 删除节点
			if (current->next->val == val) // current 当作要删除的前一个节点来使用
			{
				temp = current->next;
				current->next = current->next->next;
				delete temp;    // 释放需要删除的节点的内存
			}
			else
			{
				current = current->next;
			}
		}

		return head;
	}
};
```

### 707. 设计链表
[LeetCode](https://leetcode.cn/problems/design-linked-list/)  [文章讲解](https://programmercarl.com/0707.%E8%AE%BE%E8%AE%A1%E9%93%BE%E8%A1%A8.html)  [视频讲解](https://www.bilibili.com/video/BV1FU4y1X7WD/)

#### 题目描述：

在链表类中实现这些功能：

- get(index)：获取链表中第 index 个节点的值。如果索引无效，则返回-1。

- addAtHead(val)：在链表的第一个元素之前添加一个值为 val 的节点。插入后，新节点将成为链表的第一个节点。

- addAtTail(val)：将值为 val 的节点追加到链表的最后一个元素。

- addAtIndex(index,val)：在链表中的第 index 个节点之前添加值为 val 的节点。如果 index 等于链表的长度，则该节点将附加到链表的末尾。如果 index 大于链表长度，则不会插入节点。如果index小于0，则在头部插入节点。

- deleteAtIndex(index)：如果索引 index 有效，则删除链表中的第 index 个节点。

**示例：**

> 输入
> ["MyLinkedList", "addAtHead", "addAtTail", "addAtIndex", "get", "deleteAtIndex", "get"]
> [[], [1], [3], [1, 2], [1], [1], [1]]
> 输出
> [null, null, null, null, 2, null, 3]
>
> 解释
> MyLinkedList myLinkedList = new MyLinkedList();
> myLinkedList.addAtHead(1);
> myLinkedList.addAtTail(3);
> myLinkedList.addAtIndex(1, 2);    // 链表变为 1->2->3
> myLinkedList.get(1);              // 返回 2
> myLinkedList.deleteAtIndex(1);    // 现在，链表变为 1->3
> myLinkedList.get(1);              // 返回 3

#### 我的解法：

第一遍自己做的时候没有设置虚拟头节点，好多操作需要分头节点和非头节点进行操作，代码有些繁琐。

```C++
class MyLinkedList
{
 public:
	MyLinkedList() : m_head(nullptr), m_size(0) {}

	~MyLinkedList()    // 析构函数，释放所有节点的内存
	{
		if (m_head != nullptr)
		{
			ListNode* temp = nullptr;
			while (m_head != nullptr)
			{
				temp = m_head;
				m_head = m_head->next;
				delete temp;
			}
			m_head = nullptr;
			m_size = 0;
		}
	}

	int get(int index)
	{
		// 下标越界，直接返回 -1
		if (index < 0 || index >= m_size)
		{
			return -1;
		}

		// 下标为 index，即向后移动 index 次 
		ListNode* current = m_head;
		for (int i = 0; i < index; i++)
		{
			current = current->next;
		}
		return current->val;
	}

	void addAtHead(int val)
	{
		// 头节点直接插入
		ListNode* node = new ListNode(val, m_head);
		m_head = node;
		m_size++;
	}

	void addAtTail(int val)
	{
		// 头节点为空，相当于从头节点插入
		if (m_head == nullptr)
		{
			addAtHead(val);
			return;
		}

		// 头节点非空，遍历到 nullptr 前一个节点，方便插入
		ListNode* current = m_head;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new ListNode(val, nullptr);
		m_size++;
	}

	void addAtIndex(int index, int val)
	{
		if (index < 0 || index > m_size)
		{
			// 下标越界，直接返回
			return;
		}
		else if (index == m_size)
		{
			// 下标为 size，相当于尾部插入
			addAtTail(val);
			return;
		}
		else if (index == 0)
		{
			// 下标为 0，相当于头部插入
			addAtHead(val);
			return;
		}

		// 遍历到插入位置的前一个位置
		ListNode* current = m_head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->next;
		}

		auto node = new ListNode(val, current->next);
		current->next = node;
		m_size++;
	}

	void deleteAtIndex(int index)
	{
		if (index < 0 || index >= m_size)
		{
			// 下标越界，直接返回
			return;
		}

		// 下标为 0，删除头节点，需要特殊处理
		if (index == 0)
		{
			auto temp = m_head;
			m_head = m_head->next;
			delete temp;
			m_size--;
			return;
		}

		// 遍历到删除位置的前一个位置
		ListNode* current = m_head;
		for (int i = 0; i < index - 1; i++)
		{
			current = current->next;
		}
		auto temp = current->next;
		current->next = current->next->next;
		delete temp;
		m_size--;
	}

 private:
	ListNode* m_head;
	int m_size;
};
```

#### 设置虚拟头节点做法：

```C++
class MyLinkedList
{
 public:
	MyLinkedList() : m_size(0)
	{
		m_head = new ListNode(0, nullptr);
	}

	// 析构函数，释放所有节点的内存
	~MyLinkedList()
	{
		if (m_head != nullptr)
		{
			ListNode* temp = nullptr;
			while (m_head != nullptr)
			{
				temp = m_head;
				m_head = m_head->next;
				delete temp;
			}
			m_head = nullptr;
			temp = nullptr;
			m_size = 0;
		}
	}

	int get(int index)
	{
		// 下标越界，直接返回 -1
		if (index < 0 || index >= m_size)
		{
			return -1;
		}

		// 下标为 index，即向后移动 index 次
		ListNode* current = m_head->next;
		while (index--)
		{
			current = current->next;
		}
		return current->val;
	}

	void addAtHead(int val)
	{
		// 头节点直接插入
		auto* node = new ListNode(val, m_head->next);
		m_head->next = node;
		m_size++;
	}

	void addAtTail(int val)
	{
		ListNode* current = m_head;
		while (current->next != nullptr)
		{
			current = current->next;
		}
		current->next = new ListNode(val, nullptr);
		m_size++;
	}

	void addAtIndex(int index, int val)
	{
		if (index < 0 || index > m_size)
		{
			// 下标越界，直接返回
			return;
		}

		// 遍历到插入位置的前一个位置
		ListNode* current = m_head;
		while (index--)
		{
			current = current->next;
		}

		auto node = new ListNode(val, current->next);
		current->next = node;
		m_size++;
	}

	void deleteAtIndex(int index)
	{
		if (index < 0 || index >= m_size)
		{
			// 下标越界，直接返回
			return;
		}

		// 遍历到删除位置的前一个位置
		ListNode* current = m_head;
		while (index--)
		{
			current = current->next;
		}
		auto temp = current->next;
		current->next = current->next->next;
		delete temp;
		m_size--;
	}

 private:
	ListNode* m_head;
	int m_size;
};
```

### 206. 反转链表
[LeetCode](https://leetcode.cn/problems/reverse-linked-list/)  [文章讲解](https://programmercarl.com/0206.%E7%BF%BB%E8%BD%AC%E9%93%BE%E8%A1%A8.html)  [视频讲解](https://www.bilibili.com/video/BV1nB4y1i7eL/)

#### 题目描述：

题意：反转一个单链表。

示例: 输入: 1->2->3->4->5->NULL 输出: 5->4->3->2->1->NULL

#### 我的解法：

只需要改变链表的`next`指针的指向，直接将链表反转 ，而不用重新定义一个新的链表（纠正：动画应该是先移动`pre`，在移动`cur`）。

![206.翻转链表](imgs/206.翻转链表.gif)

```C++
class Solution
{
 public:
	ListNode* reverseList(ListNode* head)
	{
		ListNode* pre = nullptr;    // 反转后旧头节点的前一个节点是 nullptr
		ListNode* cur = head->next;
		ListNode* temp = nullptr;

		while (cur != nullptr)
		{
			// temp 是为了存放 cur 的下一个节点，以防 cur->next 被替换后丢失
			temp = cur->next;
			cur->next = pre;
			pre = cur;
			cur = temp;
		}

		return pre;
	}
};
```
#### 递归解法：

对照双指针法逐一完成：

- 递归函数结束条件对应 `while` 循环结束条件；
- 递归函数的内容对应每次 while 循环中的操作；
- 每次递归函数的传值对应 `while` 循环每次对 `cur` 和 `pre` 更新的值；
- 递归函数的初始值对应 `while` 循环之前 `cur` 和 `pre` 的初始值。

```C++
class Solution2	// 递归解法
{
 public:
	ListNode* reverse(ListNode* pre, ListNode* cur)
	{
		if (cur == nullptr)
		{
			return pre;
		}
		ListNode* temp = cur->next;
		cur->next = pre;
		return reverse(cur, temp);
	}
	
	ListNode* reverseList(ListNode* head)
	{
		return reverse(nullptr, head);
	}
};
```

### 今日总结

今天三道题目都独立完成了，最后一题双指针法转化成递归法的思路很巧妙。

理解了虚拟头节点的作用，之前学数据结构写过一个单链表的类，当时不是特别明白为什么要用虚拟头节点。核心思想：对于单链表，删除增加某个节点需要知道该位置的前一个节点。

时刻注意随时清除被删除节点的内存。

