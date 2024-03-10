/*
 * 925.长按键入		url: https://leetcode.cn/problems/long-pressed-name/
 *
 * 题目描述：你的朋友正在使用键盘输入他的名字 name。偶尔，在键入字符 c 时，
 * 按键可能会被长按，而字符可能被输入 1 次或多次。
 *
 * 你将会检查键盘输入的字符 typed。如果它对应的可能是你的朋友的名字（其中一
 * 些字符可能被长按），那么就返回 True。
 * */

#include <iostream>
#include <vector>
using namespace std;

class Solution
{
 public:
	bool isLongPressedName(const string& name, const string& typed)
	{
		int i = 0, j = 0;
		while (i < name.size() && j < typed.size())
		{
			if (name[i] == typed[j])
			{
				// 相同则同时向后匹配
				i++, j++;
			}
			else
			{
				// 不相同
				if (j == 0) return false; // 如果是第一位就不相同直接返回false
				// j跨越重复项，向后移动，同时防止j越界
				while (j < typed.size() && typed[j] == typed[j - 1]) j++;
				if (name[i] == typed[j])
				{
					// j跨越重复项之后再次和name[i]匹配
					i++, j++;
				}
				else
					return false;
			}
		}
		// 说明name没有匹配完，例如 name:"pyplrzzzzdsfa" type:"ppyypllr"
		if (i < name.size()) return false;

		// 说明type没有匹配完，例如 name:"alex" type:"alexxrrrrssda"
		while (j < typed.size())
		{
			if (typed[j] == typed[j - 1])
				j++;
			else
				return false;
		}
		return true;
	}
};

int main()
{
	Solution solution;
	string name, typed;

	{
		cout << "exp1 (true): ";
		name = "alex";
		typed = "aaleex";
		cout << solution.isLongPressedName(name, typed) << endl;
	}

	{
		cout << "exp2 (false): ";
		name = "rick";
		typed = "kric";
		cout << solution.isLongPressedName(name, typed) << endl;
	}
}