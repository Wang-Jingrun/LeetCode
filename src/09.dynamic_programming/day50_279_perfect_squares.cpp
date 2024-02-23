/*
 * 279. 完全平方数		url: https://leetcode.cn/problems/perfect-squares/
 *
 * 题目描述：给你一个整数 n ，返回 和为 n 的完全平方数的最少数量 。
 * 完全平方数 是一个整数，其值等于另一个整数的平方；换句话说，
 * 其值等于一个整数自乘的积。例如，1、4、9 和 16 都是完全平方数，而 3 和 11 不是。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int numSquares(int n)
	{
		vector<int> dp(n + 1, INT_MAX);
		dp[0] = 0;
		for (int i = 1; i * i <= n; i++)
		{
			for (int j = i * i; j <= n; j++)
			{
				if (dp[j - i * i] != INT_MAX)
				{
					dp[j] = min(dp[j - i * i] + 1, dp[j]);
				}
			}
		}

		return dp[n];
	}
};

int main()
{
	Solution solution;

	{
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.numSquares(12) << endl;
	}
}
