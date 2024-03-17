/*
 * 美团笔试. 平衡矩阵
 *
 * 题目描述：给你一个 `n*n` 的矩阵，其中每个元素都是 0 或者 1。
 * 当且仅当一个矩形区域内 0 的数量恰好等于 1 的数量，则矩形区域就是完美的。
 * 请你返回 `n*n` 的矩阵中，有多少个完美矩形区域，`1<=i<=n`。
 * */

#include <iostream>
#include <vector>
using namespace std;

int main()
{
	int n;
	cin >> n;
	string temp;
	vector<string> grid(n);
	for (int i = 0; i < n; ++i)
	{
		cin >> grid[i];
	}

	vector<vector<int>> s(n + 1, vector<int>(n + 1, 0)); // 前缀和
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + (grid[i][j] == '1');
		}
	}

	for (int k = 1; k <= n; ++k)
	{
		int count = 0;
		for (int i = 0; i <= n - k; ++i)
		{
			for (int j = 0; j <= n - k; ++j)
			{
				int sum = s[i + k][j + k] - s[i][j + k] - s[i + k][j] + s[i][j];
				if (sum * 2 == k * k) ++count;
			}
		}
		cout << count << endl;
	}

	return 0;
}
