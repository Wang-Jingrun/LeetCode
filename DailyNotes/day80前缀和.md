## Day79: 前缀和

### 1480. 一维数组的动态和

[LeetCode](https://leetcode.cn/problems/running-sum-of-1d-array/)  [文章讲解]()

#### 题目描述：

给你一个数组 `nums` 。数组「动态和」的计算公式为：`runningSum[i] = sum(nums[0]…nums[i])` 。

请返回 `nums` 的动态和。

**示例 1：**

> 输入：nums = [1,2,3,4]
> 输出：[1,3,6,10]
> 解释：动态和计算过程为 [1, 1+2, 1+2+3, 1+2+3+4] 。

**示例 2：**

> 输入：nums = [1,1,1,1,1]
> 输出：[1,2,3,4,5]
> 解释：动态和计算过程为 [1, 1+1, 1+1+1, 1+1+1+1, 1+1+1+1+1] 。

**示例 3：**

> 输入：nums = [3,1,2,10,1]
> 输出：[3,4,6,16,17]

#### 我的解法：

本题的要求就是计算一个前缀和数组。

```C++
// 就是计算前缀和
class Solution
{
 public:
	vector<int> runningSum(vector<int>& nums)
	{
		if (nums.empty()) return {};
		vector<int> result(nums.size());
		result[0] = nums[0];
		for (int i = 1; i < nums.size(); ++i)
		{
			result[i] = result[i - 1] + nums[i];
		}
		return result;
	}
};
```

### 1588. 所有奇数长度子数组的和

[LeetCode](https://leetcode.cn/problems/sum-of-all-odd-length-subarrays/)

#### 题目描述：

给你一个正整数数组 `arr` ，请你计算所有可能的奇数长度子数组的和。

**子数组** 定义为原数组中的一个连续子序列。

请你返回 `arr` 中 **所有奇数长度子数组的和** 。

**示例 1：**

> 输入：arr = [1,4,2,5,3]
> 输出：58
> 解释：所有奇数长度子数组和它们的和为：
> [1] = 1
> [4] = 4
> [2] = 2
> [5] = 5
> [3] = 3
> [1,4,2] = 7
> [4,2,5] = 11
> [2,5,3] = 10
> [1,4,2,5,3] = 15
> 我们将所有值求和得到 1 + 4 + 2 + 5 + 3 + 7 + 11 + 10 + 15 = 58

**示例 2：**

> 输入：arr = [1,2]
> 输出：3
> 解释：总共只有 2 个长度为奇数的子数组，[1] 和 [2]。它们的和为 3 。

**示例 3：**

> 输入：arr = [10,11,12]
> 输出：66

#### 参考解法：

**前缀和**：即数组 `s[i+1]` 来表示前 `i` 个 `arr` 的元素之和（使用 `i + 1` 便于循环处理）---> `区间 [i, j] 的和 = s[j + 1] - s[i]`

其中，特别注意边界问题，`s[i]` 是为了不包含 `arr[i]`，`s[j + 1]` 是为了包含 `arr[j]`，这样才是正确得到了区间 `[i, j]` 的和。

本题只需要在前缀和求区间和的基础上，考虑奇数区间即可。

```C++
class Solution
{
 public:
	int sumOddLengthSubarrays(vector<int>& arr)
	{
		vector<int> s(arr.size() + 1); // 前缀和
		for (int i = 0; i < arr.size(); ++i)
		{
			s[i + 1] = s[i] + arr[i];
		}

		int sum = 0;
		for (int i = 0; i < arr.size(); ++i)
		{
			for (int j = 1; i + j <= arr.size(); j += 2) // 区间长度
			{
				sum += s[i + j] - s[i];
			}
		}
		return sum;
	}
};
```

### 美团笔试. 平衡矩阵

#### 题目描述：

给你一个 `n*n` 的矩阵，其中每个元素都是 0 或者 1。

当且仅当一个矩形区域内 0 的数量恰好等于 1 的数量，则矩形区域就是完美的。

请你返回 `n*n` 的矩阵中，有多少个完美矩形区域，`1<=i<=n`。

**输入描述**：

第一行输入一个正整数 `n`，代表矩阵大小。

接下来的 `n` 行，每行输入一个长度为 `n` 的01串，用来表示矩阵。

**输出描述**：

输出 `n` 行，第 `i` 行输出的 `i*i` 完美矩形区域的数量。

**示例 1：**

> 输入：
>
> 4
> 1010
> 0101
> 1100
> 0011
>
> 输出：
>
> 0
> 7
> 0
> 1

#### 参考解法：

矩形区域是否完美可以转化为求和，如果 0 和 1 的数量各一半，那么就是判断正方形的和是否为 `i*i/2`，如果是则是完美区域，即该问题转化为二维前缀和。

**注意**：写代码的时候要要使用 `sum * 2 == i * i`，而不是`sum == i * i / 2`，后者由于是整数除法，会向下取整，可能导致判断错误。

```C++
#include <iostream>
#include <vector>
using namespace std;
 
int main()
{
    int n;
    cin >> n;
    string temp;
    vector<string> grid(n);
    for (int i = 0; i < n; ++i)
    {
        cin >> grid[i];
    }
 
    // 计算二维前缀和
    vector<vector<int>> s(n + 1, vector<int>(n + 1, 0)); // 前缀和
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            // 左边一格 + 右边一格 - 左上一格(重叠部分) + 当前这格
            s[i + 1][j + 1] = s[i + 1][j] + s[i][j + 1] - s[i][j] + (grid[i][j] == '1');
        }
    }
 	
    // 通过二维前缀和计算区域和
    for (int k = 1; k <= n; ++k)
    {
        int count = 0;
        for (int i = 0; i <= n - k; ++i)
        {
            for (int j = 0; j <= n - k; ++j)
            {
                // 右下顶点格 - 左下顶点格前一格 - 右上顶点格前一格 + 左上顶点格前一格(重叠部分)
                int sum = s[i + k][j + k] - s[i][j + k] - s[i + k][j] + s[i][j];
                if (sum * 2 == k * k) ++count;  // 注意判断方式，不要使用除法
            }
        }
        cout << count << endl;
    }
 
    return 0;
}
```

### 今日总结

学习了一维和二维的前缀和，还是比较巧妙的。
