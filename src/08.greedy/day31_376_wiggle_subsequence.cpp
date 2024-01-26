/*
 * 376. 摆动序列		url: https://leetcode.cn/problems/wiggle-subsequence/
 *
 * 题目描述：如果连续数字之间的差严格地在正数和负数之间交替，则数字序列称为 摆动序列 。
 * 第一个差（如果存在的话）可能是正数或负数。仅有一个元素或者含两个不等元素的序列也视作摆动序列。
 * 	例如， [1, 7, 4, 9, 2, 5] 是一个 摆动序列 ，因为差值 (6, -3, 5, -7, 3) 是正负交替出现的。
 * 	相反，[1, 4, 7, 2, 5] 和 [1, 7, 4, 5, 5] 不是摆动序列，第一个序列是因为它的前两个差值都是正数，
 * 	第二个序列是因为它的最后一个差值为零。
 * 子序列 可以通过从原始序列中删除一些（也可以不删除）元素来获得，剩下的元素保持其原始顺序。
 * 给你一个整数数组 nums ，返回 nums 中作为 摆动序列 的 最长子序列的长度 。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
 public:
	int wiggleMaxLength(vector<int>& nums) {
		if (nums.size() <= 1) return nums.size();
		int curDiff = 0; // 当前一对差值
		int preDiff = 0; // 前一对差值
		int result = 1;  // 记录峰值个数，序列默认序列最右边有一个峰值
		for (int i = 0; i < nums.size() - 1; i++) {
			curDiff = nums[i + 1] - nums[i];
			// 出现峰值
			if ((preDiff <= 0 && curDiff > 0) || (preDiff >= 0 && curDiff < 0)) {
				result++;
				preDiff = curDiff; // 注意这里，只在摆动变化的时候更新prediff
			}
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	cout << "exp1 (7): ";
	nums = { 1,17,5,10,13,15,10,5,16,8 };
	cout << solution.wiggleMaxLength(nums) << endl;

}
