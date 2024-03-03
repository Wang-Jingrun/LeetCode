/*
 * 827.最大人工岛		url: https://leetcode.cn/problems/making-a-large-island/
 *
 * 题目描述：给你一个大小为 n x n 二进制矩阵 grid 。最多 只能将一格 0 变成 1 。
 *
 * 返回执行此操作后，grid 中最大的岛屿面积是多少？
 *
 * 岛屿 由一组上、下、左、右四个方向相连的 1 形成。
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
#include <unordered_set>
#include <queue>
using namespace std;

class Solution
{
 private:
	const int direction[4][2] = { 1, 0, -1, 0, 0, 1, 0, -1 };
	int area = 0;

	void dfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y, int id)
	{
		if (grid[x][y] == 0 || visited[x][y]) return;

		visited[x][y] = true;
		grid[x][y] = id;
		area++;

		for (int i = 0; i < 4; i++)
		{
			int next_x = x + direction[i][0];
			int next_y = y + direction[i][1];
			if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size()) continue; // 越界

			dfs(grid, visited, next_x, next_y, id);
		}
	}

	void bfs(vector<vector<int>>& grid, vector<vector<bool>>& visited, int x, int y, int id)
	{
		queue<pair<int, int>> qu;
		qu.push({ x, y });
		grid[x][y] = id;
		visited[x][y] = true;
		area++;

		while (!qu.empty())
		{
			auto cur = qu.front();
			qu.pop();

			for (int i = 0; i < 4; i++)
			{
				int next_x = cur.first + direction[i][0];
				int next_y = cur.second + direction[i][1];
				if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size()) continue;

				if (!visited[next_x][next_y] && grid[next_x][next_y] == 1)
				{
					qu.push({ next_x, next_y });
					grid[next_x][next_y] = id;
					visited[next_x][next_y] = true;
					area++;
				}
			}
		}
	}

 public:
	int largestIsland(vector<vector<int>>& grid)
	{
		int n = grid.size(), m = grid[0].size();
		unordered_map<int, int> id2area;
		vector<vector<bool>> visited(n, vector<bool>(m, false));
		int result = 0;

		int id = 2; // 岛屿编号，从 2 开始
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (grid[i][j] == 1 && !visited[i][j])
				{
					area = 0;
					// dfs(grid, visited, i, j, id);
					bfs(grid, visited, i, j, id);
					id2area[id] = area;
					id++;
					result = max(result, area);
				}
			}
		}

		unordered_set<int> visitedGrid; // 标记访问过的岛屿
		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (grid[i][j] == 0)
				{
					int count = 1; // 记录连接之后的岛屿数量
					visitedGrid.clear(); // 每次使用时，清空
					for (auto& dir : direction)
					{
						int next_x = i + dir[0];
						int next_y = j + dir[1];
						if (next_x < 0 || next_x >= grid.size() || next_y < 0 || next_y >= grid[0].size())
							continue; // 越界

						if (visitedGrid.count(grid[next_x][next_y])) continue; // 添加过的岛屿不要重复添加
						count += id2area[grid[next_x][next_y]];
						visitedGrid.insert(grid[next_x][next_y]); // 标记该岛屿已经添加过
					}
					result = max(result, count);
				}
			}
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> grid;

	{
		grid = {{ 1, 0 },
				{ 0, 1 }};
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.largestIsland(grid);
	}
}
