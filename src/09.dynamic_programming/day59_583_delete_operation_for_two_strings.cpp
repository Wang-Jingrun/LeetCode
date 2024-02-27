/*
 * 583. 两个字符串的删除操作		url: https://leetcode.cn/problems/delete-operation-for-two-strings/
 *
 * 题目描述：给定两个单词 word1 和 word2 ，返回使得 word1 和  word2 相同所需的最小步数。
 * 每步 可以删除任意一个字符串中的一个字符。
 * */

#include <iostream>
#include <vector>
#include <cmath>
#include <cstdint>
using namespace std;

class Solution
{
 public:
	int minDistance(const string& word1, const string& word2)
	{
		vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1, 0));
		for (int i = 1; i <= word1.size(); i++)
		{
			for (int j = 1; j <= word2.size(); j++)
			{
				if (word1[i - 1] == word2[j - 1])
					dp[i][j] = dp[i - 1][j - 1] + 1;
				else
					dp[i][j] = max(dp[i - 1][j], dp[i][j - 1]);
			}
		}
		// 最终结果为
		// word1 长度减去公共子序列长度 + word2 长度减去公共子序列长度
		// 即为两个字符串需要删除的总字符数
		return (word1.size() - dp[word1.size()][word2.size()])
			+ (word2.size() - dp[word1.size()][word2.size()]);
	}
};

class Solution2
{
 public:
	int minDistance(string word1, string word2)
	{
		vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1));
		for (int i = 0; i <= word1.size(); i++) dp[i][0] = i;
		for (int j = 0; j <= word2.size(); j++) dp[0][j] = j;
		for (int i = 1; i <= word1.size(); i++)
		{
			for (int j = 1; j <= word2.size(); j++)
			{
				if (word1[i - 1] == word2[j - 1])
					dp[i][j] = dp[i - 1][j - 1];
				else
					dp[i][j] = min(dp[i - 1][j] + 1, dp[i][j - 1] + 1);
			}
		}
		return dp[word1.size()][word2.size()];
	}
};

int main()
{
	Solution2 solution;
	string word1;
	string word2;

	{
		word1 = "sea";
		word2 = "eat";
		cout << "exp1 (2): " << endl;
		cout << "result: " << solution.minDistance(word1, word2) << endl;
	}

	{
		word1 = "leetcode";
		word2 = "etco";
		cout << "exp2 (4): " << endl;
		cout << "result: " << solution.minDistance(word1, word2) << endl;
	}
}
