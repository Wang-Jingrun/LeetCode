/*
 * 132. 分割回文串 II		url: https://leetcode.cn/problems/palindrome-partitioning-ii/
 *
 * 题目描述：给你一个字符串 s，请你将 s 分割成一些子串，使每个子串都是回文串。
 * 返回符合要求的 最少分割次数 。
 * */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
using namespace std;

class Solution
{
 public:
	int minCut(string s)
	{
		// 二维数组isPalindromic来保存整个字符串的回文情况
		vector<vector<bool>> isPalindromic(s.size(), vector<bool>(s.size(), false));
		for (int i = s.size() - 1; i >= 0; i--)
		{
			for (int j = i; j < s.size(); j++)
			{
				if (s[i] == s[j])
				{
					if (j - i <= 1)
						isPalindromic[i][j] = true;
					else
						isPalindromic[i][j] = isPalindromic[i + 1][j - 1];
				}
			}
		}


		// dp[i]：范围是[0, i]的回文子串，最少分割次数是dp[i]
		vector<int> dp(s.size(), 0);
		for (int i = 0; i < dp.size(); i++) // 初始化
		{
			dp[i] = i;
		}

		for (int i = 1; i < s.size(); i++)
		{
			// 判断是不是回文子串
			if (isPalindromic[0][i])
			{
				dp[i] = 0;
				continue;
			}

			for (int j = 0; j < i; j++)
			{
				if (isPalindromic[j + 1][i])
				{
					dp[i] = min(dp[i], dp[j] + 1);
				}
			}
		}
		return dp.back();
	}
};

int main()
{
	Solution solution;
	string str;

	{
		str = "aab";
		cout << "exp1 (1): " << endl;
		cout << "result: " << solution.minCut(str) << endl;
	}
}
