/*
 * 704.二分查找	url: https://leetcode.cn/problems/binary-search/
 *
 * 题目描述：给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target ，
 * 写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。
 * */

#include <iostream>
#include <vector>
using namespace std;

class MySolution
{
 public:
	int search(vector<int>& nums, int target)
	{
		int left = 0;
		int right = (int)nums.size() - 1;
		int mid = 0;

		while (true)
		{
			mid = (left + right) / 2;

			if (target > nums[mid])
				left = mid;
			else if (target < nums[mid])
				right = mid;
			else
				return mid;

			if ((right - left <= 1) && mid == left)
			{
				if (target != nums[right])
					return -1;
				else
					return right;
			}
		}
	}
};

class Solution1    // [left, right]
{
 public:
	int search(vector<int>& nums, int target)
	{
		int left = 0;
		int right = (int)nums.size() - 1;  // 遵从右闭
		int mid = 0;

		// 遵从左闭右闭，left == right 时，[left, right] 是有效区间
		while (left <= right)
		{
			mid = (left + right) / 2;

			if (target < nums[mid])
				// mid 被判断过，但是由于遵从左闭，right = mid - 1
				right = mid - 1;
			else if (target > nums[mid])
				// mid 被判断过，但是由于遵从左闭，right = mid - 1
				left = mid + 1;
			else
				return mid;
		}
		return -1;
	}
};

class Solution2    // [left, right)
{
 public:
	int search(vector<int>& nums, int target)
	{
		int left = 0;
		int right = (int)nums.size();  // 遵从右开，包含更大一些的范围
		int mid = 0;

		// 遵从左闭右开，left == right 时，[left, right) 是无效区间，因此是 left < right
		while (left < right)
		{
			mid = (left + right) / 2;

			if (target < nums[mid])
				// 虽然 mid 被判断过，但是由于遵从右开，right = mid，需要包含的范围大一些
				right = mid;
			else if (target > nums[mid])
				// mid 被判断过，但是由于遵从左闭，left = mid + 1
				left = mid + 1;
			else
				return mid;
		}
		return -1;
	}
};

int main()
{
	Solution2 solution;
	vector<int> cost;

	cout << "exp1 (4): ";
	cost = { -1, 0, 3, 5, 9, 12 };
	cout << solution.search(cost, 9) << endl;

	cout << "exp2 (-1): ";
	cout << solution.search(cost, 2) << endl;

	cout << "exp3 (0): ";
	cost = { 2, 5 };
	cout << solution.search(cost, 2) << endl;

	cout << "exp4 (1): ";
	cout << solution.search(cost, 5) << endl;

	cout << "exp5 (-1): ";
	cost = { -1, 0, 3, 5, 9, 12 };
	cout << solution.search(cost, 2) << endl;

	cout << "exp6 (0): ";
	cost = { -1, 0, 5 };
	cout << solution.search(cost, -1) << endl;
}