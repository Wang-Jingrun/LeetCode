/*
 * 202. 快乐数
	url: https://leetcode.cn/problems/happy-number/
 *
 * 题目描述：编写一个算法来判断一个数 n 是不是快乐数。
 * 「快乐数」 定义为：
 * 对于一个正整数，每一次将该数替换为它每个位置上的数字的平方和。
 * 然后重复这个过程直到这个数变为 1，也可能是 无限循环 但始终变不到 1。
 * 如果这个过程 结果为 1，那么这个数就是快乐数。
 * 如果 n 是 快乐数 就返回 true ；不是，则返回 false 。
 * */

#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

class Solution
{
 public:
	// 取数值各个位上的单数之和
	int getSum(int n)
	{
		int sum = 0;
		while (n)
		{
			sum += (n % 10) * (n % 10);
			n /= 10;
		}
		return sum;
	}

	bool isHappy(int n)
	{
		unordered_set<int> set;
		while (true)
		{
			int sum = getSum(n);
			if (sum == 1)
			{
				return true;
			}
			// 如果这个sum曾经出现过，说明已经陷入了无限循环了，立刻return false
			if (set.find(sum) != set.end())
				return false;
			else
				set.insert(sum);

			n = sum;
		}
	}
};

int main()
{
	Solution solution;

	cout << "exp1 (true): ";
	cout << solution.isHappy(19) << endl;

	cout << "exp2 (false): ";
	cout << solution.isHappy(2) << endl;

	cout << "exp3 (true): ";
	cout << solution.isHappy(1) << endl;

	cout << "exp4 (true): ";
	cout << solution.isHappy(7) << endl;
}