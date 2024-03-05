/*
 * 684. 冗余连接		url: https://leetcode.cn/problems/redundant-connection/
 *
 * 题目描述：树可以看成是一个连通且 无环 的 无向 图。
 *
 * 给定往一棵 n 个节点 (节点值 1～n) 的树中添加一条边后的图。
 * 添加的边的两个顶点包含在 1 到 n 中间，且这条附加的边不属于
 * 树中已存在的边。图的信息记录于长度为 n 的二维数组 edges ，
 * edges[i] = [ai, bi] 表示图中在 ai 和 bi 之间存在一条边。
 *
 * 请找出一条可以删去的边，删除后可使得剩余部分是一个有着 n 个
 * 节点的树。如果有多个答案，则返回数组 edges 中最后出现的那个。
 * */

#include <iostream>
#include <union_set.h>
using namespace std;

class Solution
{
 public:
	vector<int> findRedundantConnection(vector<vector<int>>& edges)
	{
		vector<int> result;
		UnionSet uset(edges.size() + 1);
		for (int i = 0; i < edges.size(); i++)
		{
			if (uset.isSame(edges[i][0], edges[i][1]))
				return edges[i];
			uset.join(edges[i][0], edges[i][1]);
		}
		return {};
	}
};

class Solution2
{
 private:
	vector<int> father;

	void init(int n)
	{
		father.clear();
		father.resize(n);
		for (int i = 0; i < father.size(); i++)
		{
			father[i] = i;
		}
	}

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
	vector<int> findRedundantConnection(vector<vector<int>>& edges)
	{
		vector<int> result;
		init(edges.size() + 1);
		for (int i = 0; i < edges.size(); i++)
		{
			if (isSame(edges[i][0], edges[i][1]))
				return edges[i];
			join(edges[i][0], edges[i][1]);
		}
		return {};
	}
};

int main()
{
	Solution solution;
	vector<vector<int>> edges;

	{
		edges = {{ 1, 2 }, { 1, 3 }, { 2, 3 }};
		cout << "exp1 ([2, 3]): " << endl;
		auto result = solution.findRedundantConnection(edges);
		cout << "result: [" << result[0] << ", " << result[1] << "]" << endl;
	}

	{
		edges = {{ 1, 2 }, { 2, 3 }, { 3, 4 }, { 1, 4 }, { 1, 5 }};
		cout << "exp1 ([1, 4]): " << endl;
		auto result = solution.findRedundantConnection(edges);
		cout << "result: [" << result[0] << ", " << result[1] << "]" << endl;
	}
}
