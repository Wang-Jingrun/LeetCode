/*
 * 63. 不同路径 II		url: https://leetcode.cn/problems/unique-paths-ii/
 *
 * 题目描述：一个机器人位于一个 m x n 网格的左上角 （起始点在下图中标记为 “Start” ）。
 * 机器人每次只能向下或者向右移动一步。机器人试图达到网格的右下角（在下图中标记为 “Finish”）。
 * 现在考虑网格中有障碍物。那么从左上角到右下角将会有多少条不同的路径？
 * 网格中的障碍物和空位置分别用 1 和 0 来表示。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 public:
	int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid)
	{
		int m = obstacleGrid.size();
		int n = obstacleGrid[0].size();

		vector<vector<int>> dp(m + 1, vector<int>(n + 1));
		dp[0][1] = 1; // 或者 dp[1][0] = 1; 作为初始化

		for (int i = 1; i <= m; i++)
		{
			for (int j = 1; j <= n; j++)
			{
				// 没有障碍
				if (obstacleGrid[i - 1][j - 1] != 1)
					dp[i][j] = dp[i - 1][j] + dp[i][j - 1];
					// 有障碍
				else
					dp[i][j] = 0;
			}
		}

		return dp[m][n];
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> obstacleGrid;

	{
		obstacleGrid = {{ 0, 0, 0 }, { 0, 1, 0 }, { 0, 0, 0 }};
		cout << "exp1 (2): " << endl;
		cout << "result: " << solution.uniquePathsWithObstacles(obstacleGrid) << endl;
	}
}
