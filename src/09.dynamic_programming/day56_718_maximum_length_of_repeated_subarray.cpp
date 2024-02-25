/*
 * 718. 最长重复子数组		url: https://leetcode.cn/problems/maximum-length-of-repeated-subarray/
 *
 * 题目描述：给两个整数数组 nums1 和 nums2 ，返回 两个数组中 公共的 、长度最长的子数组的长度 。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int findLength(vector<int>& nums1, vector<int>& nums2)
	{
		int len1 = nums1.size();
		int len2 = nums2.size();
		int result = 0;
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
		for (int i = 1; i <= len1; i++)
		{
			for (int j = 1; j <= len2; j++)
			{
				if (nums1[i - 1] == nums2[j - 1])
				{
					dp[i][j] = dp[i - 1][j - 1] + 1;
					result = max(result, dp[i][j]);
				}
			}
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> nums1;
	vector<int> nums2;

	{
		nums1 = { 1, 2, 3, 2, 1 };
		nums2 = { 3, 2, 1, 4, 7 };
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.findLength(nums1, nums2) << endl;
	}

	{
		nums1 = { 0, 0, 0, 0, 0 };
		nums2 = { 0, 0, 0, 0, 0 };
		cout << "exp2 (5): " << endl;
		cout << "result: " << solution.findLength(nums1, nums2) << endl;
	}
}
