/*
 * 541. 反转字符串 II		url: https://leetcode.cn/problems/reverse-string-ii/
 *
 * 题目描述：给定一个字符串 s 和一个整数 k，从字符串开头算起，每计数至 2k 个字符，就反转这 2k 字符中的前 k 个字符。
 * 如果剩余字符少于 k 个，则将剩余字符全部反转。
 * 如果剩余字符小于 2k 但大于或等于 k 个，则反转前 k 个字符，其余字符保持原样。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 public:
	string reverseStr(string s, int k)
	{
		int size = s.size();
		int count = 0;
		int left, right;
		char temp;

		while (size >= k * 2)
		{
			left = count * 2 * k;
			right = left + k - 1;

			while (left < right)
			{
				temp = s[left];
				s[left] = s[right];
				s[right] = temp;

				left++;
				right--;
			}

			count++;
			size -= k * 2;
		}

		left = count * 2 * k;
		if (size < k)
			right = left + size - 1;
		else
			right = left + k - 1;

		while (left < right)
		{
			temp = s[left];
			s[left] = s[right];
			s[right] = temp;

			left++;
			right--;
		}

		return s;
	}
};

class Solution2
{
 public:
	string reverseStr(string s, int k)
	{
		for (int i = 0; i < s.size(); i += k * 2)
		{
			if (i + k <= s.size())
			{
				reverse(s, i, i + k - 1);
				continue;
			}

			reverse(s, i, s.size() - 1);
		}
		return s;
	}

	void reverse(string& str, int start, int end)
	{
		// 左闭右闭实现
		for (int i = start, j = end; i < j; ++i, --j)
		{
			swap(str[i], str[j]);
		}
	}
};

int main()
{
	Solution solution;
	string result;

	cout << "exp1 (\"bacdfeg\"): ";
	result = solution.reverseStr("abcdefg", 2);
	cout << result << endl;
}