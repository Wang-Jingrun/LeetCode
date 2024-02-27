/*
 * 392. 判断子序列		url: https://leetcode.cn/problems/is-subsequence/
 *
 * 题目描述：给定字符串 s 和 t ，判断 s 是否为 t 的子序列。
 * 字符串的一个子序列是原始字符串删除一些（也可以不删除）字符
 * 而不改变剩余字符相对位置形成的新字符串。（例如，"ace"是
 * "abcde"的一个子序列，而"aec"不是）。
 * 进阶：
 * 如果有大量输入的 S，称作 S1, S2, ... , Sk 其中 k >= 10亿，
 * 你需要依次检查它们是否为 T 的子序列。在这种情况下，你会怎样改变代码？
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 双指针法
class Solution
{
 public:
	bool isSubsequence(const string& s, const string& t)
	{
		int j = 0;
		for (int i = 0; i < t.size() && j < s.size(); i++)
		{
			if (t[i] == s[j]) j++;
		}

		if (j == s.size()) return true;
		return false;
	}
};

// 动态规划
class Solution2
{
 public:
	bool isSubsequence(const string& s, const string& t)
	{
		vector<vector<int>> dp(s.size() + 1, vector<int>(t.size() + 1, 0));
		for (int i = 1; i <= s.size(); i++)
		{
			for (int j = 1; j <= t.size(); j++)
			{
				if (s[i - 1] == t[j - 1])
					dp[i][j] = dp[i - 1][j - 1] + 1;
				else
					dp[i][j] = dp[i][j - 1];
			}
		}
		if (dp[s.size()][t.size()] == s.size()) return true;
		return false;
	}
};

int main()
{
	Solution2 solution;
	string s;
	string t;

	{
		s = "abc";
		t = "ahbgdc";
		cout << "exp1 (true): " << endl;
		cout << "result: " << solution.isSubsequence(s, t) << endl;
	}
}
