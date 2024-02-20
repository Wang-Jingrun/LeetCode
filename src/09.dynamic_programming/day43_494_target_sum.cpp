/*
 * 494. 目标和		url: https://leetcode.cn/problems/target-sum/
 *
 * 题目描述：给你一个非负整数数组 nums 和一个整数 target 。
 * 向数组中的每个整数前添加 '+' 或 '-' ，然后串联起所有整数，可以构造一个 表达式 ：
 * 		例如，nums = [2, 1] ，可以在 2 之前添加 '+' ，在 1 之前添加 '-' ，然后串联起来得到表达式 "+2-1" 。
 * 返回可以通过上述方法构造的、运算结果等于 target 的不同 表达式 的数目。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int result = 0;

	void backtracking(vector<int>& nums, int startIndex, int currentSum, int target)
	{
		if (startIndex == nums.size())
		{
			if (currentSum == target)
			{
				result++;
			}
			return;
		}

		// 每次取+或者-即可，不需要使用for循环
		backtracking(nums, startIndex + 1, currentSum + nums[startIndex], target); // 添加 +
		backtracking(nums, startIndex + 1, currentSum - nums[startIndex], target); // 添加 -
	}

	int findTargetSumWays(vector<int>& nums, int target)
	{
		result = 0;
		backtracking(nums, 0, 0, target);
		return result;
	}
};

class Solution2
{
 public:
	int findTargetSumWays(vector<int>& nums, int target)
	{
		// 获取背包的尺寸
		int sum = 0;
		for (auto num : nums)
		{
			sum += num;
		}
		if (abs(target) > sum) return 0; // 此时没有方案
		if ((target + sum) % 2 == 1) return 0; // 此时没有方案
		int bagSize = (sum + target) / 2;

		// 开始01背包
		vector<int> dp(bagSize + 1);
		dp[0] = 1;
		for (int num : nums)
		{
			for (int j = bagSize; j >= num; j--)
			{
				dp[j] += dp[j - num];
			}
		}

		return dp[bagSize];
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		nums = { 1, 1, 1, 1, 1 };
		cout << "exp1 (5): " << endl;
		cout << "result: " << solution.findTargetSumWays(nums, 3) << endl;
	}
}
