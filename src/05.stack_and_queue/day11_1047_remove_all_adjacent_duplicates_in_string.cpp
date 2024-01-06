/*
 * 1047. 删除字符串中的所有相邻重复项	url: https://leetcode.cn/problems/remove-all-adjacent-duplicates-in-string/
 *
 * 题目描述：给出由小写字母组成的字符串 S，重复项删除操作会选择两个相邻且相同的字母，并删除它们。
 * 在 S 上反复执行重复项删除操作，直到无法继续删除。
 * 在完成所有重复项删除操作后返回最终的字符串。答案保证唯一。
 * */

#include <iostream>
#include <stack>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	string removeDuplicates(string s)
	{
		stack<char> stack;

		for (auto ch : s)
		{
			if (!stack.empty() && stack.top() == ch)
			{
				stack.pop();
			}
			else
			{
				stack.push(ch);
			}
		}

		s.clear();
		while (!stack.empty())
		{
			s += stack.top();
			stack.pop();
		}
		reverse(s.begin(), s.end());
		return s;
	}
};

int main()
{
	Solution solution;
	string str;

	cout << "exp1 (\"ca\"): ";
	str = "abbaca";
	cout << solution.removeDuplicates(str) << endl;
}