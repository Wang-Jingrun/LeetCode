/*
 * 1020. 飞地的数量	url: https://leetcode.cn/problems/number-of-enclaves/
 *
 * 题目描述：给你一个大小为 m x n 的二进制矩阵 grid ，其中 0 表示一个海洋单元格、1 表示一个陆地单元格。
 * 一次 移动 是指从一个陆地单元格走到另一个相邻（上、下、左、右）的陆地单元格或跨过 grid 的边界。
 * 返回网格中 无法 在任意次数的移动中离开网格边界的陆地单元格的数量。
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// 深度搜索 能提交通过，但是耗时很高
class Solution
{
 private:
	// 四个方向
	vector<vector<int>> direction = {{ 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }};
	bool is_enclaves = false;
	int num_island = 0;

	void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y)
	{
		if (visited[x][y] || grid[x][y] == 0) return;

		visited[x][y] = true;
		num_island++;

		for (int i = 0; i < direction.size(); i++)
		{
			int next_x = x + direction[i][0];
			int next_y = y + direction[i][1];

			// 发生越界，则该岛屿为飞岛，改变标志位
			if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size())
			{
				is_enclaves = true;
				continue;
			}

			dfs(grid, visited, next_x, next_y);
		}
	}

 public:
	int numEnclaves(vector<vector<int>>& grid)
	{
		int result = 0;
		vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[0].size(); j++)
			{
				if (!visited[i][j] && grid[i][j] == 1)
				{
					is_enclaves = false;
					num_island = 0;
					dfs(grid, visited, i, j);

					if (!is_enclaves) result += num_island;
				}
			}
		}
		return result;
	}
};

// 深度搜索	参考解法
class Solution2
{
 private:
	// 四个方向
	vector<vector<int>> direction = {{ 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }};
	int num_island = 0;

	void dfs(vector<vector<int>>& grid, int x, int y)
	{
		if (grid[x][y] == 0) return;

		grid[x][y] = 0;
		num_island++;

		for (int i = 0; i < direction.size(); i++)
		{
			int next_x = x + direction[i][0];
			int next_y = y + direction[i][1];
			if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size()) continue; // 发生越界

			dfs(grid, next_x, next_y);
		}
	}

 public:
	int numEnclaves(vector<vector<int>>& grid)
	{
		int n = grid.size(), m = grid[0].size();

		// 从 最左侧 和 最右侧 遍历
		for (int i = 0; i < n; i++)
		{
			if (grid[i][0] == 1) dfs(grid, i, 0);
			if (grid[i][m - 1] == 1) dfs(grid, i, m - 1);
		}

		// 从 最上边 和 最下边 遍历
		for (int j = 0; j < m; j++)
		{
			if (grid[0][j] == 1) dfs(grid, 0, j);
			if (grid[n - 1][j] == 1) dfs(grid, n - 1, j);
		}

		num_island = 0;
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[0].size(); j++)
			{
				if (grid[i][j] == 1) dfs(grid, i, j);
			}
		}
		return num_island;
	}
};

// 广度搜索	参考解法
class Solution3
{
 private:
	// 四个方向
	vector<vector<int>> direction = {{ 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }};
	int num_island = 0;

	void bfs(vector<vector<int>>& grid, int x, int y)
	{
		queue<pair<int, int>> que;
		grid[x][y] = 0;
		num_island++;
		que.push({ x, y });

		while (!que.empty())
		{
			auto cur = que.front();
			que.pop();

			for (int i = 0; i < direction.size(); i++)
			{
				int next_x = cur.first + direction[i][0];
				int next_y = cur.second + direction[i][1];
				if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size()) continue; // 发生越界

				if (grid[next_x][next_y] == 1)
				{
					grid[next_x][next_y] = 0;
					num_island++;
					que.push({ next_x, next_y });
				}
			}
		}
	}

 public:
	int numEnclaves(vector<vector<int>>& grid)
	{
		int n = grid.size(), m = grid[0].size();

		// 从 最左侧 和 最右侧 遍历
		for (int i = 0; i < n; i++)
		{
			if (grid[i][0] == 1) bfs(grid, i, 0);
			if (grid[i][m - 1] == 1) bfs(grid, i, m - 1);
		}

		// 从 最上边 和 最下边 遍历
		for (int j = 0; j < m; j++)
		{
			if (grid[0][j] == 1) bfs(grid, 0, j);
			if (grid[n - 1][j] == 1) bfs(grid, n - 1, j);
		}

		num_island = 0;
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[0].size(); j++)
			{
				if (grid[i][j] == 1) bfs(grid, i, j);
			}
		}
		return num_island;
	}
};

int main()
{
	Solution3 solution;
	vector<vector<int>> grid;

	{
		grid = {{ 0, 0, 0, 0 },
				{ 1, 0, 1, 0 },
				{ 0, 1, 1, 0 },
				{ 0, 0, 0, 0 }};
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.numEnclaves(grid) << endl;
	}
}
