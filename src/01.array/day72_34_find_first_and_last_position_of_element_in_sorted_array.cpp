/*
 * 34. 在排序数组中查找元素的第一个和最后一个位置		url: https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/
 *
 * 题目描述：给你一个按照非递减顺序排列的整数数组 nums，和一个目标值 target。
 * 请你找出给定目标值在数组中的开始位置和结束位置。
 *
 * 如果数组中不存在目标值 target，返回 [-1, -1]。
 *
 * 你必须设计并实现时间复杂度为 O(log n) 的算法解决此问题。
 * */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	vector<int> searchRange(vector<int>& nums, int target)
	{
		for (int i = 0, j = nums.size() - 1; i <= j;)
		{
			if (nums[i] == target && nums[j] == target) return { i, j };

			if (nums[i] != target) i++;
			if (nums[j] != target) j--;
		}
		return { -1, -1 };
	}
};

class Solution2
{
 public:
	vector<int> searchRange(vector<int>& nums, int target)
	{
		int leftBorder = getLeftBorder(nums, target);
		int rightBorder = getRightBorder(nums, target);
		// 情况一
		if (leftBorder == -2 || rightBorder == -2) return { -1, -1 };
		// 情况三
		if (rightBorder - leftBorder > 1) return { leftBorder + 1, rightBorder - 1 };
		// 情况二
		return { -1, -1 };
	}
 private:
	int getRightBorder(vector<int>& nums, int target)
	{
		int left = 0;
		int right = nums.size() - 1;
		int rightBorder = -2; // 记录一下rightBorder没有被赋值的情况
		while (left <= right)
		{
			int middle = left + ((right - left) / 2);
			if (nums[middle] > target)
			{
				right = middle - 1;
			}
			else
			{ // 寻找右边界，nums[middle] == target的时候更新left
				left = middle + 1;
				rightBorder = left;
			}
		}
		return rightBorder;
	}
	int getLeftBorder(vector<int>& nums, int target)
	{
		int left = 0;
		int right = nums.size() - 1;
		int leftBorder = -2; // 记录一下leftBorder没有被赋值的情况
		while (left <= right)
		{
			int middle = left + ((right - left) / 2);
			if (nums[middle] >= target)
			{ // 寻找左边界，nums[middle] == target的时候更新right
				right = middle - 1;
				leftBorder = right;
			}
			else
			{
				left = middle + 1;
			}
		}
		return leftBorder;
	}
};

int main()
{
	Solution solution;
	vector<int> nums, ret;

	{
		cout << "exp1 ([3, 4]): ";
		nums = { 5, 7, 7, 8, 8, 10 };
		ret = solution.searchRange(nums, 8);
		cout << "[ ";
		for (auto i : ret)
		{
			cout << i << " ";
		}
		cout << "]" << endl;
	}
}
