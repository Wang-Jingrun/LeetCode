/*
 * 151. 反转字符串中的单词		url: https://leetcode.cn/problems/reverse-words-in-a-string/
 *
 * 题目描述：给你一个字符串 s ，请你反转字符串中 单词 的顺序。
 * 单词 是由非空格字符组成的字符串。s 中使用至少一个空格将字符串中的 单词 分隔开。
 * 返回 单词 顺序颠倒且 单词 之间用单个空格连接的结果字符串。
 * 注意：输入字符串 s中可能会存在前导空格、尾随空格或者单词间的多个空格。
 * 返回的结果字符串中，单词间应当仅用单个空格分隔，且不包含任何额外的空格。
 * */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	void reverse(string& s, int start, int end)
	{
		//翻转，区间写法：左闭右闭 []
		for (int i = start, j = end; i < j; i++, j--)
			swap(s[i], s[j]);
	}

	void removeExtraSpaces(string& s)
	{
		//去除所有空格并在相邻单词之间添加空格, 快慢指针。
		int slow = 0;
		for (int fast = 0; fast < s.size(); ++fast)
		{
			//遇到非空格就处理，即删除所有空格。
			if (s[fast] != ' ')
			{
				//手动控制空格，给单词之间添加空格。slow != 0说明不是第一个单词，需要在单词前添加空格。
				if (slow != 0) s[slow++] = ' ';

				while (fast < s.size() && s[fast] != ' ')
				{
					//补上该单词，遇到空格说明单词结束。
					s[slow++] = s[fast++];
				}
			}
		}
		s.resize(slow); //slow的大小即为去除多余空格后的大小。
	}

	string reverseWords(string s)
	{
		//去除多余空格，保证单词之间之只有一个空格，且字符串首尾没空格。
		removeExtraSpaces(s);
		reverse(s, 0, s.size() - 1);

		//removeExtraSpaces后保证第一个单词的开始下标一定是0。
		int start = 0;
		for (int i = 0; i <= s.size(); ++i)
		{
			//到达空格或者串尾，说明一个单词结束。进行翻转。
			if (i == s.size() || s[i] == ' ')
			{
				//翻转，注意是左闭右闭 []的翻转。
				reverse(s, start, i - 1);
				//更新下一个单词的开始下标start
				start = i + 1;
			}
		}
		return s;
	}
};

int main()
{
	Solution solution;
	string result;

	cout << "exp1 (\"world hello\"): ";
	cout << solution.reverseWords("  hello world  ") << endl;

	cout << "exp2 (\"example good a\"): ";
	cout << solution.reverseWords("a good   example") << endl;
}