/*
 * 216. 组合总和 III		url: https://leetcode.cn/problems/combination-sum-iii/
 *
 * 题目描述：找出所有相加之和为 n 的 k 个数的组合，且满足下列条件：
 * 		只使用数字1到9
 * 		每个数字 最多使用一次
 * 		返回 所有可能的有效组合的列表 。该列表不能包含相同的组合两次，组合可以以任何顺序返回。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 private:
	vector<int> m_nums;                // 存放每一次的结果
	vector<vector<int>> m_result;    // 存放最终的结果

	// start --记录当前开始的数字
	// k 	 --组合所需要的数字数
	// n	 --需要满足的和
	void backtracking(int start, int k, int n)
	{
		// 剪枝操作
		if (n < 0) return;

		// 满足数字个数为k
		if (m_nums.size() == k)
		{
			// 满足数字相加之和为 n
			if (n == 0) m_result.push_back(m_nums);

			return;
		}

		// 逐次遍历数字 1 到 9
		for (int i = start; i <= 9 - (k - m_nums.size()) + 1; ++i) // 剪枝操作
		{
			m_nums.push_back(i);
			// i + 1 和 n - i 中包含着回溯
			backtracking(i + 1, k, n - i);
			m_nums.pop_back();    // 回溯
		}
	}

 public:
	vector<vector<int>> combinationSum3(int k, int n)
	{
		// 数组清空，以防上次的结果对本次产生影响
		m_nums.clear();
		m_result.clear();
		backtracking(1, k, n);
		return m_result;
	}
};

int main()
{

	Solution solution;
	vector<vector<int>> result;

	{
		cout << "exp1 ([[2,4],[3,4],[2,3],[1,2],[1,3],[1,4]]): " << endl;

		cout << "result: ";
		result = solution.combinationSum3(3, 9);
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