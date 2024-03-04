/*
 * 463. 岛屿的周长		url: https://leetcode.cn/problems/island-perimeter/
 *
 * 题目描述：给定一个 row x col 的二维网格地图 grid ，
 * 其中：grid[i][j] = 1 表示陆地， grid[i][j] = 0 表示水域。
 *
 * 网格中的格子 水平和垂直 方向相连（对角线方向不相连）。整个网格被
 * 水完全包围，但其中恰好有一个岛屿（或者说，一个或多个表示陆地的格
 * 子相连组成的岛屿）。
 *
 * 岛屿中没有“湖”（“湖” 指水域在岛屿内部且不和岛屿周围的水相连）。格
 * 子是边长为 1 的正方形。网格为长方形，且宽度和高度均不超过 100 。
 * 计算这个岛屿的周长。
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

// 深搜解法
class Solution
{
 private:
	int count = 0;
	const int direction[4][2] = { 1, 0, -1, 0, 0, 1, 0, -1 };

	void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y)
	{
		if (visited[x][y]) return;

		if (grid[x][y] == 0)
		{
			count++;
			return;
		}

		visited[x][y] = true;
		for (int i = 0; i < 4; i++)
		{
			int next_x = x + direction[i][0];
			int next_y = y + direction[i][1];

			if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size())
			{
				count++;
				continue;
			}

			dfs(grid, visited, next_x, next_y);
		}
	}

 public:
	int islandPerimeter(vector<vector<int>>& grid)
	{
		int n = grid.size(), m = grid[0].size();
		vector<vector<bool>> visited(n, vector<bool>(m, false));
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (grid[i][j] == 1)
				{
					count = 0;
					dfs(grid, visited, i, j);
					return count;
				}
			}
		}
		return 0;
	}
};

// 遇到一个陆地就遍历其四周的情况
class Solution2
{
 public:
	const int direction[4][2] = { 1, 0, -1, 0, 0, 1, 0, -1 };
	int islandPerimeter(vector<vector<int>>& grid)
	{
		int count = 0;
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[0].size(); j++)
			{
				if (grid[i][j] == 1)
				{
					// 遍历四个方向
					for (int k = 0; k < 4; k++)
					{
						int next_i = i + direction[k][0];
						int next_j = j + direction[k][1];

						// 越界或者为海水
						if (next_i < 0
							|| next_i >= grid.size()
							|| next_j < 0
							|| next_j >= grid[0].size()
							|| grid[next_i][next_j] == 0)
							count++;
					}
				}
			}
		}
		return count;
	}
};

// result = 岛屿数量 * 4 - cover * 2
class Solution3
{
 public:
	const int direction[4][2] = { 1, 0, -1, 0, 0, 1, 0, -1 };
	int islandPerimeter(vector<vector<int>>& grid)
	{
		int island = 0;    // 陆地数量
		int cover = 0; // 相邻陆地数量
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[0].size(); j++)
			{
				if (grid[i][j] == 1)
				{
					island++;
					if (i - 1 >= 0 && grid[i - 1][j] == 1) cover++; // 统计上边相邻陆地
					if (j - 1 >= 0 && grid[i][j - 1] == 1) cover++; // 统计左边相邻陆地
					// 为什么没统计下边和右边？ 因为避免重复计算
				}
			}
		}
		return island * 4 - cover * 2;
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> grid;

	{
		grid = {{ 0, 1, 0, 0 },
				{ 1, 1, 1, 0 },
				{ 0, 1, 0, 0 },
				{ 1, 1, 0, 0 }};
		cout << "exp1 (16): " << endl;
		cout << "result: " << solution.islandPerimeter(grid);
	}
}
