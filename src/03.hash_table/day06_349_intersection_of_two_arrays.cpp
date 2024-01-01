/*
 * 349. 两个数组的交集		url: https://leetcode.cn/problems/intersection-of-two-arrays/
 *
 * 题目描述：给定两个数组 nums1 和 nums2 ，返回 它们的交集 。
 * 输出结果中的每个元素一定是 唯一 的。我们可以 不考虑输出结果的顺序 。
 * */

#include <iostream>
#include <vector>
#include <map>
#include <unordered_set>
using namespace std;

class Solution        // map 实现，效率较低
{
 public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
	{
		vector<int> result;
		map<int, bool> hash;

		// 将 nums1 中的数据存入哈希表
		for (auto num : nums1)
		{
			if (hash.find(num) == hash.end())
				// 新加入数据
				hash[num] = false;
		}

		// 在哈希表中寻找 nums2 中的数据
		for (auto num : nums2)
		{
			if (hash.find(num) != hash.end())
				hash[num] = true;
		}

		// 输出哈希表的内容
		for (auto it : hash)
		{
			if (it.second)
				result.push_back(it.first);
		}

		return result;
	}
};

class Solution2        // set 实现
{
 public:
	vector<int> intersection(vector<int>& nums1, vector<int>& nums2)
	{
		unordered_set<int> result_set;
		unordered_set<int> hash(nums1.begin(), nums1.end());

		for (int num : nums2)
		{
			// 发现 nums2 的元素在 hash 表中出现过
			if (hash.find(num) != hash.end())
			{
				result_set.insert(num);
			}
		}

		return vector<int>(result_set.begin(), result_set.end());
	}
};

int main()
{
	Solution solution;
	vector<int> nums1, nums2, result;

	cout << "exp1 ([2]): ";
	nums1 = { 1, 2, 2, 1 };
	nums2 = { 2 };
	result = solution.intersection(nums1, nums2);
	for (auto num : result)
	{
		cout << num << " ";
	}
	cout << endl;

	cout << "exp2 ([4, 9]): ";
	nums1 = { 4, 9, 5 };
	nums2 = { 9, 4, 9, 8, 4 };
	result = solution.intersection(nums1, nums2);
	for (auto num : result)
	{
		cout << num << " ";
	}
	cout << endl;
}