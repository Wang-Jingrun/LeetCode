/*
 * 115.不同的子序列		url: https://leetcode.cn/problems/distinct-subsequences/
 *
 * 题目描述：给你两个字符串 s 和 t ，统计并返回在 s 的
 * 子序列 中 t 出现的个数，结果需要对 10^9 + 7 取模。
 * */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
using namespace std;

class Solution
{
 public:
	int numDistinct(const string& s, const string& t)
	{
		vector<vector<uint64_t>> dp(s.size() + 1, vector<uint64_t>(t.size() + 1, 0));
		// 初始化
		for (int i = 0; i < s.size(); i++)
			dp[i][0] = 1;

		for (int i = 1; i <= s.size(); i++)
		{
			for (int j = 1; j <= t.size(); j++)
			{
				if (s[i - 1] == t[j - 1])
					dp[i][j] = dp[i - 1][j] + dp[i - 1][j - 1];
				else
					dp[i][j] = dp[i - 1][j];
			}
		}
		return dp[s.size()][t.size()];
	}
};

int main()
{
	Solution solution;
	string s;
	string t;

	{
		s = "rabbbit";
		t = "rabbit";
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.numDistinct(s, t) << endl;
	}
}
