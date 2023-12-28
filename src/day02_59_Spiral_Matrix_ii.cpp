/*
 * 59. 螺旋矩阵 II	url: https://leetcode.cn/problems/spiral-matrix-ii/
 *
 * 题目描述：给你一个正整数 n ，生成一个包含 1 到 n2 所有元素，
 * 且元素按顺时针顺序螺旋排列的 n x n 正方形矩阵 matrix 。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 public:
	vector<vector<int>> generateMatrix(int n)
	{
		vector<vector<int>> ret(n, vector<int>(n, 0));
		int loop = n / 2; // 需要转的圈数
		int start_x = 0, start_y = 0;
		int offset = 1;    // 偏移值，每转一圈加一
		int num = 1;

		while (loop--)
		{
			// 第一条边：从左到右，不包含最后一个值
			for (int j = start_x; j < n - offset; ++j)
				ret[start_x][j] = num++;

			// 第二条边：从上到下，不包含最后一个值
			for (int i = start_x; i < n - offset; ++i)
				ret[i][n - offset] = num++;

			// 第三边：从右到左，不包含最后一个值
			for (int j = n - offset; j > start_x; --j)
				ret[n - offset][j] = num++;

			// 第四边：从下到上，不包含最后一个值i
			for (int i = n - offset; i > start_x; --i)
				ret[i][start_y] = num++;

			// 下一圈开始的时候，起始位置要各自加 1
			start_x++;
			start_y++;

			// offset 控制每一圈里每一条边遍历的长度
			offset++;
		}

		if (n % 2 == 1)
			ret[n / 2][n / 2] = num;

		return ret;
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> ret;

	cout << "exp1: " << endl;
	ret = solution.generateMatrix(1);
	for (auto& it : ret)
	{
		for (auto& mit : it)
		{
			cout << mit << " ";
		}
		cout << endl;
	}

	cout << "exp2: " << endl;
	ret = solution.generateMatrix(4);
	for (auto& it : ret)
	{
		for (auto& mit : it)
		{
			cout << mit << " ";
		}
		cout << endl;
	}
}