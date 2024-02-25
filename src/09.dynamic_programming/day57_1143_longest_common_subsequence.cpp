/*
 * 1143. 最长公共子序列		url: https://leetcode.cn/problems/longest-common-subsequence/
 *
 * 题目描述：给定两个字符串 text1 和 text2，返回这两个字符串的最长
 * 公共子序列 的长度。如果不存在 公共子序列 ，返回 0 。
 * 一个字符串的 子序列 是指这样一个新的字符串：它是由原字符串在不改变
 * 字符的相对顺序的情况下删除某些字符（也可以不删除任何字符）后组成的新字符串。
 * 		例如，"ace" 是 "abcde" 的子序列，但 "aec" 不是 "abcde" 的子序列。
 * 两个字符串的 公共子序列 是这两个字符串所共同拥有的子序列。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int longestCommonSubsequence(const string& text1, const string& text2)
	{
		int len1 = text1.size();
		int len2 = text2.size();
		vector<vector<int>> dp(len1 + 1, vector<int>(len2 + 1, 0));
		for (int i = 1; i <= len1; i++)
		{
			for (int j = 1; j <= len2; j++)
			{
				if (text1[i - 1] == text2[j - 1])
					dp[i][j] = dp[i - 1][j - 1] + 1;
				else
					dp[i][j] = max(dp[i][j - 1], dp[i - 1][j]);
			}
		}
		return dp[len1][len2];
	}
};

int main()
{
	Solution solution;
	string text1;
	string text2;

	{
		text1 = "abcde";
		text2 = "ace";
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.longestCommonSubsequence(text1, text2) << endl;
	}
}
