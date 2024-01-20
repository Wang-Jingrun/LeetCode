/*
 * 17. 电话号码的字母组合	url: https://leetcode.cn/problems/letter-combinations-of-a-phone-number/
 *
 * 题目描述：给定一个仅包含数字 2-9 的字符串，返回所有它能表示的字母组合。答案可以按 任意顺序 返回。
 * 给出数字到字母的映射与电话按键相同。注意 1 不对应任何字母。
 * */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Solution
{
 private:
	const vector<string> m_d2s = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
	string m_com;
	vector<string> m_result;

	void backtracking(int start, const string& digits)
	{
		if (m_com.size() == digits.size())
		{
			m_result.push_back(m_com);
			return;
		}

		// 每个数字的循环 -> 每个数字三个字母的循环
		for (int i = start; i < digits.size(); ++i)
		{
			int digit = digits[i] - '2';
			for (auto ch : m_d2s[digit])
			{
				m_com += ch;
				backtracking(i + 1, digits);
				m_com.pop_back();
			}

		}
	}

 public:
	vector<string> letterCombinations(const string& digits)
	{
		if (digits.empty()) return m_result;

		m_com.clear();
		m_result.clear();
		backtracking(0, digits);
		return m_result;
	}
};

class Solution2
{
 private:
	const vector<string> m_d2s = { "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz" };
	string m_com;
	vector<string> m_result;

	void backtracking(int index, const string& digits)
	{
		if (index == digits.size())
		{
			m_result.push_back(m_com);
			return;
		}

		int digit = digits[index] - '2';
		for (auto ch : m_d2s[digit])
		{
			m_com += ch;
			backtracking(index + 1, digits);
			m_com.pop_back();
		}
	}

 public:
	vector<string> letterCombinations(const string& digits)
	{
		if (digits.empty()) return m_result;

		m_com.clear();
		m_result.clear();
		backtracking(0, digits);
		return m_result;
	}
};

int main()
{

	Solution2 solution;
	vector<string> result;

	{
		cout << R"(exp1 (["ad","ae","af","bd","be","bf","cd","ce","cf"]): )" << endl;

		cout << "result: ";
		result = solution.letterCombinations("23");
		cout << "[ ";
		for (const auto& combs : result)
		{
			cout << combs << " ";
		}
		cout << "]" << endl;
	}

	cout << endl;

	return 0;
}