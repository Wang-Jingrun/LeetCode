/*
 * 300. 最长递增子序列		url: https://leetcode.cn/problems/longest-increasing-subsequence/
 *
 * 题目描述：给你一个整数数组 nums ，找到其中最长严格递增子序列的长度。
 * 子序列 是由数组派生而来的序列，删除（或不删除）数组中的元素而不改变其
 * 余元素的顺序。例如，[3,6,2,7] 是数组 [0,3,1,6,2,2,7] 的子序列。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int lengthOfLIS(vector<int>& nums)
	{
		int len = nums.size();
		vector<int> dp(len, 1);
		int result = 0;
		for (int i = 1; i < len; i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (nums[i] > nums[j])
				{
					dp[i] = max(dp[i], dp[j] + 1);
				}
			}
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
		nums = { 10, 9, 2, 5, 3, 7, 101, 18 };
		cout << "exp1 (4): " << endl;
		cout << "result: " << solution.lengthOfLIS(nums) << endl;
	}
}
