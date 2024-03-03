/*
 * 127. 单词接龙		url: https://leetcode.cn/problems/word-ladder/
 *
 * 题目描述：字典 wordList 中从单词 beginWord 和 endWord 的 转换序列
 * 是一个按下述规格形成的序列 beginWord -> s1 -> s2 -> ... -> sk：
 * 		每一对相邻的单词只差一个字母。
 * 		对于 1 <= i <= k 时，每个 si 都在 wordList 中。注意， beginWord 不需要在 wordList 中。
 * 		sk == endWord
 *
 * 给你两个单词 beginWord 和 endWord 和一个字典 wordList ，返回 从
 * beginWord 到 endWord 的 最短转换序列 中的 单词数目 。如果不存在这
 * 样的转换序列，返回 0 。
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <queue>
#include <unordered_map>
#include <unordered_set>
using namespace std;

class Solution
{
 private:
	bool oneLetterDifference(const string& word1, const string& word2)
	{
		if (word1.size() != word2.size()) return false;

		int count = 0;
		for (int i = 0; i < word1.size(); i++)
		{
			if (word1[i] != word2[i]) count++;
		}

		if (count == 1) return true;
		return false;
	}

 public:
	int ladderLength(const string& beginWord, const string& endWord, vector<string>& wordList)
	{
		// 记录word是否访问过
		unordered_map<string, int> visitMap; // <word, 查询到这个word路径长度>

		queue<string> qu;
		qu.push(beginWord);
		visitMap[beginWord] = 1;

		while (!qu.empty())
		{
			auto curWord = qu.front();
			qu.pop();
			int path = visitMap[curWord]; // 这个word的路径长度

			for (int i = 0; i < wordList.size(); i++)
			{
				// 符合条件的下一个单词，并且没有被访问过
				if (oneLetterDifference(curWord, wordList[i]) && visitMap.find(wordList[i]) == visitMap.end())
				{
					qu.push(wordList[i]);
					visitMap[wordList[i]] = path + 1;

					if (wordList[i] == endWord) return path + 1;
				}
			}
		}
		return 0;
	}
};

class Solution2
{
 public:
	int ladderLength(string beginWord, string endWord, vector<string>& wordList)
	{
		// 将vector转成unordered_set，提高查询速度
		unordered_set<string> wordSet(wordList.begin(), wordList.end());
		// 如果endWord没有在wordSet出现，直接返回0
		if (wordSet.find(endWord) == wordSet.end()) return 0;
		// 记录word是否访问过
		unordered_map<string, int> visitMap; // <word, 查询到这个word路径长度>
		// 初始化队列
		queue<string> que;
		que.push(beginWord);
		// 初始化visitMap
		visitMap.insert(pair<string, int>(beginWord, 1));

		while (!que.empty())
		{
			string word = que.front();
			que.pop();
			int path = visitMap[word]; // 这个word的路径长度
			for (int i = 0; i < word.size(); i++)
			{
				string newWord = word; // 用一个新单词替换word，因为每次置换一个字母
				for (int j = 0; j < 26; j++)
				{
					newWord[i] = j + 'a';
					if (newWord == endWord) return path + 1; // 找到了end，返回path+1
					// wordSet出现了newWord，并且newWord没有被访问过
					if (wordSet.find(newWord) != wordSet.end()
						&& visitMap.find(newWord) == visitMap.end())
					{
						// 添加访问信息
						visitMap.insert(pair<string, int>(newWord, path + 1));
						que.push(newWord);
					}
				}
			}
		}
		return 0;
	}
};

int main()
{
	Solution solution;
	vector<string> wordList;

	{
		wordList = { "hot", "cog", "dog", "tot", "hog", "hop", "pot", "dot" };
		cout << "exp1 (3): " << endl;
		cout << "result: " << solution.ladderLength("hot", "dog", wordList) << endl;
	}

	{
		wordList =
			{ "si", "go", "se", "cm", "so", "ph", "mt", "db", "mb", "sb", "kr", "ln", "tm", "le", "av", "sm", "ar",
			  "ci", "ca", "br", "ti", "ba", "to", "ra", "fa", "yo", "ow", "sn", "ya", "cr", "po", "fe", "ho", "ma",
			  "re", "or", "rn", "au", "ur", "rh", "sr", "tc", "lt", "lo", "as", "fr", "nb", "yb", "if", "pb", "ge",
			  "th", "pm", "rb", "sh", "co", "ga", "li", "ha", "hz", "no", "bi", "di", "hi", "qa", "pi", "os", "uh",
			  "wm", "an", "me", "mo", "na", "la", "st", "er", "sc", "ne", "mn", "mi", "am", "ex", "pt", "io", "be",
			  "fm", "ta", "tb", "ni", "mr", "pa", "he", "lr", "sq", "ye" };
		cout << "exp2 (5): " << endl;
		cout << "result: " << solution.ladderLength("qa", "sq", wordList) << endl;
	}
}
