/*
 * 503. 下一个更大元素 II		url: https://leetcode.cn/problems/next-greater-element-ii/
 *
 * 题目描述：给定一个循环数组 nums （ nums[nums.length - 1] 的下一个元素是 nums[0] ），
 * 返回 nums 中每个元素的 下一个更大元素 。
 * 数字 x 的 下一个更大的元素 是按数组遍历顺序，这个数字之后的第一个比它更大的数，这意味着你应
 * 该循环地搜索它的下一个更大的数。如果不存在，则输出 -1 。
 * */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution
{
 public:
	vector<int> nextGreaterElements(vector<int>& nums)
	{
		vector<int> result(nums.size(), -1);
		stack<int> st;
		st.push(0);
		// 模拟走了两边nums
		for (int i = 0; i < nums.size() * 2; i++)
		{
			while (!st.empty() && nums[i % nums.size()] > nums[st.top()])
			{
				result[st.top()] = nums[i % nums.size()];
				st.pop();
			}
			st.push(i % nums.size());
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> nums;

	{
		nums = { 1, 2, 3, 4, 3 };
		cout << "exp1 ([2,3,4,-1,4]): " << endl;
		cout << "result: [ ";
		auto result = solution.nextGreaterElements(nums);
		for (auto num : result)
		{
			cout << num << " ";
		}
		cout << "]" << endl;
	}
}
