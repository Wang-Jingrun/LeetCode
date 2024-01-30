/*
 * 860. 柠檬水找零		url: https://leetcode.cn/problems/lemonade-change/
 *
 * 题目描述：在柠檬水摊上，每一杯柠檬水的售价为 5 美元。顾客排队购买你的产品，（按账单 bills 支付的顺序）一次购买一杯。
 * 每位顾客只买一杯柠檬水，然后向你付 5 美元、10 美元或 20 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 5 美元。
 * 注意，一开始你手头没有任何零钱。
 * 给你一个整数数组 bills ，其中 bills[i] 是第 i 位顾客付的账。如果你能给每位顾客正确找零，返回 true ，否则返回 false 。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	bool lemonadeChange(vector<int>& bills)
	{
		int changes[2] = { 0 };
		for (auto bill : bills)
		{
			if (bill == 5)
				changes[0]++;
			else if (bill == 10)
			{
				// 获得 10 块，找零 5 块
				if (changes[0])
				{
					changes[1]++;
					changes[0]--;
				}
				else
					return false;
			}
			else if (bill == 20)
			{
				// 有 10 块优先用块找零
				if (changes[1] && changes[0])
				{
					changes[1]--;
					changes[0]--;
				}
				else if (changes[0] >= 3)
				{
					changes[0] -= 3;
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	cout << "exp1 (true): ";
	nums = { 5, 5, 5, 10, 20 };
	cout << solution.lemonadeChange(nums) << endl;

	cout << "exp2 (false): ";
	nums = { 5, 5, 10, 10, 20 };
	cout << solution.lemonadeChange(nums) << endl;
}
