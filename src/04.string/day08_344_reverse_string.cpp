/*
 * 344. 反转字符串	url: https://leetcode.cn/problems/reverse-string/
 *
 * 题目描述：编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 s 的形式给出。
 * 不要给另外的数组分配额外的空间，你必须原地修改输入数组、使用 O(1) 的额外空间解决这一问题。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 public:
	void reverseString(vector<char>& s)
	{
		int left = 0, right = s.size() - 1;
		char temp;
		while (left < right)
		{
			temp = s[left];
			s[left] = s[right];
			s[right] = temp;

			left++;
			right--;
		}
	}
};

class Solution2
{
 public:
	void reverseString(vector<char>& s)
	{
		for (int i = 0, j = s.size() - 1; i < s.size() / 2; i++, j--)
			swap(s[i], s[j]);
	}
};

int main()
{
	Solution solution;
	vector<char> str;

	cout << "exp1 (e d c b a): ";
	str = { 'a', 'b', 'c', 'd', 'e' };
	solution.reverseString(str);
	for (auto ch : str)
		cout << ch << " ";

	cout << endl;
}