/*
 * 70. 爬楼梯	url: https://leetcode.cn/problems/climbing-stairs/
 *
 * 题目描述：假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
 * 每次你可以爬 1 或 2 个台阶。你有多少种不同的方法可以爬到楼顶呢？
 * */

#include <iostream>
#include <cmath>
#include <vector>
using namespace std;

class Solution
{
 public:
	int climbStairs(int n)
	{
		if (n <= 1) return n;

		vector<int> dp(n + 1);
		dp[1] = 1;
		dp[2] = 2;
		for (int i = 3; i <= n; i++)
		{
			dp[i] = dp[i - 1] + dp[i - 2];
		}

		return dp[n];
	}
};

int main()
{
	Solution solution;

	{
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.climbStairs(3) << endl;
	}
}
