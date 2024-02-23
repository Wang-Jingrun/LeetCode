/*
 * 卡码网：57. 爬楼梯		url: https://kamacoder.com/problempage.php?pid=1067
 *
 * 题目描述：假设你正在爬楼梯。需要 n 阶你才能到达楼顶。
 * 每次你可以爬至多m (1 <= m < n)个台阶。你有多少种不同的方法可以爬到楼顶呢？
 * 注意：给定 n 是一个正整数。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 先遍历背包，再遍历物品
void climbingStairs(int m, int n)
{
	vector<int> dp(n + 1, 0);
	dp[0] = 1;

	// 遍历背包容量
	for (int i = 0; i <= n; i++)
	{
		// 遍历物品
		for (int j = 1; j <= m; j++)
		{
			if (i >= j)dp[i] += dp[i - j];
		}
	}
	cout << dp[n] << endl;
}

int main()
{
	int m, n;
	cin >> m >> n;
	climbingStairs(m, n);
	return 0;
}
