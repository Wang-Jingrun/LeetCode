/*
 * 42. 接雨水		url: https://leetcode.cn/problems/trapping-rain-water/
 *
 * 题目描述：给定 n 个非负整数表示每个宽度为 1 的柱子的高度图，计算按此排列的柱子，下雨之后能接多少雨水。
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

// 暴力解法
class Solution
{
 public:
	int trap(vector<int>& height)
	{
		int sum = 0;
		for (int i = 0; i < height.size(); i++)
		{
			// 第一个柱子和最后一个柱子不接雨水
			if (i == 0 || i == height.size() - 1) continue;

			int rHeight = height[i]; // 记录右边柱子的最高高度
			int lHeight = height[i]; // 记录左边柱子的最高高度
			for (int r = i + 1; r < height.size(); r++)
			{
				if (height[r] > rHeight) rHeight = height[r];
			}
			for (int l = i - 1; l >= 0; l--)
			{
				if (height[l] > lHeight) lHeight = height[l];
			}
			int h = min(lHeight, rHeight) - height[i];
			if (h > 0) sum += h;
		}
		return sum;
	}
};

// 暴力解法优化
class Solution2
{
 public:
	int trap(vector<int>& height)
	{
		if (height.size() <= 2) return 0;
		vector<int> maxLeft(height.size(), 0);
		vector<int> maxRight(height.size(), 0);
		int size = maxRight.size();

		// 记录每个柱子左边柱子最大高度
		maxLeft[0] = height[0];
		for (int i = 1; i < size; i++)
		{
			maxLeft[i] = max(height[i], maxLeft[i - 1]);
		}
		// 记录每个柱子右边柱子最大高度
		maxRight[size - 1] = height[size - 1];
		for (int i = size - 2; i >= 0; i--)
		{
			maxRight[i] = max(height[i], maxRight[i + 1]);
		}
		// 求和
		int sum = 0;
		for (int i = 0; i < size; i++)
		{
			int count = min(maxLeft[i], maxRight[i]) - height[i];
			if (count > 0) sum += count;
		}
		return sum;
	}
};

// 单调栈
class Solution3
{
 public:
	int trap(vector<int>& height)
	{
		if (height.size() <= 2) return 0; // 可以不加
		stack<int> st; // 存着下标，计算的时候用下标对应的柱子高度
		st.push(0);
		int sum = 0;
		for (int i = 1; i < height.size(); i++)
		{
			if (height[i] < height[st.top()])
			{     // 情况一
				st.push(i);
			}
			if (height[i] == height[st.top()])
			{  // 情况二
				st.pop(); // 其实这一句可以不加，效果是一样的，但处理相同的情况的思路却变了。
				st.push(i);
			}
			else
			{
				// 情况三
				while (!st.empty() && height[i] > height[st.top()])
				{ // 注意这里是while
					int mid = st.top();
					st.pop();
					if (!st.empty())
					{
						int h = min(height[st.top()], height[i]) - height[mid];
						int w = i - st.top() - 1; // 注意减一，只求中间宽度
						sum += h * w;
					}
				}
				st.push(i);
			}
		}
		return sum;
	}
};

// 单调栈 精简版
class Solution4
{
 public:
	int trap(vector<int>& height)
	{
		stack<int> st;
		st.push(0);
		int sum = 0;
		for (int i = 1; i < height.size(); i++)
		{
			while (!st.empty() && height[i] > height[st.top()])
			{
				int mid = st.top();
				st.pop();
				if (!st.empty())
				{
					int h = min(height[st.top()], height[i]) - height[mid];
					int w = i - st.top() - 1;
					sum += h * w;
				}
			}
			st.push(i);
		}
		return sum;
	}
};

int main()
{
	Solution3 solution;
	vector<int> height;

	{
		height = { 0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1 };
		cout << "exp1 (6): " << endl;
		cout << "result: " << solution.trap(height);
	}
}
