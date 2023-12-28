/*
 * 209. 长度最小的子数组	url: https://leetcode.cn/problems/minimum-size-subarray-sum/
 *
 * 题目描述：给定一个含有 n 个正整数的数组和一个正整数 target 。
 * 找出该数组中满足其总和大于等于 target 的长度最小的 连续子数组
 * [nums_l, nums_(l+1), ..., nums_(r-1), nums_r] ，并返回其长度。
 * 如果不存在符合条件的子数组，返回 0 。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution    // 暴力解法
{
 public:
	int minSubArrayLen(int target, vector<int>& nums)
	{
		int sum = 0;    // 窗口内的元素和
		int subLength = 0;    // 满足条件的子数组长度
		int result = INT_MAX;    // 需要返回的结果, 取最大值才能继续更新更小的值
		for (int left = 0; left < nums.size(); left++)
		{
			// 每次向右累加之前 sum 重新清 0
			sum = 0;
			for (int right = left; right < nums.size(); right++)
			{
				// 依次将窗口中的元素求和
				sum += nums[right];

				// 如果满足条件
				if (sum >= target)
				{
					// 更新子数组长度
					subLength = right - left + 1;
					result = result < subLength ? result : subLength;
					// 满足条件退出即可，不需要继续累加了
					break;
				}
			}
		}

		return result == INT_MAX ? 0 : result;
	}
};

class Solution1    // 滑动窗口法
{
 public:
	int minSubArrayLen(int target, vector<int>& nums)
	{
		int sum = 0;    // 滑动窗口内的元素和
		int left = 0;    // 滑动窗口左侧下标
		int subLength = 0;    // 满足条件的子数组长度
		int result = INT_MAX;    // 需要返回的结果, 取最大值才能继续更新更小的值
		for (int right = 0; right < nums.size(); right++)
		{
			// 依次将滑动窗口中的元素求和
			sum += nums[right];

			// 此处为 while, 因为更新滑动窗口左侧需要使得不满足 sum >= target 时, 才能继续寻找满足条件的子数组
			// 每当 sum >= target 时, 更新子数组长度
			while (sum >= target)
			{
				subLength = right - left + 1;
				// 更新最终结果
				result = result < subLength ? result : subLength;

				// 滑动窗口左边前移, 继续寻找满足条件的子数组
				sum -= nums[left++];
			}
		}

		return result == INT_MAX ? 0 : result;
	}
};

int main()
{
	Solution solution;
	vector<int> cost;

	cout << "exp1 (2): ";
	cost = { 2, 3, 1, 2, 4, 3 };
	cout << solution.minSubArrayLen(7, cost) << endl;

	cout << "exp2 (1): ";
	cost = { 1, 4, 4 };
	cout << solution.minSubArrayLen(4, cost) << endl;

	cout << "exp3 (0): ";
	cost = { 1, 1, 1, 1, 1, 1, 1, 1 };
	cout << solution.minSubArrayLen(11, cost) << endl;

	cout << "exp4 (8): ";
	cost = { 12, 28, 83, 4, 25, 26, 25, 2, 25, 25, 25, 12 };
	cout << solution.minSubArrayLen(213, cost) << endl;
}