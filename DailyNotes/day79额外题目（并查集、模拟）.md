## Day79: 额外题目（并查集、模拟）

### 657. 机器人能否返回原点

[LeetCode](https://leetcode.cn/problems/robot-return-to-origin/)  [文章讲解](https://programmercarl.com/0657.%E6%9C%BA%E5%99%A8%E4%BA%BA%E8%83%BD%E5%90%A6%E8%BF%94%E5%9B%9E%E5%8E%9F%E7%82%B9.html)

#### 题目描述：

在二维平面上，有一个机器人从原点 `(0, 0)` 开始。给出它的移动顺序，判断这个机器人在完成移动后是否在 **`(0, 0)` 处结束**。

移动顺序由字符串 `moves` 表示。字符 `move[i]` 表示其第 `i` 次移动。机器人的有效动作有 `R`（右），`L`（左），`U`（上）和 `D`（下）。

如果机器人在完成所有动作后返回原点，则返回 `true`。否则，返回 `false`。

**注意：**机器人“面朝”的方向无关紧要。 `“R”` 将始终使机器人向右移动一次，`“L”` 将始终向左移动等。此外，假设每次移动机器人的移动幅度相同。

**示例 1:**

> 输入: moves = "UD"
> 输出: true
> 解释：机器人向上移动一次，然后向下移动一次。所有动作都具有相同的幅度，因此它最终回到它开始的原点。因此，我们返回 true。

**示例 2:**

> 输入: moves = "LL"
> 输出: false
> 解释：机器人向左移动两次。它最终位于原点的左侧，距原点有两次 “移动” 的距离。我们返回 false，因为它在移动结束时没有返回原点。

#### 我的解法：

```C++
class Solution
{
 public:
	bool judgeCircle(string moves)
	{
		int cur[2] = { 0, 0 };
		for (char move : moves)
		{
			if (move == 'R')
				++cur[0];
			else if (move == 'L')
				--cur[0];
			else if (move == 'U')
				++cur[1];
			else if (move == 'D')
				--cur[1];
			else
				return false;
		}
		if (cur[0] == 0 && cur[1] == 0) return true;
		return false;
	}
};
```

### 31. 下一个排列

[LeetCode](https://leetcode.cn/problems/next-permutation/)  [文章讲解](https://programmercarl.com/0031.%E4%B8%8B%E4%B8%80%E4%B8%AA%E6%8E%92%E5%88%97.html)

#### 题目描述：

整数数组的一个 **排列** 就是将其所有成员以序列或线性顺序排列。

- 例如，`arr = [1,2,3]` ，以下这些都可以视作 `arr` 的排列：`[1,2,3]`、`[1,3,2]`、`[3,1,2]`、`[2,3,1]` 。

整数数组的 **下一个排列** 是指其整数的下一个字典序更大的排列。更正式地，如果数组的所有排列根据其字典顺序从小到大排列在一个容器中，那么数组的 **下一个排列** 就是在这个有序容器中排在它后面的那个排列。如果不存在下一个更大的排列，那么这个数组必须重排为字典序最小的排列（即，其元素按升序排列）。

- 例如，`arr = [1,2,3]` 的下一个排列是 `[1,3,2]` 。
- 类似地，`arr = [2,3,1]` 的下一个排列是 `[3,1,2]` 。
- 而 `arr = [3,2,1]` 的下一个排列是 `[1,2,3]` ，因为 `[3,2,1]` 不存在一个字典序更大的排列。

给你一个整数数组 `nums` ，找出 `nums` 的下一个排列。

必须**[ 原地 ](https://baike.baidu.com/item/原地算法)**修改，只允许使用额外常数空间。

**示例 1：**

> 输入：nums = [1,2,3]
> 输出：[1,3,2]

**示例 2：**

> 输入：nums = [3,2,1]
> 输出：[1,2,3]

**示例 3：**

> 输入：nums = [1,1,5]
> 输出：[1,5,1]

#### 我的解法：

```C++
class Solution
{
 public:
	void nextPermutation(vector<int>& nums)
	{
		for (int i = nums.size() - 1; i >= 0; --i)
		{
			for (int j = nums.size() - 1; j > i; --j)
			{
				if (nums[j] > nums[i])
				{
					swap(nums[j], nums[i]);
					reverse(nums.begin() + i + 1, nums.end());
					return;
				}
			}
		}

		sort(nums.begin(), nums.end());
	}
};
```

### 今日总结

复习了并查集
