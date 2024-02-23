/*
 * 139. 单词拆分		url: https://leetcode.cn/problems/word-break/
 *
 * 题目描述：给你一个字符串 s 和一个字符串列表 wordDict 作为字典。
 * 如果可以利用字典中出现的一个或多个单词拼接出 s 则返回 true。
 * 注意：不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	bool wordBreak(const string& s, vector<string>& wordDict)
	{
		vector<bool> dp(s.size() + 1, false);
		dp[0] = true;

		for (int i = 0; i <= s.size(); i++)
		{
			for (int j = 0; j < wordDict.size(); j++)
			{
				if (wordDict[j].size() > i) continue;

				if (dp[i - wordDict[j].size()]
					&& s.substr(i - wordDict[j].size(), wordDict[j].size()) == wordDict[j])
				{
					dp[i] = true;
				}
			}
		}

		return dp[s.size()];
	}
};

int main()
{
	Solution solution;
	vector<string> wordDict;

	{
		wordDict = { "leet", "code" };
		cout << "exp1 (true): " << endl;
		cout << "result: " << solution.wordBreak("leetcode", wordDict) << endl;
	}
}
