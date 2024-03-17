/*
 * 1480. 一维数组的动态和		url: https://leetcode.cn/problems/running-sum-of-1d-array/
 *
 * 题目描述：给你一个数组 nums 。数组「动态和」的计算公式为：
 * 		runningSum[i] = sum(nums[0]…nums[i]) 。
 * 请返回 nums 的动态和。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// 就是计算前缀和
class Solution
{
 public:
	vector<int> runningSum(vector<int>& nums)
	{
		if (nums.empty()) return {};
		vector<int> result(nums.size());
		result[0] = nums[0];
		for (int i = 1; i < nums.size(); ++i)
		{
			result[i] = result[i - 1] + nums[i];
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		nums = { 1, 2, 3, 4 };
		cout << "exp1 ([1,3,6,10]): ";
		auto result = solution.runningSum(nums);
		for (int num : result)
		{
			cout << num << " ";
		}
		cout << endl;
	}
}
