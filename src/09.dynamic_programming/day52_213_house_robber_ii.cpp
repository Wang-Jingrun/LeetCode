/*
 * 213. 打家劫舍 II		url: https://leetcode.cn/problems/house-robber-ii/
 *
 * 题目描述：你是一个专业的小偷，计划偷窃沿街的房屋，每间房内都藏有一定的现金。
 * 这个地方所有的房屋都 围成一圈 ，这意味着第一个房屋和最后一个房屋是紧挨着的。
 * 同时，相邻的房屋装有相互连通的防盗系统，如果两间相邻的房屋在同一晚上被小偷闯
 * 入，系统会自动报警 。
 * 给定一个代表每个房屋存放金额的非负整数数组，计算你 在不触动警报装置的情况下 ，
 * 今晚能够偷窃到的最高金额。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int sub_rob(vector<int>& nums, int begin, int end)
	{
		if (end - begin == 0) return nums[begin];

		vector<int> dp(nums.size());
		dp[begin] = nums[begin];
		dp[begin + 1] = max(nums[begin], nums[begin + 1]);
		for (int i = begin + 2; i <= end; i++)
		{
			dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
		}
		return dp[end];
	}

	int rob(vector<int>& nums)
	{
		if (nums.size() == 0) return 0;
		if (nums.size() == 1) return nums[0];
		return max(sub_rob(nums, 0, nums.size() - 2),
			sub_rob(nums, 1, nums.size() - 1));
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		nums = { 2, 3, 2 };
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.rob(nums) << endl;
	}

	{
		nums = { 1, 2, 3, 1 };
		cout << "exp2 (4): " << endl;
		cout << "result: " << solution.rob(nums) << endl;
	}
}
