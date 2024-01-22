## Day27: 回溯算法part03

### 39. 组合总和

[LeetCode](https://leetcode.cn/problems/combination-sum/)  [文章讲解](https://programmercarl.com/0039.%E7%BB%84%E5%90%88%E6%80%BB%E5%92%8C.html)  [视频讲解](https://www.bilibili.com/video/BV1KT4y1M7HJ/)

#### 题目描述：

给你一个 **无重复元素** 的整数数组 `candidates` 和一个目标整数 `target` ，找出 `candidates` 中可以使数字和为目标数 `target` 的 所有 **不同组合** ，并以列表形式返回。你可以按 **任意顺序** 返回这些组合。

`candidates` 中的 **同一个** 数字可以 **无限制重复被选取** 。如果至少一个数字的被选数量不同，则两种组合是不同的。 

对于给定的输入，保证和为 `target` 的不同组合数少于 `150` 个。

**示例 1：**

> 输入：candidates = [2,3,6,7], target = 7
> 输出：[[2,2,3],[7]]
> 解释：
> 2 和 3 可以形成一组候选，2 + 2 + 3 = 7 。注意 2 可以使用多次。
> 7 也是一个候选， 7 = 7 。
> 仅有这两种组合。

**提示**：1 <= candidates[i] <= 200，即不会出现0

#### 我的解法：

回溯模版题，精髓在于 `startIndex=i`，因为单个元素可以重复选取。

![39.组合总和](imgs/20201223170730367-20230310135342472.png)

```C++
class Solution
{
 private:
	vector<int> m_path;
	vector<vector<int>> m_result;

	void backtracking(vector<int>& candidates, int startIndex, int target)
	{
		// 剪枝
		if (target < 0) return;

		// 找到目标结果
		if (target == 0)
		{
			m_result.push_back(m_path);
			return;
		}

		for (int i = startIndex; i < candidates.size(); ++i)
		{
			m_path.push_back(candidates[i]);
			backtracking(candidates, i, target - candidates[i]); // target - num 隐藏回溯
			m_path.pop_back();    // 回溯
		}
	}

 public:
	vector<vector<int>> combinationSum(vector<int>& candidates, int target)
	{
		m_path.clear();
		m_result.clear();
		backtracking(candidates, 0, target);
		return m_result;
	}
};
```

### 40.组合总和II

[LeetCode](https://leetcode.cn/problems/combination-sum-ii/)  [文章讲解](https://programmercarl.com/0040.%E7%BB%84%E5%90%88%E6%80%BB%E5%92%8CII.html)  [视频讲解](https://www.bilibili.com/video/BV12V4y1V73A/)

#### 题目描述：

给定一个候选人编号的集合 `candidates` 和一个目标数 `target` ，找出 `candidates` 中所有可以使数字和为 `target` 的组合。

`candidates` 中的每个数字在每个组合中只能使用 **一次** 。

**注意：**解集不能包含重复的组合。 

**示例 1:**

> 输入: candidates = [10,1,2,7,6,1,5], target = 8,
> 输出:
> [
> [1,1,6],
> [1,2,5],
> [1,7],
> [2,6]
> ]

**示例 2:**

> 输入: candidates = [2,5,2,1,2], target = 5,
> 输出:
> [
> [1,2,2],
> [5]
> ]

#### 思路：

把所有组合求出来，再用set或者map去重，这么做很容易超时！例如，测试例子中 `candidates` 为 40 多个 1，`target=30`。

选择过程树形结构如图所示：

![40.组合总和II](imgs/20230310000918.png)

##### 回溯三部曲

首先将`candidates`，进行排序，使得重复的元素在一起。

- **递归函数参数**

与[39.组合总和](https://programmercarl.com/0039.组合总和.html)套路相同，此题还需要加一个bool型数组used，用来记录同一树枝上的元素是否使用过。这个集合去重的重任就是used来完成的。代码如下：

```cpp
vector<vector<int>> result; // 存放组合集合
vector<int> path;           // 符合条件的组合
void backtracking(vector<int>& candidates, int target, int sum, int startIndex, vector<bool>& used) {
```

- **递归终止条件**

与[39.组合总和](https://programmercarl.com/0039.组合总和.html)相同，终止条件为 `sum > target` 和 `sum == target`。代码如下：

```cpp
if (sum > target) {
    return;
}
if (sum == target) {
    result.push_back(path);
    return;
}
```

- **单层搜索的逻辑**

这里与[39.组合总和](https://programmercarl.com/0039.组合总和.html)最大的不同就是要去重了。**如果`candidates[i] == candidates[i - 1]` 并且 `used[i - 1] == false`，就说明：前一个树枝，使用了`candidates[i - 1]`，也就是说同一树层使用过`candidates[i - 1]`**。此时for循环里就应该做continue的操作。

**如果`candidates[i] == candidates[i - 1]` 并且 `used[i - 1] == false`，表示的是上一树层使用过`candidates[i - 1]`，此时不应该跳过，否则会导致类似`[1, 1, 1]`之类的结果没有被收集到**

总结来说就是，**重复的结果导致的原因就是同一层使用了相同的元素**。

这块比较抽象，如图：

![40.组合总和II1](imgs/20230310000954.png)

在candidates[i] == candidates[i - 1]相同的情况下：

- used[i - 1] == true，说明同一树枝candidates[i - 1]使用过
- used[i - 1] == false，说明同一树层candidates[i - 1]使用过

为什么 used[i - 1] == false 就是同一树层呢，因为同一树层，used[i - 1] == false 才能表示，当前取的 candidates[i] 是从 candidates[i - 1] 回溯而来的。而 used[i - 1] == true，说明是进入下一层递归，去下一个数，所以是树枝上，如图所示：

![img](imgs/20221021163812.png)

整体C++代码如下：

```cpp
class Solution
{
 private:
	vector<int> m_path;
	vector<vector<int>> m_result;

	void backtracking(vector<int>& candidates, vector<bool>& used, int startIndex, int target)
	{
		// 剪枝
		if (target < 0) return;

		// 找到目标结果
		if (target == 0)
		{
			m_result.push_back(m_path);
			return;
		}

		for (int i = startIndex; i < candidates.size(); ++i)
		{
			// 树层去重，!used[i - 1] 表示是在树层的位置去重
			if (i > 0 && candidates[i] == candidates[i - 1] && !used[i - 1])
			{
				continue;
			}

			m_path.push_back(candidates[i]);
			used[i] = true;
			backtracking(candidates, used, i + 1, target - candidates[i]); // target - num 隐藏回溯
			m_path.pop_back();    	// 回溯
			used[i] = false;		// 回溯
		}
	}

 public:
	vector<vector<int>> combinationSum2(vector<int> candidates, int target)
	{
		vector<bool> used(candidates.size(), false);
		m_path.clear();
		m_result.clear();
		// 首先把给candidates排序，让其相同的元素都挨在一起。
		sort(candidates.begin(), candidates.end());
		backtracking(candidates, used, 0, target);
		return m_result;
	}
};
```

##### 优化

直接用`startIndex`来去重， 就不用used数组了。

`i > startIndex && candidates[i] == candidates[i - 1]`即保证了每一层的去重，某个元素在某一层（一个for中）第一次出现采用，第二次出现跳过。

```cpp
class Solution2
{
 private:
    vector<int> m_path;
    vector<vector<int>> m_result;

    void backtracking(vector<int>& candidates, int startIndex, int target)
    {
       // 剪枝
       if (target < 0) return;

       // 找到目标结果
       if (target == 0)
       {
          m_result.push_back(m_path);
          return;
       }

       for (int i = startIndex; i < candidates.size(); ++i)
       {
          // 树层去重
          if (i > startIndex && candidates[i] == candidates[i - 1])
          {
             continue;
          }

          m_path.push_back(candidates[i]);
          backtracking(candidates, i + 1, target - candidates[i]); // target - num 隐藏回溯
          m_path.pop_back();        // 回溯
       }
    }

 public:
    vector<vector<int>> combinationSum2(vector<int> candidates, int target)
    {
       m_path.clear();
       m_result.clear();
       // 首先把给candidates排序，让其相同的元素都挨在一起。
       sort(candidates.begin(), candidates.end());
       backtracking(candidates, 0, target);
       return m_result;
    }
};
```


### 131.分割回文串

[LeetCode](https://leetcode.cn/problems/palindrome-partitioning/)  [文章讲解](https://programmercarl.com/0131.%E5%88%86%E5%89%B2%E5%9B%9E%E6%96%87%E4%B8%B2.html)  [视频讲解](https://www.bilibili.com/video/BV1c54y1e7k6/)

#### 题目描述：

给你一个字符串 `s`，请你将 `s` 分割成一些子串，使每个子串都是 **回文串** 。返回 `s` 所有可能的分割方案。

**回文串** 是正着读和反着读都一样的字符串。

**示例 1：**

> 输入：s = "aab"
> 输出：[["a","a","b"],["aa","b"]]

**示例 2：**

> 输入：s = "a"
> 输出：[["a"]]

#### 思路：

难点：

- 切割问题可以抽象为组合问题
- 如何模拟那些切割线
- 切割问题中递归如何终止
- 在递归循环中如何截取子串
- 如何判断回文

**切割问题类似组合问题**。

例如对于字符串abcdef：

- 组合问题：选取一个a之后，在bcdef中再去选取第二个，选取b之后在cdef中再选取第三个.....。
- 切割问题：切割一个a之后，在bcdef中再去切割第二段，切割b之后在cdef中再切割第三段.....。

感受出来了不？所以切割问题，也可以抽象为一棵树形结构，如图：

![131.分割回文串](imgs/131.分割回文串.jpg)

递归用来纵向遍历，for循环用来横向遍历，切割线（就是图中的红线）切割到字符串的结尾位置，说明找到了一个切割方法。

##### 回溯三部曲

- 递归函数参数

全局变量数组path存放切割后回文的子串，二维数组result存放结果集。 （这两个参数可以放到函数参数里）

本题递归函数参数还需要startIndex，因为切割过的地方，不能重复切割，和组合问题也是保持一致的。

- 递归函数终止条件

切割线切到了字符串最后面，说明找到了一种切割方法，此时就是本层递归的终止条件。递归参数需要传入startIndex，表示下一轮递归遍历的起始位置，这个startIndex就是切割线。

- 单层搜索的逻辑

在`for (int i = startIndex; i < s.size(); i++)`循环中，定义了起始位置startIndex，那么 [startIndex, i] 就是要截取的子串。

首先判断这个子串是不是回文，如果是回文，就加入在`vector<string> path`中，path用来记录切割过的回文子串。否则直接continue。

整体代码如下：

```cpp
class Solution
{
 private:
    vector<string> m_path;
    vector<vector<string>> m_result;

    void backtracking(const string& str, int startIndex)
    {
       // 如果起始位置已经大于s的大小，说明已经找到了一组分割方案了
       if (startIndex == str.size())
       {
          m_result.push_back(m_path);
          return;
       }

       // 子串的范围为 [startIndex, i]
       for (int i = startIndex; i < str.size(); ++i)
       {
          if (isPalindrome(str, startIndex, i))
             m_path.push_back(str.substr(startIndex, i - startIndex + 1));
          else
             continue;

          backtracking(str, i + 1);
          m_path.pop_back();
       }
    }

 public:
    bool isPalindrome(const string& s, int start, int end)
    {
       for (int i = start, j = end; i < j; i++, j--)
       {
          if (s[i] != s[j]) return false;
       }
       return true;
    }

    vector<vector<string>> partition(const string& str)
    {
       m_path.clear();
       m_result.clear();
       backtracking(str, 0);
       return m_result;
    }
};
```


### 今日总结

今天的题目有点小难。重点掌握第二题中去重的思想，以及第三题中将分割问题转化为组合问题的思想。
