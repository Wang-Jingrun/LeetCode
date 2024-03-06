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
		int slowIndex = 0;
		for (int fastIndex = 0; fastIndex < nums.size(); fastIndex++)
		{
			if (nums[fastIndex] != 0) nums[slowIndex++] = nums[fastIndex];
		}

		// 将slowIndex之后的冗余元素赋值为0
		for (int i = slowIndex; i < nums.size(); i++)
			nums[i] = 0;
	}
};

class Solution2
{
 public:
	void moveZeroes(vector<int>& nums)
	{
		for (int i = 0, j = 0; j < nums.size(); j++)
		{
			if (nums[j] != 0)
			{
				swap(nums[i], nums[j]);
				i++;
			}
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
