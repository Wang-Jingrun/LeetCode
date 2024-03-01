/*
 * 200. 岛屿数量		url: https://leetcode.cn/problems/number-of-islands/
 *
 * 题目描述：给你一个由 '1'（陆地）和 '0'（水）组成的的二维网格，请你计算网格中岛屿的数量。
 * 岛屿总是被水包围，并且每座岛屿只能由水平方向和/或竖直方向上相邻的陆地连接形成。
 * 此外，你可以假设该网格的四条边均被水包围。
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

// 深度优先搜索版本
class Solution
{
 private:
	// 四个方向
	const vector<vector<int>> direction = {{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 }};

	void dfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y)
	{
		if (visited[x][y] || grid[x][y] == '0') return; // 终止条件：访问过的节点 或者 遇到海水
		visited[x][y] = true; // 标记访问过
		for (int i = 0; i < direction.size(); i++)
		{
			visited[x][y] = true;
			int next_x = x + direction[i][0];
			int next_y = y + direction[i][1];
			if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size()) continue; // 越界
			dfs(grid, visited, next_x, next_y);
		}
	}

 public:
	int numIslands(vector<vector<char>>& grid)
	{
		int result = 0;
		// 记录遍历过的节点
		vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));
		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				if (grid[i][j] == '1' && !visited[i][j])
				{
					dfs(grid, visited, i, j);
					result++;
				}
			}
		}
		return result;
	}
};

// 广度度优先搜索版本
class Solution2
{
 private:
	// 四个方向
	const vector<vector<int>> direction = {{ -1, 0 }, { 1, 0 }, { 0, -1 }, { 0, 1 }};

	void bfs(vector<vector<char>>& grid, vector<vector<bool>>& visited, int x, int y)
	{
		queue<pair<int, int>> qu;
		qu.push({ x, y });
		visited[x][y] = true; // 只要加入队列，立刻标记

		while (!qu.empty())
		{
			auto cur = qu.front();
			qu.pop();

			for (int i = 0; i < direction.size(); i++)
			{
				int next_x = cur.first + direction[i][0];
				int next_y = cur.second + direction[i][1];
				if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size()) continue;

				if (!visited[next_x][next_y] && grid[next_x][next_y] == '1')
				{
					visited[next_x][next_y] = true; // 只要加入队列，立刻标记
					qu.push({ next_x, next_y });
				}
			}
		}
	}

 public:
	int numIslands(vector<vector<char>>& grid)
	{
		int result = 0;
		vector<vector<bool>> visited(grid.size(), vector<bool>(grid[0].size(), false));

		for (int i = 0; i < grid.size(); i++)
		{
			for (int j = 0; j < grid[i].size(); j++)
			{
				if (!visited[i][j] && grid[i][j] == '1')
				{
					bfs(grid, visited, i, j); // 将与其链接的陆地都标记上 true
					result++; // 遇到没访问过的陆地，+1
				}
			}
		}
		return result;
	}
};

int main()
{
	Solution2 solution;
	vector<vector<char>> grid;

	{
		grid = {
			{ '1', '1', '0', '0', '0' },
			{ '1', '1', '0', '0', '0' },
			{ '0', '0', '1', '0', '0' },
			{ '0', '0', '0', '1', '1' }
		};
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.numIslands(grid) << endl;
	}
}



