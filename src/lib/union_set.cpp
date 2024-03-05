#include <union_set.h>

UnionSet::UnionSet(int n)
{
	m_father.resize(n);

	// 并查集初始化
	for (int i = 0; i < m_father.size(); i++)
	{
		m_father[i] = i;
	}
}

int UnionSet::size() const
{
	return m_father.size();
}

int UnionSet::father(int u) const
{
	return m_father[u];
}

// 并查集里寻根的过程
int UnionSet::find(int u)
{
	return u == m_father[u] ? u : m_father[u] = find(m_father[u]); // 压缩路径
}

// 判断 u 和 v是否找到同一个根
bool UnionSet::isSame(int u, int v)
{
	return find(u) == find(v);
}

// 将v->u 这条边加入并查集
void UnionSet::join(int u, int v)
{
	u = find(u); // 寻找u的根
	v = find(v); // 寻找v的根
	if (u == v) return; // 如果发现根相同，则说明在一个集合，不用两个节点相连直接返回
	m_father[v] = u;
}
