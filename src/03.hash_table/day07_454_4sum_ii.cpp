/*
 * 454. 四数相加 II	url: https://leetcode.cn/problems/4sum-ii/
 *
 * 题目描述：给你四个整数数组 nums1、nums2、nums3 和 nums4 ，数组长度都是 n ，
 * 请你计算有多少个元组 (i, j, k, l) 能满足：
 * 			0 <= i, j, k, l < n
 * 			nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0
 * */

#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

class Solution
{
 public:
	int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4)
	{
		unordered_map<int, int> hash;
		int count = 0;

		for (int num1 : nums1)
		{
			for (int num2 : nums2)
			{
				// 默认创建的值为 0，直接 ++ 即可
				hash[num1 + num2]++;
			}
		}

		for (int num3 : nums3)
		{
			for (int num4 : nums4)
			{
				if (hash.find(0 - (num3 + num4)) != hash.end())
					count += hash[0 - (num3 + num4)];
			}
		}

		return count;
	}
};

int main()
{
	Solution solution;
	vector<int> nums1, nums2, nums3, nums4;

	cout << "exp1 (6): ";
	nums1 = { -1, -1 };
	nums2 = { -1, 1 };
	nums3 = { -1, 1 };
	nums4 = { 1, -1 };
	cout << solution.fourSumCount(nums1, nums2, nums3, nums4) << endl;
}