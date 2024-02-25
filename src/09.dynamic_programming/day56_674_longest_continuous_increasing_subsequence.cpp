/*
 * 674. 最长连续递增序列	url: https://leetcode.cn/problems/longest-continuous-increasing-subsequence/
 *
 * 题目描述：给定一个未经排序的整数数组，找到最长且 连续递增的子序列，并返回该序列的长度。
 * 连续递增的子序列 可以由两个下标 l 和 r（l < r）确定，如果对于每个 l <= i < r，都有
 * nums[i] < nums[i + 1] ，那么子序列 [nums[l], nums[l + 1], ..., nums[r - 1],
 * nums[r]] 就是连续递增子序列。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int findLengthOfLCIS(vector<int>& nums)
	{
		int result = 1;
		for (int i = 1; i < nums.size();)
		{
			int temp = 1;
			while ((i < nums.size()) && (nums[i] > nums[i - 1]))
			{
				temp++;
				i++;
			}
			result = max(result, temp);
			i++;
		}
		return result;
	}
};

// 动态规划
class Solution2
{
 public:
	int findLengthOfLCIS(vector<int>& nums)
	{
		int len = nums.size();
		vector<int> dp(len, 1);
		int result = 1;

		for (int i = 1; i < len; i++)
		{
			if (nums[i] > nums[i - 1]) dp[i] = dp[i - 1] + 1;
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
		nums = { 1, 3, 5, 7 };
		cout << "exp1 (4): " << endl;
		cout << "result: " << solution.findLengthOfLCIS(nums) << endl;
	}
}
