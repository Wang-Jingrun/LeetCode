/*
 * 797. 所有可能的路径		url: https://leetcode.cn/problems/all-paths-from-source-to-target/
 *
 * 题目描述：给你一个有 n 个节点的 有向无环图（DAG），
 * 请你找出所有从节点 0 到节点 n-1 的路径并输出（不要求按特定顺序）
 * graph[i] 是一个从节点 i 可以访问的所有节点的列表（即从节点 i 到节点 graph[i][j]存在一条有向边）。
 * */

#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Solution
{
 private:
	vector<vector<int>> result; // 收集符合条件的路径
	vector<int> path; // 0节点到终点的路径
	// nodeIndex：目前遍历的节点
	// graph：存当前的图
	void dfs(vector<vector<int>>& graph, int nodeIndex)
	{
		// 要求从节点 0 到节点 n-1 的路径并输出，所以是 graph.size() - 1
		if (nodeIndex == graph.size() - 1)
		{
			result.push_back(path);
			return;
		}

		for (int i = 0; i < graph[nodeIndex].size(); i++) // 遍历节点链接的所有节点
		{
			path.push_back(graph[nodeIndex][i]); // 遍历到的节点加入到路径中来
			dfs(graph, graph[nodeIndex][i]); // 进入下一层递归
			path.pop_back();
		}
	}

 public:
	vector<vector<int>> allPathsSourceTarget(vector<vector<int>>& graph)
	{
		result.clear();
		path.clear();
		path.push_back(0);
		dfs(graph, 0);
		return result;
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> graph;

	{
		graph = {{ 4, 3, 1 }, { 3, 2, 4 }, { 3 }, { 4 }, {}};
		cout << "exp1 ([[0,4],[0,3,4],[0,1,3,4],[0,1,2,3,4],[0,1,4]]): " << endl;
		cout << "result: [";
		auto result = solution.allPathsSourceTarget(graph);
		for (auto& nums : result)
		{
			cout << "[ ";
			for (auto num : nums)
			{
				cout << num << " ";
			}
			cout << "]";
		}
		cout << "]";
	}
}
