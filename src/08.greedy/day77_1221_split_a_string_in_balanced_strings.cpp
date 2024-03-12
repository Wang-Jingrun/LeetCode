/*
 * 1221. 分割平衡字符串		url: https://leetcode.cn/problems/split-a-string-in-balanced-strings/
 *
 * 题目描述：平衡字符串 中，'L' 和 'R' 字符的数量是相同的。
 * 给你一个平衡字符串 s，请你将它分割成尽可能多的子字符串，并满足：
 * 		每个子字符串都是平衡字符串。
 * 返回可以通过分割得到的平衡字符串的 最大数量 。
 * */

#include <iostream>
using namespace std;

class Solution
{
 public:
	int balancedStringSplit(const string& s)
	{
		int result = 0;
		int count = 0;
		char preChar;

		for (int i = 0; i < s.size(); i++)
		{
			if (count == 0)
			{
				preChar = s[i];
				++count;
			}
			else
			{
				if (preChar == s[i])
				{
					++count;
				}
				else
				{
					--count;
					if (count == 0) ++result;
				}
			}
		}
		return result;
	}
};

class Solution2
{
 public:
	int balancedStringSplit(string s)
	{
		int result = 0;
		int count = 0;
		for (int i = 0; i < s.size(); i++)
		{
			if (s[i] == 'R') count++;
			else count--;
			if (count == 0) result++;
		}
		return result;
	}
};

int main()
{
	Solution2 solution;

	{
		string str = "RLRRRLLRLL";
		cout << "exp1 (2): " << endl;
		cout << "result: " << solution.balancedStringSplit(str) << endl;
	}
}
