/*
 * 27.移除元素	url: https://leetcode.cn/problems/remove-element/
 *
 * 题目描述：给你一个数组 nums 和一个值 val，你需要原地移除所有数值等于 val 的元素，并返回移除后数组的新长度。
 * 不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并原地修改输入数组。
 * 元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
 * */

#include <iostream>
#include <vector>
using namespace std;

class MySolution    // 暴力解法
{
 public:
	int removeElement(vector<int>& nums, int val)
	{
		int len = (int)nums.size();
		for (int i = 0; i < len; ++i)
		{
			if (nums[i] == val)
			{
				for (int j = i; j < len - 1; ++j)
				{
					nums[j] = nums[j + 1];
				}
				nums[len - 1] = 0; // 后面的值赋 0
				i--;    // 需要前移一位，以免后移的数据中含有目标值
				len--;  // 此时数组大小也需要减 1
			}
		}
		return len;
	}
};

class Solution    // 双指针法
{
 public:
	int removeElement(vector<int>& nums, int val)
	{
		int slow = 0;
		for (int fast = 0; fast < nums.size(); ++fast)
		{
			if (nums[fast] != val)
				nums[slow++] = nums[fast];
		}

		return slow;
	}
};

int main()
{
	Solution solution;
	vector<int> cost;

	cout << "exp1 (2, [2, 2]): ";
	cost = { 3, 2, 2, 3 };
	cout << solution.removeElement(cost, 3) << endl;

	cout << "exp2 (5, [0, 1, 3, 0, 4]): ";
	cost = { 0, 1, 2, 2, 3, 0, 4, 2 };
	cout << solution.removeElement(cost, 2) << endl;
}
