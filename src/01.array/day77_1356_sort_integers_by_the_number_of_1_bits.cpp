/*
 * 1356. 根据数字二进制下 1 的数目排序		url: https://leetcode.cn/problems/sort-integers-by-the-number-of-1-bits/
 *
 * 题目描述：给你一个整数数组 arr 。请你将数组中的元素按照其二进制表示中数字 1 的数目升序排序。
 * 如果存在多个数字二进制中 1 的数目相同，则必须将它们按照数值大小升序排列。
 * 请你返回排序后的数组。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 private:
	int bitCount1(int n)
	{
		int count = 0; // 计数器
		while (n > 0)
		{
			if ((n & 1) == 1) ++count;  // 当前位是1，count++
			n >>= 1; // n向右移位
		}
		return count;
	}

	int bitCount2(int n)
	{
		int count = 0;
		while (n)
		{
			n &= (n - 1); // 清除最低位的1
			++count;
		}
		return count;
	}

 public:
	vector<int> sortByBits(vector<int>& arr)
	{
		sort(arr.begin(), arr.end(), [this](int a, int b) -> bool
		{
		  int count_a = bitCount2(a);
		  int count_b = bitCount2(b);
		  if (count_a == count_b) return a < b; // 如果bit中1数量相同，比较数值大小
		  return count_a < count_b; // 否则比较bit中1数量大小
		});

		return arr;
	}
};

int main()
{
	Solution solution;
	vector<int> nums, ret;

	{
		cout << "exp1 ([2,3,5,17,7,11,13,19]): ";
		nums = { 2, 3, 5, 7, 11, 13, 17, 19 };
		ret = solution.sortByBits(nums);
		cout << "[ ";
		for (auto i : ret)
		{
			cout << i << " ";
		}
		cout << "]" << endl;
	}
}
