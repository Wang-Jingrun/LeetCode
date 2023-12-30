## Day01: 数组part01

### 704. 二分查找 
[LeetCode](https://leetcode.cn/problems/binary-search/)  [文章讲解](https://programmercarl.com/0704.%E4%BA%8C%E5%88%86%E6%9F%A5%E6%89%BE.html)  [视频讲解](https://www.bilibili.com/video/BV1fA4y1o715)

#### 题目描述：

给定一个 n 个元素有序的（升序）整型数组 nums 和一个目标值 target  ，写一个函数搜索 nums 中的 target，如果目标值存在返回下标，否则返回 -1。

示例 1:

```text
输入: nums = [-1,0,3,5,9,12], target = 9     
输出: 4       
解释: 9 出现在 nums 中并且下标为 4     
```

示例 2:

```text
输入: nums = [-1,0,3,5,9,12], target = 2     
输出: -1        
解释: 2 不存在 nums 中因此返回 -1        
```

提示：

- 你可以假设 nums 中的所有元素是不重复的。
- n 将在 [1, 10000]之间。
- nums 的每个元素都将在 [-9999, 9999]之间。

#### 我的解法：

自己写的第一版解法，由于没有理顺思路，循环结束的条件想了好久，总是卡在 [2, 5] 这种两个值的数组。

当 `right - left <= 1` 时， 此时 `(left + right) / 2` 恒等于 `left` ，因此无论如何取不到 `right` ，需要手动判断 `target != nums[right]` ，然后结束循环。

```C++
class MySolution
{
 public:
	int search(vector<int>& nums, int target)
	{
		int left = 0;
		int right = (int)nums.size() - 1;
		int mid = 0;

		while (true)
		{
			mid = (left + right) / 2;

			if (target > nums[mid])
				left = mid;
			else if (target < nums[mid])
				right = mid;
			else
				return mid;

			if ((right - left <= 1) && mid == left)
			{
				if (target != nums[right])
					return -1;
				else
					return right;
			}
		}
	}
};
```

#### 左闭右闭 [left, right]：

每次构建或者更新区间的时候牢牢把握左闭右闭原则。

```c++
class Solution1    // [left, right]
{
 public:
	int search(vector<int>& nums, int target)
	{
		int left = 0;
		int right = (int)nums.size() - 1;  // 遵从右闭
		int mid = 0;

		// 遵从左闭右闭，left == right 时，[left, right] 是有效区间
		while (left <= right)
		{
			mid = (left + right) / 2;

			if (target < nums[mid])
				// mid 被判断过，但是由于遵从左闭，right = mid - 1
				right = mid - 1;
			else if (target > nums[mid])
				// mid 被判断过，但是由于遵从左闭，right = mid - 1
				left = mid + 1;
			else
				return mid;
		}
		return -1;
	}
};
```

#### 左闭右开 [left, right)：

每次构建或者更新区间的时候牢牢把握左闭右开原则。

```C++
class Solution2    // [left, right)
{
 public:
	int search(vector<int>& nums, int target)
	{
		int left = 0;
		int right = (int)nums.size();  // 遵从右开，包含更大一些的范围
		int mid = 0;

		// 遵从左闭右开，left == right 时，[left, right) 是无效区间，因此是 left < right
		while (left < right)
		{
			mid = (left + right) / 2;

			if (target < nums[mid])
				// 虽然 mid 被判断过，但是由于遵从右开，right = mid，需要包含的范围大一些
				right = mid;
			else if (target > nums[mid])
				// mid 被判断过，但是由于遵从左闭，left = mid + 1
				left = mid + 1;
			else
				return mid;
		}
		return -1;
	}
};
```

### 27. 移除元素  
[LeetCode](https://leetcode.cn/problems/remove-element/)  [文章讲解](https://programmercarl.com/0027.%E7%A7%BB%E9%99%A4%E5%85%83%E7%B4%A0.html)  [视频讲解](https://www.bilibili.com/video/BV12A4y1Z7LP)

#### 题目描述：

给你一个数组 nums 和一个值 val，你需要 **原地** 移除所有数值等于 val 的元素，并返回移除后数组的新长度。

不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并 **原地** 修改输入数组。

元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。

示例 1: 给定 nums = [3,2,2,3], val = 3, 函数应该返回新的长度 2, 并且 nums 中的前两个元素均为 2。 **你不需要考虑数组中超出新长度后面的元素**。

示例 2: 给定 nums = [0,1,2,2,3,0,4,2], val = 2, 函数应该返回新的长度 5, 并且 nums 中的前五个元素为 0, 1, 3, 0, 4。**你不需要考虑数组中超出新长度后面的元素**。

#### 我的解法（暴力解法）：

第一版采用的暴力解法，值得注意的是，下标 `i` 以后的元素都往前移动了一位，因此 `i` 也需要往前移动一位，以免恰好 `i` 的下一个元素的值也为 `val` 时，正好被错过了。

```C++
class MySolution    // 暴力解法
{
 public:
    int removeElement(vector<int>& nums, int val)
    {
       int len = (int)nums.size();
       for (int i = 0; i < len; ++i)
       {
          if (nums[i] == val)
          {
             for (int j = i; j < len - 1; ++j)
             {
                nums[j] = nums[j + 1];
             }
             nums[len - 1] = 0; // 后面的值赋 0 
             i--;    // 需要前移一位，以免后移的数据中含有目标值
             len--;  // 此时数组大小也需要减 1
          }
       }
       return len;
    }
};
```

#### 快慢指针法：

快指针：指向需要往新数组中进行移动的元素的下标，即跳过为 `val` 的值；

慢指针：指向新数组中的下标。

![双指针法](imgs/27.移除元素-双指针法.gif)

```C++
class Solution    // 双指针法
{
 public:
	int removeElement(vector<int>& nums, int val)
	{
		int slow = 0;
		for (int fast = 0; fast < nums.size(); ++fast)
		{
			if (nums[fast] != val)
				nums[slow++] = nums[fast];
		}

		return slow;
	}
};
```


### 今日总结

今天的题目总的来说都不是特别难，自己没有看解答就能够完成，但是都不够丝滑，时间上的消耗反而不少。第一题卡在循环结束条件的判断，第二题 `i` 需要前移一位也没想到，都是通过 debug 出来的。

二分查找的左闭右闭和左闭右开，以及移除元素的双指针法都很巧妙，看完卡哥视频讲解后，写代码的时候非常丝滑。

自己做题思路不够清晰，没有水到渠成的感觉，不依靠 debug 总是会漏掉一些情况。 
