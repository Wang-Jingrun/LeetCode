/*
 * 347. 前 K 个高频元素	url: https://leetcode.cn/problems/top-k-frequent-elements/
 *
 * 题目描述：给你一个整数数组 nums 和一个整数 k ，
 * 请你返回其中出现频率前 k 高的元素。你可以按 任意顺序 返回答案。
 * */

#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

class Solution
{
 public:
	vector<int> topKFrequent(vector<int>& nums, int k)
	{
		unordered_map<int, int> map;
		vector<int> result;

		for (auto num : nums)
		{
			map[num]++;
		}

		int count = 0;
		int num;
		for (int i = 0; i < k; i++)
		{
			for (auto& item : map)
			{
				if (item.second > count)
				{
					num = item.first;
					count = item.second;
				}
			}

			result.push_back(num);
			map.erase(num);
			count = 0;
		}
		return result;
	}
};

// 小顶堆
class mycomparison
{
 public:
	bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs)
	{
		return lhs.second > rhs.second;
	}
};

class Solution2
{
 public:
	vector<int> topKFrequent(vector<int>& nums, int k)
	{
		// 统计元素出现频率
		unordered_map<int, int> map;
		for (auto num : nums)
		{
			map[num]++;
		}

		// 对频率排序
		// 定义一个小顶堆，大小为k
		priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;

		// 用固定大小为k的小顶堆，扫面所有频率的数值
		for (auto& it : map)
		{
			pri_que.push(it);
			if (pri_que.size() > k)
			{ // 如果堆的大小大于了K，则队列弹出，保证堆的大小一直为k
				pri_que.pop();
			}
		}

		// 找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒序来输出到数组
		vector<int> result(k);
		for (int i = k - 1; i >= 0; i--)
		{
			result[i] = pri_que.top().first;
			pri_que.pop();
		}
		return result;
	}
};

int main()
{
	Solution solution;
	vector<int> nums, ret;

	cout << "exp1 ([1, 2]): ";
	nums = { 1, 1, 1, 2, 2, 3 };
	ret = solution.topKFrequent(nums, 2);
	cout << "[ ";
	for (auto i : ret)
	{
		cout << i << " ";
	}
	cout << "]" << endl;

	cout << "exp2 ([1]): ";
	nums = { 1 };
	ret = solution.topKFrequent(nums, 1);
	cout << "[ ";
	for (auto i : ret)
	{
		cout << i << " ";
	}
	cout << "]" << endl;

	cout << "exp2 ([0]): ";
	nums = { 3, 0, 1, 0 };
	ret = solution.topKFrequent(nums, 1);
	cout << "[ ";
	for (auto i : ret)
	{
		cout << i << " ";
	}
	cout << "]" << endl;
}