/*
 * 383. 赎金信	url: https://leetcode.cn/problems/ransom-note/
 *
 * 题目描述：给你两个字符串：ransomNote 和 magazine ，判断 ransomNote 能不能由 magazine 里面的字符构成。
 * 如果可以，返回 true ；否则返回 false 。
 * magazine 中的每个字符只能在 ransomNote 中使用一次。
 * */

#include <iostream>
using namespace std;

class Solution
{
 public:
	bool canConstruct(string ransomNote, string magazine)
	{
		int record[26] = { 0 };

		// 子串大于目标串，不可能出现
		if (ransomNote.size() > magazine.size())
			return false;

		// 通过record数据记录 magazine里各个字符出现次数
		for (int i = 0; i < magazine.length(); i++)
			record[magazine[i] - 'a']++;

		for (int j = 0; j < ransomNote.length(); j++)
		{
			// 遍历ransomNote，在record里对应的字符个数做--操作
			record[ransomNote[j] - 'a']--;

			// 如果小于零说明ransomNote里出现的字符，magazine没有
			if (record[ransomNote[j] - 'a'] < 0)
				return false;
		}
		return true;
	}
};

int main()
{
	Solution solution;

	cout << "exp1 (true): ";
	cout << solution.canConstruct("aa", "aab") << endl;
}