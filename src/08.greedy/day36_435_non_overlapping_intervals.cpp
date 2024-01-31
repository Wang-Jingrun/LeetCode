/*
 * 435. 无重叠区间		url: https://leetcode.cn/problems/non-overlapping-intervals/
 *
 * 题目描述：给定一个区间的集合 intervals ，其中 intervals[i] = [starti, endi] 。
 * 返回 需要移除区间的最小数量，使剩余区间互不重叠 。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	static bool cmp(const vector<int>& a, const vector<int>& b)
	{
		return a[0] < b[0];
	}

	int eraseOverlapIntervals(vector<vector<int>>& intervals)
	{
		// 排序，使得重叠的区间在一起
		sort(intervals.begin(), intervals.end(), cmp);

		int result = 0;
		int right = intervals[0][1];
		for (int i = 1; i < intervals.size(); i++)
		{
			if (intervals[i][0] < right)
			{
				// 有重叠，计数加 1
				result++;
				// 移除范围更大的区间，即等价于移除最少得区间
				// 更新区间
				right = min(right, intervals[i][1]);
			}
			else
			{
				// 没有重叠，更新区间
				right = intervals[i][1];
			}

		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> intervals;

	{
		intervals = {{ 1, 2 }, { 2, 3 }, { 3, 4 }, { 1, 3 }};
		cout << "exp1 (1): " << endl;
		cout << "result: " << solution.eraseOverlapIntervals(intervals) << endl;
	}
}
