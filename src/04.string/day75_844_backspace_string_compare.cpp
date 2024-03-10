/*
 * 844. 比较含退格的字符串		url: https://leetcode.cn/problems/backspace-string-compare/
 *
 * 题目描述：给定 s 和 t 两个字符串，当它们分别被输入到空白的文本编辑器后，如果两者相等，返回 true 。# 代表退格字符。
 *
 * 注意：如果对空文本输入退格字符，文本继续为空。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 private:
	string getString(const string& S)
	{
		string s;
		for (int i = 0; i < S.size(); i++)
		{
			if (S[i] != '#')
				s += S[i];
			else if (!s.empty())
				s.pop_back();
		}
		return s;
	}
 public:
	bool backspaceCompare(string S, string T)
	{
		return getString(S) == getString(T);
	}
};

class Solution2
{
 public:
	bool backspaceCompare(string S, string T)
	{
		int sSkipNum = 0; // 记录S的#数量
		int tSkipNum = 0; // 记录T的#数量
		int i = S.size() - 1;
		int j = T.size() - 1;
		while (true)
		{
			while (i >= 0)
			{
				// 从后向前，消除S的#
				if (S[i] == '#') sSkipNum++;
				else
				{
					if (sSkipNum > 0) sSkipNum--;
					else break;
				}
				i--;
			}

			while (j >= 0)
			{
				// 从后向前，消除T的#
				if (T[j] == '#') tSkipNum++;
				else
				{
					if (tSkipNum > 0) tSkipNum--;
					else break;
				}
				j--;
			}

			// 后半部分#消除完了，接下来比较S[i] != T[j]
			if (i < 0 || j < 0) break; // S 或者T 遍历到头了

			if (S[i] != T[j]) return false;
			i--;
			j--;
		}
		// 说明S和T同时遍历完毕
		if (i == -1 && j == -1) return true;
		return false;
	}
};

int main()
{
	Solution2 solution;
	string s, t;

	{
		cout << "exp1 (true): ";
		s = "y#fo##f";
		t = "y#f#o##f";
		cout << solution.backspaceCompare(s, t) << endl;
	}

	{
		cout << "exp2 (true): ";
		s = "xywrrmp";
		t = "xywrrmu#p";
		cout << solution.backspaceCompare(s, t) << endl;
	}
}