/*
 * 673. 最长递增子序列的个数		url: https://leetcode.cn/problems/number-of-longest-increasing-subsequence/
 *
 * 题目描述：给定一个未排序的整数数组 nums ， 返回最长递增子序列的个数 。
 * 注意 这个数列必须是 严格 递增的。
 * */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
using namespace std;

class Solution
{
 public:
	int findNumberOfLIS(vector<int>& nums)
	{
		if (nums.size() <= 1) return nums.size();

		vector<int> dp(nums.size(), 1);
		vector<int> count(nums.size(), 1);
		int maxCount = 0;
		for (int i = 1; i < nums.size(); ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (nums[i] > nums[j])
				{
					if (dp[j] + 1 > dp[i])
					{
						dp[i] = dp[j] + 1;

						count[i] = count[j];
					}
					else if (dp[j] + 1 == dp[i])
					{
						count[i] += count[j];
					}
				}
			}
			if (dp[i] > maxCount) maxCount = dp[i];
		}

		int result = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			if (maxCount == dp[i]) result += count[i];
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		nums = { 1, 3, 5, 4, 7 };
		cout << "exp1 (2): " << endl;
		cout << "result: " << solution.findNumberOfLIS(nums) << endl;
	}
}
