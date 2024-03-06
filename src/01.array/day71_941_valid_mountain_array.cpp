/*
 * 941.有效的山脉数组		url: https://leetcode.cn/problems/valid-mountain-array/
 *
 * 题目描述：给你一个数组 `nums`，对于其中每个元素 `nums[i]`，请你统计数组中比它小的所有数字的数目。
 * 换而言之，对于每个 `nums[i]` 你必须计算出有效的 `j` 的数量，其中 `j` 满足 `j != i` **且** `nums[j] < nums[i]` 。
 * 以数组形式返回答案。
 * */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

// 暴力法
class Solution
{
 public:
	bool validMountainArray(vector<int>& arr)
	{
		if (arr.size() < 3) return false;

		int maxIndex = 0;
		for (int i = 1; i < arr.size(); i++)
		{
			if (arr[i] > arr[maxIndex]) maxIndex = i;
		}
		// 如果 maxIndex 在两端，说明不是山峰
		if (maxIndex == 0 || maxIndex == arr.size() - 1) return false;

		for (int i = 1; i < arr.size(); i++)
		{
			if (i <= maxIndex && arr[i - 1] < arr[i]) continue;
			else if (i > maxIndex && arr[i - 1] > arr[i]) continue;

			return false;
		}

		return true;
	}
};

// 双指针法
class Solution2
{
 public:
	bool validMountainArray(vector<int>& arr)
	{
		if (arr.size() < 3) return false;

		int left = 0;
		int right = arr.size() - 1;

		// 注意防止越界
		while (left < arr.size() - 1 && arr[left] < arr[left + 1]) left++;

		while (right > 0 && arr[right] < arr[right - 1]) right--;

		// 如果left或者right都在起始位置，说明不是山峰
		if (left == right && left != 0 && right != arr.size() - 1) return true;
		return false;
	}
};

int main()
{
	Solution solution;
	vector<int> nums, ret;

	{
		cout << "exp1 (true) " << endl;
		nums = { 0, 3, 2, 1 };
		cout << "result: " << solution.validMountainArray(nums) << endl;
	}
}
