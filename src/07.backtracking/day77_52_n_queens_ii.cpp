/*
 * 52. N 皇后 II		url: https://leetcode.cn/problems/n-queens-ii/
 *
 * 题目描述：n 皇后问题 研究的是如何将 n 个皇后放置在 n × n 的棋盘上，并且使皇后彼此之间不能相互攻击。
 * 给你一个整数 n ，返回 n 皇后问题 不同的解决方案的数量。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 private:
	int count = 0;
	void backtracking(int n, int row, vector<string>& chessboard)
	{
		if (row == n)
		{
			++count;
			return;
		}

		for (int col = 0; col < n; ++col)
		{
			if (isValid(row, col, chessboard, n))
			{
				chessboard[row][col] = 'Q';
				backtracking(n, row + 1, chessboard);
				chessboard[row][col] = '.';
			}
		}
	}

	bool isValid(int row, int col, vector<string>& chessboard, int n)
	{
		// 检查列
		for (int i = 0; i < row; ++i)
		{
			if (chessboard[i][col] == 'Q') return false;
		}

		// 检查 45°
		for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; --i, --j)
		{
			if (chessboard[i][j] == 'Q') return false;
		}

		// 检查 135°
		for (int i = row - 1, j = col + 1; i >= 0 && j < n; --i, ++j)
		{
			if (chessboard[i][j] == 'Q') return false;
		}

		return true;
	}

 public:
	int totalNQueens(int n)
	{
		count = 0;
		vector<string> chessboard(n, string(n, '.'));
		backtracking(n, 0, chessboard);
		return count;
	}
};

int main()
{

	Solution solution;

	{
		cout << R"(exp1 (2): )" << endl;
		cout << "result: " << solution.totalNQueens(4) << endl;
	}

	return 0;
}