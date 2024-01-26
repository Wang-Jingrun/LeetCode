/*
 * 332. 重新安排行程	url: https://leetcode.cn/problems/reconstruct-itinerary/
 *
 * 题目描述：给你一份航线列表 tickets ，其中 tickets[i] = [fromi, toi]
 * 表示飞机出发和降落的机场地点。请你对该行程进行重新规划排序。
 * 所有这些机票都属于一个从 JFK（肯尼迪国际机场）出发的先生，所以该行程必须从 JFK 开始。
 * 如果存在多种有效的行程，请你按字典排序返回最小的行程组合。
 * 例如，行程 ["JFK", "LGA"] 与 ["JFK", "LGB"] 相比就更小，排序更靠前。
 * 假定所有机票至少存在一种合理的行程。且所有的机票 必须都用一次 且 只能用一次。
 * */

#include <iostream>
#include <vector>
#include <map>
#include <unordered_map>
using namespace std;

class Solution
{
 private:
	// unordered_map<出发机场, map<到达机场, 航班次数>> targets
	unordered_map<string, map<string, int>> targets;
	bool backtracking(int ticketNum, vector<string>& result)
	{
		if (result.size() == ticketNum + 1)
		{
			return true;
		}

		for (pair<const string, int>& target : targets[result.back()])
		{
			if (target.second > 0)
			{
				// 记录到达机场是否飞过了
				result.push_back(target.first);
				target.second--;
				if (backtracking(ticketNum, result)) return true;
				result.pop_back();
				target.second++;
			}
		}
		return false;
	}
 public:
	vector<string> findItinerary(vector<vector<string>>& tickets)
	{
		targets.clear();
		vector<string> result;
		for (const vector<string>& vec : tickets)
		{
			targets[vec[0]][vec[1]]++; // 记录映射关系
		}
		result.push_back("JFK"); // 起始机场
		backtracking(tickets.size(), result);
		return result;
	}
};

int main()
{

	Solution solution;
	vector<vector<string>> input;
	{
		cout << R"(exp1 (["JFK","ATL","JFK","SFO","ATL","SFO"]): )" << endl;

		cout << "result: ";
		input = {{ "JFK", "SFO" }, { "JFK", "ATL" }, { "SFO", "ATL" }, { "ATL", "JFK" }, { "ATL", "SFO" }};
		auto result = solution.findItinerary(input);
		cout << "[";
		for (const auto& ip : result)
		{
			cout << ip << " ";
		}
		cout << "]" << endl;
	}

	cout << endl;

	return 0;
}