/*
 * 121. 买卖股票的最佳时机		url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock/
 *
 * 题目描述：给定一个数组 prices ，它的第 i 个元素 prices[i] 表示一支给定股票第 i 天的价格。
 * 你只能选择 某一天 买入这只股票，并选择在 未来的某一个不同的日子 卖出该股票。设计一个算法来计算你所能获取的最大利润。
 * 返回你可以从这笔交易中获取的最大利润。如果你不能获取任何利润，返回 0 。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 贪心算法
class Solution
{
 public:
	int maxProfit(vector<int>& prices)
	{
		int low = INT_MAX;
		int result = 0;
		for (int i = 0; i < prices.size(); i++)
		{
			low = min(low, prices[i]);  // 取最左最小价格
			result = max(result, prices[i] - low); // 直接取最大区间利润
		}
		return result;
	}
};

// 动态规划 版本一
class Solution2
{
 public:
	int maxProfit(vector<int>& prices)
	{
		int len = prices.size();
		if (len == 0) return 0;
		vector<vector<int>> dp(len, vector<int>(2));
		dp[0][0] -= prices[0];
		dp[0][1] = 0;
		for (int i = 1; i < len; i++)
		{
			dp[i][0] = max(dp[i - 1][0], -prices[i]);
			dp[i][1] = max(dp[i - 1][1], prices[i] + dp[i - 1][0]);
		}
		return dp[len - 1][1];
	}
};

// 动态规划 版本二
class Solution3
{
 public:
	int maxProfit(vector<int>& prices)
	{
		int len = prices.size();
		vector<vector<int>> dp(2, vector<int>(2)); // 注意这里只开辟了一个2 * 2大小的二维数组
		dp[0][0] -= prices[0];
		dp[0][1] = 0;
		for (int i = 1; i < len; i++)
		{
			dp[i % 2][0] = max(dp[(i - 1) % 2][0], -prices[i]);
			dp[i % 2][1] = max(dp[(i - 1) % 2][1], prices[i] + dp[(i - 1) % 2][0]);
		}
		return dp[(len - 1) % 2][1];
	}
};

int main()
{
	Solution3 solution;
	vector<int> nums;

	{
		nums = { 7, 1, 5, 3, 6, 4 };
		cout << "exp1 (5): " << endl;
		cout << "result: " << solution.maxProfit(nums) << endl;
	}
}
