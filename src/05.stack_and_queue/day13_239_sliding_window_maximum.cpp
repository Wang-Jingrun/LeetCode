/*
 * 239. 滑动窗口最大值		url: https://leetcode.cn/problems/sliding-window-maximum/
 *
 * 题目描述：给你一个整数数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。
 * 你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。返回 滑动窗口中的最大值 。
 * */

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
using namespace std;

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

int main()
{
	Solution2 solution;
	vector<int> nums, ret;

	cout << "exp2 ([3,3,5,5,6,7]): ";
	nums = { 1, 3, -1, -3, 5, 3, 6, 7 };
	ret = solution.maxSlidingWindow(nums, 3);
	cout << "[ ";
	for (auto i : ret)
	{
		cout << i << " ";
	}
	cout << "]" << endl;

	cout << "exp2 ([7,7,7,7,7]): ";
	nums = { -7, -8, 7, 5, 7, 1, 6, 0 };
	ret = solution.maxSlidingWindow(nums, 4);
	cout << "[ ";
	for (auto i : ret)
	{
		cout << i << " ";
	}
	cout << "]" << endl;

	cout << "exp3 ([3,3,2,5]): ";
	nums = { 1, 3, 1, 2, 0, 5 };
	ret = solution.maxSlidingWindow(nums, 3);
	cout << "[ ";
	for (auto i : ret)
	{
		cout << i << " ";
	}
	cout << "]" << endl;
}

