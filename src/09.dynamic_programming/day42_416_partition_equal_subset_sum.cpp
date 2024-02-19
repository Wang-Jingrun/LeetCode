/*
 * 416. 分割等和子集		url: https://leetcode.cn/problems/partition-equal-subset-sum/
 *
 * 题目描述：给你一个 只包含正整数 的 非空 数组 nums 。
 * 请你判断是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	bool canPartition(vector<int>& nums)
	{
		// 求和，获得 target 值
		int sum = 0;
		for (auto num : nums)
		{
			sum += num;
		}

		if (sum % 2 != 0) return false;	// sum 不是 2 的倍数则无法分割
		int target = sum / 2;

		// 开始 01背包
		vector<int> dp(target + 1);
		for (int num : nums)
		{
			// 每一个元素一定是不可重复放入，所以从大到小遍历
			// j >= num 保证取 dp[j - num] 合法
			for (int j = target; j >= num; j--)
			{
				dp[j] = max(dp[j], dp[j - num] + num);
			}
		}

		// 集合中的元素正好可以凑成总和target
		if (dp[target] == target) return true;
		return false;
	}
};


int main()
{
	Solution solution;
	vector<int> nums;

	{
		nums = { 1, 5, 11, 5 };
		cout << "exp1 (true): " << endl;
		cout << "result: " << solution.canPartition(nums) << endl;
	}
}
