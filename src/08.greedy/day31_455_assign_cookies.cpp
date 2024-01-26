/*
 * 455. 分发饼干		url: https://leetcode.cn/problems/assign-cookies/
 *
 * 题目描述：假设你是一位很棒的家长，想要给你的孩子们一些小饼干。但是，每个孩子最多只能给一块饼干。
 * 对每个孩子 i，都有一个胃口值 g[i]，这是能让孩子们满足胃口的饼干的最小尺寸；并且每块饼干 j，都
 * 有一个尺寸 s[j] 。如果 s[j] >= g[i]，我们可以将这个饼干 j 分配给孩子 i ，这个孩子会得到满足。
 * 你的目标是尽可能满足越多数量的孩子，并输出这个最大数值。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	int findContentChildren(vector<int>& g, vector<int>& s)
	{
		// 首先进行排序
		sort(g.begin(), g.end());
		sort(s.begin(), s.end());

		int count = 0;
		for (int j = 0; count < g.size() && j < s.size(); j++)
		{
			// 每次使用最小的饼干满足孩子
			// 不满足就取下一个饼干
			if (s[j] >= g[count])
			{
				count++;
			}
		}

		return count;
	}
};

int main()
{
	Solution solution;
	vector<int> g;
	vector<int> s;

	cout << "exp1 (2): ";
	g = { 10, 9, 8, 7 };
	s = { 5, 6, 7, 8 };
	cout << solution.findContentChildren(g, s) << endl;

}
