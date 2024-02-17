/*
 * 96. 不同的二叉搜索树		url: https://leetcode.cn/problems/unique-binary-search-trees/
 *
 * 题目描述：给你一个整数 n ，求恰由 n 个节点组成且节点值从 1 到 n 互不相同的
 * 二叉搜索树 有多少种？返回满足题意的二叉搜索树的种数。
 * */

#include <iostream>
#include <vector>
using namespace std;


class Solution
{
 public:
	int numTrees(int n)
	{
		vector<int> dp(n + 1);
		dp[0] = 1;
		for (int i = 1; i <= n; i++)
		{
			for (int j = 1; j <= i; j++)
			{
				dp[i] += dp[j - 1] * dp[i - j];
			}
		}
		return dp[n];
	}
};


int main()
{
	Solution solution;

	{
		cout << "exp1 (5): " << endl;
		cout << "result: " << solution.numTrees(3) << endl;
	}
}
