/*
 * 47. 全排列 II		url: https://leetcode.cn/problems/permutations-ii/
 *
 * 题目描述：给定一个可包含重复数字的序列 nums ，按任意顺序 返回所有不重复的全排列。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 private:
	vector<int> path;
	vector<vector<int>> result;

	void backtracking(vector<int>& nums, vector<bool>& used)
	{
		if (path.size() == nums.size())
		{
			result.push_back(path);
			return;
		}

		for (int i = 0; i < nums.size(); ++i)
		{
			if (used[i]) continue;

			if (i > 0 && nums[i] == nums[i - 1] && !used[i - 1]) continue;

			path.push_back(nums[i]);
			used[i] = true;
			backtracking(nums, used);
			path.pop_back();
			used[i] = false;
		}
	}

 public:
	vector<vector<int>> permuteUnique(vector<int>& nums)
	{
		path.clear();
		result.clear();
		sort(nums.begin(), nums.end());
		vector<bool> used(nums.size(), false);
		backtracking(nums, used);
		return result;
	}
};

int main()
{

	Solution solution;
	vector<int> input;
	vector<vector<int>> result;

	{
		cout << "exp1 ([[1,1,2],[1,2,1],[2,1,1]]): " << endl;

		cout << "result: ";
		input = { 1, 1, 2 };
		result = solution.permuteUnique(input);
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