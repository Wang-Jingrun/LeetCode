/*
 * 377. 组合总和 Ⅳ		url: https://leetcode.cn/problems/combination-sum-iv/
 *
 * 题目描述：给你一个由 不同 整数组成的数组 nums ，和一个目标整数 target 。
 * 请你从 nums 中找出并返回总和为 target 的元素组合的个数。
 * 题目数据保证答案符合 32 位整数范围。
 * */

#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

class Solution
{
 public:
	int result = 0;

	void backtracking(vector<int>& nums, int target, int sum)
	{
		if (sum > target) return;
		if (sum == target)
		{
			result++;
			return;
		}

		for (int i = 0; i < nums.size(); i++)
		{
			backtracking(nums, target, sum + nums[i]);
		}
	}

	int combinationSum4(vector<int>& nums, int target)
	{
		result = 0;
		backtracking(nums, target, 0);
		return result;
	}
};

class Solution2
{
 public:
	int combinationSum4(vector<int>& nums, int target)
	{
		vector<int> dp(target + 1);
		dp[0] = 1;

		for (int j = 1; j <= target; j++)
		{
			for (int i = 0; i < nums.size(); i++)
			{
				if (j - nums[i] >= 0 && dp[j] < INT_MAX - dp[j - nums[i]])
					dp[j] += dp[j - nums[i]];
			}
		}
		return dp[target];
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums;

	{
		nums = { 1, 2, 3 };
		cout << "exp1 (7): " << endl;
		cout << "result: " << solution.combinationSum4(nums, 4) << endl;
	}

	{
		nums = { 1, 2, 3 };
		cout << "exp2 (181997601): " << endl;
		cout << "result: " << solution.combinationSum4(nums, 32) << endl;
	}

	{
		nums =
			{ 10, 20, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 180, 190, 200, 210, 220, 230,
			  240, 250, 260, 270, 280, 290, 300, 310, 320, 330, 340, 350, 360, 370, 380, 390, 400, 410, 420, 430, 440,
			  450, 460, 470, 480, 490, 500, 510, 520, 530, 540, 550, 560, 570, 580, 590, 600, 610, 620, 630, 640, 650,
			  660, 670, 680, 690, 700, 710, 720, 730, 740, 750, 760, 770, 780, 790, 800, 810, 820, 830, 840, 850, 860,
			  870, 880, 890, 900, 910, 920, 930, 940, 950, 960, 970, 980, 990, 111 };
		cout << "exp3 (1): " << endl;
		cout << "result: " << solution.combinationSum4(nums, 999) << endl;
	}
}

