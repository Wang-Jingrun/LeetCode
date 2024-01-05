/*
 * 28. 找出字符串中第一个匹配项的下标	url: https://leetcode.cn/problems/find-the-index-of-the-first-occurrence-in-a-string/
 *
 * 题目描述：给你两个字符串 haystack 和 needle ，
 * 请你在 haystack 字符串中找出 needle 字符串的
 * 第一个匹配项的下标（下标从 0 开始）。如果 needle
 * 不是 haystack 的一部分，则返回  -1 。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 public:
	int strStr(string haystack, string needle)
	{
		for (int i = 0; i < haystack.size(); ++i)
		{
			for (int j = 0; j < needle.size(); ++j)
			{
				if (needle[j] == haystack[i + j])
				{
					if (j == needle.size() - 1)
						return i;

					continue;
				}
				else
					break;
			}
		}

		return -1;
	}
};

class Solution2    // kmp 算法
{
 public:
	void getNext(int* next, const string& str)
	{
		int j = 0;
		next[0] = 0;

		for (int i = 1; i < str.size(); ++i)
		{
			// j要保证大于0，因为下面有取j-1作为数组下标的操作
			while (j > 0 && str[i] != str[j]) j = next[j - 1]; // 找前一位的对应的回退位置了

			if (str[i] == str[j]) j++;
			next[i] = j;
		}
	}

	int strStr(string haystack, string needle)
	{
		if (needle.empty()) return 0;

		int next[needle.size()];
		getNext(next, needle);

		int j = 0;
		for (int i = 0; i < haystack.size(); ++i)
		{
			// 不匹配时，j 寻找之前匹配的位置
			while (j > 0 && haystack[i] != needle[j]) j = next[j - 1];

			// 匹配时，j 和 i 同时向后移动，i 的增加在 for 循环里
			if (haystack[i] == needle[j]) ++j;

			// 文本串 s 里出现了模式串 t
			if (j == needle.size())
				return (i - int(needle.size()) + 1);
		}

		return -1;
	}
};

int main()
{
	Solution2 solution;
	string haystack, needle;

	cout << "exp1 (0): ";
	haystack = "sadbutsad";
	needle = "sad";
	cout << solution.strStr(haystack, needle) << endl;

	cout << "exp2 (-1): ";
	haystack = "leetcode";
	needle = "leeto";
	cout << solution.strStr(haystack, needle) << endl;

	cout << "exp3 (4): ";
	haystack = "aabaaabaaac";
	needle = "aabaaac";
	cout << solution.strStr(haystack, needle) << endl;
}