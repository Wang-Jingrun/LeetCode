## Day36: 贪心算法part05

### 435. 无重叠区间

[LeetCode](https://leetcode.cn/problems/non-overlapping-intervals/)  [文章讲解](https://programmercarl.com/0435.%E6%97%A0%E9%87%8D%E5%8F%A0%E5%8C%BA%E9%97%B4.html)  [视频讲解](https://www.bilibili.com/video/BV1A14y1c7E1/)

#### 题目描述：

给定一个区间的集合 `intervals` ，其中 `intervals[i] = [starti, endi]` 。返回 *需要移除区间的最小数量，使剩余区间互不重叠* 。

**示例 1:**

> 输入: intervals = [[1,2],[2,3],[3,4],[1,3]]
> 输出: 1
> 解释: 移除 [1,3] 后，剩下的区间没有重叠。

**示例 2:**

> 输入: intervals = [ [1,2], [1,2], [1,2] ]
> 输出: 2
> 解释: 你需要移除两个 [1,2] 来使剩下的区间没有重叠。

**示例 3:**

> 输入: intervals = [ [1,2], [2,3] ]
> 输出: 0
> 解释: 你不需要移除任何区间，因为它们已经是无重叠的了。

#### 我的解法：

每次发生重叠，`result`的计数加1，同时移除范围相对更大的区间，即等价移除最少得区间。

```C++
class Solution
{
 public:
	static bool cmp(const vector<int>& a, const vector<int>& b)
	{
		return a[0] < b[0];
	}

	int eraseOverlapIntervals(vector<vector<int>>& intervals)
	{
		// 排序，使得重叠的区间在一起
		sort(intervals.begin(), intervals.end(), cmp);

		int result = 0;
		int right = intervals[0][1];
		for (int i = 1; i < intervals.size(); i++)
		{
			if (intervals[i][0] < right)
			{
				// 有重叠，计数加 1
				result++;
				// 移除范围更大的区间，即等价于移除最少得区间
				// 更新区间
				right = min(right, intervals[i][1]);
			}
			else
			{
				// 没有重叠，更新区间
				right = intervals[i][1];
			}

		}
		return result;
	}
};
```

### 763. 划分字母区间

[LeetCode](https://leetcode.cn/problems/partition-labels/)  [文章讲解](https://programmercarl.com/0763.%E5%88%92%E5%88%86%E5%AD%97%E6%AF%8D%E5%8C%BA%E9%97%B4.html)  [视频讲解](https://www.bilibili.com/video/BV18G4y1K7d5/)

#### 题目描述：

给你一个字符串 `s` 。我们要把这个字符串划分为尽可能多的片段，同一字母最多出现在一个片段中。

注意，划分结果需要满足：将所有划分结果按顺序连接，得到的字符串仍然是 `s` 。

返回一个表示每个字符串片段的长度的列表。

**示例 1：**

> 输入：s = "ababcbacadefegdehijhklij"
> 输出：[9,7,8]
> 解释：
> 划分结果为 "ababcbaca"、"defegde"、"hijhklij" 。
> 每个字母最多出现在一个片段中。
> 像 "ababcbacadefegde", "hijhklij" 这样的划分是错误的，因为划分的片段数较少。 

**示例 2：**

> 输入：s = "eccbbbbdec"
> 输出：[10]

#### 我的解法：

分为如下两步：

- 统计每一个字符最后出现的位置
- 从头遍历字符，并更新字符的最远出现下标，如果找到字符最远出现位置下标和当前下标相等了，则找到了分割点

![763.划分字母区间](imgs/20201222191924417.png)

```C++
class Solution
{
 public:
	vector<int> partitionLabels(const string& s)
	{
		vector<int> result;
		unordered_map<char, int> m; // 可以使用数组，效率更高

		// 统计区间，记录每个字符出现的最大下标
		for (int i = 0; i < s.size(); i++)
		{
			m[s[i]] = i;
		}

		// 遍历寻找重叠的区间
		int right = INT_MIN;
		int start = 0;
		for (int i = 0; i < s.size(); i++)
		{
			// 每次遍历，更新所需要达到的最大下标
			auto pos = m.find(s[i]);
			right = max(right, pos->second);

			// 当前区间满足要求，同一字母均出现在该片段
			if (right == i)
			{
				// 记录结果
				result.push_back(i + 1 - start);
				start = i + 1;
			}
		}

		return result;
	}
};
```

### 56. 合并区间

[LeetCode](https://leetcode.cn/problems/merge-intervals/)  [文章讲解](https://programmercarl.com/0056.%E5%90%88%E5%B9%B6%E5%8C%BA%E9%97%B4.html)  [视频讲解](https://www.bilibili.com/video/BV1wx4y157nD/)

#### 题目描述：

以数组 `intervals` 表示若干个区间的集合，其中单个区间为 `intervals[i] = [starti, endi]` 。请你合并所有重叠的区间，并返回 *一个不重叠的区间数组，该数组需恰好覆盖输入中的所有区间* 。

**示例 1：**

> 输入：intervals = [[1,3],[2,6],[8,10],[15,18]]
> 输出：[[1,6],[8,10],[15,18]]
> 解释：区间 [1,3] 和 [2,6] 重叠, 将它们合并为 [1,6].

**示例 2：**

> 输入：intervals = [[1,4],[4,5]]
> 输出：[[1,5]]
> 解释：区间 [1,4] 和 [4,5] 可被视为重叠区间。

#### 我的解法：

```C++
class Solution
{
 public:
	static bool cmp(const vector<int>& a, const vector<int>& b)
	{
		return a[0] < b[0];
	}

	vector<vector<int>> merge(vector<vector<int>>& intervals)
	{
		// 排序，使得重叠的区间在一起
		sort(intervals.begin(), intervals.end(), cmp);

		vector<vector<int>> result;

		int right;
		for (int i = 0; i < intervals.size();i++)
		{
			result.push_back({ intervals[i][0], intervals[i][1] });
			right = result.back()[1];

			// i == 0 强制进行去重
			// 有重叠，取到不重叠为止
			if (intervals[i][0] <= right || i == 0)
			{
				result.pop_back();

				int left = intervals[i][0];
				while (i < intervals.size() && intervals[i][0] <= right)
				{
					right = max(right, intervals[i][1]);
					i++;
				}

				// 记录结果
				result.push_back({ left, right });
				i--;	// for 循环中 带有 i++，此处需要回退
			}
		}

		return result;
	}
};
```

### 今日总结

三道题目都AC了。
