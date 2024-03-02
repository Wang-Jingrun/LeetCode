/*
 * 130. 被围绕的区域	url: https://leetcode.cn/problems/surrounded-regions/
 *
 * 题目描述：给你一个 m x n 的矩阵 board ，由若干字符 'X' 和 'O' ，
 * 找到所有被 'X' 围绕的区域，并将这些区域里所有的 'O' 用 'X' 填充。
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

class Solution
{
 private:
	// 四个方向
	vector<vector<int>> direction = {{ 0, 1 }, { 0, -1 }, { 1, 0 }, { -1, 0 }};

	void dfs(vector<vector<char>>& board, int x, int y)
	{
		if (board[x][y] != 'O') return;

		board[x][y] = 'Y';

		for (int i = 0; i < direction.size(); i++)
		{
			int next_x = x + direction[i][0];
			int next_y = y + direction[i][1];
			if (next_x < 0 || next_x >= board.size() || next_y < 0 || next_y >= board[0].size()) continue; // 发生越界

			dfs(board, next_x, next_y);
		}
	}

 public:
	void solve(vector<vector<char>>& board)
	{
		int n = board.size(), m = board[0].size();

		// 从 最左侧 和 最右侧 遍历，使用 Y 标记需要还原的位置
		for (int i = 0; i < n; i++)
		{
			if (board[i][0] == 'O') dfs(board, i, 0);
			if (board[i][m - 1] == 'O') dfs(board, i, m - 1);
		}

		// 从 最上边 和 最下边 遍历，使用 Y 标记需要还原的位置
		for (int j = 0; j < m; j++)
		{
			if (board[0][j] == 'O') dfs(board, 0, j);
			if (board[n - 1][j] == 'O') dfs(board, n - 1, j);
		}

		for (int i = 0; i < n; i++)
		{
			for (int j = 0; j < m; j++)
			{
				if (board[i][j] == 'O') board[i][j] = 'X';
				if (board[i][j] == 'Y') board[i][j] = 'O';	// 还原
			}
		}
	}
};

int main()
{
	Solution solution;
	vector<vector<char>> board;

	{
		board = {{ 'X', 'X', 'X', 'X' },
				 { 'X', 'O', 'O', 'X' },
				 { 'X', 'X', 'O', 'X' },
				 { 'X', 'O', 'X', 'X' }};
		cout << "exp1 : " << endl;
		cout << "input: ";
		for (auto& chs : board)
		{
			cout << "[ ";
			for (auto ch : chs)
			{
				cout << ch << " ";
			}
			cout << "]";
		}
		cout << "]" << endl;

		cout << "output: ";
		solution.solve(board);
		for (auto& chs : board)
		{
			cout << "[ ";
			for (auto ch : chs)
			{
				cout << ch << " ";
			}
			cout << "]";
		}
		cout << "]";
	}
}
