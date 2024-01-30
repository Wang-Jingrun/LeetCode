/*
 * 452. 用最少数量的箭引爆气球		url: https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/
 *
 * 题目描述：有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 points ，
 * 其中points[i] = [xstart, xend] 表示水平直径在 xstart 和 xend之间的气球。你不知道气球的确切 y 坐标。
 * 一支弓箭可以沿着 x 轴从不同点 完全垂直 地射出。在坐标 x 处射出一支箭，若有一个气球的直径的开始和结束坐标为 xstart，xend，
 * 且满足  xstart ≤ x ≤ xend，则该气球会被 引爆 。可以射出的弓箭的数量 没有限制 。 弓箭一旦被射出之后，可以无限地前进。
 * 给你一个数组 points ，返回引爆所有气球所必须射出的 最小 弓箭数 。
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

	int findMinArrowShots(vector<vector<int>>& points)
	{
		sort(points.begin(), points.end(), cmp);

		int result = 0;
		int left = INT_MIN;
		int right = INT_MAX;

		for (int i = 0; i < points.size();)
		{
			// 如有重叠，一直取到不重叠为止
			while (i < points.size() && points[i][0] <= right)
			{
				left = max(left, points[i][0]);
				right = min(right, points[i][1]);
				i++;
			}
			result++;
			left = INT_MIN;
			right = INT_MAX;
		}

		return result;
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> points;

	{
		points = {{ 3, 9 }, { 7, 12 }, { 3, 8 }, { 6, 8 }, { 9, 10 }, { 2, 9 }, { 0, 9 }, { 3, 9 }, { 0, 6 }, { 2, 8 }};
		cout << "exp1 (2): " << endl;
		cout << "result: " << solution.findMinArrowShots(points) << endl;
	}

	{
		points = {{ 1, 2 }, { 2, 3 }, { 3, 4 }, { 4, 5 }};
		cout << "exp2 (2): " << endl;
		cout << "result: " << solution.findMinArrowShots(points) << endl;
	}
}
