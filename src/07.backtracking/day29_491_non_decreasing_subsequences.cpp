/*
 * 491.递增子序列		url: https://leetcode.cn/problems/non-decreasing-subsequences/
 *
 * 题目描述：给你一个整数数组 nums ，找出并返回所有该数组中不同的递增子序列，
 * 递增子序列中 至少有两个元素 。你可以按 任意顺序 返回答案。
 * 数组中可能含有重复元素，如出现两个整数相等，也可以视作递增序列的一种特殊情况。
 * */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
 private:
	vector<int> m_path;
	vector<vector<int>> m_result;

	void backtracking(vector<int>& nums, int startIndex)
	{
		if (m_path.size() >= 2)
		{
			m_result.push_back(m_path);
		}

		unordered_set<int> uset; // 使用set对本层元素进行去重
		for (int i = startIndex; i < nums.size(); ++i)
		{
			if (!m_path.empty() && nums[i] < m_path.back()) continue;

			if (uset.find(nums[i]) != uset.end()) continue;

			m_path.push_back(nums[i]);
			uset.insert(nums[i]); // 记录这个元素在本层用过了，本层后面不能再用了
			backtracking(nums, i + 1);
			m_path.pop_back();
		}
	}

 public:
	vector<vector<int>> findSubsequences(vector<int>& nums)
	{
		m_path.clear();
		m_result.clear();
		backtracking(nums, 0);
		return m_result;
	}
};

int main()
{

	Solution solution;
	vector<int> input;
	vector<vector<int>> result;

	{
		cout << "exp1 ([[4,6],[4,6,7],[4,6,7,7],[4,7],[4,7,7],[6,7],[6,7,7],[7,7]]): " << endl;

		cout << "result: ";
		input = { 4, 6, 7, 7 };
		result = solution.findSubsequences
			(input);
		cout << "[ ";
		for (const auto& nums : result)
		{
			cout << "[ ";
			for (auto num : nums)
			{
				cout << num << " ";
			}
			cout << "]";
		}
		cout << "]" << endl;
	}

	cout << endl;

	return 0;
}