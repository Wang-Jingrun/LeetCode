/*
 * 189. 轮转数组		url: https://leetcode.cn/problems/rotate-array/
 *
 * 题目描述：给定一个整数数组 nums，将数组中的元素向右轮转 k 个位置，其中 k 是非负数。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	void rotate(vector<int>& nums, int k)
	{
		vector<int> vec = nums;

		for (int i = vec.size() - k % vec.size(), j = 0; j < nums.size(); i++, j++)
		{
			nums[j] = vec[i % vec.size()];
		}
	}
};

class Solution2
{
 public:
	void rotate(vector<int>& nums, int k)
	{
		k = k % nums.size();
		reverse(nums.begin(), nums.end());
		reverse(nums.begin(), nums.begin() + k);
		reverse(nums.begin() + k, nums.end());
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		cout << "exp1 ([5, 6, 7, 1, 2, 3, 4]): ";
		nums = { 1, 2, 3, 4, 5, 6, 7 };
		solution.rotate(nums, 3);
		cout << "[ ";
		for (auto i : nums)
		{
			cout << i << " ";
		}
		cout << "]" << endl;
	}
}
