## Day35: 贪心算法part04

### 860.柠檬水找零

[LeetCode](https://leetcode.cn/problems/lemonade-change/)  [文章讲解](https://programmercarl.com/0860.%E6%9F%A0%E6%AA%AC%E6%B0%B4%E6%89%BE%E9%9B%B6.html)  [视频讲解](https://www.bilibili.com/video/BV12x4y1j7DD/)

#### 题目描述：

在柠檬水摊上，每一杯柠檬水的售价为 `5` 美元。顾客排队购买你的产品，（按账单 `bills` 支付的顺序）一次购买一杯。

每位顾客只买一杯柠檬水，然后向你付 `5` 美元、`10` 美元或 `20` 美元。你必须给每个顾客正确找零，也就是说净交易是每位顾客向你支付 `5` 美元。

注意，一开始你手头没有任何零钱。

给你一个整数数组 `bills` ，其中 `bills[i]` 是第 `i` 位顾客付的账。如果你能给每位顾客正确找零，返回 `true` ，否则返回 `false` 。

**示例 1：**

> 输入：bills = [5,5,5,10,20]
> 输出：true
> 解释：
> 前 3 位顾客那里，我们按顺序收取 3 张 5 美元的钞票。
> 第 4 位顾客那里，我们收取一张 10 美元的钞票，并返还 5 美元。
> 第 5 位顾客那里，我们找还一张 10 美元的钞票和一张 5 美元的钞票。
> 由于所有客户都得到了正确的找零，所以我们输出 true。

**示例 2：**

> 输入：bills = [5,5,10,10,20]
> 输出：false
> 解释：
> 前 2 位顾客那里，我们按顺序收取 2 张 5 美元的钞票。
> 对于接下来的 2 位顾客，我们收取一张 10 美元的钞票，然后返还 5 美元。
> 对于最后一位顾客，我们无法退回 15 美元，因为我们现在只有两张 10 美元的钞票。
> 由于不是每位顾客都得到了正确的找零，所以答案是 false。

#### 我的解法：

有如下三种情况：

- 情况一：账单是5，直接收下。
- 情况二：账单是10，消耗一个5，增加一个10
- 情况三：账单是20，优先消耗一个10和一个5，如果不够，再消耗三个5

**因为美元10只能给账单20找零，而美元5可以给账单10和账单20找零，美元5更万能！**

所以局部最优：遇到账单20，优先消耗美元10，完成本次找零。全局最优：完成全部账单的找零。

```C++
class Solution
{
 public:
	bool lemonadeChange(vector<int>& bills)
	{
		int changes[2] = { 0 };
		for (auto bill : bills)
		{
			if (bill == 5)
				changes[0]++;
			else if (bill == 10)
			{
				// 获得 10 块，找零 5 块
				if (changes[0])
				{
					changes[1]++;
					changes[0]--;
				}
				else
					return false;
			}
			else if (bill == 20)
			{
				// 有 10 块优先用块找零
				if (changes[1] && changes[0])
				{
					changes[1]--;
					changes[0]--;
				}
				else if (changes[0] >= 3)
				{
					changes[0] -= 3;
				}
				else
				{
					return false;
				}
			}
		}

		return true;
	}
};
```

### 406.根据身高重建队列

[LeetCode](https://leetcode.cn/problems/queue-reconstruction-by-height/)  [文章讲解](https://programmercarl.com/0406.%E6%A0%B9%E6%8D%AE%E8%BA%AB%E9%AB%98%E9%87%8D%E5%BB%BA%E9%98%9F%E5%88%97.html)  [视频讲解](https://www.bilibili.com/video/BV1EA411675Y/)

#### 题目描述：

假设有打乱顺序的一群人站成一个队列，数组 `people` 表示队列中一些人的属性（不一定按顺序）。每个 `people[i] = [hi, ki]` 表示第 `i` 个人的身高为 `hi` ，前面 **正好** 有 `ki` 个身高大于或等于 `hi` 的人。

请你重新构造并返回输入数组 `people` 所表示的队列。返回的队列应该格式化为数组 `queue` ，其中 `queue[j] = [hj, kj]` 是队列中第 `j` 个人的属性（`queue[0]` 是排在队列前面的人）。

**题目数据确保队列可以被重建。**

**示例 1：**

> 输入：people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
> 输出：[[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]
> 解释：
> 编号为 0 的人身高为 5 ，没有身高更高或者相同的人排在他前面。
> 编号为 1 的人身高为 7 ，没有身高更高或者相同的人排在他前面。
> 编号为 2 的人身高为 5 ，有 2 个身高更高或者相同的人排在他前面，即编号为 0 和 1 的人。
> 编号为 3 的人身高为 6 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
> 编号为 4 的人身高为 4 ，有 4 个身高更高或者相同的人排在他前面，即编号为 0、1、2、3 的人。
> 编号为 5 的人身高为 7 ，有 1 个身高更高或者相同的人排在他前面，即编号为 1 的人。
> 因此 [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]] 是重新构造后的队列。

**示例 2：**

> 输入：people = [[6,0],[5,0],[4,0],[3,2],[2,2],[1,4]]
> 输出：[[4,0],[5,0],[2,2],[3,2],[1,4],[6,0]]

#### 我的解法：

1. 进行身高从大到小进行排序，同时如果两个身高相等，`ki`小的在前面。
2. 依次插入`result`数组，按`ki`的位置插入。

排序后已经保证了先插入大的数，后插入小的数。插入小的数的时候，`ki`为多少，就插入`ki`的位置。因为插入`result`数组的时候，该数组中所有的值都大于或等于该值，所以只需要在`ki`位置插入即可。

![406.根据身高重建队列](imgs/20201216201851982.png)

**局部最优：优先按身高高的people的k来插入。插入操作过后的people满足队列属性**

**全局最优：最后都做完插入操作，整个队列满足题目队列属性**

```C++
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
```

### 452. 用最少数量的箭引爆气球

[LeetCode](https://leetcode.cn/problems/minimum-number-of-arrows-to-burst-balloons/)  [文章讲解](https://programmercarl.com/0452.%E7%94%A8%E6%9C%80%E5%B0%91%E6%95%B0%E9%87%8F%E7%9A%84%E7%AE%AD%E5%BC%95%E7%88%86%E6%B0%94%E7%90%83.html)  [视频讲解](https://www.bilibili.com/video/BV1SA41167xe/)

#### 题目描述：

有一些球形气球贴在一堵用 XY 平面表示的墙面上。墙面上的气球记录在整数数组 `points` ，其中`points[i] = [xstart, xend]` 表示水平直径在 `xstart` 和 `xend`之间的气球。你不知道气球的确切 y 坐标。

一支弓箭可以沿着 x 轴从不同点 **完全垂直** 地射出。在坐标 `x` 处射出一支箭，若有一个气球的直径的开始和结束坐标为 `x``start`，`x``end`， 且满足  `xstart ≤ x ≤ x``end`，则该气球会被 **引爆** 。可以射出的弓箭的数量 **没有限制** 。 弓箭一旦被射出之后，可以无限地前进。

给你一个数组 `points` ，*返回引爆所有气球所必须射出的 **最小** 弓箭数* 。

**示例 1：**

> 输入：points = [[10,16],[2,8],[1,6],[7,12]]
> 输出：2
> 解释：气球可以用2支箭来爆破:
> - 在x = 6处射出箭，击破气球[2,8]和[1,6]。
> - 在x = 11处发射箭，击破气球[10,16]和[7,12]。

**示例 2：**

> 输入：points = [[1,2],[3,4],[5,6],[7,8]]
> 输出：4
> 解释：每个气球需要射出一支箭，总共需要4支箭。

**示例 3：**

> 输入：points = [[1,2],[2,3],[3,4],[4,5]]
> 输出：2
> 解释：气球可以用2支箭来爆破:
> - 在x = 2处发射箭，击破气球[1,2]和[2,3]。
> - 在x = 4处射出箭，击破气球[3,4]和[4,5]。

#### 我的解法：

如果发生重叠，就一直更新区间，每当不发生重叠的时候result才加1。

```C++
class Solution
{
 public:
	static bool cmp(const vector<int>& a, const vector<int>& b)
	{
		return a[0] < b[0];
	}

	int findMinArrowShots(vector<vector<int>>& points)
	{
		sort(points.begin(), points.end(), cmp);

		int result = 0;
		int left = INT_MIN;
		int right = INT_MAX;

		for (int i = 0; i < points.size();)
		{
			// 如有重叠，一直取到不重叠为止
			while (i < points.size() && points[i][0] <= right)
			{
				left = max(left, points[i][0]);
				right = min(right, points[i][1]);
				i++;
			}
			result++;
			left = INT_MIN;
			right = INT_MAX;
		}

		return result;
	}
};
```

#### 贪心思路

局部最优：当气球出现重叠，一起射，所用弓箭最少。全局最优：把所有气球射爆所用弓箭最少。

把气球排序之后，从前到后遍历气球，被射过的气球仅仅跳过就行了，没有必要让气球数组remove气球，只要记录一下箭的数量就可以了。

**如果气球重叠了，重叠气球中右边边界的最小值 之前的区间一定需要一个弓箭**。

以题目示例： [[10,16],[2,8],[1,6],[7,12]]为例，如图：（方便起见，已经排序）

![452.用最少数量的箭引爆气球](imgs/20201123101929791.png)

可以看出首先第一组重叠气球，一定是需要一个箭，气球3，的左边界大于了 第一组重叠气球的最小右边界，所以再需要一支箭来射气球3了。

```cpp
class Solution {
private:
    static bool cmp(const vector<int>& a, const vector<int>& b) {
        return a[0] < b[0];
    }
public:
    int findMinArrowShots(vector<vector<int>>& points) {
        if (points.size() == 0) return 0;
        sort(points.begin(), points.end(), cmp);

        int result = 1; // points 不为空至少需要一支箭
        for (int i = 1; i < points.size(); i++) {
            if (points[i][0] > points[i - 1][1]) {  // 气球i和气球i-1不挨着，注意这里不是>=
                result++; // 需要一支箭
            }
            else {  // 气球i和气球i-1挨着
                points[i][1] = min(points[i - 1][1], points[i][1]); // 更新重叠气球最小右边界
            }
        }
        return result;
    }
};
```

### 今日总结

虽然三道题目都AC了，但是做的时候好像没有往“贪心”的方向去想，如贪。
