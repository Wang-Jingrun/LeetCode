/*
 * 1005. K 次取反后最大化的数组和		url: https://leetcode.cn/problems/maximize-sum-of-array-after-k-negations/
 *
 * 题目描述：给你一个整数数组 nums 和一个整数 k ，按以下方法修改该数组：
 * 	选择某个下标 i 并将 nums[i] 替换为 -nums[i] 。
 * 重复这个过程恰好 k 次。可以多次选择同一个下标 i 。
 * 以这种方式修改数组后，返回数组 可能的最大和 。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
	static bool cmp(int a, int b)
	{
		return abs(a) > abs(b);
	}

 public:
	int largestSumAfterKNegations(vector<int>& nums, int k)
	{
		sort(nums.begin(), nums.end(), cmp);

		for (int& num : nums)
		{
			if (num < 0 && k > 0)
			{
				num *= -1;
				k--;
			}
		}

		if (k % 2 == 1) nums.back() *= -1;
		int sum = 0;
		for (int num : nums)
		{
			sum += num;
		}

		return sum;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	cout << "exp1 (5): ";
	nums = { 4, 2, 3 };
	cout << solution.largestSumAfterKNegations(nums, 1) << endl;

	cout << "exp2 (6): ";
	nums = { 3, -1, 0, 2 };
	cout << solution.largestSumAfterKNegations(nums, 3) << endl;

	cout << "exp3 (13): ";
	nums = { 2, -3, -1, 5, -4 };
	cout << solution.largestSumAfterKNegations(nums, 2) << endl;

}
