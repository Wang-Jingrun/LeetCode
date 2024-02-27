/*
 * 739. 每日温度		url: https://leetcode.cn/problems/daily-temperatures/
 *
 * 题目描述：给定一个整数数组 temperatures ，表示每天的温度，返回一个数组 answer ，
 * 其中 answer[i] 是指对于第 i 天，下一个更高温度出现在几天后。如果气温在这之后都不会
 * 升高，请在该位置用 0 来代替。
 * */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

// 暴力解法
class Solution2
{
 public:
	vector<int> dailyTemperatures(vector<int>& temperatures)
	{
		vector<int> result(temperatures.size(), 0);
		for (int i = 0; i < temperatures.size(); i++)
		{
			for (int j = i + 1; j < temperatures.size(); j++)
			{
				if (temperatures[j] > temperatures[i])
				{
					result[i] = j - i;
					break;
				}
			}
		}
		return result;
	}
};

class Solution
{
 public:
	vector<int> dailyTemperatures(vector<int>& temperatures)
	{
		vector<int> result(temperatures.size(), 0);
		stack<int> st;
		st.push(0);
		for (int i = 1; i < temperatures.size(); i++)
		{
			// 情况三
			while (!st.empty() && temperatures[i] > temperatures[st.top()])
			{
				result[st.top()] = i - st.top();
				st.pop();
			}

			// 情况一、二
			// 同时，情况三也需要push
			st.push(i);
		}

		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> temperatures;

	{
		temperatures = { 73, 74, 75, 71, 69, 72, 76, 73 };
		cout << "exp1 ([1,1,4,2,1,1,0,0]): " << endl;
		cout << "result: [ ";
		auto result = solution.dailyTemperatures(temperatures);
		for (auto num : result)
		{
			cout << num << " ";
		}
		cout << "]" << endl;
	}
}
