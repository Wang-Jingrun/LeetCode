/*
 * 205. 同构字符串	url: https://leetcode.cn/problems/isomorphic-strings/
 *
 * 题目描述：给定两个字符串 s 和 t ，判断它们是否是同构的。
 *
 * 如果 s 中的字符可以按某种映射关系替换得到 t ，那么这两个字符串是同构的。
 *
 * 每个出现的字符都应当映射到另一个字符，同时不改变字符的顺序。不同字符不能映
 * 射到同一个字符上，相同字符只能映射到同一个字符上，字符可以映射到自己本身。
 * */

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
 public:
	bool isIsomorphic(const string& s, const string& t)
	{
		unordered_map<char, char> umap1;
		unordered_map<char, char> umap2;
		for (int i = 0; i < s.size(); i++)
		{
			if (!umap1.count(s[i])) umap1[s[i]] = t[i];
			if (!umap2.count(t[i])) umap2[t[i]] = s[i];

			if (umap1[s[i]] != t[i] || umap2[t[i]] != s[i]) return false;
		}
		return true;
	}
};

int main()
{
	Solution solution;
	string s, t;

	{
		cout << "exp1 (true): ";
		s = "egg";
		t = "add";
		cout << solution.isIsomorphic(s, t) << endl;
	}

	{
		cout << "exp2 (false): ";
		s = "foo";
		t = "bar";
		cout << solution.isIsomorphic(s, t) << endl;
	}
}