/*
 * 1002. 查找共用字符		url: https://leetcode.cn/problems/find-common-characters/
 *
 * 题目描述：给你一个字符串数组 words ，请你找出所有在 words 的
 * 每个字符串中都出现的共用字符（ 包括重复字符），并以数组形式返回。
 * 你可以按 任意顺序 返回答案。
 * */

#include <iostream>
#include <vector>
#include <cstring>
using namespace std;

class Solution
{
 public:
	vector<string> commonChars(vector<string>& words)
	{
		int hash[26] = { 0 }; // 用来统计所有字符串里字符出现的最小频率
		// 用第一个字符串给hash初始化
		for (char ch : words[0])
		{
			hash[ch - 'a']++;
		}

		int hashOther[26] = { 0 }; // 统计除第一个字符串外字符的出现频率
		for (int i = 1; i < words.size(); i++)
		{
			memset(hashOther, 0, 26 * sizeof(int));
			for (char ch : words[i])
			{
				hashOther[ch - 'a']++;
			}

			// 更新hash，保证hash里统计26个字符在所有字符串里出现的最小次数
			for (int k = 0; k < 26; k++)
			{
				hash[k] = min(hash[k], hashOther[k]);
			}
		}

		vector<string> result;
		// 将hash统计的字符次数，转成输出形式
		for (int k = 0; k < 26; k++)
		{
			while (hash[k] != 0) // 注意这里是while，多个重复的字符
			{
				result.push_back(string(1, 'a' + k)); // char -> string
				hash[k]--;
			}
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<string> words;

	{
		cout << R"(exp1 ([e, l, l]): )";
		words = { "bella", "label", "roller" };
		auto result = solution.commonChars(words);
		for (const string& str : result)
		{
			cout << str << " ";
		}
		cout << endl;
	}
}