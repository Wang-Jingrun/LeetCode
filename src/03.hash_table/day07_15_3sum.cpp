/*
 * 15. 三数之和	url: https://leetcode.cn/problems/3sum/
 *
 * 题目描述：给你一个整数数组 nums ，判断是否存在三元组 [nums[i], nums[j], nums[k]]
 * 满足 i != j、i != k 且 j != k ，同时还满足 nums[i] + nums[j] + nums[k] == 0 。
 * 请你返回所有和为 0 且不重复的三元组。
 * 注意：答案中不可以包含重复的三元组。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution
{
 public:
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());

		// 找出a + b + c = 0
		// a = nums[i], b = nums[left], c = nums[right]
		for (int i = 0; i < nums.size(); ++i)
		{
			// 排序之后如果第一个元素已经大于零，那么无论如何组合都不可能凑成三元组，直接返回结果就可以了
			if (nums[i] > 0) return result;

			// 错误去重a方法，将会漏掉-1,-1,2 这种情况
			/*
			if (nums[i] == nums[i + 1]) {
				continue;
			}
			*/

			// 正确去重a方法
			/*
			 * 因为已经排序过了，只要a前面有一样的，接下来的abc要么是和前面重复的，
			 * 要么就找不到这组了。bc同理只要重复一次就重复了。例如，a[0]=a[1]的
			 * 时候，后者三元组的集合是前者的真子集，就是一个集合问题.
			 * */
			if (i > 0 && nums[i] == nums[i - 1]) continue;

			int left = i + 1;
			int right = nums.size() - 1;

			while (left < right)
			{
				// 去重复逻辑如果放在这里，0，0，0 的情况，可能直接导致 right<=left 了，从而漏掉了 0,0,0 这种三元组
				/*
				while (right > left && nums[right] == nums[right - 1]) right--;
				while (right > left && nums[left] == nums[left + 1]) left++;
				*/
				if (nums[i] + nums[left] + nums[right] > 0) right--;
				else if (nums[i] + nums[left] + nums[right] < 0) left++;
				else
				{
					// cout << i << " " << left << " " << right << endl;
					result.push_back({ nums[i], nums[left], nums[right] });

					// 去重逻辑应该放在找到一个三元组之后，对b 和 c去重
					while (right > left && nums[right] == nums[right - 1]) right--;
					while (right < left && nums[left] == nums[left + 1]) left++;

					// 找到答案时，双指针同时收缩
					right--;
					left++;
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

	cout << "exp1 ([[-1,-1,2],[-1,0,1]]): " << endl;
	input = { -1, 0, 1, 2, -1, -4 };
	result = solution.threeSum(input);
	for (auto nums : result)
	{
		for (auto num : nums)
		{
			cout << num << " ";
		}
		cout << endl;
	}

	cout << "exp2 ([[0, 0, 0]]): " << endl;
	input = { 0, 0, 0, 0 };
	result = solution.threeSum(input);
	for (auto nums : result)
	{
		for (auto num : nums)
		{
			cout << num << " ";
		}
		cout << endl;
	}
}