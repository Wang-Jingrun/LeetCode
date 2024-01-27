/*
 * 53. 最大子数组和		url: https://leetcode.cn/problems/maximum-subarray/
 *
 * 题目描述：给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
 * 子数组 是数组中的一个连续部分。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	int maxSubArray(vector<int>& nums)
	{
		int result = INT_MIN;
		int sum = 0;
		for (int num : nums)
		{
			sum += num;
			// 取区间累计的最大值（相当于不断确定最大子序终止位置）
			if (sum > result) result = sum;
			// 相当于重置最大子序起始位置，因为遇到负数一定是拉低总和
			if (sum < 0) sum = 0;
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	cout << "exp1 (6): ";
	nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
	cout << solution.maxSubArray(nums) << endl;

}
