/*
 * 496. 下一个更大元素 I		url: https://leetcode.cn/problems/next-greater-element-i/
 *
 * 题目描述：nums1 中数字 x 的 下一个更大元素 是指 x 在 nums2 中对应位置 右侧 的 第一个 比 x 大的元素。
 * 给你两个 没有重复元素 的数组 nums1 和 nums2 ，下标从 0 开始计数，其中nums1 是 nums2 的子集。
 * 对于每个 0 <= i < nums1.length ，找出满足 nums1[i] == nums2[j] 的下标 j ，并且在 nums2 确定
 * nums2[j] 的 下一个更大元素 。如果不存在下一个更大元素，那么本次查询的答案是 -1 。
 *
 * 返回一个长度为 nums1.length 的数组 ans 作为答案，满足 ans[i] 是如上所述的 下一个更大元素 。
 * */

#include <iostream>
#include <vector>
#include <stack>
#include <unordered_map>
using namespace std;

class Solution
{
 public:
	vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2)
	{
		vector<int> result(nums1.size(), -1);
		stack<int> st;
		st.push(0);
		for (int i = 1; i < nums2.size(); i++)
		{
			while (!st.empty() && nums2[i] > nums2[st.top()])
			{
				for (int j = 0; j < nums1.size(); j++)
				{
					if (nums1[j] == nums2[st.top()])
					{
						result[j] = nums2[i];
						break;
					}
				}
				st.pop();
			}
			st.push(i);
		}
		return result;
	}
};

class Solution2
{
 public:
	vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2)
	{
		unordered_map<int, int> umap; // key:下标元素，value：下标
		for (int i = 0; i < nums1.size(); i++)
			umap[nums1[i]] = i;

		vector<int> result(nums1.size(), -1);
		stack<int> st;
		st.push(0);
		for (int i = 1; i < nums2.size(); i++)
		{
			while (!st.empty() && nums2[i] > nums2[st.top()])
			{
				// 看map里是否存在这个元素
				if (umap.find(nums2[st.top()])!=umap.end())
				{
					// 根据map找到nums2[st.top()] 在 nums1中的下标
					result[umap[nums2[st.top()]]] = nums2[i];
				}
				st.pop();
			}
			st.push(i);
		}
		return result;
	}
};

int main()
{
	Solution2 solution;
	vector<int> nums1;
	vector<int> nums2;

	{
		nums1 = { 4, 1, 2 };
		nums2 = { 1, 3, 4, 2 };
		cout << "exp1 ([-1,3,-1]): " << endl;
		cout << "result: [ ";
		auto result = solution.nextGreaterElement(nums1, nums2);
		for (auto num : result)
		{
			cout << num << " ";
		}
		cout << "]" << endl;
	}
}
