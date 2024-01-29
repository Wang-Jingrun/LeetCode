/*
 * 135. 分发糖果		url: https://leetcode.cn/problems/candy/
 *
 * 题目描述：n 个孩子站成一排。给你一个整数数组 ratings 表示每个孩子的评分。
 * 你需要按照以下要求，给这些孩子分发糖果：
 * 		每个孩子至少分配到 1 个糖果。
 * 		相邻两个孩子评分更高的孩子会获得更多的糖果。
 * 请你给每个孩子分发糖果，计算并返回需要准备的 最少糖果数目 。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	int candy(vector<int>& ratings)
	{
		int result = 1;
		for (int i = 1; i < ratings.size();)
		{
			// 左低右高
			if (ratings[i] < ratings[i - 1])
			{
				int num = 2;
				while (i < ratings.size() && ratings[i] < ratings[i - 1])
				{
					result += num;
					num++;
					i++;
				}
			}

				// 左高右低
			else if (ratings[i] > ratings[i - 1])
			{
				int index = i - 1;
				while (i < ratings.size() && ratings[i] > ratings[i - 1])
				{
					result += i - index + 1;
					i++;
				}
			}
			else
			{
				result++;
				i++;
			}
		}

		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	cout << "exp1 (5): ";
	nums = { 1, 0, 2 };
	cout << solution.candy(nums) << endl;

	cout << "exp2 (4): ";
	nums = { 1, 2, 2 };
	cout << solution.candy(nums) << endl;

	cout << "exp3 (7): ";
	nums = { 1, 3, 2, 2, 1 };
	cout << solution.candy(nums) << endl;
}
