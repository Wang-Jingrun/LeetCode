/*
 * 55. 跳跃游戏	url: https://leetcode.cn/problems/jump-game/
 *
 * 题目描述：给你一个非负整数数组 nums ，你最初位于数组的 第一个下标 。
 * 数组中的每个元素代表你在该位置可以跳跃的最大长度。
 * 断你是否能够到达最后一个下标，如果可以，返回 true ；否则，返回 false 。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
 public:
	bool canJump(vector<int>& nums)
	{
		int count = 0;    // 记录当前还能往后走的步数
		for (int i = 0; i < nums.size(); i++)
		{
			// 更新当前能走的步数
			count = max(nums[i], count);

			// 不是终点位置，但是还能走的步数为 0，表示已经无法走到终点了
			if (count == 0 && i != nums.size() - 1) return false;
			// 向后移动一格
			count--;
		}

		return true;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	cout << "exp1 (1): ";
	nums = { 2, 3, 1, 1, 4 };
	cout << solution.canJump(nums) << endl;

	cout << "exp2 (0): ";
	nums = { 3, 2, 1, 0, 4 };
	cout << solution.canJump(nums) << endl;

	cout << "exp3 (1): ";
	nums = { 0 };
	cout << solution.canJump(nums) << endl;

}
