/*
 * 18. 四数之和	url: https://leetcode.cn/problems/4sum/
 *
 * 题目描述：给你一个由 n 个整数组成的数组 nums ，和一个目标值 target 。
 * 请你找出并返回满足下述全部条件且不重复的四元组 [nums[a], nums[b], nums[c], nums[d]]
 * （若两个四元组元素一一对应，则认为两个四元组重复）
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	vector<vector<int>> fourSum(vector<int>& nums, int target)
	{
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());

		// nums.size()返回的是size_t类型的，也就是无符号整型,所以它不支持负数。
		// 当使用 nums.size()-3 进行计算时，如果结果小于0，它将会被视为一个很大的正数
		// 因此此处虽然 nums.size()-3 逻辑正确，但是实际上会出错，除非进行强转 int(nums.size())-3
		for (int i = 0; i < nums.size(); i++)
		{
			// 一级剪枝，去掉不必要的循环
			// 这里使用break，统一通过最后的return返回
			if ((nums[i] > target) && (nums[i] > 0) && (target > 0)) break;

			// 一级去重，对 i 去重
			if (i > 0 && nums[i] == nums[i - 1]) continue;

			for (int j = i + 1; j < nums.size(); j++)
			{
				/*
				 * 对于 j 的循环，此时相当于 nums[i] + nums[j] 为一个整体，
				 * 同时 j 开始的地方 也就是 i + 1，只有 j > i + 1，j - 1才是合法的。
				 * */

				// 二级剪枝，去掉不必要的循环
				// 这里使用break，统一通过最后的return返回
				if ((nums[i] + nums[j] > target) && (nums[i] + nums[j] > 0) && (target > 0)) break;

				// 一级去重，对 j 去重
				if (j > i + 1 && nums[j] == nums[j - 1]) continue;

				int left = j + 1;
				int right = nums.size() - 1;

				while (left < right)
				{
					// nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
					if ((long)nums[i] + nums[j] + nums[left] + nums[right] > target) right--;
						// nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
					else if ((long)nums[i] + nums[j] + nums[left] + nums[right] < target) left++;
					else
					{
						// cout << i << " " << left << " " << right << endl;
						result.push_back({ nums[i], nums[j], nums[left], nums[right] });

						// 对nums[left]和nums[right]去重
						while (right > left && nums[right] == nums[right - 1]) right--;
						while (right < left && nums[left] == nums[left + 1]) left++;

						// 找到答案时，双指针同时收缩
						right--;
						left++;
					}
				}
			}
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> input;
	vector<vector<int>> result;

	cout << "exp1 ([[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]): " << endl;
	input = { 1, 0, -1, 0, -2, 2 };
	result = solution.fourSum(input, 0);
	for (const auto& nums : result)
	{
		for (auto num : nums)
		{
			cout << num << " ";
		}
		cout << endl;
	}

	cout << "exp2 ([[2,2,2,2]]): " << endl;
	input = { 2, 2, 2, 2, 2 };
	result = solution.fourSum(input, 8);
	for (const auto& nums : result)
	{
		for (auto num : nums)
		{
			cout << num << " ";
		}
		cout << endl;
	}

	cout << "exp3 ([[-2,-1,1,2],[-1,-1,1,1]]): " << endl;
	input = { -2, -1, -1, 1, 1, 2, 2 };
	result = solution.fourSum(input, 0);
	for (const auto& nums : result)
	{
		for (auto num : nums)
		{
			cout << num << " ";
		}
		cout << endl;
	}
}