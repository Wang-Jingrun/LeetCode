/*
 * 78. 子集		url: https://leetcode.cn/problems/subsets/
 *
 * 题目描述：给你一个整数数组 nums ，数组中的元素 互不相同 。返回该数组所有可能的子集（幂集）。
 * 解集 不能 包含重复的子集。你可以按 任意顺序 返回解集。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 private:
	vector<int> m_path;
	vector<vector<int>> m_result;

	void backtracking(vector<int>& nums, int startIndex)
	{
		// 所有的情况都需要记录结果
		m_result.push_back(m_path);

		for (int i = startIndex; i < nums.size(); ++i)
		{
			m_path.push_back(nums[i]);
			backtracking(nums, i + 1);
			m_path.pop_back();
		}
	}

 public:
	vector<vector<int>> subsets(vector<int>& nums)
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

	{
		cout << R"(exp1 ([[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]): )" << endl;
		input = { 1, 2, 3 };
		cout << "result: ";
		auto result = solution.subsets(input);
		cout << "[";
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