## Day51: 动态规划part08

### 139.单词拆分

[LeetCode](https://leetcode.cn/problems/word-break/)  [文章讲解](https://programmercarl.com/0139.%E5%8D%95%E8%AF%8D%E6%8B%86%E5%88%86.html)  [视频讲解](https://www.bilibili.com/video/BV1pd4y147Rh/)

#### 题目描述：

给你一个字符串 `s` 和一个字符串列表 `wordDict` 作为字典。如果可以利用字典中出现的一个或多个单词拼接出 `s` 则返回 `true`。

**注意：**不要求字典中出现的单词全部都使用，并且字典中的单词可以重复使用。

**示例 1：**

> 输入: s = "leetcode", wordDict = ["leet", "code"]
> 输出: true
> 解释: 返回 true 因为 "leetcode" 可以由 "leet" 和 "code" 拼接成。

**示例 2：**

> 输入: s = "applepenapple", wordDict = ["apple", "pen"]
> 输出: true
> 解释: 返回 true 因为 "applepenapple" 可以由 "apple" "pen" "apple" 拼接成。
>      注意，你可以重复使用字典中的单词。

**示例 3：**

> 输入: s = "catsandog", wordDict = ["cats", "dog", "sand", "and", "cat"]
> 输出: false

#### 我的解法：

单词就是物品，字符串s就是背包，单词能否组成字符串s，就是问物品能不能把背包装满。

拆分时可以重复使用字典中的单词，说明就是一个完全背包！

动规五部曲分析如下：

1. **确定dp数组以及下标的含义**

**dp[i] : 字符串长度为i的话，dp[i]为true，表示可以拼凑到s的下标为i的地方**。

2. **确定递推公式**

如果`dp[i - wordDict[j].size()]==true`，且`s.substr(i - wordDict[j].size(), wordDict[j].size()) == wordDict[j]`那么 dp[i] = true。

3. **dp数组如何初始化**

从递推公式中可以看出，`dp[i]` 的状态依靠`dp[i - wordDict[j].size()]`是否为true，那么`dp[0]`就是递推的根基，`dp[0]`一定要为true，否则递推下去后面都都是false了。

4. **确定遍历顺序**

题目中说是拆分为一个或多个在字典中出现的单词，所以这是完全背包。

还要讨论两层for循环的前后顺序。

**如果求组合数就是外层for循环遍历物品，内层for遍历背包**。

**如果求排列数就是外层for遍历背包，内层for循环遍历物品**。

而本题其实求的是排列数，拿 s = "applepenapple", wordDict = ["apple", "pen"] 举例。

"apple", "pen" 是物品，那么要求物品的组合一定是 "apple" + "pen" + "apple" 才能组成 "applepenapple"。

"apple" + "apple" + "pen" 或者 "pen" + "apple" + "apple" 是不可以的，那么就是强调物品之间顺序。

所以说，本题一定是 先遍历 背包，再遍历物品。

5. **举例推导dp[i]**

以输入: s = "leetcode", wordDict = ["leet", "code"]为例，dp状态如图：

![139.单词拆分](imgs/20210202162652727.jpg)

dp[s.size()]就是最终结果。

动规五部曲分析完毕，C++代码如下：

```cpp
class Solution
{
 public:
	bool wordBreak(string s, vector<string>& wordDict)
	{
		vector<bool> dp(s.size() + 1, false);
		dp[0] = true;

		for (int i = 0; i <= s.size(); i++)
		{
			for (int j = 0; j < wordDict.size(); j++)
			{
				if (wordDict[j].size() > i) continue;

				if (dp[i - wordDict[j].size()]
				&& s.substr(i - wordDict[j].size(), wordDict[j].size()) == wordDict[j])
				{
					dp[i] = true;
				}
			}
		}

		return dp[s.size()];
	}
};
```

### 多重背包

[卡码网](https://kamacoder.com/problempage.php?pid=1066)  [文章讲解](https://programmercarl.com/%E8%83%8C%E5%8C%85%E9%97%AE%E9%A2%98%E7%90%86%E8%AE%BA%E5%9F%BA%E7%A1%80%E5%A4%9A%E9%87%8D%E8%83%8C%E5%8C%85.html)

#### 题目描述：

有N种物品和一个容量为V的背包。第i种物品最多有Mi件可用，每件耗费的空间是Ci ，价值是Wi 。求解将哪些物品装入背包可使这些物品的耗费的空间 总和不超过背包容量，且价值总和最大。

多重背包和01背包是非常像的， 为什么和01背包像呢？每件物品最多有Mi件可用，把Mi件摊开，其实就是一个01背包问题了。

例如：

背包最大重量为10。

物品为：

|       | 重量 | 价值 | 数量 |
| ----- | ---- | ---- | ---- |
| 物品0 | 1    | 15   | 2    |
| 物品1 | 3    | 20   | 3    |
| 物品2 | 4    | 30   | 2    |

问背包能背的物品最大价值是多少？

和如下情况有区别么？

|       | 重量 | 价值 | 数量 |
| ----- | ---- | ---- | ---- |
| 物品0 | 1    | 15   | 1    |
| 物品0 | 1    | 15   | 1    |
| 物品1 | 3    | 20   | 1    |
| 物品1 | 3    | 20   | 1    |
| 物品1 | 3    | 20   | 1    |
| 物品2 | 4    | 30   | 1    |
| 物品2 | 4    | 30   | 1    |

毫无区别，这就转成了一个01背包问题了，且每个物品只用一次。

练习题目：[卡码网第56题，多重背包](https://kamacoder.com/problempage.php?pid=1066)

代码如下：

```cpp
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// 先遍历背包，再遍历物品
void multipleBackpack(int bagWeight, vector<int>& weight, vector<int>& value, vector<int>& nums)
{
	vector<int> new_weight;
	vector<int> new_value;

	for (int i = 0; i < weight.size(); i++)
	{
		for (int j = 0; j < nums[i]; j++)
		{
			new_weight.push_back(weight[i]);
			new_value.push_back(value[i]);
		}
	}

	vector<int> dp(bagWeight + 1, 0);

	// 遍历物品
	for (int i = 0; i < new_weight.size(); i++)
	{
		// 遍历背包
		for (int j = bagWeight; j >= new_weight[i]; j--)
		{
			dp[j] = max(dp[j], dp[j - new_weight[i]] + new_value[i]);
		}
	}

	cout << dp[bagWeight] << endl;
}

int main()
{
	int bagWeight, n;
	cin >> bagWeight >> n;
	vector<int> weight(n, 0);
	vector<int> value(n, 0);
	vector<int> nums(n, 0);
	for (int i = 0; i < n; i++) cin >> weight[i];
	for (int i = 0; i < n; i++) cin >> value[i];
	for (int i = 0; i < n; i++) cin >> nums[i];
	multipleBackpack(bagWeight, weight, value, nums);
	return 0;
}
```

这个解法超时了，为什么呢，哪里耗时呢？

耗时就在 这段代码：

```cpp
for (int i = 0; i < weight.size(); i++)
{
    for (int j = 0; j < nums[i]; j++)
    {
        new_weight.push_back(weight[i]);
        new_value.push_back(value[i]);
    }
}
```

如果物品数量很多的话，C++中，这种操作十分费时，主要消耗在vector的动态底层扩容上。（其实这里也可以优化，先把 所有物品数量都计算好，一起申请vector的空间。

这里也有另一种实现方式，就是把每种商品遍历的个数放在01背包里面在遍历一遍。

代码如下：

```cpp
// 先遍历背包，再遍历物品
void multipleBackpack(int bagWeight, vector<int>& weight, vector<int>& value, vector<int>& nums)
{
	vector<int> dp(bagWeight + 1, 0);

	// 遍历物品
	for (int i = 0; i < weight.size(); i++)
	{
		// 遍历背包
		for (int j = bagWeight; j >= weight[i]; j--)
		{
			// 以上为01背包，然后加一个遍历个数
			for (int k = 1; k <= nums[i] && (j - k * weight[i] >= 0); k++)
			{
				dp[j] = max(dp[j], dp[j - k * weight[i]] + k * value[i]);
			}
		}
	}

	cout << dp[bagWeight] << endl;
}
```

时间复杂度：O(m × n × k)，m：物品种类个数，n背包容量，k单类物品数量

从代码里可以看出是01背包里面在加一个for循环遍历一个每种商品的数量。 和01背包还是如出一辙的。

多重背包在面试中基本不会出现，力扣上也没有对应的题目，大家对多重背包的掌握程度知道它是一种01背包，并能在01背包的基础上写出对应代码就可以了。

### 背包问题总结

关于这几种常见的背包，其关系如下：

![416.分割等和子集1](imgs/20230310000726.png)

在讲解背包问题的时候，都是按照如下五部来逐步分析：

1. 确定dp数组（dp table）以及下标的含义
2. 确定递推公式
3. dp数组如何初始化
4. 确定遍历顺序
5. 举例推导dp数组

**其实这五部里哪一步都很关键，但确定递推公式和确定遍历顺序都具有规律性和代表性，所以从这两点来对背包问题做一做总结**。

#### 背包递推公式

问能否能装满背包（或者最多装多少）：dp[j] = max(dp[j], dp[j - nums[i]] + nums[i]); ，对应题目如下：

- [动态规划：416.分割等和子集](https://programmercarl.com/0416.分割等和子集.html)
- [动态规划：1049.最后一块石头的重量 II](https://programmercarl.com/1049.最后一块石头的重量II.html)

问装满背包有几种方法：dp[j] += dp[j - nums[i]] ，对应题目如下：

- [动态规划：494.目标和](https://programmercarl.com/0494.目标和.html)
- [动态规划：518. 零钱兑换 II](https://programmercarl.com/0518.零钱兑换II.html)
- [动态规划：377.组合总和Ⅳ](https://programmercarl.com/0377.组合总和Ⅳ.html)
- [动态规划：70. 爬楼梯进阶版（完全背包）](https://programmercarl.com/0070.爬楼梯完全背包版本.html)

问背包装满最大价值：dp[j] = max(dp[j], dp[j - weight[i]] + value[i]); ，对应题目如下：

- [动态规划：474.一和零](https://programmercarl.com/0474.一和零.html)

问装满背包所有物品的最小个数：dp[j] = min(dp[j - coins[i]] + 1, dp[j]); ，对应题目如下：

- [动态规划：322.零钱兑换](https://programmercarl.com/0322.零钱兑换.html)
- [动态规划：279.完全平方数](https://programmercarl.com/0279.完全平方数.html)

#### 遍历顺序

##### 01背包

在[动态规划：关于01背包问题，你该了解这些！](https://programmercarl.com/背包理论基础01背包-1.html)中二维dp数组01背包先遍历物品还是先遍历背包都是可以的，且第二层for循环是从小到大遍历。

和[动态规划：关于01背包问题，你该了解这些！（滚动数组）](https://programmercarl.com/背包理论基础01背包-2.html)中一维dp数组01背包只能先遍历物品再遍历背包容量，且第二层for循环是从大到小遍历。

**一维dp数组的背包在遍历顺序上和二维dp数组实现的01背包其实是有很大差异，值得注意！**

##### 完全背包

说完01背包，再看看完全背包。

在[动态规划：关于完全背包，你该了解这些！](https://programmercarl.com/背包问题理论基础完全背包.html)中，讲解了纯完全背包的一维dp数组实现，先遍历物品还是先遍历背包都是可以的，且第二层for循环是从小到大遍历。

但是仅仅是纯完全背包的遍历顺序是这样的，题目稍有变化，两个for循环的先后顺序就不一样了。

**如果求组合数就是外层for循环遍历物品，内层for遍历背包**。

**如果求排列数就是外层for遍历背包，内层for循环遍历物品**。

相关题目如下：

- 求组合数：[动态规划：518.零钱兑换II](https://programmercarl.com/0518.零钱兑换II.html)
- 求排列数：[动态规划：377. 组合总和 Ⅳ](https://mp.weixin.qq.com/s/Iixw0nahJWQgbqVNk8k6gA)、[动态规划：70. 爬楼梯进阶版（完全背包）(opens new window)](https://programmercarl.com/0070.爬楼梯完全背包版本.html)

如果求最小数，那么两层for循环的先后顺序就无所谓了，相关题目如下：

- 求最小数：[动态规划：322. 零钱兑换](https://programmercarl.com/0322.零钱兑换.html)、[动态规划：279.完全平方数](https://programmercarl.com/0279.完全平方数.html)

**对于背包问题，其实递推公式算是容易的，难是难在遍历顺序上，如果把遍历顺序搞透，才算是真正理解了**。

#### 思维导图：

![img](imgs/背包问题1.jpeg)

### 今日总结

背包问题暂时完结，注重对递推公式和遍历顺序的理解！
