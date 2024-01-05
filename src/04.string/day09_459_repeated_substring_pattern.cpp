/*
 * 459. 重复的子字符串		url: https://leetcode.cn/problems/repeated-substring-pattern/
 *
 * 题目描述：给定一个非空的字符串 s ，检查是否可以通过由它的一个子串重复多次构成。
 * 提示：
 * 1 <= s.length <= 10^4
 * s 由小写英文字母组成
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 public:
	bool repeatedSubstringPattern(string s)
	{
		string t = s + s;
		t.erase(t.begin());
		t.erase(t.end() - 1); // 掐头去尾
		if (t.find(s) != std::string::npos) return true;
		return false;
	}
};

class Solution2
{
 public:
	void getNext(int* next, const string& str)
	{
		next[0] = 0;
		int j = 0;
		for (int i = 1; i < str.size(); ++i)
		{
			while ((j > 0) && (str[i] != str[j])) j = next[j - 1];

			if (str[i] == str[j]) j++;

			next[i] = j;
		}
	}

	bool repeatedSubstringPattern(string s)
	{
		if (s.empty()) return false;

		int next[s.size()];
		getNext(next, s);

		int len = int(s.size());
		if (next[len - 1] != 0 && len % (len - next[len - 1]) == 0)
			return true;

		return false;
	}
};

int main()
{
	Solution2 solution;
	string s;

	cout << "exp1 (true): ";
	s = "abab";
	cout << solution.repeatedSubstringPattern(s) << endl;

	cout << "exp2 (false): ";
	s = "aba";
	cout << solution.repeatedSubstringPattern(s) << endl;
}