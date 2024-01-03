/*
 * 卡码网 54. 替换数字		url: https://kamacoder.com/problempage.php?pid=1064
 *
 * 题目描述：给定一个字符串 s，它包含小写字母和数字字符，请编写一个函数，
 * 将字符串中的字母字符保持不变，而将每个数字字符替换为number。
 * 例如，对于输入字符串 "a1b2c3"，函数应该将其转换为 "anumberbnumbercnumber"。
 * */

#include <iostream>
#include <string>
using namespace std;

// 使用了额外的空间
class Solution
{
 public:
	string replaceNumbers(string str)
	{
		string result;

		for (char ch : str)
		{
			if (isLetter(ch))
			{
				result += ch;
				continue;
			}

			result += "number";
		}

		return result;
	}

	bool isLetter(char ch)
	{
		if ((ch - 'a') >= 0 && (ch - 'a') < 26)
			return true;

		return false;
	}

};

// 不使用额外的空间
class Solution2
{
 public:
	string replaceNumbers(string s)
	{
		// 统计数字的个数
		int count = 0;
		int sOldSize = s.size();
		for (int i = 0; i < s.size(); i++)
		{
			if (!isLetter(s[i])) count++;
		}

		// 扩充字符串s的大小，也就是每个空格替换成"number"之后的大小
		s.resize(s.size() + count * 5);
		int sNewSize = s.size();

		// 从后先前将空格替换为"number"
		for (int i = sNewSize - 1, j = sOldSize - 1; j < i; i--, j--)
		{
			if (isLetter(s[j]))
			{
				s[i] = s[j];
			}
			else
			{
				s[i] = 'r';
				s[i - 1] = 'e';
				s[i - 2] = 'b';
				s[i - 3] = 'm';
				s[i - 4] = 'u';
				s[i - 5] = 'n';
				i -= 5;
			}
		}
		return s;
	}

	bool isLetter(char ch)
	{
		if ((ch - 'a') >= 0 && (ch - 'a') < 26)
			return true;

		return false;
	}

};

int main()
{
	Solution2 solution;
	string str;
	while (cin >> str)
	{
		cout << solution.replaceNumbers(str) << endl;
	}
}