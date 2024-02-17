/*
 * 343. 整数拆分		url: https://leetcode.cn/problems/integer-break/
 *
 * 题目描述：给定一个正整数 n ，将其拆分为 k 个 正整数 的和（ k >= 2 ），并使这些整数的乘积最大化。
 * 返回 你可以获得的最大乘积 。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;


class Solution
{
 public:
	int integerBreak(int n)
	{
		vector<int> dp(n + 1);
		for (int i = 2; i <= n; i++)
		{
			int m = n % i;
			int num = n / i;
			dp[i] = pow(num, i - m) * pow(num + 1, m);
		}

		// 取最大的dp数组值
		int result = INT_MIN;
		for (auto num : dp)
		{
			if (num > result) result = num;
		}

		return result;
	}
};


class Solution2
{
 public:
	int integerBreak(int n)
	{
		vector<int> dp(n + 1);
		dp[2] = 1;
		for (int i = 3; i <= n; i++)
		{
			for (int j = 1; j <= i / 2; j++)
			{
				dp[i] = max(dp[i], max((i - j) * j, dp[i - j] * j));
			}
		}
		return dp[n];
	}
};


int main()
{
	Solution2 solution;

	{
		cout << "exp1 (36): " << endl;
		cout << "result: " << solution.integerBreak(10) << endl;
	}
}
