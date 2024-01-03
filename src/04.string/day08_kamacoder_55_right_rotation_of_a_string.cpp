/*
 * 卡码网 55. 右旋字符串		url: https://kamacoder.com/problempage.php?pid=1065
 *
 * 题目描述：字符串的右旋转操作是把字符串尾部的若干个字符转移到字符串的前面。
 * 给定一个字符串 s 和一个正整数 k，请编写一个函数，将字符串中的后面 k 个
 * 字符移到字符串的前面，实现字符串的右旋转操作。
 * 例如，对于输入字符串 "abcdefg" 和整数 2，函数应该将其转换为 "fgabcde"。
 * */

#include <iostream>
#include <string>
using namespace std;

class Solution
{
 public:
	string rightRotationString(string str, int k)
	{
		reverse(str, 0, str.size()-1);
		reverse(str, 0, k-1);
		reverse(str, k, str.size()-1);
		return str;
	}

	void reverse(string& str, int start, int end)
	{
		for (int i = start, j = end; i < j; i++, j--)
		{
			swap(str[i], str[j]);
		}
	}
};

int main()
{
	Solution solution;
	string str;
	int k;
	while (cin >> k >> str)
	{
		cout << solution.rightRotationString(str, k) << endl;
	}
}