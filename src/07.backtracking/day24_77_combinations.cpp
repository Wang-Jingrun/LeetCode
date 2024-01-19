/*
 * 77. 组合	url: https://leetcode.cn/problems/combinations/
 *
 * 题目描述：给定两个整数 n 和 k，返回范围 [1, n] 中所有可能的 k 个数的组合。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 private:
	// start --循环开始，end --循环结束，k --最大递归次数
	// path --存放一次完整的结果，result --存放所有的结果
	void backtracking(int start, int end, int k, vector<int>& path, vector<vector<int>>& result)
	{
		// 终止条件，找够了一次的结果
		if (path.size() >= k)
		{
			result.push_back(path);
			return;
		}

		for (int i = start; i <= end - (k - path.size()) + 1; ++i)
		// for (int i = start; i <= end; ++i)
		{
			path.push_back(i);
			// i + 1 中包含着回溯
			backtracking(i + 1, end, k, path, result);
			path.pop_back(); // 回溯
		}
	}

 public:
	vector<vector<int>> combine(int n, int k)
	{
		vector<int> nums;
		vector<vector<int>> result;
		backtracking(1, n, k, nums, result);
		return result;
	}
};

int main()
{

	Solution solution;
	vector<vector<int>> result;

	{
		cout << "exp1 ([[2,4],[3,4],[2,3],[1,2],[1,3],[1,4]]): " << endl;

		cout << "result: ";
		result = solution.combine(4, 2);
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