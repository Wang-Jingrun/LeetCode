/*
 * 1207.独一无二的出现次数		url: https://leetcode.cn/problems/unique-number-of-occurrences/
 *
 * 题目描述：给你一个整数数组 `arr`，请你帮忙统计数组中每个数的出现次数。
 *
 * 如果每个数的出现次数都是独一无二的，就返回 `true`；否则返回 `false`。
 * */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	bool uniqueOccurrences(vector<int>& arr)
	{
		// 统计出现的频率
		unordered_map<int, int> umap;
		for (int i = 0; i < arr.size(); i++)
			umap[arr[i]]++;

		unordered_set<int> uset;
		for (auto it = umap.begin(); it != umap.end(); ++it)
		{
			if (uset.count(it->second)) return false;

			uset.insert(it->second);
		}
		return true;
	}
};

int main()
{
	Solution solution;
	vector<int> nums, ret;

	{
		cout << "exp1 (true) " << endl;
		nums = { -3, 0, 1, -3, 1, 1, 1, -3, 10, 0 };
		cout << "result: " << solution.uniqueOccurrences(nums) << endl;
	}

	{
		cout << "exp2 (false) " << endl;
		nums = { 1, 2 };
		cout << "result: " << solution.uniqueOccurrences(nums) << endl;
	}
}
