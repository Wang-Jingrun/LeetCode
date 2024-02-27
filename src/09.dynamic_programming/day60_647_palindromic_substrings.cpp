/*
 * 647. 回文子串		url: https://leetcode.cn/problems/palindromic-substrings/
 *
 * 题目描述：给你一个字符串 s ，请你统计并返回这个字符串中 回文子串 的数目。
 * 	回文字符串 是正着读和倒过来读一样的字符串。
 * 	子字符串 是字符串中的由连续字符组成的一个序列。
 * 具有不同开始位置或结束位置的子串，即使是由相同的字符组成，也会被视作不同的子串。
 * */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
using namespace std;

class Solution
{
 public:
	int countSubstrings(const string& str)
	{
		vector<vector<bool>> dp(str.size(), vector<bool>(str.size(), false));
		int result = 0;
		for (int i = str.size() - 1; i >= 0; i--)
		{
			for (int j = i; j < str.size(); j++)
			{
				if (str[i] == str[j])
				{
					if (j - i <= 1)
					{
						dp[i][j] = true;
						result++;
					}
					else if (dp[i + 1][j - 1])
					{
						dp[i][j] = true;
						result++;
					}
				}
			}
		}
		return result;
	}
};

class Solution2
{
 public:
	int countSubstrings(const string& s)
	{
		int result = 0;
		for (int i = 0; i < s.size(); i++)
		{
			result += extend(s, i, i, s.size()); // 以i为中心
			result += extend(s, i, i + 1, s.size()); // 以i和i+1为中心
		}
		return result;
	}

	int extend(const string& s, int i, int j, int n)
	{
		int res = 0;
		while (i >= 0 && j < n && s[i] == s[j])
		{
			i--;
			j++;
			res++;
		}
		return res;
	}
};

int main()
{
	Solution2 solution;
	string str;

	{
		str = "abc";
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.countSubstrings(str) << endl;
	}

	{
		str = "aaa";
		cout << "exp2 (6): " << endl;
		cout << "result: " << solution.countSubstrings(str) << endl;
	}
}
