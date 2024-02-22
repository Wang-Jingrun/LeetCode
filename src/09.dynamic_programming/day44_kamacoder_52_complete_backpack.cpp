#include <iostream>
#include <vector>
using namespace std;

// 先遍历背包，再遍历物品
void test_CompletePack(vector<int> weight, vector<int> value, int bagWeight)
{
	vector<int> dp(bagWeight + 1, 0);

	for (int j = 0; j <= bagWeight; j++)
	{ // 遍历背包容量
		for (int i = 0; i < weight.size(); i++)
		{ // 遍历物品
			if (j - weight[i] >= 0) dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
		}
	}
	cout << dp[bagWeight] << endl;
}

int main()
{
	int N, V;
	cin >> N >> V;
	vector<int> weight;
	vector<int> value;
	for (int i = 0; i < N; i++)
	{
		int w;
		int v;
		cin >> w >> v;
		weight.push_back(w);
		value.push_back(v);
	}
	test_CompletePack(weight, value, V);
	return 0;
}