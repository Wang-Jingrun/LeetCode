/*
 * 417. 太平洋大西洋水流问题	url: https://leetcode.cn/problems/pacific-atlantic-water-flow/
 *
 * 题目描述：有一个 m × n 的矩形岛屿，与 太平洋 和 大西洋 相邻。 “太平洋” 处于大陆
 * 的左边界和上边界，而 “大西洋” 处于大陆的右边界和下边界。
 *
 * 这个岛被分割成一个由若干方形单元格组成的网格。给定一个 m x n 的整数矩阵 heights ，
 * heights[r][c] 表示坐标 (r, c) 上单元格 高于海平面的高度 。
 *
 * 岛上雨水较多，如果相邻单元格的高度 小于或等于 当前单元格的高度，雨水可以直接向北、
 * 南、东、西流向相邻单元格。水可以从海洋附近的任何单元格流入海洋。
 *
 * 返回网格坐标 result 的 2D 列表 ，其中 result[i] = [ri, ci] 表示雨水从单元格
 * (ri, ci) 流动 既可流向太平洋也可流向大西洋
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class Solution
{
 private:
	const int direction[4][2] = { -1, 0, 1, 0, 0, -1, 0, 1 };

	// 深度搜索
	void dfs(vector<vector<int>>& heights, vector<vector<bool>>& visited, int x, int y)
	{
		if (visited[x][y]) return;
		visited[x][y] = true;

		for (int i = 0; i < 4; i++)
		{
			int next_x = x + direction[i][0];
			int next_y = y + direction[i][1];
			if (next_x < 0 || next_x >= heights.size() || next_y < 0 || next_y >= heights[0].size()) continue; // 越界
			if (heights[x][y] > heights[next_x][next_y]) continue; // 高度不合适

			dfs(heights, visited, next_x, next_y);
		}
	}

 public:
	vector<vector<int>> pacificAtlantic(vector<vector<int>>& heights)
	{
		vector<vector<int>> result;
		int n = heights.size();
		int m = heights[0].size(); // 这里不用担心空指针，题目要求说了长宽都大于1

		// 记录从太平洋边出发，可以遍历的节点
		vector<vector<bool>> pacific(heights.size(), vector<bool>(heights[0].size(), false));
		// 记录从大西洋出发，可以遍历的节点
		vector<vector<bool>> atlantic(heights.size(), vector<bool>(heights[0].size(), 0));

		// 从最上最下行的节点出发，向高处遍历
		for (int i = 0; i < n; i++)
		{
			 dfs(heights, pacific, i, 0); // 遍历最左列，接触太平洋
			 dfs(heights, atlantic, i, m - 1); // 遍历最右列，接触大西
		}

		// 从最左最右列的节点出发，向高处遍历
		for (int j = 0; j < m; j++)
		{
			dfs(heights, pacific, 0, j); // 遍历最上行，接触太平洋
			dfs(heights, atlantic, n - 1, j); // 遍历最下行，接触大西洋
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				// 如果这个节点，从太平洋和大西洋出发都遍历过，就是结果
				if (pacific[i][j] && atlantic[i][j]) result.push_back({ i, j });
			}
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> heights;

	{
		heights = {{ 1, 2, 2, 3, 5 },
				   { 3, 2, 3, 4, 4 },
				   { 2, 4, 5, 3, 1 },
				   { 6, 7, 1, 4, 5 },
				   { 5, 1, 1, 2, 4 }};
		cout << "exp1 ([[0,4],[1,3],[1,4],[2,2],[3,0],[3,1],[4,0]): " << endl;
		cout << "result: ";
		auto result = solution.pacificAtlantic(heights);
		for (auto& nums : result)
		{
			cout << "[ ";
			for (auto num : nums)
			{
				cout << num << " ";
			}
			cout << "]";
		}
		cout << "]";
	}
}
