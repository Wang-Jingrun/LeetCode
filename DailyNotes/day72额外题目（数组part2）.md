## Day72: 额外题目（数组part2）

### 724. 寻找数组的中心下标

[LeetCode](https://leetcode.cn/problems/find-pivot-index/)  [文章讲解](https://programmercarl.com/0724.%E5%AF%BB%E6%89%BE%E6%95%B0%E7%BB%84%E7%9A%84%E4%B8%AD%E5%BF%83%E7%B4%A2%E5%BC%95.html)

#### 题目描述：

给你一个整数数组 `nums` ，请计算数组的 **中心下标** 。

数组 **中心下标** 是数组的一个下标，其左侧所有元素相加的和等于右侧所有元素相加的和。

如果中心下标位于数组最左端，那么左侧数之和视为 `0` ，因为在下标的左侧不存在元素。这一点对于中心下标位于数组最右端同样适用。

如果数组有多个中心下标，应该返回 **最靠近左边** 的那一个。如果数组不存在中心下标，返回 `-1` 。

**示例 1：**

> 输入：nums = [1, 7, 3, 6, 5, 6]
> 输出：3
> 解释：
> 中心下标是 3 。
> 左侧数之和 sum = nums[0] + nums[1] + nums[2] = 1 + 7 + 3 = 11 ，
> 右侧数之和 sum = nums[4] + nums[5] = 5 + 6 = 11 ，二者相等。

**示例 2：**

> 输入：nums = [1, 2, 3]
> 输出：-1
> 解释：
> 数组中不存在满足此条件的中心下标。

**示例 3：**                                    

> 输入：nums = [2, 1, -1]
> 输出：0
> 解释：
> 中心下标是 0 。
> 左侧数之和 sum = 0 ，（下标 0 左侧不存在元素），
> 右侧数之和 sum = nums[1] + nums[2] = 1 + -1 = 0 。

#### 我的解法：

`leftSum` 统计中心下标左侧的和，`rightSum` 统计中心下标右侧的和。遍历的时候 `rightSum -= nums[i];`，`leftSum += nums[i - 1];`，当 `leftSum == rightSum` 表明找到中心下标了，返回即可。

```C++
class Solution
{
 public:
	int pivotIndex(vector<int>& nums)
	{
		int rightSum = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			rightSum += nums[i];
		}

		int leftSum = 0;
		for (int i = 0; i < nums.size(); i++)
		{
			rightSum -= nums[i];
			if (i > 0) leftSum += nums[i - 1];
			if (leftSum == rightSum) return i;
		}

		return -1;
	}
};
```

### 34. 在排序数组中查找元素的第一个和最后一个位置

[LeetCode](https://leetcode.cn/problems/find-first-and-last-position-of-element-in-sorted-array/)  [文章讲解](https://programmercarl.com/0034.%E5%9C%A8%E6%8E%92%E5%BA%8F%E6%95%B0%E7%BB%84%E4%B8%AD%E6%9F%A5%E6%89%BE%E5%85%83%E7%B4%A0%E7%9A%84%E7%AC%AC%E4%B8%80%E4%B8%AA%E5%92%8C%E6%9C%80%E5%90%8E%E4%B8%80%E4%B8%AA%E4%BD%8D%E7%BD%AE.html)

#### 题目描述：

给你一个按照非递减顺序排列的整数数组 `nums`，和一个目标值 `target`。请你找出给定目标值在数组中的开始位置和结束位置。

如果数组中不存在目标值 `target`，返回 `[-1, -1]`。

你必须设计并实现时间复杂度为 `O(log n)` 的算法解决此问题。

**示例 1：**

> 输入：nums = [5,7,7,8,8,10], target = 8
> 输出：[3,4]

**示例 2：**

> 输入：nums = [5,7,7,8,8,10], target = 6
> 输出：[-1,-1]

**示例 3：**

> 输入：nums = [], target = 0
> 输出：[-1,-1]

#### 我的解法：

双指针法，左边不等左指针前移，右边不等右指针后移。

```C++
class Solution
{
 public:
	vector<int> searchRange(vector<int>& nums, int target)
	{
		for (int i = 0, j = nums.size() - 1; i <= j;)
		{
			if (nums[i] == target && nums[j] == target) return { i, j };

			if (nums[i] != target) i++;
			if (nums[j] != target) j--;
		}
		return { -1, -1 };
	}
};
```

#### 二分法：

寻找 `target` 在数组里的左右边界，有如下三种情况：

- 情况一： `target` 在数组范围的右边或者左边，例如数组{3, 4, 5}， `target` 为2或者数组{3, 4, 5}, `target` 为6，此时应该返回{-1, -1}
- 情况二： `target` 在数组范围中，且数组中不存在 `target` ，例如数组{3,6,7}, `target` 为5，此时应该返回{-1, -1}
- 情况三： `target` 在数组范围中，且数组中存在 `target` ，例如数组{3,6,7}, `target` 为6，此时应该返回{1, 1}

这三种情况都考虑到，说明就想的很清楚了。

接下来，在去寻找左边界，和右边界了。

采用二分法来去寻找左右边界，为了让代码清晰，分别写两个二分来寻找左边界和右边界。

```cpp
class Solution2
{
 public:
    vector<int> searchRange(vector<int>& nums, int target)
    {
       int leftBorder = getLeftBorder(nums, target);
       int rightBorder = getRightBorder(nums, target);
       // 情况一
       if (leftBorder == -2 || rightBorder == -2) return { -1, -1 };
       // 情况三
       if (rightBorder - leftBorder > 1) return { leftBorder + 1, rightBorder - 1 };
       // 情况二
       return { -1, -1 };
    }
 private:
    int getRightBorder(vector<int>& nums, int target)
    {
       int left = 0;
       int right = nums.size() - 1;
       int rightBorder = -2; // 记录一下rightBorder没有被赋值的情况
       while (left <= right)
       {
          int middle = left + ((right - left) / 2);
          if (nums[middle] > target)
          {
             right = middle - 1;
          }
          else
          { // 寻找右边界，nums[middle] == target的时候更新left
             left = middle + 1;
             rightBorder = left;
          }
       }
       return rightBorder;
    }
    int getLeftBorder(vector<int>& nums, int target)
    {
       int left = 0;
       int right = nums.size() - 1;
       int leftBorder = -2; // 记录一下leftBorder没有被赋值的情况
       while (left <= right)
       {
          int middle = left + ((right - left) / 2);
          if (nums[middle] >= target)
          { // 寻找左边界，nums[middle] == target的时候更新right
             right = middle - 1;
             leftBorder = right;
          }
          else
          {
             left = middle + 1;
          }
       }
       return leftBorder;
    }
};
```

### 922. 按奇偶排序数组 II

[LeetCode](https://leetcode.cn/problems/sort-array-by-parity-ii/)  [文章讲解](https://programmercarl.com/0922.%E6%8C%89%E5%A5%87%E5%81%B6%E6%8E%92%E5%BA%8F%E6%95%B0%E7%BB%84II.html)

#### 题目描述：

给定一个非负整数数组 `nums`， `nums` 中一半整数是 **奇数** ，一半整数是 **偶数** 。

对数组进行排序，以便当 `nums[i]` 为奇数时，`i` 也是 **奇数** ；当 `nums[i]` 为偶数时， `i` 也是 **偶数** 。

你可以返回 *任何满足上述条件的数组作为答案* 。

**示例 1：**

> 输入：nums = [4,2,5,7]
> 输出：[4,5,2,7]
> 解释：[4,7,2,5]，[2,5,4,7]，[2,7,4,5] 也会被接受。

**示例 2：**

> 输入：nums = [2,3]
> 输出：[2,3]

#### 我的解法：

`even` 记录偶数下标，`odd` 记录奇数下标。

```C++
class Solution
{
 public:
	vector<int> sortArrayByParityII(vector<int>& nums)
	{
		vector<int> result(nums.size());
		int even = 0, odd = 1;

		for (int i = 0; i < nums.size(); i++)
		{
			if (nums[i] % 2 == 0)
			{
				result[even] = nums[i];
				even += 2;
			}
			else
			{
				result[odd] = nums[i];
				odd += 2;
			}
		}
		return result;
	}
};
```

### 35. 搜索插入位置

[LeetCode](https://leetcode.cn/problems/search-insert-position/)  [文章讲解](https://programmercarl.com/0035.%E6%90%9C%E7%B4%A2%E6%8F%92%E5%85%A5%E4%BD%8D%E7%BD%AE.html)

#### 题目描述：

给定一个排序数组和一个目标值，在数组中找到目标值，并返回其索引。如果目标值不存在于数组中，返回它将会被按顺序插入的位置。

请必须使用时间复杂度为 `O(log n)` 的算法。

**示例 1:**

> 输入: nums = [1,3,5,6], target = 5
> 输出: 2

**示例 2:**

> 输入: nums = [1,3,5,6], target = 2
> 输出: 1

**示例 3:**

> 输入: nums = [1,3,5,6], target = 7
> 输出: 4

#### 参考解法：

这道题目，要在数组中插入目标值，无非是这四种情况。

![35_搜索插入位置3](imgs/20201216232148471.png)

- 目标值在数组所有元素之前
- 目标值等于数组中某一个元素
- 目标值插入数组中的位置
- 目标值在数组所有元素之后

```C++
class Solution
{
 public:
	int searchInsert(vector<int>& nums, int target)
	{
		int n = nums.size();
		int left = 0;
		int right = n - 1; // 定义target在左闭右闭的区间里，[left, right]
		while (left <= right) // 当left==right，区间[left, right]依然有效
		{
			int middle = left + ((right - left) / 2);// 防止溢出 等同于(left + right)/2
			if (nums[middle] > target)
				right = middle - 1; // target 在左区间，所以[left, middle - 1]
			else if (nums[middle] < target)
				left = middle + 1; // target 在右区间，所以[middle + 1, right]
			else // nums[middle] == target
				return middle;
		}
		// 分别处理如下四种情况
		// 目标值在数组所有元素之前  [0, -1]
		// 目标值等于数组中某一个元素  return middle;
		// 目标值插入数组中的位置 [left, right]，return  right + 1
		// 目标值在数组所有元素之后的情况 [left, right]， 因为是右闭区间，所以 return right + 1
		return right + 1;
	}
};
```

### 今日总结

回顾了二分法，坚持不变量原则。
