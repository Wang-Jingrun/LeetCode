/*
 * 20. 有效的括号		url: https://leetcode.cn/problems/valid-parentheses/
 *
 * 题目描述：给定一个只包括 '('，')'，'{'，'}'，'['，']' 的字符串 s ，判断字符串是否有效。
 * 有效字符串需满足：
 * 1、左括号必须用相同类型的右括号闭合。
 * 2、左括号必须以正确的顺序闭合。
 * 3、每个右括号都有一个对应的相同类型的左括号。
 * */

#include <iostream>
#include <stack>
using namespace std;

class Solution
{
 public:
	bool isValid(const string& s)
	{
		stack<char> stack;

		for (auto ch : s)
		{
			if (ch == '(' || ch == '[' || ch == '{')
			{
				stack.push(ch);
			}
			else if(stack.empty())
			{
				return false;
			}
			else
			{
				switch (ch)
				{
				case ')':
				{
					if (stack.top() != '(') return false;

					stack.pop();
					break;
				}
				case ']':
				{
					if (stack.top() != '[') return false;

					stack.pop();
					break;
				}
				case '}':
				{
					if (stack.top() != '{') return false;

					stack.pop();
					break;
				}
				default:
					break;
				}
			}

		}

		if (stack.empty()) return true;
		else return false;
	}
};

int main()
{
	Solution solution;
	string str;

	cout << "exp1 (true): ";
	str = "()";
	cout << solution.isValid(str) << endl;

	cout << "exp2 (true): ";
	str = "()[]{}";
	cout << solution.isValid(str) << endl;

	cout << "exp3 (false): ";
	str = "(]";
	cout << solution.isValid(str) << endl;
}