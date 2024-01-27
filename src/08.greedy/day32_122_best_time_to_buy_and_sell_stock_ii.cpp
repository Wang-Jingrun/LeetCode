/*
 * 122. 买卖股票的最佳时机 II		url: https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-ii/
 *
 * 题目描述：给你一个整数数组 prices ，其中 prices[i] 表示某支股票第 i 天的价格。
 * 在每一天，你可以决定是否购买和/或出售股票。你在任何时候 最多 只能持有 一股 股票。
 * 你也可以先购买，然后在 同一天 出售。返回 你能获得的 最大 利润 。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	int maxProfit(vector<int>& prices)
	{

		int price = 0;
		int profit = 0;

		for (int i = 0; i < prices.size() - 1; i++)
		{
			// 后一天比今天高，买入点
			if (prices[i] < prices[i + 1])
			{
				// 买入
				price = prices[i];
				i++;

				// 等到下降的那一天，寻找卖的时机
				while (i < prices.size() - 1 && prices[i] < prices[i + 1])
				{
					i++;
				}

				// 记录一次买卖的利润
				profit += prices[i] - price;
			}
		}

		return profit;
	}
};

int main()
{
	Solution solution;
	vector<int> prices;

	cout << "exp1 (7): ";
	prices = { 7, 1, 5, 3, 6, 4 };
	cout << solution.maxProfit(prices) << endl;

	cout << "exp2 (4): ";
	prices = { 1, 2, 3, 4, 5 };
	cout << solution.maxProfit(prices) << endl;

	cout << "exp3 (0): ";
	prices = { 7, 6, 4, 3, 1 };
	cout << solution.maxProfit(prices) << endl;

}
