/*
 * 53. 最大子数组和		url: https://leetcode.cn/problems/maximum-subarray/
 *
 * 题目描述：给你一个整数数组 nums ，请你找出一个具有最大和的连续子数组（子数组最少包含一个元素），返回其最大和。
 * 子数组 是数组中的一个连续部分。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int maxSubArray(vector<int>& nums)
	{
		vector<int> dp(nums.size(), 0);
		dp[0] = nums[0];
		int result = nums[0];
		for (int i = 1; i < nums.size(); i++)
		{
			dp[i] = max(dp[i - 1] + nums[i], nums[i]);
			result = max(result, dp[i]);
		}

		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		nums = { -2, 1, -3, 4, -1, 2, 1, -5, 4 };
		cout << "exp1 (6): " << endl;
		cout << "result: " << solution.maxSubArray(nums) << endl;
	}
}
