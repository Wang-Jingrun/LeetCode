/*
 * 84. 柱状图中最大的矩形		url: https://leetcode.cn/problems/largest-rectangle-in-histogram/
 *
 * 题目描述：给定 n 个非负整数，用来表示柱状图中各个柱子的高度。每个柱子彼此相邻，且宽度为 1 。
 * 求在该柱状图中，能够勾勒出来的矩形的最大面积。
 * */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 暴力解法
class Solution
{
 public:
	int largestRectangleArea(vector<int>& heights)
	{
		int sum = 0;
		for (int i = 0; i < heights.size(); i++)
		{
			int left = i;
			int right = i;
			for (; left >= 0; left--)
			{
				if (heights[left] < heights[i]) break;
			}
			for (; right < heights.size(); right++)
			{
				if (heights[right] < heights[i]) break;
			}
			int w = right - left - 1;
			int h = heights[i];
			sum = max(sum, w * h);
		}
		return sum;
	}
};

// 优化暴力解法
class Solution2
{
 public:
	int largestRectangleArea(vector<int>& heights)
	{
		vector<int> minLeftIndex(heights.size());
		vector<int> minRightIndex(heights.size());
		int size = heights.size();

		// 记录每个柱子 左边第一个小于该柱子的下标
		minLeftIndex[0] = -1; // 注意这里初始化，防止下面while死循环
		for (int i = 1; i < size; i++)
		{
			int t = i - 1;
			// 这里不是用if，而是不断向左寻找的过程
			while (t >= 0 && heights[t] >= heights[i]) t = minLeftIndex[t];
			minLeftIndex[i] = t;
		}
		// 记录每个柱子 右边第一个小于该柱子的下标
		minRightIndex[size - 1] = size; // 注意这里初始化，防止下面while死循环
		for (int i = size - 2; i >= 0; i--)
		{
			int t = i + 1;
			// 这里不是用if，而是不断向右寻找的过程
			while (t < size && heights[t] >= heights[i]) t = minRightIndex[t];
			minRightIndex[i] = t;
		}
		// 求和
		int result = 0;
		for (int i = 0; i < size; i++)
		{
			int sum = heights[i] * (minRightIndex[i] - minLeftIndex[i] - 1);
			result = max(sum, result);
		}
		return result;
	}
};

// 单调栈解法
class Solution3
{
 public:
	int largestRectangleArea(vector<int>& heights)
	{
		heights.insert(heights.begin(), 0); // 数组头部加入元素0
		heights.push_back(0); // 数组尾部加入元素0
		stack<int> st;
		st.push(0);
		int result = 0;
		for (int i = 1; i < heights.size(); i++)
		{
			while (!st.empty() && heights[i] < heights[st.top()])
			{
				int mid = st.top();
				st.pop();
				if (!st.empty())
				{
					int w = i - st.top() - 1;
					result = max(result, w * heights[mid]);
				}
			}
			st.push(i);
		}
		return result;
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		nums = { 2, 1, 5, 6, 2, 3 };
		cout << "exp1 (10): " << endl;
		cout << "result: " << solution.largestRectangleArea(nums) << endl;
	}
}
