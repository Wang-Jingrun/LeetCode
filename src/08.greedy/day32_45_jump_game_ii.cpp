/*
 * 45. 跳跃游戏 II		url: https://leetcode.cn/problems/jump-game-ii/
 *
 * 题目描述：给定一个长度为 n 的 0 索引整数数组 nums。初始位置为 nums[0]。
 * 每个元素 nums[i] 表示从索引 i 向前跳转的最大长度。换句话说，如果你在 nums[i] 处，你可以跳转到任意 nums[i + j] 处:
 * 	0 <= j <= nums[i]
 * 	i + j < n
 * 	返回到达 nums[n - 1] 的最小跳跃次数。生成的测试用例可以到达 nums[n - 1]。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution {
 public:
	int jump(vector<int>& nums) {
		if (nums.size() == 1) return 0;
		int curDistance = 0;    // 当前覆盖最远距离下标
		int ans = 0;            // 记录走的最大步数
		int nextDistance = 0;   // 下一步覆盖最远距离下标
		for (int i = 0; i < nums.size(); i++) {
			nextDistance = max(nums[i] + i, nextDistance);  // 更新下一步覆盖最远距离下标
			if (i == curDistance) {                         // 遇到当前覆盖最远距离下标
				ans++;                                  // 需要走下一步
				curDistance = nextDistance;             // 更新当前覆盖最远距离下标（相当于加油了）
				if (nextDistance >= nums.size() - 1) break;  // 当前覆盖最远距到达集合终点，不用做ans++操作了，直接结束
			}
		}
		return ans;
	}
};

int main()
{
	Solution solution;
	vector<int> prices;

	cout << "exp1 (2): ";
	prices = { 2, 3, 1, 1, 4 };
	cout << solution.jump(prices) << endl;

	cout << "exp2 (2): ";
	prices = { 2, 3, 0, 1, 4 };
	cout << solution.jump(prices) << endl;

	cout << "exp3 (0): ";
	prices = { 0 };
	cout << solution.jump(prices) << endl;

}
