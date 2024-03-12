/*
 * 649. Dota2 参议院		url: https://leetcode.cn/problems/dota2-senate/
 *
 * 题目描述：Dota2 的世界里有两个阵营：Radiant（天辉）和 Dire（夜魇）
 *
 * Dota2 参议院由来自两派的参议员组成。现在参议院希望对一个 Dota2 游戏
 * 里的改变作出决定。他们以一个基于轮为过程的投票进行。在每一轮中，每一位
 * 参议员都可以行使两项权利中的 一 项：
 * 		禁止一名参议员的权利：参议员可以让另一位参议员在这一轮和随后的几轮中丧失 所有的权利 。
 * 		宣布胜利：如果参议员发现有权利投票的参议员都是 同一个阵营的 ，他可以宣布胜利并决定在游戏中的有关变化。
 *
 * 给你一个字符串 senate 代表每个参议员的阵营。字母 'R' 和 'D'分别代
 * 表了 Radiant（天辉）和 Dire（夜魇）。然后，如果有 n 个参议员，给定
 * 字符串的大小将是 n。
 *
 * 以轮为基础的过程从给定顺序的第一个参议员开始到最后一个参议员结束。这一
 * 过程将持续到投票结束。所有失去权利的参议员将在过程中被跳过。
 *
 * 假设每一位参议员都足够聪明，会为自己的政党做出最好的策略，你需要预测哪
 * 一方最终会宣布胜利并在 Dota2 游戏中决定改变。输出应该是 "Radiant"
 * 或 "Dire" 。
 * */

#include <iostream>
using namespace std;

class Solution
{
 public:
	string predictPartyVictory(string senate)
	{
		// R = true表示本轮循环结束后，字符串里依然有R。D同理
		bool R = true, D = true;
		// 当flag大于0时，R在D前出现，R可以消灭D。当flag小于0时，D在R前出现，D可以消灭R
		int flag = 0;
		while (R && D)  // 一旦R或者D为false，就结束循环，说明本轮结束后只剩下R或者D了
		{
			R = false;
			D = false;

			for (int i = 0; i < senate.size(); ++i)
			{
				if (senate[i] == 'R')
				{
					if (flag < 0)
						senate[i] = '0'; // 消灭R，R此时为false
					else
						R = true;  // 如果没被消灭，本轮循环结束有R

					++flag;
				}

				if (senate[i] == 'D')
				{
					if (flag > 0)
						senate[i] = '0';
					else
						D = true;

					--flag;
				}
			}
		}
		// 循环结束之后，R和D只能有一个为true
		return R == true ? "Radiant" : "Dire";
	}
};

int main()
{
	Solution solution;

	{
		string senate = "DDRRR";
		cout << "exp1 (Dire): " << endl;
		cout << "result: " << solution.predictPartyVictory(senate) << endl;
	}
}
