/*
 * 150. 逆波兰表达式求值	url: https://leetcode.cn/problems/evaluate-reverse-polish-notation/
 *
 * 题目描述：给你一个字符串数组 tokens ，表示一个根据 逆波兰表示法 表示的算术表达式。
 * 请你计算该表达式。返回一个表示表达式值的整数。
 * */

#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

class Solution
{
 public:
	int evalRPN(vector<string>& tokens)
	{
		stack<string> stack;
		int result = 0;
		int num1, num2;

		for (auto& token : tokens)
		{
			if (!isOperator(token))
			{
				stack.push(token);
			}
			else
			{
				num2 = stoi(stack.top());
				stack.pop();
				num1 = stoi(stack.top());
				stack.pop();

				if (token == "+")
					result = num1 + num2;
				else if (token == "-")
					result = num1 - num2;
				else if (token == "*")
					result = num1 * num2;
				else if (token == "/")
					result = num1 / num2;

				stack.push(to_string(result));
			}
		}
		return stoi(stack.top());
	}

	bool isOperator(const string& op)
	{
		return (op == "+" || op == "-" || op == "*" || op == "/");
	}
};

int main()
{
	Solution solution;
	vector<string> tokens;

	cout << "exp1 (22): ";
	tokens = { "10", "6", "9", "3", "+", "-11", "*", "/", "*", "17", "+", "5", "+" };
	cout << solution.evalRPN(tokens) << endl;
}