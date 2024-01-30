/*
 * 406. 根据身高重建队列		url: https://leetcode.cn/problems/queue-reconstruction-by-height/
 *
 * 题目描述：假设有打乱顺序的一群人站成一个队列，数组 people 表示队列中一些人的属性（不一定按顺序）。
 * 每个 people[i] = [hi, ki] 表示第 i 个人的身高为 hi ，前面 正好 有 ki 个身高大于或等于 hi 的人。
 * 请你重新构造并返回输入数组 people 所表示的队列。返回的队列应该格式化为数组 queue ，
 * 其中 queue[j] = [hj, kj] 是队列中第 j 个人的属性（queue[0] 是排在队列前面的人）。
 * */

#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

class Solution
{
	static bool cmp(const vector<int>& a, const vector<int>& b)
	{
		if (a[0] > b[0])
			return true;
		else if (a[0] == b[0] && a[1] < b[1])
			return true;

		return false;
	}

 public:
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people)
	{
		sort(people.begin(), people.end(), cmp);
		vector<vector<int>> result;

		// 题目数据确保队列可以被重建, 所以最大的数必定是 [max, 0]
		for (int i = 0; i < people.size(); i++)
		{
			result.insert(result.begin() + people[i][1], people[i]);
		}

		return result;
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> people;

	{
		people = {{ 7, 0 }, { 4, 4 }, { 7, 1 }, { 5, 0 }, { 6, 1 }, { 5, 2 }};
		cout << "exp1 ([[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]): " << endl;

		auto result = solution.reconstructQueue(people);
		cout << "result: [";
		for (const auto& nums : result)
		{
			cout << "[ ";
			for (auto num : nums)
			{
				cout << num << " ";
			}
			cout << "]";
		}
		cout << "]" << endl;
	}

	cout << endl;

	{
		people = {{ 9, 0 }, { 7, 0 }, { 1, 9 }, { 3, 0 }, { 2, 7 }, { 5, 3 }, { 6, 0 }, { 3, 4 }, { 6, 2 }, { 5, 2 }};
		cout << "exp2 ([[3,0],[6,0],[7,0],[5,2],[3,4],[5,3],[6,2],[2,7],[9,0],[1,9]]): " << endl;

		auto result = solution.reconstructQueue(people);
		cout << "result: [";
		for (const auto& nums : result)
		{
			cout << "[ ";
			for (auto num : nums)
			{
				cout << num << " ";
			}
			cout << "]";
		}
		cout << "]" << endl;
	}
}
