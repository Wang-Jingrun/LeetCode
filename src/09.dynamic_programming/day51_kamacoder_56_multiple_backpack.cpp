/*
 * 卡码网：56. 携带矿石资源		url: https://kamacoder.com/problempage.php?pid=1066
 *
 * 题目描述：你是一名宇航员，即将前往一个遥远的行星。在这个行星上，
 * 有许多不同类型的矿石资源，每种矿石都有不同的重要性和价值。你需要
 * 选择哪些矿石带回地球，但你的宇航舱有一定的容量限制。
 * 给定一个宇航舱，最大容量为 C。现在有 N 种不同类型的矿石，每种矿
 * 石有一个重量 w[i]，一个价值 v[i]，以及最多 k[i] 个可用。不同
 * 类型的矿石在地球上的市场价值不同。你需要计算如何在不超过宇航舱容
 * 量的情况下，最大化你所能获取的总价值。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 先遍历背包，再遍历物品
void multipleBackpack(int bagWeight, vector<int>& weight, vector<int>& value, vector<int>& nums)
{
	vector<int> dp(bagWeight + 1, 0);

	// 遍历物品
	for (int i = 0; i < weight.size(); i++)
	{
		// 遍历背包
		for (int j = bagWeight; j >= weight[i]; j--)
		{
			// 以上为01背包，然后加一个遍历个数
			for (int k = 1; k <= nums[i] && (j - k * weight[i] >= 0); k++)
			{
				dp[j] = max(dp[j], dp[j - k * weight[i]] + k * value[i]);
			}
		}
	}

	cout << dp[bagWeight] << endl;
}

int main()
{
	int bagWeight, n;
	cin >> bagWeight >> n;
	vector<int> weight(n, 0);
	vector<int> value(n, 0);
	vector<int> nums(n, 0);
	for (int i = 0; i < n; i++) cin >> weight[i];
	for (int i = 0; i < n; i++) cin >> value[i];
	for (int i = 0; i < n; i++) cin >> nums[i];
	multipleBackpack(bagWeight, weight, value, nums);
	return 0;
}