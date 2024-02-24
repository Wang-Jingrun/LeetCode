## Day55: 动态规划part12

### 309.最佳买卖股票时机含冷冻期

[LeetCode](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-cooldown/)  [文章讲解](https://programmercarl.com/0309.%E6%9C%80%E4%BD%B3%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E6%97%B6%E6%9C%BA%E5%90%AB%E5%86%B7%E5%86%BB%E6%9C%9F.html)  [视频讲解](https://www.bilibili.com/video/BV1rP4y1D7ku/)

#### 题目描述：

给定一个整数数组`prices`，其中第 `prices[i]` 表示第 `*i*` 天的股票价格 。

设计一个算法计算出最大利润。在满足以下约束条件下，你可以尽可能地完成更多的交易（多次买卖一支股票）:

- 卖出股票后，你无法在第二天买入股票 (即冷冻期为 1 天)。

**注意：**你不能同时参与多笔交易（你必须在再次购买前出售掉之前的股票）。

**示例 1:**

> 输入: prices = [1,2,3,0,2]
> 输出: 3 
> 解释: 对应的交易状态为: [买入, 卖出, 冷冻期, 买入, 卖出]

**示例 2:**

> 输入: prices = [1]
> 输出: 0

#### 参考解法：

动规五部曲，分析如下：

1. **确定dp数组以及下标的含义**

`dp[i][j]`，第`i`天状态为`j`，所剩的最多现金为`dp[i][j]`。

具体可以区分出如下四个状态：

- 状态一：持有股票状态（今天买入股票，或者是之前就买入了股票然后没有操作，一直持有）
- 不持有股票状态，这里就有两种卖出股票状态
  - 状态二：保持卖出股票的状态（两天前就卖出了股票，度过一天冷冻期。或者是前一天就是卖出股票状态，一直没操作）
  - 状态三：今天卖出股票
- 状态四：今天为冷冻期状态，但冷冻期状态不可持续，只有一天！

![img](imgs/518d5baaf33f4b2698064f8efb42edbf.png)

`j`的状态为：

- 0：状态一
- 1：状态二
- 2：状态三
- 3：状态四

之前买卖股票最佳时机 1，2，3，4 中

- [动态规划：121.买卖股票的最佳时机](https://programmercarl.com/0121.买卖股票的最佳时机.html)
- [动态规划：122.买卖股票的最佳时机II](https://programmercarl.com/0122.买卖股票的最佳时机II（动态规划）.html)
- [动态规划：123.买卖股票的最佳时机III](https://programmercarl.com/0123.买卖股票的最佳时机III.html)
- [动态规划：188.买卖股票的最佳时机IV](https://programmercarl.com/0188.买卖股票的最佳时机IV.html)

「今天卖出股票」是没有单独列出一个状态的归类为「不持有股票的状态」，而本题为什么要单独列出「今天卖出股票」 一个状态呢？

因为本题有冷冻期，而冷冻期的前一天，只能是 「今天卖出股票」状态，如果是 「不持有股票状态」那么就很模糊，因为不一定是 卖出股票的操作。

**注意这里的每一个状态，例如状态一，是持有股票股票状态并不是说今天一定就买入股票，而是说保持买入股票的状态即：可能是前几天买入的，之后一直没操作，所以保持买入股票的状态**。

2. **确定递推公式**

**达到买入股票状态**（状态一）即：`dp[i][0]`，有两个具体操作：

- 操作一：前一天就是持有股票状态（状态一），`dp[i][0] = dp[i - 1][0]`
- 操作二：今天买入了，有两种情况
  - 前一天是冷冻期（状态四），`dp[i - 1][3] - prices[i]`
  - 前一天是保持卖出股票的状态（状态二），`dp[i - 1][1] - prices[i]`

那么`dp[i][0] = max(dp[i - 1][0], dp[i - 1][3] - prices[i], dp[i - 1][1] - prices[i])`;

**达到保持卖出股票状态**（状态二）即：`dp[i][1]`，有两个具体操作：

- 操作一：前一天就是状态二
- 操作二：前一天是冷冻期（状态四）

`dp[i][1] = max(dp[i - 1][1], dp[i - 1][3])`;

**达到今天就卖出股票状态**（状态三），即：`dp[i][2]` ，只有一个操作：

昨天一定是持有股票状态（状态一），今天卖出

即：`dp[i][2] = dp[i - 1][0] + prices[i];`

**达到冷冻期状态**（状态四），即：`dp[i][3]`，只有一个操作：

昨天卖出了股票（状态三）

`dp[i][3] = dp[i - 1][2]`;

综上分析，递推代码如下：

```cpp
dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][3], dp[i - 1][1]) - prices[i]);
dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
dp[i][2] = dp[i - 1][0] + prices[i];
dp[i][3] = dp[i - 1][2];
```

3. **dp数组如何初始化**

如果是持有股票状态（状态一）那么：`dp[0][0] = -prices[0]`，一定是当天买入股票。其他初始化为0即可。

4. **确定遍历顺序**

从递归公式上可以看出，`dp[i]` 依赖于 `dp[i-1]`，所以是从前向后遍历。

5. **举例推导dp数组**

以 [1,2,3,0,2] 为例，dp数组如下：

![309.最佳买卖股票时机含冷冻期](imgs/2021032317451040.png)

最后结果是取 状态二，状态三，和状态四的最大值，状态四是冷冻期，最后一天如果是冷冻期也可能是最大值。

```cpp
class Solution
{
 public:
	int maxProfit(vector<int>& prices)
	{
		int len = prices.size();
		vector<vector<int>> dp(len, vector<int>(4, 0));
		dp[0][0] -= prices[0];
		for (int i = 1; i < len; i++)
		{
			dp[i][0] = max(dp[i - 1][0], max(dp[i - 1][1], dp[i - 1][3]) - prices[i]);
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][3]);
			dp[i][2] = dp[i - 1][0] + prices[i];
			dp[i][3] = dp[i - 1][2];
		}

		return max(max(dp[len - 1][1], dp[len - 1][2]), dp[len - 1][3]);
	}
};
```

节省空间版本：

```cpp
// 节省空间版本
class Solution2
{
 public:
    int maxProfit(vector<int>& prices)
    {
       int len = prices.size();
       vector<vector<int>> dp(2, vector<int>(4, 0));
       dp[0][0] -= prices[0];
       for (int i = 1; i < len; i++)
       {
          dp[i % 2][0] = max(dp[(i - 1) % 2][0], max(dp[(i - 1) % 2][1], dp[(i - 1) % 2][3]) - prices[i]);
          dp[i % 2][1] = max(dp[(i - 1) % 2][1], dp[(i - 1) % 2][3]);
          dp[i % 2][2] = dp[(i - 1) % 2][0] + prices[i];
          dp[i % 2][3] = dp[(i - 1) % 2][2];
       }

       return max(max(dp[(len - 1) % 2][1], dp[(len - 1) % 2][2]), dp[(len - 1) % 2][3]);
    }
};
```

## 714.买卖股票的最佳时机含手续费

[LeetCode](https://leetcode.cn/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/)  [文章讲解](https://programmercarl.com/0714.%E4%B9%B0%E5%8D%96%E8%82%A1%E7%A5%A8%E7%9A%84%E6%9C%80%E4%BD%B3%E6%97%B6%E6%9C%BA%E5%90%AB%E6%89%8B%E7%BB%AD%E8%B4%B9%EF%BC%88%E5%8A%A8%E6%80%81%E8%A7%84%E5%88%92%EF%BC%89.html)  [视频讲解](https://www.bilibili.com/video/BV1z44y1Z7UR/)

#### 题目描述：

给定一个整数数组 `prices`，其中 `prices[i]`表示第 `i` 天的股票价格 ；整数 `fee` 代表了交易股票的手续费用。

你可以无限次地完成交易，但是你每笔交易都需要付手续费。如果你已经购买了一个股票，在卖出它之前你就不能再继续购买股票了。

返回获得利润的最大值。

**注意：**这里的一笔交易指买入持有并卖出股票的整个过程，每笔交易你只需要为支付一次手续费。

**示例 1：**

> 输入：prices = [1, 3, 2, 8, 4, 9], fee = 2
> 输出：8
> 解释：能够达到的最大利润: 
> 在此处买入 prices[0] = 1
> 在此处卖出 prices[3] = 8
> 在此处买入 prices[4] = 4
> 在此处卖出 prices[5] = 9
> 总利润: ((8 - 1) - 2) + ((9 - 4) - 2) = 8

**示例 2：**

> 输入：prices = [1,3,7,5,10,3], fee = 3
> 输出：6

#### 我的解法：

相对于[122.买卖股票的最佳时机II](https://programmercarl.com/0122.买卖股票的最佳时机II（动态规划）.html)，本题只需要在计算卖出操作的时候减去手续费就可以了，代码几乎是一样的。

唯一差别在于递推公式部分，主要分析一下递推公式部分。

dp数组的含义：

`dp[i][0]` 表示第`i`天持有股票所省最多现金。 `dp[i][1]` 表示第`i`天不持有股票所得最多现金

如果第`i`天持有股票即`dp[i][0]`， 那么可以由两个状态推出来

- 第`i-1`天就持有股票，那么就保持现状，所得现金就是昨天持有股票的所得现金 即：`dp[i - 1][0]`
- 第`i`天买入股票，所得现金就是昨天不持有股票的所得现金减去 今天的股票价格 即：`dp[i - 1][1] - prices[i]`

所以：`dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i])`;

在来看看如果第`i`天不持有股票即`dp[i][1]`的情况， 依然可以由两个状态推出来

- 第`i-1`天就不持有股票，那么就保持现状，所得现金就是昨天不持有股票的所得现金 即：`dp[i - 1][1]`
- 第`i`天卖出股票，所得现金就是按照今天股票价格卖出后所得现金，**注意这里需要有手续费了**即：`dp[i - 1][0] + prices[i] - fee`

所以：`dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee)`;

**本题和[122.买卖股票的最佳时机II](https://programmercarl.com/0122.买卖股票的最佳时机II（动态规划）.html)的区别就是这里需要多一个减去手续费的操作**。

```cpp
class Solution
{
 public:
	int maxProfit(vector<int>& prices, int fee)
	{
		int len = prices.size();
		vector<vector<int>> dp(len, vector<int>(2, 0));
		dp[0][0] -= prices[0];
		for (int i = 1; i < len; i++)
		{
			dp[i][0] = max(dp[i - 1][0], dp[i - 1][1] - prices[i]);
			dp[i][1] = max(dp[i - 1][1], dp[i - 1][0] + prices[i] - fee);
		}
		return dp[len - 1][1];
	}
};
```

节省空间版本：

```C++
class Solution2
{
 public:
	int maxProfit(vector<int>& prices, int fee)
	{
		int len = prices.size();
		vector<vector<int>> dp(2, vector<int>(2, 0));
		dp[0][0] -= prices[0];
		for (int i = 1; i < len; i++)
		{
			dp[i % 2][0] = max(dp[(i - 1) % 2][0], dp[(i - 1) % 2][1] - prices[i]);
			dp[i % 2][1] = max(dp[(i - 1) % 2][1], dp[(i - 1) % 2][0] + prices[i] - fee);
		}
		return dp[(len - 1) % 2][1];
	}
};
```

### 今日总结

冷冻期股票真有有点复杂，将不持有股票分成两个状态真有点巧妙。
