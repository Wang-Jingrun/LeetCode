/*
 * 1. 两数之和	url:https://leetcode.cn/problems/two-sum/description/
 *
 * 题目描述：给定一个整数数组 nums 和一个整数目标值 target，
 * 请你在该数组中找出 和为目标值 target  的那 两个 整数，
 * 并返回它们的数组下标。你可以假设每种输入只会对应一个答案。
 * 但是，数组中同一个元素在答案里不能重复出现。你可以按任意顺序返回答案。
 * */

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution    // 暴力解法
{
 public:
	vector<int> twoSum(vector<int>& nums, int target)
	{
		for (int i = 0; i < nums.size() - 1; i++)
		{
			for (int j = i + 1; j < nums.size(); j++)
			{
				if (nums[i] + nums[j] == target)
				{
					return { i, j };
				}
			}
		}

		return {};
	}
};

class Solution2    // map 哈希表
{
 public:
	vector<int> twoSum(vector<int>& nums, int target)
	{
		unordered_map<int, int> hash;

		for (int i = 0; i < nums.size(); ++i)
		{
			// 遍历当前元素，并在map中寻找是否有匹配的key
			auto pos = hash.find(target - nums[i]);
			if (pos != hash.end())
			{
				return { pos->second, i };
			}

			// 如果没找到匹配对，就把访问过的元素和下标加入到map中
			hash[nums[i]] = i;
		}

		return {};
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums, result;

	cout << "exp1 ([0, 1]): ";
	nums = { 2, 7, 11, 15 };
	result = solution.twoSum(nums, 9);
	for (auto num : result)
	{
		cout << num << " ";
	}
	cout << endl;

	cout << "exp2 ([1, 2]): ";
	nums = { 3, 2, 4 };
	result = solution.twoSum(nums, 6);
	for (auto num : result)
	{
		cout << num << " ";
	}
	cout << endl;

	cout << "exp3 ([0, 1]): ";
	nums = { 3, 3 };
	result = solution.twoSum(nums, 6);
	for (auto num : result)
	{
		cout << num << " ";
	}
	cout << endl;
}