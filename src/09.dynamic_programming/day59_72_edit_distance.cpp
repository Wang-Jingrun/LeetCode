/*
 * 72. 编辑距离		url: https://leetcode.cn/problems/edit-distance/
 *
 * 题目描述：给你两个单词 word1 和 word2， 请返回将 word1 转换成 word2 所使用的最少操作数  。
 * 你可以对一个单词进行如下三种操作：
 * 		插入一个字符
 * 		删除一个字符
 * 		替换一个字符
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
		vector<vector<int>> dp(word1.size() + 1, vector<int>(word2.size() + 1));

		// 初始化
		for (int i = 0; i <= word1.size(); i++)
			dp[i][0] = i;
		for (int j = 0; j <= word2.size(); j++)
			dp[0][j] = j;

		for (int i = 1; i <= word1.size(); i++)
		{
			for (int j = 1; j <= word2.size(); j++)
			{
				if (word1[i - 1] == word2[j - 1])
					dp[i][j] = dp[i - 1][j - 1];
				else
					dp[i][j] = min(dp[i - 1][j - 1] + 1, min(dp[i - 1][j] + 1, dp[i][j - 1] + 1));
			}
		}
		return dp[word1.size()][word2.size()];
	}
};

int main()
{
	Solution solution;
	string word1;
	string word2;

	{
		word1 = "horse";
		word2 = "ros";
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.minDistance(word1, word2) << endl;
	}

	{
		word1 = "intention";
		word2 = "execution";
		cout << "exp2 (5): " << endl;
		cout << "result: " << solution.minDistance(word1, word2) << endl;
	}
}
