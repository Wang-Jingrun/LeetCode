/*
 * 1588. 所有奇数长度子数组的和		url: https://leetcode.cn/problems/sum-of-all-odd-length-subarrays/
 *
 * 题目描述：给你一个正整数数组 arr ，请你计算所有可能的奇数长度子数组的和。
 * 子数组 定义为原数组中的一个连续子序列。
 * 请你返回 arr 中 所有奇数长度子数组的和 。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	int sumOddLengthSubarrays(vector<int>& arr)
	{
		vector<int> s(arr.size() + 1); // 前缀和
		for (int i = 0; i < arr.size(); ++i)
		{
			s[i + 1] = s[i] + arr[i];
		}

		int sum = 0;
		for (int i = 0; i < arr.size(); ++i)
		{
			for (int j = 1; i + j <= arr.size(); j += 2)
			{
				sum += s[i + j] - s[i];
			}
		}
		return sum;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		nums = { 1, 4, 2, 5, 3 };
		cout << "exp1 (58): " << solution.sumOddLengthSubarrays(nums) << endl;
	}
}
