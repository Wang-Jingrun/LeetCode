/*
 * 283. 移动零		url: https://leetcode.cn/problems/move-zeroes/
 *
 * 题目描述：给定一个数组 nums，编写一个函数将所有 0 移动到数组的末尾，同时保持非零元素的相对顺序。
 * 请注意 ，必须在不复制数组的情况下原地对数组进行操作。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	void moveZeroes(vector<int>& nums)
	{
		for (int i = 0, j = 0; i < nums.size() && j < nums.size();)
		{
			if (nums[j] != 0)
			{
				swap(nums[i], nums[j]);
				i++;
			}
			j++;
		}
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		cout << "exp1 ([1,3,12,0,0]): ";
		nums = { 0, 1, 0, 3, 12 };
		solution.moveZeroes(nums);
		cout << "[";
		for (auto i : nums)
		{
			cout << i << " ";
		}
		cout << "]" << endl;
	}

}
