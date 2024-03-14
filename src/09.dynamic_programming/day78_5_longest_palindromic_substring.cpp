/*
 * 5. 最长回文子串		url: https://leetcode.cn/problems/longest-palindromic-substring/
 *
 * 题目描述：给你一个字符串 s，找到 s 中最长的回文子串。
 * 如果字符串的反序与原始字符串相同，则该字符串称为回文字符串。
 * */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
using namespace std;

class Solution
{
 public:
	string longestPalindrome(const string& s)
	{
		vector<vector<bool>> dp(s.size(), vector<bool>(s.size(), false));

		int start = 0, end = 0;
		for (int i = s.size() - 1; i >= 0; --i)
		{
			for (int j = i; j < s.size(); ++j)
			{
				if (s[i] == s[j])
				{
					if (i == j || i + 1 == j)
						dp[i][j] = true;
					else
						dp[i][j] = dp[i + 1][j - 1];

					if (dp[i][j] && (end - start < j - i))
					{
						end = j;
						start = i;
					}
				}
			}
		}
		return s.substr(start, end - start + 1);
	}
};

int main()
{
	Solution solution;
	string str;

	{
		str = "cbbd";
		cout << "exp1 (bb): " << endl;
		cout << "result: " << solution.longestPalindrome(str) << endl;
	}
}
