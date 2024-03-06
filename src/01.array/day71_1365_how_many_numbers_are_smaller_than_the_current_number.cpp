/*
 * 1365. 有多少小于当前数字的数字	url: https://leetcode.cn/problems/how-many-numbers-are-smaller-than-the-current-number/
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
	vector<int> smallerNumbersThanCurrent(vector<int>& nums)
	{
		vector<int> result(nums.size(), 0);
		for (int i = 0; i < nums.size(); i++)
		{
			for (int j = 0; j < nums.size(); j++)
			{
				if (nums[j] < nums[i]) result[i]++;
			}
		}
		return result;
	}
};

// 哈希法
class Solution2
{
 public:
	vector<int> smallerNumbersThanCurrent(vector<int>& nums)
	{
		vector<int> vec = nums;
		sort(vec.begin(), vec.end());  // 从小到大排序之后，元素下标就是小于当前数字的数字

		unordered_map<int, int> umap;
		// 从后向前，记录 vec[i] 对应的下标, 这样 umap 里存放的就是相同元素最左面的数值和下标了
		for (int i = vec.size() - 1; i >= 0; i--)
			umap[vec[i]] = i;

		// 此时 umap 里保存的每一个元素数值 对应的 小于这个数值的个数
		for (int i = 0; i < vec.size(); i++)
		{
			vec[i] = umap[nums[i]];
		}
		return vec;
	}
};

int main()
{
	Solution solution;
	vector<int> nums, ret;

	{
		cout << "exp1 ([4, 0, 1, 1, 3]): ";
		nums = { 8, 1, 2, 2, 3 };
		ret = solution.smallerNumbersThanCurrent(nums);
		cout << "[";
		for (auto i : ret)
		{
			cout << i << " ";
		}
		cout << "]" << endl;
	}
}
