/*
 * 474. 一和零		url: https://leetcode.cn/problems/ones-and-zeroes/
 *
 * 题目描述：给你一个二进制字符串数组 strs 和两个整数 m 和 n 。
 * 请你找出并返回 strs 的最大子集的长度，该子集中 最多 有 m 个 0 和 n 个 1 。
 * 如果 x 的所有元素也是 y 的元素，集合 x 是集合 y 的 子集 。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int findMaxForm(vector<string>& strs, int m, int n)
	{
		vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0)); // 默认初始化0
		for (const string& str : strs)
		{ // 遍历物品
			int oneNum = 0, zeroNum = 0;
			for (char c : str)
			{
				if (c == '0') zeroNum++;
				else oneNum++;
			}
			for (int i = m; i >= zeroNum; i--)
			{ // 遍历背包容量且从后向前遍历！
				for (int j = n; j >= oneNum; j--)
				{
					dp[i][j] = max(dp[i][j], dp[i - zeroNum][j - oneNum] + 1);
				}
			}
		}
		return dp[m][n];
	}
};

int main()
{
	Solution solution;
	vector<string> strs;

	{
		strs = { "10", "0001", "111001", "1", "0" };
		cout << "exp1 (4): " << endl;
		cout << "result: " << solution.findMaxForm(strs, 5, 3) << endl;
	}
}
