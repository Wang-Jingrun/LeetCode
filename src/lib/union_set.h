#pragma once
#include <vector>
using std::vector;

class UnionSet
{
 public:
	UnionSet(int n);
	~UnionSet() = default;

	int size() const;               // 返回 m_father 数组的大小
	int father(int u) const;        // 返回 u 的根节点
	int find(int u);                // 并查集里寻根的过程
	bool isSame(int u, int v);      // 判断 u 和 v是否找到同一个根
	void join(int u, int v);        // 将v->u 这条边加入并查集

 private:
	vector<int> m_father;
};

