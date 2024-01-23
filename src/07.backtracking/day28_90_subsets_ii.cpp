/*
 90. 子集 II		url: https://leetcode.cn/problems/subsets-ii/
 *
 * 题目描述：给你一个整数数组 nums ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。
 * 解集 不能 包含重复的子集。返回的解集中，子集可以按 任意顺序 排列。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
	vector<int> m_path;
	vector<vector<int>> m_result;

	void backtracking(vector<int>& nums, int startIndex)
	{
		m_result.push_back(m_path);

		for (int i = startIndex; i < nums.size(); ++i)
		{
			// 去重，树层去重
			if (i > startIndex && nums[i] == nums[i - 1]) continue;

			m_path.push_back(nums[i]);
			backtracking(nums, i + 1);
			m_path.pop_back();
		}
	}

 public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums)
	{
		m_path.clear();
		m_result.clear();
		// 排序，使相同的元素在一起
		sort(nums.begin(), nums.end());
		backtracking(nums, 0);
		return m_result;
	}
};

int main()
{

	Solution solution;

	{
		cout << R"(exp1 (["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]): )" << endl;

		cout << "result: ";
		auto result = solution.subsetsWithDup("101023");
		cout << "[";
		for (const auto& ip : result)
		{
			cout << ip << " ";
		}
		cout << "]" << endl;
	}

	cout << endl;

	return 0;
}