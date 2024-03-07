/*
 * 922. 按奇偶排序数组 II		url: https://leetcode.cn/problems/sort-array-by-parity-ii/
 *
 * 题目描述：给定一个非负整数数组 nums，  nums 中一半整数是 奇数 ，一半整数是 偶数 。
 *
 * 对数组进行排序，以便当 nums[i] 为奇数时，i 也是 奇数 ；当 nums[i] 为偶数时， i 也是 偶数 。
 *
 * 你可以返回 任何满足上述条件的数组作为答案 。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 public:
	vector<int> sortArrayByParityII(vector<int>& nums)
	{
		vector<int> result(nums.size());
		int even = 0, odd = 1;

		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] % 2 == 0)
			{
				result[even] = nums[i];
				even += 2;
			}
			else
			{
				result[odd] = nums[i];
				odd += 2;
			}
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> nums, ret;

	{
		cout << "exp1 : ";
		nums = { 3, 1, 4, 2 };
		ret = solution.sortArrayByParityII(nums);
		cout << "[ ";
		for (auto i : ret)
		{
			cout << i << " ";
		}
		cout << "]" << endl;
	}
}
