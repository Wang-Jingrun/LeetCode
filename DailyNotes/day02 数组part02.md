### Day02: 数组part02

#### 977. 有序数组的平方
[LeetCode](https://leetcode.cn/problems/squares-of-a-sorted-array/)  [文章讲解](https://programmercarl.com/0977.%E6%9C%89%E5%BA%8F%E6%95%B0%E7%BB%84%E7%9A%84%E5%B9%B3%E6%96%B9.html)  [视频讲解](https://www.bilibili.com/video/BV1QB4y1D7ep)

##### 题目描述：

给你一个按 非递减顺序 排序的整数数组 nums，返回 每个数字的平方 组成的新数组，要求也按 非递减顺序 排序。

示例 1：

- 输入：nums = [-4,-1,0,3,10]
- 输出：[0,1,9,16,100]
- 解释：平方后，数组变为 [16,1,0,9,100]，排序后，数组变为 [0,1,9,16,100]

示例 2：

- 输入：nums = [-7,-3,2,3,11]
- 输出：[4,9,9,49,121]

##### 我的解法（暴力解法）：

即先平方后排序，但是由于自己写的冒泡排序的复杂度较高（O(n + n^2)）似乎过不了LeetCode，调用 stl 的 sort 就可以通过，sort 内部实现是快速排序（O(n + nlogn)）。

```C++
class MySolution    // 暴力解法：先平方后排序
{
 public:
	vector<int> sortedSquares(vector<int>& nums)
	{
		for (int& num : nums)
			num *= num;

//		// 冒泡排序 -- leetcode 无法通过
//		int temp = 0;
//		for (int i = 0; i < nums.size() - 1; ++i)
//		{
//			for (int j = i + 1; j < nums.size(); ++j)
//			{
//				if (nums[i] > nums[j])
//				{
//					temp = nums[i];
//					nums[i] = nums[j];
//					nums[j] = temp;
//				}
//			}
//		}

		sort(nums.begin(), nums.end()); // 快速排序

		return nums;
	}
};
```

##### 双指针法：

数组其实是有序的， 只不过负数平方之后可能成为最大数了，即数组平方的最大值就在数组的两端，不是最左边就是最右边，不可能是中间。

考虑双指针法了，`i` 指向起始位置，`j` 指向终止位置。定义一个新数组 `ret`，和 `A` 数组一样的大小，让 `k` 指向 `result` 数组终止位置。时间复杂度为 O(n)。

![双指针法](imgs/977.有序数组的平方.gif)

```C++
class Solution    // 双指针法
{
 public:
	vector<int> sortedSquares(vector<int>& nums)
	{
		vector<int> ret;
		ret.resize(nums.size());

		int i = 0;
		int j = (int)nums.size() - 1;
		int k = (int)nums.size() - 1;

		while (k >= 0)
		{
			if (nums[i] * nums[i] >= nums[j] * nums[j])
			{
				ret[k--] = (nums[i] * nums[i]);
				++i;
			}
			else if (nums[i] * nums[i] < nums[j] * nums[j])
			{
				ret[k--] = (nums[j] * nums[j]);
				--j;
			}
		}

		return ret;
	}
};
```

#### 209.长度最小的子数组
[LeetCode](https://leetcode.cn/problems/minimum-size-subarray-sum/)  [文章讲解](https://programmercarl.com/0209.%E9%95%BF%E5%BA%A6%E6%9C%80%E5%B0%8F%E7%9A%84%E5%AD%90%E6%95%B0%E7%BB%84.html)  [视频讲解](https://www.bilibili.com/video/BV1tZ4y1q7XE)

##### 题目描述：

给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的 连续 子数组，并返回其长度。如果不存在符合条件的子数组，返回 0。

示例：

- 输入：s = 7, nums = [2,3,1,2,4,3]
- 输出：2
- 解释：子数组 [4,3] 是该条件下的长度最小的子数组。

提示：

- 1 <= target <= 10^9
- 1 <= nums.length <= 10^5
- 1 <= nums[i] <= 10^5

##### 暴力解法：

两个for循环，然后不断的寻找符合条件的子序列，时间复杂度为O(n^2)。LeetCode上似乎没法通过。

```C++
class Solution    // 暴力解法
{
 public:
	int minSubArrayLen(int target, vector<int>& nums)
	{
		int sum = 0;    // 窗口内的元素和
		int subLength = 0;    // 满足条件的子数组长度
		int result = INT_MAX;    // 需要返回的结果, 取最大值才能继续更新更小的值
		for (int left = 0; left < nums.size(); left++)
		{
			// 每次向右累加之前 sum 重新清 0
			sum = 0;
			for (int right = left; right < nums.size(); right++)
			{
				// 依次将窗口中的元素求和
				sum += nums[right];

				// 如果满足条件
				if (sum >= target)
				{
					// 更新子数组长度
					subLength = right - left + 1;
					result = result < subLength ? result : subLength;
					// 满足条件退出即可，不需要继续累加了
					break;
				}
			}
		}

		return result == INT_MAX ? 0 : result;
	}
```

##### 滑动窗口法：

题目中 s = 7, nums = [2,3,1,2,4,3] 时的过程：



![209.长度最小的子数组](imgs/209.长度最小的子数组.gif)

可以看出滑动窗口也可以理解为双指针法的一种！只不过这种解法更像是一个窗口的移动，所以叫做滑动窗口更适合一些。

在本题中实现滑动窗口，主要确定如下三点：

- 窗口内是什么？
- 如何移动窗口的起始位置？
- 如何移动窗口的结束位置？

窗口就是 满足其和 ≥ s 的长度最小的连续子数组。

窗口的起始位置如何移动：如果当前窗口的值大于s了，窗口就要向前移动了（也就是该缩小了）。

窗口的结束位置如何移动：窗口的结束位置就是遍历数组的指针，也就是for循环里的索引。

滑动窗口的精妙之处在于根据当前子序列和大小的情况，不断调节子序列的起始位置。从而将O(n^2)暴力解法降为O(n)。

```C++
class Solution    // 滑动窗口法
{
 public:
    int minSubArrayLen(int target, vector<int>& nums)
    {
       int sum = 0;    // 滑动窗口内的元素和
       int left = 0;    // 滑动窗口左侧下标
       int subLength = 0;    // 满足条件的子数组长度
       int result = INT_MAX;    // 需要返回的结果, 取最大值才能继续更新更小的值
       for (int right = 0; right < nums.size(); right++)
       {
          // 依次将滑动窗口中的元素求和
          sum += nums[right];

          // 此处为 while, 因为更新滑动窗口左侧需要使得不满足 sum >= target 时, 才能继续寻找满足条件的子数组
          // 每当 sum >= target 时, 更新子数组长度
          while (sum >= target)
          {
             subLength = right - left + 1;
             // 更新最终结果
             result = result < subLength ? result : subLength;

             // 滑动窗口左边前移, 继续寻找满足条件的子数组
             sum -= nums[left++];
          }
       }

       return result == INT_MAX ? 0 : result;
    }
};
```

#### 59. 螺旋矩阵II
[LeetCode](https://leetcode.cn/problems/spiral-matrix-ii/)  [文章讲解](https://programmercarl.com/0059.%E8%9E%BA%E6%97%8B%E7%9F%A9%E9%98%B5II.html)  [视频讲解](https://www.bilibili.com/video/BV1SL4y1N7mV/)

##### 题目描述：

给定一个正整数 n，生成一个包含 1 到 n^2 所有元素，且元素按顺时针顺序螺旋排列的正方形矩阵。

示例:

- 输入: 3 

- 输出: [ [ 1, 2, 3 ], [ 8, 9, 4 ], [ 7, 6, 5 ] ]

##### 解法：

每一圈为循环，每条边单独处理，模拟顺时针画矩阵的过程:

- 填充上行从左到右
- 填充右列从上到下
- 填充下行从右到左
- 填充左列从下到上

由外向内一圈一圈这么画下去。每画一条边都要坚持一致的左闭右开，或者左开右闭的原则，这样这一圈才能按照统一的规则画下来。

<img src="imgs/20220922102236.png" alt="20220922102236" style="zoom:50%;" />

```C++
class Solution
{
 public:
	vector<vector<int>> generateMatrix(int n)
	{
		vector<vector<int>> ret(n, vector<int>(n, 0));
		int loop = n / 2; // 需要转的圈数
		int start_x = 0, start_y = 0;
		int offset = 1;    // 偏移值，每转一圈加一
		int num = 1;

		while (loop--)
		{
			// 第一条边：从左到右，不包含最后一个值
			for (int j = start_x; j < n - offset; ++j)
				ret[start_x][j] = num++;

			// 第二条边：从上到下，不包含最后一个值
			for (int i = start_x; i < n - offset; ++i)
				ret[i][n - offset] = num++;

			// 第三边：从右到左，不包含最后一个值
			for (int j = n - offset; j > start_x; --j)
				ret[n - offset][j] = num++;

			// 第四边：从下到上，不包含最后一个值i
			for (int i = n - offset; i > start_x; --i)
				ret[i][start_y] = num++;

			// 下一圈开始的时候，起始位置要各自加 1
			start_x++;
			start_y++;

			// offset 控制每一圈里每一条边遍历的长度
			offset++;
		}

		if (n % 2 == 1)
			ret[n / 2][n / 2] = num;
		
		return ret;
	}
};
```





#### 今日总结

第一题有通过暴力解法完成，第二第三道题都没能独立完成。

通过两天数组的题目发现：暴力解法很容易想到，通常都是为 O(n^2) 的复杂度，并且大部分都是直观地思想，从数组左端到右端逐次遍历，然后在遍历的过程中进行条件判断，而条件判断过程中也常常会再次进行遍历，导致 O(n^2) 的复杂度。有时也需要考虑从数组右端到左端逐次遍历，或者分析数组中值分布的特点。

#### 数组篇总结

- 数组下标都是从0开始的
- 数组内存空间的地址是连续的
- 正是因为数组的在内存空间的地址是连续的，所以我们在删除或者增添元素的时候，就难免要移动其他元素的地址
- 数组的元素是不能删的，只能覆盖

![数组总结](imgs/数组总结.png)
