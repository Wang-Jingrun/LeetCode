/*
 * 242. 有效的字母异位词	url: https://leetcode.cn/problems/valid-anagram/
 *
 * 题目描述：给定两个字符串 s 和 t ，编写一个函数来判断 t 是否是 s 的字母异位词。
 * 注意：若 s 和 t 中每个字符出现的次数都相同，则称 s 和 t 互为字母异位词。
 * */

#include <string>
#include <iostream>
#include <map>
using namespace std;

class Solution    // map 哈希表，可以判断任意字符，但是复杂度较高
{
 public:
	bool isAnagram(const string& s, const string& t)
	{
		map<char, int> hash;

		for (auto ch : s)
		{
			auto pos = hash.find(ch);
			if (pos != hash.end())
				hash[ch]++;
			else
				hash[ch] = 1;
		}

		for (auto ch : t)
		{
			auto pos = hash.find(ch);
			if (pos != hash.end())
			{
				hash[ch]--;
				if (hash[ch] <= 0)
					hash.erase(ch);
			}
			else
				return false;
		}

		if (hash.empty())
			return true;
		else
			return false;
	}
};

class Solution2    // 数组 哈希表，对于题目要求仅小写字母，采用数组效率较高
{
 public:
	bool isAnagram(const string& s, const string& t)
	{
		int hash[26] = { 0 };

		// 遍历字符串 s，对应 hash 表中的值加 1
		for (char ch : s)
			hash[ch - 'a']++;

		// 遍历字符串 t，对应 hash 表中的值减 1
		for (auto ch : t)
			hash[ch - 'a']--;

		// 如果 hash 表中值全为 0，则符合题意
		for (int i : hash)
			if (i != 0)
				return false;

		return true;
	}
};

int main()
{
	Solution solution;

	cout << "exp1 (true): ";
	cout << solution.isAnagram("anagram", "nagaram") << endl;

	cout << "exp2 (false): ";
	cout << solution.isAnagram("rat", "car") << endl;

}