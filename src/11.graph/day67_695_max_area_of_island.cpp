/*
 * 695. 岛屿的最大面积		url: https://leetcode.cn/problems/max-area-of-island/
 *
 * 题目描述：给你一个大小为 m x n 的二进制矩阵 grid 。
 *
 * 岛屿 是由一些相邻的 1 (代表土地) 构成的组合，这里的「相邻」要求
 * 两个 1 必须在 水平或者竖直的四个方向上 相邻。你可以假设 grid 的
 * 四个边缘都被 0（代表水）包围着。
 *
 * 岛屿的面积是岛上值为 1 的单元格的数目。
 *
 * 计算并返回 grid 中最大的岛屿面积。如果没有岛屿，则返回面积为 0 。
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// 深搜版本
class Solution
{
 private:
	int num_island = 0; // 记录每次深搜的岛屿面积
	// 四个方向
	const vector<vector<int>> direction = {{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 }};

	void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y)
	{
		if (visited[x][y] || grid[x][y] == 0) return;

		visited[x][y] = true;
		num_island++;

		for (int i = 0; i < direction.size(); i++)
		{
			int next_x = x + direction[i][0];
			int next_y = y + direction[i][1];

			if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size()) continue; // 越界

			dfs(grid, visited, next_x, next_y);
		}
	}

 public:
	int maxAreaOfIsland(vector<vector<int>>& grid)
	{
		int result = 0; // 记录结果
		vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[0].size(); j++)
			{
				if (!visited[i][j] && grid[i][j] == 1)
				{
					num_island = 0;
					dfs(grid, visited, i, j);
					result = max(result, num_island);
				}
			}
		}

		return result;
	}
};

// 广搜版本
class Solution2
{
 private:
	// 四个方向
	const vector<vector<int>> direction = {{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 }};

	int bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y)
	{
		int area = 0;
		queue<pair<int, int>> que;
		que.push({ x, y });
		visited[x][y] = true;
		area++;

		while (!que.empty())
		{
			auto cur = que.front();
			que.pop();

			for (int i = 0; i < direction.size(); i++)
			{
				int next_x = cur.first + direction[i][0];
				int next_y = cur.second + direction[i][1];

				if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size()) continue; // 越界

				if (!visited[next_x][next_y] && grid[next_x][next_y])
				{
					visited[next_x][next_y] = true;
					area++;
					que.push({ next_x, next_y });
				}
			}
		}

		return area;
	}

 public:
	int maxAreaOfIsland(vector<vector<int>>& grid)
	{
		int result = 0; // 记录结果
		vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[0].size(); j++)
			{
				if (!visited[i][j] && grid[i][j] == 1)
					result = max(result, bfs(grid, visited, i, j));
			}
		}

		return result;
	}
};

int main()
{
	Solution2 solution;
	vector<vector<int>> grid;

	{
		grid = {{ 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0 },
				{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 0, 1, 0, 0 },
				{ 0, 1, 0, 0, 1, 1, 0, 0, 1, 1, 1, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0 },
				{ 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0 }};
		cout << "exp1 (6): " << endl;
		cout << "result: " << solution.maxAreaOfIsland(grid) << endl;
	}
}
