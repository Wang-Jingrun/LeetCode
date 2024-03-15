/*
 * 657. 机器人能否返回原点		url: https://leetcode.cn/problems/robot-return-to-origin/
 *
 * 题目描述：在二维平面上，有一个机器人从原点 (0, 0) 开始。给出它的移动顺序，
 * 判断这个机器人在完成移动后是否在 (0, 0) 处结束。
 *
 * 移动顺序由字符串 moves 表示。字符 move[i] 表示其第 i 次移动。机器人的有
 * 效动作有 R（右），L（左），U（上）和 D（下）。
 *
 * 如果机器人在完成所有动作后返回原点，则返回 true。否则，返回 false。
 *
 * 注意：机器人“面朝”的方向无关紧要。 “R” 将始终使机器人向右移动一次，“L” 将
 * 始终向左移动等。此外，假设每次移动机器人的移动幅度相同。
 * */

#include <iostream>
#include <union_set.h>
using namespace std;

class Solution
{
 public:
	bool judgeCircle(string moves)
	{
		int cur[2] = { 0, 0 };
		for (char move : moves)
		{
			if (move == 'R')
				++cur[0];
			else if (move == 'L')
				--cur[0];
			else if (move == 'U')
				++cur[1];
			else if (move == 'D')
				--cur[1];
			else
				return false;
		}
		if (cur[0] == 0 && cur[1] == 0) return true;
		return false;
	}
};

int main()
{
	Solution solution;
	string moves;

	{
		moves = "UD";
		cout << "exp1 (true): " << endl;
		cout << "result: " << solution.judgeCircle(moves) << endl;
	}
}
