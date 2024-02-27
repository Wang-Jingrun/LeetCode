/*
 * 516. 最长回文子序列		url: https://leetcode.cn/problems/longest-palindromic-subsequence/
 *
 * 题目描述：给你一个字符串 s ，找出其中最长的回文子序列，并返回该序列的长度。
 * 	子序列定义为：不改变剩余字符顺序的情况下，删除某些字符或者不删除任何字符形成的一个序列。
 * */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
using namespace std;

class Solution
{
 public:
	int longestPalindromeSubseq(const string& s)
	{
		vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));
		for (int i = s.size() - 1; i >= 0; i--)
		{
			for (int j = i; j < s.size(); j++)
			{
				if (s[i] == s[j])
				{
					if (i == j)
						dp[i][j] = 1;
					else if (j == i + 1)
						dp[i][j] = 2;
					else
						dp[i][j] = dp[i + 1][j - 1] + 2;
				}
				else
				{
					dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
				}
			}
		}
		return dp[0][s.size() - 1];
	}
};

int main()
{
	Solution solution;
	string str;

	{
		str = "bbbab";
		cout << "exp1 (4): " << endl;
		cout << "result: " << solution.longestPalindromeSubseq(str) << endl;
	}

	{
		str = "cbbd";
		cout << "exp2 (2): " << endl;
		cout << "result: " << solution.longestPalindromeSubseq(str) << endl;
	}
}
