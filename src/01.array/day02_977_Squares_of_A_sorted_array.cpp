/*
 * 977. 有序数组的平方		url: https://leetcode.cn/problems/squares-of-a-sorted-array/
 *
 * 题目描述：给你一个按非递减顺序排序的整数数组 nums，返回每个数字的平方组成的新数组，要求也按非递减顺序排序。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class MySolution    // 暴力解法：先平方后排序
{
 public:
	vector<int> sortedSquares(vector<int>& nums)
	{
		for (int& num : nums)
			num *= num;

//		// 冒泡排序 -- leetcode 无法通过
//		int temp = 0;
//		for (int i = 0; i < nums.size() - 1; ++i)
//		{
//			for (int j = i + 1; j < nums.size(); ++j)
//			{
//				if (nums[i] > nums[j])
//				{
//					temp = nums[i];
//					nums[i] = nums[j];
//					nums[j] = temp;
//				}
//			}
//		}

		sort(nums.begin(), nums.end()); // 快速排序

		return nums;
	}
};

class Solution    // 双指针法
{
 public:
	vector<int> sortedSquares(vector<int>& nums)
	{
		vector<int> ret;
		ret.resize(nums.size());

		int i = 0;
		int j = (int)nums.size() - 1;
		int k = (int)nums.size() - 1;

		while (k >= 0)
		{
			if (nums[i] * nums[i] >= nums[j] * nums[j])
			{
				ret[k--] = (nums[i] * nums[i]);
				++i;
			}
			else if (nums[i] * nums[i] < nums[j] * nums[j])
			{
				ret[k--] = (nums[j] * nums[j]);
				--j;
			}
		}

		return ret;
	}
};

int main()
{
	Solution solution;
	vector<int> nums, ret;

	cout << "exp1 ([0, 1, 9, 16, 100]): ";
	nums = { -4, -1, 0, 3, 10 };
	ret = solution.sortedSquares(nums);
	cout << "[";
	for (auto i : ret)
	{
		cout << i << " ";
	}
	cout << "]" << endl;

	cout << "exp2 ([4, 9, 9, 49, 121]): ";
	nums = { -7, -3, 2, 3, 11 };
	ret = solution.sortedSquares(nums);
	cout << "[";
	for (auto i : ret)
	{
		cout << i << " ";
	}
	cout << "]" << endl;
}
