## Day28: 回溯算法part04

### 93.复原IP地址

[LeetCode](https://leetcode.cn/problems/restore-ip-addresses/)  [文章讲解](https://programmercarl.com/0093.%E5%A4%8D%E5%8E%9FIP%E5%9C%B0%E5%9D%80.html)  [视频讲解](https://www.bilibili.com/video/BV1XP4y1U73i/)

#### 题目描述：

**有效 IP 地址** 正好由四个整数（每个整数位于 `0` 到 `255` 之间组成，且不能含有前导 `0`），整数之间用 `'.'` 分隔。

- 例如：`"0.1.2.201"` 和` "192.168.1.1"` 是 **有效** IP 地址，但是 `"0.011.255.245"`、`"192.168.1.312"` 和 `"192.168@1.1"` 是 **无效** IP 地址。

给定一个只包含数字的字符串 `s` ，用以表示一个 IP 地址，返回所有可能的**有效 IP 地址**，这些地址可以通过在 `s` 中插入 `'.'` 来形成。你 **不能** 重新排序或删除 `s` 中的任何数字。你可以按 **任何** 顺序返回答案。

**示例 1：**

> 输入：s = "25525511135"
> 输出：["255.255.11.135","255.255.111.35"]

**示例 2：**

> 输入：s = "0000"
> 输出：["0.0.0.0"]

**示例 3：**

> 输入：s = "101023"
> 输出：["1.0.10.23","1.0.102.3","10.1.0.23","10.10.2.3","101.0.2.3"]

#### 我的解法：

切割问题可以抽象为树型结构，如图：

![93.复原IP地址](imgs/20201123203735933.png)

```C++
class Solution
{
 private:
	vector<string> m_result; // 记录结果

	// startIndex: 搜索的起始位置，nums: 递归的次数
	void backtracking(const string& str, int startIndex, string ip, int nums)
	{
		// 如果起始位置已经大于s的大小，说明已经找到了一组分割方案了
		if (startIndex == str.size())
		{
			if (nums == 4)
			{
				ip.pop_back(); // 去掉最后多的一个 .
				m_result.push_back(ip);
			}

			return;
		}

		// 子串的范围为 [startIndex, i]
		for (int i = startIndex; i < str.size(); ++i)
		{
			string sub_str = str.substr(startIndex, i - startIndex + 1);

			// 不合法，直接结束本层循环
			if (!isValid(sub_str)) continue;

            // 隐含回溯
			backtracking(str, i + 1, ip + sub_str + '.', nums + 1);
		}
	}

 public:
	bool isValid(const string& s)
	{
		// 为空 或者 大于三位数 都是非法的
		if (s.empty() || s.size() > 3)
			return false;
		// 只有一位数 必然是有效的
		else if (s.size() == 1)
			return true;
		// 两位数需要判断第一位不是0
		else if (s.size() == 2)
		{
			if (s[0] == '0')
				return false;

			return true;
		}
		// 三位数，需要判断第一位不是0且小于255
		else
		{
			if (s[0] == '0')
				return false;

			if (stoi(s) > 255)
				return false;

			return true;
		}
	}

	vector<string> restoreIpAddresses(const string& str)
	{
		m_result.clear();
		backtracking(str, 0, "", 0);
		return m_result;
	}
};
```

#### 参考解法：

```cpp
class Solution2
{
 private:
    vector<string> result;// 记录结果
    // startIndex: 搜索的起始位置，pointNum:添加逗点的数量
    void backtracking(string& s, int startIndex, int pointNum)
    {
       if (pointNum == 3)
       { // 逗点数量为3时，分隔结束
          // 判断第四段子字符串是否合法，如果合法就放进result中
          if (isValid(s, startIndex, s.size() - 1))
          {
             result.push_back(s);
          }
          return;
       }
       for (int i = startIndex; i < s.size(); i++)
       {
          if (isValid(s, startIndex, i))
          { // 判断 [startIndex,i] 这个区间的子串是否合法
             s.insert(s.begin() + i + 1, '.');  // 在i的后面插入一个逗点
             pointNum++;
             backtracking(s, i + 2, pointNum);   // 插入逗点之后下一个子串的起始位置为i+2
             pointNum--;                         // 回溯
             s.erase(s.begin() + i + 1);         // 回溯删掉逗点
          }
          else break; // 不合法，直接结束本层循环
       }
    }
    // 判断字符串s在左闭又闭区间[start, end]所组成的数字是否合法
    bool isValid(const string& s, int start, int end)
    {
       if (start > end)
       {
          return false;
       }
       if (s[start] == '0' && start != end)
       { // 0开头的数字不合法
          return false;
       }
       int num = 0;
       for (int i = start; i <= end; i++)
       {
          if (s[i] > '9' || s[i] < '0')
          { // 遇到非数字字符不合法
             return false;
          }
          num = num * 10 + (s[i] - '0');
          if (num > 255)
          { // 如果大于255了不合法
             return false;
          }
       }
       return true;
    }
 public:
    vector<string> restoreIpAddresses(string s)
    {
       result.clear();
       if (s.size() < 4 || s.size() > 12) return result; // 算是剪枝了
       backtracking(s, 0, 0);
       return result;
    }
};
```


### 78.子集

[LeetCode](https://leetcode.cn/problems/subsets/)  [文章讲解](https://programmercarl.com/0078.%E5%AD%90%E9%9B%86.html)  [视频讲解](https://www.bilibili.com/video/BV1U84y1q7Ci/)

#### 题目描述：

给你一个整数数组 `nums` ，数组中的元素 **互不相同** 。返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。你可以按 **任意顺序** 返回解集。

**示例 1：**

> 输入：nums = [1,2,3]
> 输出：[[],[1],[2],[1,2],[3],[1,3],[2,3],[1,2,3]]

**示例 2：**

> 输入：nums = [0]
> 输出：[[],[0]]

#### 我的解法：

子集也是一种组合问题，因为它的集合是无序的，子集{1,2} 和 子集{2,1}是一样的。

**那么既然是无序，取过的元素不会重复取，写回溯算法的时候，for就要从startIndex开始，而不是从0开始！**

什么时候for可以从0开始呢？

求排列问题的时候，就要从0开始，因为集合是有序的，{1, 2} 和{2, 1}是两个集合。

以示例中nums = [1,2,3]为例把求子集抽象为树型结构，如下：

![78.子集](imgs/78.子集.png)

从图中红线部分，可以看出**遍历这个树的时候，把所有节点都记录下来，就是要求的子集集合**。

```C++
class Solution
{
 private:
	vector<int> m_path;
	vector<vector<int>> m_result;

	void backtracking(vector<int>& nums, int startIndex)
	{
        // 所有的情况都需要记录结果
		m_result.push_back(m_path);

		for (int i = startIndex; i < nums.size(); ++i)
		{
			m_path.push_back(nums[i]);
			backtracking(nums, i + 1);
			m_path.pop_back();
		}
	}

 public:
	vector<vector<int>> subsets(vector<int>& nums)
	{
		m_path.clear();
		m_result.clear();
		backtracking(nums, 0);
		return m_result;
	}
};
```

### 90.子集II

[LeetCode](https://leetcode.cn/problems/subsets-ii/)  [文章讲解](https://programmercarl.com/0090.%E5%AD%90%E9%9B%86II.html)  [视频讲解](https://www.bilibili.com/video/BV1vm4y1F71J/)

#### 题目描述：

给你一个整数数组 `nums` ，其中可能包含重复元素，请你返回该数组所有可能的子集（幂集）。

解集 **不能** 包含重复的子集。返回的解集中，子集可以按 **任意顺序** 排列。

**示例 1：**

> 输入：nums = [1,2,2]
> 输出：[[],[1],[1,2],[1,2,2],[2],[2,2]]

**示例 2：**

> 输入：nums = [0]
> 输出：[[],[0]]

#### 我的解法：

用示例中的[1, 2, 2] 来举例，如图所示： （**注意去重需要先对集合排序**）

![90.子集II](imgs/20201124195411977.png)

从图中可以看出，同一树层上重复取2 就要过滤掉，同一树枝上就可以重复取2，因为同一树枝上元素的集合才是唯一子集！

```C++
class Solution
{
	vector<int> m_path;
	vector<vector<int>> m_result;

	void backtracking(vector<int>& nums, int startIndex)
	{
		m_result.push_back(m_path);

		for (int i = startIndex; i < nums.size(); ++i)
		{
			// 去重，树层去重
			if (i > startIndex && nums[i] == nums[i - 1]) continue;

			m_path.push_back(nums[i]);
			backtracking(nums, i + 1);
			m_path.pop_back();
		}
	}

 public:
	vector<vector<int>> subsetsWithDup(vector<int>& nums)
	{
		m_path.clear();
		m_result.clear();
		// 排序，使相同的元素在一起
		sort(nums.begin(), nums.end());
		backtracking(nums, 0);
		return m_result;
	}
};
```

### 今日总结

今天的题目思路跟昨天的差不多，做过类似的题目之后很容易想到，三道题目都提交通过了。
