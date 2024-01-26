/*
 * 93. 复原IP地址		url: https://leetcode.cn/problems/restore-ip-addresses/
 *
 * 题目描述：有效 IP 地址 正好由四个整数（每个整数位于 0 到 255 之间组成，
 * 且不能含有前导 0），整数之间用 '.' 分隔。
 * 例如：'0.1.2.201' 和 '192.168.1.1' 是 有效 IP 地址，但是 '0.011.255.245'、
 * '192.168.1.312' 和 '192.168@1.1' 是 无效 IP 地址。
 * 给定一个只包含数字的字符串 s ，用以表示一个 IP 地址，返回所有可能的有效 IP 地址，
 * 这些地址可以通过在 s 中插入 '.' 来形成。你 不能 重新排序或删除 s 中的任何数字。你可以按 任何 顺序返回答案。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution {
 private:
	bool backtracking(vector<vector<char>>& board) {
		for (int i = 0; i < board.size(); i++) {        // 遍历行
			for (int j = 0; j < board[0].size(); j++) { // 遍历列
				if (board[i][j] == '.') {
					for (char k = '1'; k <= '9'; k++) {     // (i, j) 这个位置放k是否合适
						if (isValid(i, j, k, board)) {
							board[i][j] = k;                // 放置k
							if (backtracking(board)) return true; // 如果找到合适一组立刻返回
							board[i][j] = '.';              // 回溯，撤销k
						}
					}
					return false;  // 9个数都试完了，都不行，那么就返回false
				}
			}
		}
		return true; // 遍历完没有返回false，说明找到了合适棋盘位置了
	}
	bool isValid(int row, int col, char val, vector<vector<char>>& board) {
		for (int i = 0; i < 9; i++) { // 判断行里是否重复
			if (board[row][i] == val) {
				return false;
			}
		}
		for (int j = 0; j < 9; j++) { // 判断列里是否重复
			if (board[j][col] == val) {
				return false;
			}
		}
		int startRow = (row / 3) * 3;
		int startCol = (col / 3) * 3;
		for (int i = startRow; i < startRow + 3; i++) { // 判断9方格里是否重复
			for (int j = startCol; j < startCol + 3; j++) {
				if (board[i][j] == val ) {
					return false;
				}
			}
		}
		return true;
	}
 public:
	void solveSudoku(vector<vector<char>>& board) {
		backtracking(board);
	}
};


int main()
{
	Solution solution;
	vector<vector<char>> input;

	{
		cout << "exp1:\n"
				"5 3 4 6 7 8 9 1 2\n"
				"6 7 2 1 9 5 3 4 8\n"
				"1 9 8 3 4 2 5 6 7\n"
				"8 5 9 7 6 1 4 2 3\n"
				"4 2 6 8 5 3 7 9 1\n"
				"7 1 3 9 2 4 8 5 6\n"
				"9 6 1 5 3 7 2 8 4\n"
				"2 8 7 4 1 9 6 3 5\n"
				"3 4 5 2 8 6 1 7 9\n" << endl;

		input = {{ '5', '3', '.', '.', '7', '.', '.', '.', '.' },
				 { '6', '.', '.', '1', '9', '5', '.', '.', '.' },
				 { '.', '9', '8', '.', '.', '.', '.', '6', '.' },
				 { '8', '.', '.', '.', '6', '.', '.', '.', '3' },
				 { '4', '.', '.', '8', '.', '3', '.', '.', '1' },
				 { '7', '.', '.', '.', '2', '.', '.', '.', '6' },
				 { '.', '6', '.', '.', '.', '.', '2', '8', '.' },
				 { '.', '.', '.', '4', '1', '9', '.', '.', '5' },
				 { '.', '.', '.', '.', '8', '.', '.', '7', '9' }};

		cout << "output: " << endl;
		solution.solveSudoku(input);

		for (const auto& row : input)
		{
			for (auto ch : row)
			{
				cout << ch << ' ';
			}
			cout << endl;
		}
	}

	cout << endl;

	return 0;
}