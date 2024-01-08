## Day13: 栈和队列part03

### 239. 滑动窗口最大值
[LeetCode](https://leetcode.cn/problems/sliding-window-maximum/)  [文章讲解](https://programmercarl.com/0239.%E6%BB%91%E5%8A%A8%E7%AA%97%E5%8F%A3%E6%9C%80%E5%A4%A7%E5%80%BC.html)  [视频讲解](https://www.bilibili.com/video/BV1XS4y1p7qj/)

#### 题目描述：

给你一个整数数组 `nums`，有一个大小为 `k` 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 `k` 个数字。滑动窗口每次只向右移动一位。返回 *滑动窗口中的最大值* 。

**示例 1：**

> 输入：nums = [1,3,-1,-3,5,3,6,7], k = 3
> 输出：[3,3,5,5,6,7]
> 解释：
> 滑动窗口的位置                最大值
>
> ---------------               -----
> [1  3  -1] -3  5  3  6  7       3
>  1 [3  -1  -3] 5  3  6  7       3
>  1  3 [-1  -3  5] 3  6  7       5
>  1  3  -1 [-3  5  3] 6  7       5
>  1  3  -1  -3 [5  3  6] 7       6
>  1  3  -1  -3  5 [3  6  7]      7

**示例 2：**

> 输入：nums = [1], k = 1
> 输出：[1]

#### 我的解法：

类似于暴力解法，每次在新的窗口中寻找最大的值，LeetCode 超时。

```C++
class Solution    // 超时，复杂度 O(n*k)
{
 public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k)
	{
		int left = 0, right = 1;
		vector<int> result = { nums[left] };

		// 先将窗口滑动到大小为 k
		for (; right <= k - 1; ++right)
		{
			if (nums[right] > *(result.end() - 1))
				result[left] = nums[right];
		}

		// 再将窗口整体滑动
		for (++left; right < nums.size(); ++left, ++right)
		{
			// 新加入窗口的值比目前的窗口值大
			if (nums[right] > *(result.end() - 1))
				result.push_back(nums[right]); // 直接将新加入的值存入到结果

			// 要移走的值比目前窗口的值小
			else if (*(result.end() - 1) > nums[left - 1])
			{
				result.push_back(*(result.end() - 1)); // 直接将上次窗口的最大的值存入到结果
			}

			// 需要到窗口重新寻找最大值
			else
			{
				result.push_back(nums[left]);
				for (int i = left + 1; i <= right; ++i)
				{
					if (nums[i] > *(result.end() - 1))
						*(result.end() - 1) = nums[i];
				}
			}
		}

		return result;
	}
};
```

#### 单调队列法：

**其实队列没有必要维护窗口里的所有元素，只需要维护有可能成为窗口里最大值的元素就可以了，同时保证队列里的元素数值是由大到小的。**那么这个维护元素单调递减的队列就叫做**单调队列，即单调递减或单调递增的队列。C++中没有直接支持单调队列，需要我们自己来实现一个单调队列**

动画如下：

![239.滑动窗口最大值](imgs/239.滑动窗口最大值.gif)

对于窗口里的元素{2, 3, 5, 1 ,4}，单调队列里只维护{5, 4} 就够了，保持单调队列里单调递减，此时队列出口元素就是窗口里最大元素。

此时大家应该怀疑单调队列里维护着{5, 4} 怎么配合窗口进行滑动呢？

设计单调队列的时候，pop，和push操作要保持如下规则：

1. pop(value)：如果窗口移除的元素value等于单调队列的出口元素，那么队列弹出元素，否则不用任何操作
2. push(value)：如果push的元素value大于**入口**元素的数值，那么就将队列**入口**的元素弹出，直到push元素的数值小于等于队列入口元素的数值为止。**注意是入口，如果弹出的是出口元素，会导致新加入的值和目前最大值相等，再经历一次pop后，可能会失去维护的最大值。**

保持如上规则，每次窗口移动的时候，只要问que.front()就可以返回当前窗口的最大值。

为了更直观的感受到单调队列的工作过程，以题目示例为例，输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3，动画如下：

![239.滑动窗口最大值-2](imgs/239.滑动窗口最大值-2.gif)

那么我们用什么数据结构来实现这个单调队列呢？使用deque最为合适，在文章[栈与队列：来看看栈和队列不为人知的一面 (opens new window)](https://programmercarl.com/栈与队列理论基础.html)中，我们就提到了常用的queue在没有指定容器的情况下，deque就是默认底层容器。

```C++
class MyQueue
{
 public:
	MyQueue() = default;
	~MyQueue() = default;

	//添加元素时，如果要添加的元素大于入口处的元素，就将入口元素弹出
	void push(int num)
	{
		while (!m_queue.empty() && m_queue.back() < num)
		{
			m_queue.pop_back();
		}
		m_queue.push_back(num);
	}

	//弹出元素时，比较当前要弹出的数值是否等于队列出口的数值，如果相等则弹出
	void pop(int num)
	{
		if (!m_queue.empty() && num == m_queue.front())
			m_queue.pop_front();
	}

	//队列队顶元素始终为最大值
	int get_max_value()
	{
		return m_queue.front();
	}

 private:
	deque<int> m_queue;
};

class Solution2    // 单调队列
{
 public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k)
	{
		vector<int> result;
		MyQueue queue;

		for (int i = 0; i < k; i++)
		{
			queue.push(nums[i]);
		}
		result.push_back(queue.get_max_value());

		for (int i = 0, j = k; j < nums.size(); i++, j++)
		{
			queue.pop(nums[i]);
			queue.push(nums[j]);
			result.push_back(queue.get_max_value());
		}

		return result;
	}
};
```

### 347. 前 K 个高频元素

[LeetCode](https://leetcode.cn/problems/top-k-frequent-elements/)  [文章讲解](https://programmercarl.com/0347.%E5%89%8DK%E4%B8%AA%E9%AB%98%E9%A2%91%E5%85%83%E7%B4%A0.html)  [视频讲解](https://www.bilibili.com/video/BV1Xg41167Lz/)

#### 题目描述：

给你一个整数数组 `nums` 和一个整数 `k` ，请你返回其中出现频率前 `k` 高的元素。你可以按 **任意顺序** 返回答案。

**示例 1:**

> 输入: nums = [1,1,1,2,2,3], k = 2
> 输出: [1,2]

**示例 2:**

> 输入: nums = [1], k = 1
> 输出: [1]

#### 我的解法：

暴力解法，先通过map统计频次，然后逐次取最大频次的值。

```C++
class Solution
{
 public:
	vector<int> topKFrequent(vector<int>& nums, int k)
	{
        // 统计频次
		unordered_map<int, int> map;
		for (auto num : nums)
		{
			map[num]++;
		}

        // 依次取频次最大的数
        vector<int> result;
		int count = 0;
		int num;
		for (int i = 0; i < k; i++)
		{
			for (auto& item : map)
			{
				if (item.second > count)
				{
					num = item.first;
					count = item.second;
				}
			}

			result.push_back(num);
			map.erase(num);
			count = 0;
		}
		return result;
	}
};
```

#### 小顶堆法：

这道题目主要涉及到如下三块内容：

1. 要统计元素出现频率
2. 对频率排序
3. 找出前K个高频元素

首先统计元素出现的频率，这一类的问题可以使用map来进行统计。

然后是对频率进行排序，这里我们可以使用一种 容器适配器就是**优先级队列：一个披着队列外衣的堆**。因为优先级队列对外接口只是从队头取元素，从队尾添加元素，再无其他取元素的方式，看起来就是一个队列。而且优先级队列内部元素是自动依照元素的权值排列。

**堆是一棵完全二叉树，树中每个结点的值都不小于（或不大于）其左右孩子的值。** 如果父亲结点是大于等于左右孩子就是大顶堆，小于等于左右孩子就是小顶堆。

本题我们就要使用优先级队列来对部分频率进行排序。

为什么不用快排呢， 使用快排要将map转换为vector的结构，然后对整个数组进行排序， 而这种场景下，我们其实只需要维护k个有序的序列就可以了，所以使用优先级队列是最优的。

此时要思考一下，是使用小顶堆呢，还是大顶堆？

**我们要用小顶堆，因为要统计最大前k个元素，只有小顶堆每次将最小的元素弹出，最后小顶堆里积累的才是前k个最大元素。**

寻找前k个最大元素流程如图所示：（图中的频率只有三个，所以正好构成一个大小为3的小顶堆，如果频率更多一些，则用这个小顶堆进行扫描）

![347.前K个高频元素](imgs/347.前K个高频元素.jpg)

```C++
// 小顶堆
class mycomparison // 时间复杂度: O(nlogk)
{
 public:
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs)
    {
       return lhs.second > rhs.second;
    }
};

class Solution2
{
 public:
    vector<int> topKFrequent(vector<int>& nums, int k)
    {
       // 统计元素出现频率
       unordered_map<int, int> map;
       for (auto num : nums)
       {
          map[num]++;
       }

       // 对频率排序
       // 定义一个小顶堆，大小为k
       priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;

       // 用固定大小为k的小顶堆，扫面所有频率的数值
       for (auto& it : map)
       {
          pri_que.push(it);
          if (pri_que.size() > k)
          { // 如果堆的大小大于了K，则队列弹出，保证堆的大小一直为k
             pri_que.pop();
          }
       }

       // 找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒序来输出到数组
       vector<int> result(k);
       for (int i = k - 1; i >= 0; i--)
       {
          result[i] = pri_que.top().first;
          pri_que.pop();
       }
       return result;
    }
};
```

### 栈和队列篇总结

#### 栈与队列的理论基础

灵魂四问：

1. C++中stack，queue 是容器么？
2. 我们使用的stack，queue是属于那个版本的STL？
3. 我们使用的STL中stack，queue是如何实现的？
4. stack，queue 提供迭代器来遍历空间么？

同样，可以出一道面试题：栈里面的元素在内存中是连续分布的么？

这个问题有两个陷阱：

- 陷阱1：栈是容器适配器，底层容器使用不同的容器，导致栈内数据在内存中不一定是连续分布的。
- 陷阱2：缺省情况下，默认底层容器是deque，那么deque在内存中的数据分布是什么样的呢？ 答案是：不连续的，下文也会提到deque。

#### 栈经典题目

##### 栈在系统中的应用

如果还记得编译原理的话，编译器在词法分析的过程中处理括号、花括号等这个符号的逻辑，就是使用了栈这种数据结构。

再举个例子，linux系统中，cd这个进入目录的命令我们应该再熟悉不过了。

```text
cd a/b/c/../../
```

这个命令最后进入a目录，系统是如何知道进入了a目录呢 ，这就是栈的应用。这在leetcode上也是一道题目，编号：71. 简化路径，大家有空可以做一下。**递归的实现是栈：每一次递归调用都会把函数的局部变量、参数值和返回地址等压入调用栈中**，然后递归返回的时候，从栈顶弹出上一次递归的各项参数，所以这就是递归为什么可以返回上一层位置的原因。所以栈在计算机领域中应用是非常广泛的。

##### 括号匹配问题

括号匹配是使用栈解决的经典问题。这里有三种不匹配的情况，

1. 第一种情况，字符串里左方向的括号多余了，所以不匹配。
2. 第二种情况，括号没有多余，但是括号的类型没有匹配上。
3. 第三种情况，字符串里右方向的括号多余了，所以不匹配。

##### 字符串去重问题

思路就是可以把字符串顺序放到一个栈中，然后如果相同的话 栈就弹出，这样最后栈里剩下的元素都是相邻不相同的元素了。

##### 逆波兰表达式问题

思路就类似字符串去重问题，遇到数字就入栈，遇到运算符就取出两个数字进行运算，然后再将结果入栈即可。

#### 队列的经典题目

##### 滑动窗口最大值问题

在[栈与队列：滑动窗口里求最大值引出一个重要数据结构](https://programmercarl.com/0239.滑动窗口最大值.html)中讲解了一种数据结构：单调队列。主要思想是**队列没有必要维护窗口里的所有元素，只需要维护有可能成为窗口里最大值的元素就可以了，同时保证队列里的元素数值是由大到小的。**那么这个维护元素单调递减的队列就叫做**单调队列。不要以为实现的单调队列就是 对窗口里面的数进行排序，如果排序的话，那和优先级队列又有什么区别了呢。**

设计单调队列的时候，pop，和push操作要保持如下规则：

1. pop(value)：如果窗口移除的元素value等于单调队列的出口元素，那么队列弹出元素，否则不用任何操作
2. push(value)：如果push的元素value大于**入口**元素的数值，那么就将队列**入口**的元素弹出，直到push元素的数值小于等于队列**入口**元素的数值为止

保持如上规则，每次窗口移动的时候，只要问que.front()就可以返回当前窗口的最大值。

**单调队列不是一成不变的，而是不同场景不同写法**，总之要保证队列里单调递减或递增的原则，所以叫做单调队列。**不要以为本地中的单调队列实现就是固定的写法。**

用deque作为单调队列的底层数据结构，C++中deque是stack和queue默认的底层实现容器（这个我们之前已经讲过），deque是可以两边扩展的，而且deque里元素并不是严格的连续分布的。

##### 求前 K 个高频元素

通过求前 K 个高频元素，引出另一种队列就是**优先级队列：一个披着队列外衣的堆**，因为优先级队列对外接口只是从队头取元素，从队尾添加元素，再无其他取元素的方式，看起来就是一个队列。

而且优先级队列内部元素是自动依照元素的权值排列。那么它是如何有序排列的呢？

缺省情况下priority_queue利用max-heap（大顶堆）完成对元素的排序，这个大顶堆是以vector为表现形式的complete binary tree（完全二叉树）。

什么是堆呢？**堆是一棵完全二叉树，树中每个结点的值都不小于（或不大于）其左右孩子的值。** 如果父亲结点是大于等于左右孩子就是大顶堆，小于等于左右孩子就是小顶堆。

所以大家经常说的大顶堆（堆头是最大元素），小顶堆（堆头是最小元素），如果懒得自己实现的话，就直接用priority_queue（优先级队列）就可以了，底层实现都是一样的，从小到大排就是小顶堆，从大到小排就是大顶堆。

本题就要**使用优先级队列来对部分频率进行排序。** 注意这里是对部分数据进行排序而不需要对所有数据排序！

所以排序的过程的时间复杂度是$O(\log k)$，整个算法的时间复杂度是$O(n\log k)$。


### 今日总结

我是暴力王，今天两题都是通过暴力解法写出来的。单调栈和大小堆没怎么见过和使用，需要多加熟悉。