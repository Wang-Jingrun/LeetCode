/*
 * 724. 寻找数组的中心下标		url: https://leetcode.cn/problems/find-pivot-index/
 *
 * 题目描述：给你一个整数数组 nums ，请计算数组的 中心下标 。
 *
 * 数组 中心下标 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。
 *
 * 如果中心下标位于数组最左端，那么左侧数之和视为 0 ，因为在下标的左侧不存在元素。
 * 这一点对于中心下标位于数组最右端同样适用。
 *
 * 如果数组有多个中心下标，应该返回 最靠近左边 的那一个。如果数组不存在中心下标，
 * 返回 -1 。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 public:
	int pivotIndex(vector<int>& nums)
	{
		int rightSum = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			rightSum += nums[i];
		}

		int leftSum = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			rightSum -= nums[i];
			if (i > 0) leftSum += nums[i - 1];
			if (leftSum == rightSum) return i;
		}

		return -1;
	}
};

int main()
{
	Solution solution;
	vector<int> nums, ret;

	{
		cout << "exp1 (3): ";
		nums = { 1, 7, 3, 6, 5, 6 };
		cout << solution.pivotIndex(nums) << endl;
	}
}
