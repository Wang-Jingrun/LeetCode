/*
 * 131. 分割回文串		url: https://leetcode.cn/problems/palindrome-partitioning/
 *
 * 题目描述：给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是 回文串 。返回 s 所有可能的分割方案。
 * 回文串 是正着读和反着读都一样的字符串。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 private:
	vector<string> m_path;
	vector<vector<string>> m_result;

	void backtracking(const string& str, int startIndex)
	{
		// 如果起始位置已经大于s的大小，说明已经找到了一组分割方案了
		if (startIndex == str.size())
		{
			m_result.push_back(m_path);
			return;
		}

		// 子串的范围为 [startIndex, i]
		for (int i = startIndex; i < str.size(); ++i)
		{
			if (isPalindrome(str, startIndex, i))
				m_path.push_back(str.substr(startIndex, i - startIndex + 1));
			else
				continue;

			backtracking(str, i + 1);
			m_path.pop_back();
		}
	}

 public:
	bool isPalindrome(const string& s, int start, int end)
	{
		for (int i = start, j = end; i < j; i++, j--)
		{
			if (s[i] != s[j]) return false;
		}
		return true;
	}

	vector<vector<string>> partition(const string& str)
	{
		m_path.clear();
		m_result.clear();
		backtracking(str, 0);
		return m_result;
	}
};

int main()
{

	Solution solution;
	vector<int> candidates;
	vector<vector<int>> result;

	{
//		cout << "exp1 ([[2,2,2,2],[2,3,3],[3,5]]): " << endl;
//
//		cout << "result: ";
//		candidates = { 2, 3, 5 };
//		result = solution.combinationSum(candidates, 8);
//		cout << "[";
//		for (const auto& nums : result)
//		{
//			cout << "[ ";
//			for (auto num : nums)
//			{
//				cout << num << " ";
//			}
//			cout << "]";
//		}
//		cout << "]" << endl;
	}

	cout << endl;

	return 0;
}