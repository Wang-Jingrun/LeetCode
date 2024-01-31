/*
 * 56. 合并区间		url: https://leetcode.cn/problems/merge-intervals/
 *
 * 题目描述：以数组 intervals 表示若干个区间的集合，其中单个区间为 intervals[i] = [start_i, end_i] 。
 * 请你合并所有重叠的区间，并返回 一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间 。
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

	vector<vector<int>> merge(vector<vector<int>>& intervals)
	{
		// 排序，使得重叠的区间在一起
		sort(intervals.begin(), intervals.end(), cmp);

		vector<vector<int>> result;

		int right;
		for (int i = 0; i < intervals.size();i++)
		{
			result.push_back({ intervals[i][0], intervals[i][1] });
			right = result.back()[1];

			// i == 0 强制进行去重
			// 有重叠，取到不重叠为止
			if (intervals[i][0] <= right || i == 0)
			{
				result.pop_back();

				int left = intervals[i][0];
				while (i < intervals.size() && intervals[i][0] <= right)
				{
					right = max(right, intervals[i][1]);
					i++;
				}

				// 记录结果
				result.push_back({ left, right });
				i--;	// for 循环中 带有 i++，此处需要回退
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
		intervals = {{ 1, 3 }, { 2, 6 }, { 8, 10 }, { 15, 18 }};
		cout << "exp1 ([[1,6],[8,10],[15,18]]): " << endl;

		auto result = solution.merge(intervals);
		cout << "result: [";
		for (const auto& nums : result)
		{
			cout << "[ ";
			for (auto num : nums)
			{
				cout << num << " ";
			}
			cout << "]";
		}
		cout << "]" << endl;
	}

	{
		intervals = {{ 2, 3 }, { 2, 2 }, { 3, 3 }, { 1, 3 }, { 5, 7 }, { 2, 2 }, {4, 6 }};
		cout << "exp2 ([[1,3],[4,7]]): " << endl;

		auto result = solution.merge(intervals);
		cout << "result: [";
		for (const auto& nums : result)
		{
			cout << "[ ";
			for (auto num : nums)
			{
				cout << num << " ";
			}
			cout << "]";
		}
		cout << "]" << endl;
	}
}
