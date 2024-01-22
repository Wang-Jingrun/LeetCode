/*
 * 40. 组合总和 II		url: https://leetcode.cn/problems/combination-sum-ii/
 *
 * 题目描述：给定一个候选人编号的集合 candidates 和一个目标数 target ，
 * 找出 candidates 中所有可以使数字和为 target 的组合。
 * candidates 中的每个数字在每个组合中只能使用 一次 。
 * 注意：解集不能包含重复的组合。
 * */

#include <iostream>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <vector>
using namespace std;

class Solution
{
 private:
	vector<int> m_path;
	vector<vector<int>> m_result;

	void backtracking(vector<int>& candidates, vector<bool>& used, int startIndex, int target)
	{
		// 剪枝
		if (target < 0) return;

		// 找到目标结果
		if (target == 0)
		{
			m_result.push_back(m_path);
			return;
		}

		for (int i = startIndex; i < candidates.size(); ++i)
		{
			// 树层去重，!used[i - 1] 表示是在树层的位置去重
			if (i > 0 && candidates[i] == candidates[i - 1] && !used[i - 1])
			{
				continue;
			}

			m_path.push_back(candidates[i]);
			used[i] = true;
			backtracking(candidates, used, i + 1, target - candidates[i]); // target - num 隐藏回溯
			m_path.pop_back();        // 回溯
			used[i] = false;        // 回溯
		}
	}

 public:
	vector<vector<int>> combinationSum2(vector<int> candidates, int target)
	{
		vector<bool> used(candidates.size(), false);
		m_path.clear();
		m_result.clear();
		// 首先把给candidates排序，让其相同的元素都挨在一起。
		sort(candidates.begin(), candidates.end());
		backtracking(candidates, used, 0, target);
		return m_result;
	}
};

class Solution2
{
 private:
	vector<int> m_path;
	vector<vector<int>> m_result;

	void backtracking(vector<int>& candidates, int startIndex, int target)
	{
		// 剪枝
		if (target < 0) return;

		// 找到目标结果
		if (target == 0)
		{
			m_result.push_back(m_path);
			return;
		}

		for (int i = startIndex; i < candidates.size(); ++i)
		{
			// 树层去重
			if (i > startIndex && candidates[i] == candidates[i - 1])
			{
				continue;
			}

			m_path.push_back(candidates[i]);
			backtracking(candidates, i + 1, target - candidates[i]); // target - num 隐藏回溯
			m_path.pop_back();        // 回溯
		}
	}

 public:
	vector<vector<int>> combinationSum2(vector<int> candidates, int target)
	{
		m_path.clear();
		m_result.clear();
		// 首先把给candidates排序，让其相同的元素都挨在一起。
		sort(candidates.begin(), candidates.end());
		backtracking(candidates, 0, target);
		return m_result;
	}
};

int main()
{

	Solution2 solution;
	vector<int> candidates;
	vector<vector<int>> result;

	{
		cout << "exp1 ([[1,1,6],[1,2,5],[1,7],[2,6]]): " << endl;

		cout << "result: ";
		candidates = { 10, 1, 2, 7, 6, 1, 5 };
		result = solution.combinationSum2(candidates, 8);
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

	{
		cout << "exp2 ([[1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1 1]]): " << endl;

		cout << "result: ";
		candidates =
			{ 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
			  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
		result = solution.combinationSum2(candidates, 30);
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

	return 0;
}