## Day07: 哈希表part02

### 454.四数相加II
[LeetCode](https://leetcode.cn/problems/4sum-ii/)  [文章讲解](https://programmercarl.com/0454.%E5%9B%9B%E6%95%B0%E7%9B%B8%E5%8A%A0II.html)  [视频讲解](https://www.bilibili.com/video/BV1Md4y1Q7Yh/)

#### 题目描述：

给你四个整数数组 `nums1`、`nums2`、`nums3` 和 `nums4` ，数组长度都是 `n` ，请你计算有多少个元组 `(i, j, k, l)` 能满足：

- `0 <= i, j, k, l < n`
- `nums1[i] + nums2[j] + nums3[k] + nums4[l] == 0`

**示例 1：**

> 输入：nums1 = [1,2], nums2 = [-2,-1], nums3 = [-1,2], nums4 = [0,2]
> 输出：2
> 解释：
> 两个元组如下：
> 1. (0, 0, 0, 1) -> nums1[0] + nums2[0] + nums3[0] + nums4[1] = 1 + (-2) + (-1) + 2 = 0
> 2. (1, 1, 0, 0) -> nums1[1] + nums2[1] + nums3[0] + nums4[0] = 2 + (-1) + (-1) + 0 = 0

**示例 2：**

> 输入：nums1 = [0], nums2 = [0], nums3 = [0], nums4 = [0]
> 输出：1

#### map哈希表解法：

而这道题目是四个独立的数组，只要找到`A[i] + B[j] + C[k] + D[l] = 0`就可以。可以类似`1.两数之和`的思想，将4个数变成2+2，也是类似于两数之和，区别在于本题map的`value`中记录的是`key`对应的值出现的次数，而不是下标值。

本题解题步骤：

1. 首先定义 一个unordered_map，`key`放`num1`和`num2`两数之和，`value` 放`num1`和`num2`两数之和出现的次数。
2. 遍历`nums1`和`nums2`数组，统计两个数组元素之和，和出现的次数，放到map中。
3. 定义int变量`count`，用来统计 `num1+num2+num3+num4 = 0` 出现的次数。
4. 在遍历`nums3`和`nums4`数组，找到如果 `0-(num3+num4)` 在map中出现过的话，就用`count`把map中`key`对应的`value`也就是出现次数统计出来。
5. 最后返回统计值 `count` 就可以了

```C++
class Solution
{
 public:
	int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4)
	{
		unordered_map<int, int> hash;
		int count = 0;

		for (int num1 : nums1)
		{
			for (int num2 : nums2)
			{
				// 默认创建的值为 0，直接 ++ 即可
				hash[num1 + num2]++;
			}
		}

		for (int num3 : nums3)
		{
			for (int num4 : nums4)
			{
				if (hash.find(0 - (num3 + num4)) != hash.end())
					count += hash[0 - (num3 + num4)];
			}
		}

		return count;
	}
};
```

### 383. 赎金信
[LeetCode](https://leetcode.cn/problems/ransom-note/)  [文章讲解](https://programmercarl.com/0383.%E8%B5%8E%E9%87%91%E4%BF%A1.html)

#### 题目描述：

给你两个字符串：`ransomNote` 和 `magazine` ，判断 `ransomNote` 能不能由 `magazine` 里面的字符构成。如果可以，返回 `true` ；否则返回 `false` 。`magazine` 中的每个字符只能在 `ransomNote` 中使用一次。

**提示：**

- `1 <= ransomNote.length, magazine.length <= 10^5`
- `ransomNote` 和 `magazine` 由小写英文字母组成

**示例 1：**

> 输入：ransomNote = "a", magazine = "b"
> 输出：false

**示例 2：**

> 输入：ransomNote = "aa", magazine = "ab"
> 输出：false

**示例 3：**

> 输入：ransomNote = "aa", magazine = "aab"
> 输出：true

#### 我的解法：

思路同 242.有效的字母异位词。

```C++
class Solution
{
 public:
	bool canConstruct(string ransomNote, string magazine)
	{
		int record[26] = { 0 };

		// 子串大于目标串，不可能出现
		if (ransomNote.size() > magazine.size())
			return false;

		// 通过record数据记录 magazine里各个字符出现次数
		for (int i = 0; i < magazine.length(); i++)
			record[magazine[i] - 'a']++;

		for (int j = 0; j < ransomNote.length(); j++)
		{
			// 遍历ransomNote，在record里对应的字符个数做--操作
			record[ransomNote[j] - 'a']--;

			// 如果小于零说明ransomNote里出现的字符，magazine没有
			if (record[ransomNote[j] - 'a'] < 0)
				return false;
		}
		return true;
	}
};
```

### 15. 三数之和
[LeetCode](https://leetcode.cn/problems/3sum/)  [文章讲解](https://programmercarl.com/0015.%E4%B8%89%E6%95%B0%E4%B9%8B%E5%92%8C.html#)  [视频讲解](https://www.bilibili.com/video/BV1GW4y127qo/)

#### 题目描述：

给你一个包含 n 个整数的数组 nums，判断 nums 中是否存在三个元素 a，b，c ，使得 a + b + c = 0 ？请你找出所有满足条件且不重复的三元组。

**注意：**1、若两个三元组元素一一对应，则认为两个三元组重复；2、a、b和c互不相同。

**示例 1：**

>  输入：nums = [1,0,-1,0,-2,2], target = 0
>  输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

**示例 2：**

>  输入：nums = [2,2,2,2,2], target = 8
>  输出：[[2,2,2,2]]

#### 双指针解法：

![15.三数之和](imgs/15.三数之和.gif)

首先将数组排序，然后有一层for循环，`i`从下标0的地方开始，同时定一个下标`left` 定义在`i+1`的位置上，定义下标`right`在数组结尾的位置上。依然还是在数组中找到 `abc` 使得`a + b +c =0`，我们这里相当于 `a = nums[i]`，`b = nums[left]`，`c = nums[right]`。

接下来如何移动`left`和`right`呢， 如果`nums[i] + nums[left] + nums[right] > 0` 就说明 此时三数之和大了，因为数组是排序后了，所以`right`下标就应该向左移动，这样才能让三数之和小一些。

如果 `nums[i] + nums[left] + nums[right] < 0` 说明 此时 三数之和小了，`left` 就向右移动，才能让三数之和大一些，直到`left`与`right`相遇为止。

时间复杂度：O(n^2)。

```C++
class Solution
{
 public:
	vector<vector<int>> threeSum(vector<int>& nums)
	{
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());

		// 找出a + b + c = 0
		// a = nums[i], b = nums[left], c = nums[right]
		for (int i = 0; i < nums.size(); ++i)
		{
			// 排序之后如果第一个元素已经大于零，那么无论如何组合都不可能凑成三元组，直接返回结果就可以了
			if (nums[i] > 0) return result;

			// 错误去重a方法，将会漏掉-1,-1,2 这种情况
			/*
			if (nums[i] == nums[i + 1]) {
				continue;
			}
			*/

			// 正确去重a方法
			/* 
			 * 因为已经排序过了，只要a前面有一样的，接下来的abc要么是和前面重复的，
			 * 要么就找不到这组了。bc同理只要重复一次就重复了。例如，a[0]=a[1]的
			 * 时候，后者三元组的集合是前者的真子集，就是一个集合问题。
			 * */
			if (i > 0 && nums[i] == nums[i - 1]) continue;

			int left = i + 1;
			int right = nums.size() - 1;

			while (left < right)
			{
				// 去重复逻辑如果放在这里，0，0，0 的情况，可能直接导致 right<=left 了，从而漏掉了 0,0,0 这种三元组
				/*
				while (right > left && nums[right] == nums[right - 1]) right--;
				while (right > left && nums[left] == nums[left + 1]) left++;
				*/
				if (nums[i] + nums[left] + nums[right] > 0) right--;
				else if (nums[i] + nums[left] + nums[right] < 0) left++;
				else
				{
					// cout << i << " " << left << " " << right << endl;
					result.push_back({ nums[i], nums[left], nums[right] });

					// 去重逻辑应该放在找到一个三元组之后，对b 和 c去重
					while (right > left && nums[right] == nums[right - 1]) right--;
					while (right < left && nums[left] == nums[left + 1]) left++;

					// 找到答案时，双指针同时收缩
					right--;
					left++;
				}
			}
		}

		return result;
	}
};
```

### 18. 四数之和
[LeetCode](https://leetcode.cn/problems/4sum/)  [文章讲解](https://programmercarl.com/0018.%E5%9B%9B%E6%95%B0%E4%B9%8B%E5%92%8C.html#)  [视频讲解](https://www.bilibili.com/video/BV1DS4y147US/)

#### 题目描述：

给你一个由 `n` 个整数组成的数组 `nums` ，和一个目标值 `target` 。请你找出并返回满足下述全部条件且**不重复**的四元组 `[nums[a], nums[b], nums[c], nums[d]]` （若两个四元组元素一一对应，则认为两个四元组重复）：

- `0 <= a, b, c, d < n`
- `a`、`b`、`c` 和 `d` **互不相同**
- `nums[a] + nums[b] + nums[c] + nums[d] == target`

你可以按 **任意顺序** 返回答案 。

**示例 1：**

> 输入：nums = [1,0,-1,0,-2,2], target = 0
> 输出：[[-2,-1,1,2],[-2,0,0,2],[-1,0,0,1]]

**示例 2：**

> 输入：nums = [2,2,2,2,2], target = 8
> 输出：[[2,2,2,2]]

#### 双指针解法：

四数之和，和[15.三数之和](https://programmercarl.com/0015.三数之和.html)是一个思路，都是使用双指针法, 基本解法就是在[15.三数之和](https://programmercarl.com/0015.三数之和.html)的基础上再套一层for循环。

但是有一些细节需要注意，例如： 不要判断`nums[i] > target` 就返回了，三数之和 可以通过 `nums[i] > 0` 就返回了，因为 0 已经是确定的数了，四数之和这道题目 target是任意值。比如：数组是`[-4, -3, -2, -1]`，`target`是`-10`，不能因为`-4 > -10`而跳过，此处减枝的逻辑需要进行修改。

[15.三数之和](https://programmercarl.com/0015.三数之和.html)的双指针解法是一层for循环`num[i]`为确定值，然后循环内有`left`和`right`下标作为双指针，找到`nums[i] + nums[left] + nums[right] == 0`。

四数之和的双指针解法是两层for循环`nums[i] + nums[j]`为确定值，依然是循环内有`left`和`right`下标作为双指针，找出`nums[i] + nums[j] + nums[left] + nums[right] == target`的情况，三数之和的时间复杂度是O($n^2$)，四数之和的时间复杂度是O($n^3$) 。

那么一样的道理，五数之和、六数之和等等都采用这种解法。

双指针法将时间复杂度：O(n^2)的解法优化为 O(n)的解法。也就是降一个数量级，题目如下：

- [27.移除元素](https://programmercarl.com/0027.移除元素.html)
- [15.三数之和](https://programmercarl.com/0015.三数之和.html)
- [18.四数之和](https://programmercarl.com/0018.四数之和.html)

链表相关双指针题目：

- [206.反转链表](https://programmercarl.com/0206.翻转链表.html)
- [19.删除链表的倒数第N个节点](https://programmercarl.com/0019.删除链表的倒数第N个节点.html)
- [面试题 02.07. 链表相交](https://programmercarl.com/面试题02.07.链表相交.html)
- [142题.环形链表II](https://programmercarl.com/0142.环形链表II.html)

```C++
class Solution
{
 public:
	vector<vector<int>> fourSum(vector<int>& nums, int target)
	{
		vector<vector<int>> result;
		sort(nums.begin(), nums.end());

		// nums.size()返回的是size_t类型的，也就是无符号整型,所以它不支持负数。
		// 当使用 nums.size()-3 进行计算时，如果结果小于0，它将会被视为一个很大的正数
		// 因此此处虽然 nums.size()-3 逻辑正确，但是实际上会出错，除非进行强转 int(nums.size())-3
		for (int i = 0; i < nums.size(); i++)
		{
			// 一级剪枝，去掉不必要的循环
			// 这里使用break，统一通过最后的return返回
			if ((nums[i] > target) && (nums[i] > 0) && (target > 0)) break;

			// 一级去重，对 i 去重
			if (i > 0 && nums[i] == nums[i - 1]) continue;

			for (int j = i + 1; j < nums.size(); j++)
			{
				/*
				 * 对于 j 的循环，此时相当于 nums[i] + nums[j] 为一个整体，
				 * 同时 j 开始的地方 也就是 i + 1，只有 j > i + 1，j - 1才是合法的。
				 * */

				// 二级剪枝，去掉不必要的循环
				// 这里使用break，统一通过最后的return返回
				if ((nums[i] + nums[j] > target) && (nums[i] + nums[j] > 0) && (target > 0)) break;

				// 一级去重，对 j 去重
				if (j > i + 1 && nums[j] == nums[j - 1]) continue;

				int left = j + 1;
				int right = nums.size() - 1;

				while (left < right)
				{
					// nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
					if ((long)nums[i] + nums[j] + nums[left] + nums[right] > target) right--;
						// nums[k] + nums[i] + nums[left] + nums[right] > target 会溢出
					else if ((long)nums[i] + nums[j] + nums[left] + nums[right] < target) left++;
					else
					{
						// cout << i << " " << left << " " << right << endl;
						result.push_back({ nums[i], nums[j], nums[left], nums[right] });

						// 对nums[left]和nums[right]去重
						while (right > left && nums[right] == nums[right - 1]) right--;
						while (right < left && nums[left] == nums[left + 1]) left++;

						// 找到答案时，双指针同时收缩
						right--;
						left++;
					}
				}
			}
		}
		return result;
	}
};
```
### 哈希表总结

**一般来说哈希表都是用来快速判断一个元素是否出现集合里**。

对于哈希表，要知道**哈希函数**和**哈希碰撞**在哈希表中的作用。

哈希函数是把传入的key映射到符号表的索引上。

哈希碰撞处理有多个key映射到相同索引上时的情景，处理碰撞的普遍方式是拉链法和线性探测法。

接下来是常见的三种哈希结构：

- 数组
- set（集合）
- map（映射）

在C++语言中，set 和 map 都分别提供了三种数据结构，每种数据结构的底层实现和用途都有所不同，例如什么时候用std::set，什么时候用std::multiset，什么时候用std::unordered_set，都是很有考究的。**只有对这些数据结构的底层实现很熟悉，才能灵活使用，否则很容易写出效率低下的程序**。

#### 数组作为哈希表

在[242.有效的字母异位词](https://programmercarl.com/0242.有效的字母异位词.html)中，这道题目包含小写字母，那么使用数组来做哈希最合适不过。数组就是简单的哈希表，但是数组的大小是受限的！

在[383.赎金信](https://programmercarl.com/0383.赎金信.html)中同样要求只有小写字母，那么就给我们浓浓的暗示，用数组！

**上面两道题目用map确实可以，但使用map的空间消耗要比数组大一些，因为map要维护红黑树或者符号表，而且还要做哈希函数的运算。所以数组更加简单直接有效！**

#### set作为哈希表

在[349. 两个数组的交集](https://programmercarl.com/0349.两个数组的交集.html)中给出了什么时候用数组就不行了，需要用set。

这道题目没有限制数值的大小，就无法使用数组来做哈希表了。

**主要因为如下两点：**

- 数组的大小是有限的，受到系统栈空间（不是数据结构的栈）的限制。
- 如果数组空间够大，但哈希值比较少、特别分散、跨度非常大，使用数组就造成空间的极大浪费。

所以此时一样的做映射的话，就可以使用set了。

关于set，C++ 给提供了如下三种可用的数据结构：

- std::set
- std::multiset
- std::unordered_set

std::set和std::multiset底层实现都是红黑树，std::unordered_set的底层实现是哈希， 使用unordered_set 读写效率是最高的，本题并不需要对数据进行排序，而且还不要让数据重复，所以选择unordered_set。

在[202.快乐数](https://programmercarl.com/0202.快乐数.html)中，再次使用了unordered_set来判断一个数是否重复出现过。

#### map作为哈希表

在[1.两数之和](https://programmercarl.com/0001.两数之和.html)中map正式登场。

来说一说：使用数组和set来做哈希法的局限。

- 数组的大小是受限制的，而且如果元素很少，而哈希值太大会造成内存空间的浪费。
- set是一个集合，里面放的元素只能是一个key，而两数之和这道题目，不仅要判断y是否存在而且还要记录y的下标位置，因为要返回x 和 y的下标。所以set 也不能用。

map是一种`<key, value>`的结构，本题可以用key保存数值，用value在保存数值所在的下标。所以使用map最为合适。

C++提供如下三种map：

- std::map
- std::multimap
- std::unordered_map

std::unordered_map 底层实现为哈希，std::map 和std::multimap 的底层实现是红黑树。

同理，std::map 和std::multimap 的key也是有序的（这个问题也经常作为面试题，考察对语言容器底层的理解），[1.两数之和](https://programmercarl.com/0001.两数之和.html)中并不需要key有序，选择std::unordered_map 效率更高！

在[454.四数相加](https://programmercarl.com/0454.四数相加II.html)中我们提到了其实需要哈希的地方都能找到map的身影。

本题咋眼一看好像和[18. 四数之和](https://programmercarl.com/0018.四数之和.html)，[15.三数之和](https://programmercarl.com/0015.三数之和.html)差不多，其实差很多！

**关键差别是本题为四个独立的数组，只要找到A[i] + B[j] + C[k] + D[l] = 0就可以，不用考虑重复问题，而[18. 四数之和](https://programmercarl.com/0018.四数之和.html)，[15.三数之和 ](https://programmercarl.com/0015.三数之和.html)是一个数组（集合）里找到和为0的组合，可就难很多了！**

用哈希法解决了两数之和，感觉用哈希法也可以解决三数之和，四数之和。其实是可以解决，但是非常麻烦，需要去重导致代码效率很低。

所以18. 四数之和，15.三数之和都推荐使用双指针法！

**虽然map是万能的，详细介绍了什么时候用数组，什么时候用set**。

### 今日总结

正如卡哥所说，梦破碎了。。。第三题和第四题没做出来。。。双指针法真牛！