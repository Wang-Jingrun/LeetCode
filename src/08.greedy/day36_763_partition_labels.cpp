/*
 * 763. 划分字母区间		url: https://leetcode.cn/problems/partition-labels/
 *
 * 题目描述：给你一个字符串 s 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。
 * 注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 s 。
 * 返回一个表示每个字符串片段的长度的列表。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
#include <unordered_map>
using namespace std;

class Solution
{
 public:
	vector<int> partitionLabels(const string& s)
	{
		vector<int> result;
		unordered_map<char, int> m;

		// 统计区间，记录每个字符出现的最大下标
		for (int i = 0; i < s.size(); i++)
		{
			m[s[i]] = i;
		}

		// 遍历寻找重叠的区间
		int right = INT_MIN;
		int start = 0;
		for (int i = 0; i < s.size(); i++)
		{
			// 每次遍历，更新所需要达到的最大下标
			auto pos = m.find(s[i]);
			right = max(right, pos->second);

			// 当前区间满足要求，同一字母均出现在该片段
			if (right == i)
			{
				// 记录结果
				result.push_back(i + 1 - start);
				start = i + 1;
			}
		}

		return result;
	}
};

int main()
{
	Solution solution;
	string s;

	{
		s = "ababcbacadefegdehijhklij";
		cout << "exp1 ([9,7,8]): " << endl;

		auto result = solution.partitionLabels(s);
		cout << "result: [ ";
		for (auto num : result)
		{
			cout << num << " ";
		}
		cout << "]" << endl;
	}
}
