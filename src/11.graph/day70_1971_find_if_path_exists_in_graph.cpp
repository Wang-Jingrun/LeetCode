/*
 * 1971. 寻找图中是否存在路径	url: https://leetcode.cn/problems/find-if-path-exists-in-graph/
 *
 * 题目描述：有一个具有 n 个顶点的 双向 图，其中每个顶点标记从 0 到 n - 1（包含 0 和 n - 1）。
 * 图中的边用一个二维整数数组 edges 表示，其中 edges[i] = [ui, vi] 表示顶点 ui 和顶点 vi 之
 * 间的双向边。 每个顶点对由 最多一条 边连接，并且没有顶点存在与自身相连的边。
 *
 * 请你确定是否存在从顶点 source 开始，到顶点 destination 结束的 有效路径 。
 *
 * 给你数组 edges 和整数 n、source 和 destination，如果从 source 到 destination 存在 有效
 * 路径 ，则返回 true，否则返回 false 。
 * */

#include <iostream>
#include <union_set.h>
using namespace std;

class Solution
{
 public:
	bool validPath(int n, vector<vector<int>>& edges, int source, int destination)
	{
		UnionSet uset(n);
		for (int i = 0; i < edges.size(); i++)
		{
			uset.join(edges[i][0], edges[i][1]);
		}
		return uset.isSame(source, destination);
	}
};

// LeetCode 提交的版本
class Solution2
{
 private:
	vector<int> father;

	void init(int n)
	{
		father.clear();
		father.resize(n);

		// 并查集初始化
		for (int i = 0; i < n; i++)
		{
			father[i] = i;
		}
	}

	// 查找根节点
	int find(int u)
	{
		return u == father[u] ? u : father[u] = find(father[u]);
	}

	bool isSame(int u, int v)
	{
		return find(u) == find(v);
	}

	void join(int u, int v)
	{
		u = find(u);
		v = find(v);
		if (u == v) return;
		father[v] = u;
	}

 public:
	bool validPath(int n, vector<vector<int>>& edges, int source, int destination)
	{
		init(n);
		for (int i = 0; i < edges.size(); i++)
		{
			join(edges[i][0], edges[i][1]);
		}
		return isSame(source, destination);
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> edges;

	{
		edges = {{ 0, 1 }, { 1, 2 }, { 2, 0 }};
		cout << "exp1 (true): " << endl;
		cout << "result: " << solution.validPath(3, edges, 0, 2) << endl;
	}

	{
		edges = {{ 0, 1 }, { 0, 2 }, { 3, 5 }, { 5, 4 }, { 4, 3 }};
		cout << "exp2 (false): " << endl;
		cout << "result: " << solution.validPath(6, edges, 0, 5) << endl;
	}
}
