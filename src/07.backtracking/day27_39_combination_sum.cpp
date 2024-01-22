/*
 * 39. 组合总和		url: https://leetcode.cn/problems/combination-sum/
 *
 * 题目描述：给你一个 无重复元素 的整数数组 candidates 和一个目标整数 target ，
 * 找出 candidates 中可以使数字和为目标数 target 的 所有 不同组合 ，并以列表形式返回。
 * 你可以按 任意顺序 返回这些组合。
 * candidates 中的 同一个 数字可以 无限制重复被选取 。如果至少一个数字的被选数量不同，则两种组合是不同的。
 * 对于给定的输入，保证和为 target 的不同组合数少于 150 个。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
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
			m_path.push_back(candidates[i]);
			// 精髓在 startIndex = i，因为同一个数字可以无限制重复被选取
			backtracking(candidates, i, target - candidates[i]); // target - num 隐藏回溯
			m_path.pop_back();    // 回溯
		}
	}

 public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target)
	{
		m_path.clear();
		m_result.clear();
		backtracking(candidates, 0, target);
		return m_result;
	}
};

int main()
{

	Solution solution;
	vector<int> candidates;
	vector<vector<int>> result;

	{
		cout << "exp1 ([[2,2,2,2],[2,3,3],[3,5]]): " << endl;

		cout << "result: ";
		candidates = { 2, 3, 5 };
		result = solution.combinationSum(candidates, 8);
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