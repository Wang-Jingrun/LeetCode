/*
 * 46. 全排列		url: https://leetcode.cn/problems/permutations/
 *
 * 题目描述：给定一个不含重复数字的数组 nums ，返回其 所有可能的全排列 。你可以 按任意顺序 返回答案。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 private:
	vector<int> path;
	vector<vector<int>> result;

	void backtracking(const vector<int>& nums, vector<bool>& used)
	{
		if (path.size() == nums.size())
		{
			result.push_back(path);
			return;
		}

		for (int i = 0; i < nums.size(); ++i)
		{
			if (used[i]) continue;

			path.push_back(nums[i]);
			used[i] = true;
			backtracking(nums, used);
			path.pop_back();
			used[i] = false;
		}
	}

 public:
	vector<vector<int>> permute(const vector<int>& nums)
	{
		path.clear();
		result.clear();
		vector<bool> used(nums.size(), false);
		backtracking(nums, used);
		return result;
	}
};

int main()
{

	Solution solution;
	vector<vector<int>> result;

	{
		cout << "exp1 ([[1,2,3],[1,3,2],[2,1,3],[2,3,1],[3,1,2],[3,2,1]]): " << endl;

		cout << "result: ";
		result = solution.permute({ 1, 2, 3 });
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