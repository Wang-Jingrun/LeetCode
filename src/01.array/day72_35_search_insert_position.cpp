/*
 * 35. 搜索插入位置		url: https://leetcode.cn/problems/search-insert-position/
 *
 * 题目描述：给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。
 * 如果目标值不存在于数组中，返回它将会被按顺序插入的位置。
 *
 * 请必须使用时间复杂度为 O(log n) 的算法。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 public:
	int searchInsert(vector<int>& nums, int target)
	{
		int n = nums.size();
		int left = 0;
		int right = n - 1; // 定义target在左闭右闭的区间里，[left, right]
		while (left <= right) // 当left==right，区间[left, right]依然有效
		{
			int middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
			if (nums[middle] > target)
				right = middle - 1; // target 在左区间，所以[left, middle - 1]
			else if (nums[middle] < target)
				left = middle + 1; // target 在右区间，所以[middle + 1, right]
			else // nums[middle] == target
				return middle;
		}
		// 分别处理如下四种情况
		// 目标值在数组所有元素之前  [0, -1]
		// 目标值等于数组中某一个元素  return middle;
		// 目标值插入数组中的位置 [left, right]，return  right + 1
		// 目标值在数组所有元素之后的情况 [left, right]， 因为是右闭区间，所以 return right + 1
		return right + 1;
	}
};

int main()
{
	Solution solution;
	vector<int> nums, ret;

	{
		cout << "exp1 (4): ";
		nums = { 1, 3, 5, 6 };
		cout << solution.searchInsert(nums, 7) << endl;
	}
}
