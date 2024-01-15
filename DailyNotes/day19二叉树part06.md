## Day19: 二叉树part06

### 654. 最大二叉树
[LeetCode](https://leetcode.cn/problems/maximum-binary-tree/)  [文章讲解](https://programmercarl.com/0654.%E6%9C%80%E5%A4%A7%E4%BA%8C%E5%8F%89%E6%A0%91.html)  [视频讲解](https://www.bilibili.com/video/BV1MG411G7ox/)

#### 题目描述：

给定一个不重复的整数数组 `nums` 。 **最大二叉树** 可以用下面的算法从 `nums` 递归地构建:

1. 创建一个根节点，其值为 `nums` 中的最大值。
2. 递归地在最大值 **左边** 的 **子数组前缀上** 构建左子树。
3. 递归地在最大值 **右边** 的 **子数组后缀上** 构建右子树。

返回 *`nums` 构建的* ***最大二叉树\*** 。

**示例 1：**

![img](imgs/tree1-17052314729591.jpg)

> 输入：nums = [3,2,1,6,0,5]
> 输出：[6,3,5,null,2,0,null,null,1]
> 解释：递归调用如下所示：
> - [3,2,1,6,0,5] 中的最大值是 6 ，左边部分是 [3,2,1] ，右边部分是 [0,5] 。
>     - [3,2,1] 中的最大值是 3 ，左边部分是 [] ，右边部分是 [2,1] 。
>         - 空数组，无子节点。
>         - [2,1] 中的最大值是 2 ，左边部分是 [] ，右边部分是 [1] 。
>             - 空数组，无子节点。
>             - 只有一个元素，所以子节点是一个值为 1 的节点。
>     - [0,5] 中的最大值是 5 ，左边部分是 [0] ，右边部分是 [] 。
>         - 只有一个元素，所以子节点是一个值为 0 的节点。
>         - 空数组，无子节点。

#### 我的解法：

最大二叉树的构建过程如下：

![654.最大二叉树](imgs/654.最大二叉树.gif)

构造树一般采用的是前序遍历，因为先构造中间节点，然后递归构造左子树和右子树。

- 确定递归函数的参数和返回值

参数传入的是存放元素的数组，返回该数组构造的二叉树的头结点，返回类型是指向节点的指针。

```c++
TreeNode* constructMaximumBinaryTree(vector<int>& nums)
```

- 确定终止条件

如果传入的数组大小为1，说明遍历到了叶子节点了。那么应该定义一个新的节点，并把这个数组的数值赋给新的节点，然后返回这个节点。 

- 确定单层递归的逻辑

这里有三步工作

1. 先要找到数组中最大的值和对应的下标， 最大的值构造根节点，下标用来下一步分割数组。

2. 最大值所在的下标左区间 构造左子树

3. 最大值所在的下标右区间 构造右子树

整体代码如下：

```cpp
class Solution
{
 public:
	int getMaxIndex(vector<int>& nums)
	{
		int max_index = 0;
		for (int i = 1; i < nums.size(); ++i)
		{
			if (nums[i] > nums[max_index]) max_index = i;
		}
		return max_index;
	}

	TreeNode* constructMaximumBinaryTree(vector<int>& nums)
	{
		// 空节点返回
		if (nums.empty()) return nullptr;

		// 获取根节点
		int rootIndex = getMaxIndex(nums);
		auto root = new TreeNode(nums[rootIndex]);
		if (nums.size() == 1) return root; // 叶子节点

		// 分割左区间，左开右闭
		vector<int> leftNums(nums.begin(), nums.begin() + rootIndex);

		// 分割右区间，左开右闭
		vector<int> rightNums(nums.begin() + rootIndex + 1, nums.end());

		// 递归处理
		root->left = constructMaximumBinaryTree(leftNums);
		root->right = constructMaximumBinaryTree(rightNums);

		return root;
	}
};
```

以上代码比较冗余，效率也不高，每次还要切割的时候每次都要定义新的vector（也就是数组），但逻辑比较清晰。

优化思路，就是每次分隔不用定义新的数组，而是通过下标索引直接在原数组上操作：

```cpp
class Solution2    // 优化版
{
 private:
	// 左闭右开
	TreeNode* traversal(vector<int>& nums, int left, int right)
	{
		// 空节点返回
		if (left >= right) return nullptr;

		// 寻找最大节点
		int max_index = left;
		for (int i = left + 1; i < right; ++i)
		{
			if (nums[i] > nums[max_index]) max_index = i;
		}
		auto root = new TreeNode(nums[max_index]);
		if (left == right + 1) return root;    // 叶子节点返回

		// 分割左区间
		root->left = traversal(nums, left, max_index);

		// 分割右区间
		root->right = traversal(nums, max_index + 1, right);

		return root;
	}

 public:
	TreeNode* constructMaximumBinaryTree(vector<int>& nums)
	{
		return traversal(nums, 0, nums.size());
	}
};
```

**注意类似用数组构造二叉树的题目，每次分隔尽量不要定义新的数组，而是通过下标索引直接在原数组上操作，这样可以节约时间和空间上的开销。**

### 617.合并二叉树
[LeetCode](https://leetcode.cn/problems/merge-two-binary-trees/)  [文章讲解](https://programmercarl.com/0617.%E5%90%88%E5%B9%B6%E4%BA%8C%E5%8F%89%E6%A0%91.html)  [视频讲解](https://www.bilibili.com/video/BV1m14y1Y7JK/)

#### 题目描述：

给你两棵二叉树： `root1` 和 `root2` 。

想象一下，当你将其中一棵覆盖到另一棵之上时，两棵树上的一些节点将会重叠（而另一些不会）。你需要将这两棵树合并成一棵新二叉树。合并的规则是：如果两个节点重叠，那么将这两个节点的值相加作为合并后节点的新值；否则，**不为** null 的节点将直接作为新二叉树的节点。

返回合并后的二叉树。

**注意:** 合并过程必须从两个树的根节点开始。

**示例 1：**

![img](imgs/merge.jpg)

> 输入：root1 = [1,3,2,5], root2 = [2,1,3,null,4,null,7]
> 输出：[3,4,5,5,4,null,7]

#### 我的解法：

分情况，逐个节点遍历，完全生成一棵全新的树

```C++
class Solution
{
 public:
	TreeNode* mergeTrees(TreeNode* root1, TreeNode* root2)
	{
		// 终止条件
		if (root1 == nullptr && root2 == nullptr) return nullptr;

		// 递归处理，分情况
		TreeNode* root = nullptr;
		if (root1 == nullptr)
		{
			root = new TreeNode(root2->val);
			root->left = mergeTrees(nullptr, root2->left);
			root->right = mergeTrees(nullptr, root2->right);
		}
		else if (root2 == nullptr)
		{
			root = new TreeNode(root1->val);
			root->left = mergeTrees(root1->left, nullptr);
			root->right = mergeTrees(root1->right, nullptr);
		}
		else
		{
			root = new TreeNode(root1->val + root2->val);
			root->left = mergeTrees(root1->left, root2->left);
			root->right = mergeTrees(root1->right, root2->right);
		}

		return root;
	}
};
```

#### 简化解法：

本题使用哪种遍历都是可以的，注意此方法会修改 t1 的值，同时新生成的树会共用 t1 或者 t2 的部分，析构时候容易出现错误。

```C++
class Solution {
public:
    TreeNode* mergeTrees(TreeNode* t1, TreeNode* t2) {
        if (t1 == nullptr) return t2; // 如果t1为空，合并之后就应该是t2
        if (t2 == nullptr) return t1; // 如果t2为空，合并之后就应该是t1
        // 修改了t1的数值和结构
        t1->val += t2->val;                             // 中
        t1->left = mergeTrees(t1->left, t2->left);      // 左
        t1->right = mergeTrees(t1->right, t2->right);   // 右
        return t1;
    }
};
```


### 700.二叉搜索树中的搜索

[LeetCode](https://leetcode.cn/problems/search-in-a-binary-search-tree/)  [文章讲解](https://programmercarl.com/0700.%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E4%B8%AD%E7%9A%84%E6%90%9C%E7%B4%A2.html)  [视频讲解](https://www.bilibili.com/video/BV1wG411g7sF/)

#### 题目描述：

给定二叉搜索树（BST）的根节点 `root` 和一个整数值 `val`。

你需要在 BST 中找到节点值等于 `val` 的节点。 返回以该节点为根的子树。 如果节点不存在，则返回 `null` 。

**示例 1:**

![img](imgs/tree1-17052385375474.jpg)

> 输入：root = [4,2,7,1,3], val = 2
> 输出：[2,1,3]

**示例 2:**

![img](imgs/tree2-17052385375496.jpg)

> 输入：root = [4,2,7,1,3], val = 5
> 输出：[]

#### 我的解法（递归法）：

```C++
class Solution
{
 public:
	TreeNode* searchBST(TreeNode* root, int val)
	{
		if (root == nullptr || root->val == val) return root;
		if (root->val < val) return searchBST(root->right, val);
		if(root->val > val) return searchBST(root->left, val);
		return nullptr;
	}
};
```

#### 迭代法：

对于一般二叉树，递归过程中还有回溯的过程，例如走一个左方向的分支走到头了，那么要调头，在走右分支。

而**对于二叉搜索树，不需要回溯的过程，因为节点的有序性就帮我们确定了搜索的方向。**

```C++
class Solution2
{
 public:
    TreeNode* searchBST(TreeNode* root, int val)
    {
       while (root != nullptr)
       {
          if (root->val > val) root = root->left;
          else if (root->val < val) root = root->right;
          else return root;
       }
       return nullptr;
    }
};
```

### 98.验证二叉搜索树

[LeetCode](https://leetcode.cn/problems/validate-binary-search-tree/)  [文章讲解](https://programmercarl.com/0098.%E9%AA%8C%E8%AF%81%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91.html)  [视频讲解](https://www.bilibili.com/video/BV18P411n7Q4/)

#### 题目描述：

给你一个二叉树的根节点 `root` ，判断其是否是一个有效的二叉搜索树。

**有效** 二叉搜索树定义如下：

- 节点的左子树只包含 **小于** 当前节点的数。
- 节点的右子树只包含 **大于** 当前节点的数。
- 所有左子树和右子树自身必须也是二叉搜索树。

**示例 1：**

![img](imgs/tree1-17052386271608.jpg)

> 输入：root = [2,1,3]
> 输出：true

**示例 2：**

![img](imgs/tree2-17052386271619.jpg)

> 输入：root = [5,1,4,null,null,3,6]
> 输出：false
> 解释：根节点的值是 5 ，但是右子节点的值是 4 。

#### 直观法：

中序遍历下，输出的二叉搜索树节点的数值是有序序列。有了这个特性，**验证二叉搜索树，就相当于变成了判断一个序列是不是递增的了。**

```C++

```

#### 递归法

边遍历边记录当前最大值。

递归三部曲：

- 确定递归函数，返回值以及参数

要定义一个longlong的全局变量，用来比较遍历的节点是否有序，因为后台测试数据中有int最小值，所以定义为longlong的类型，初始化为longlong最小值。

注意递归函数要有bool类型的返回值， 在寻找一个不符合条件的节点，如果没有找到这个节点就遍历了整个树，如果找到不符合的节点了，立刻返回。

```cpp
long long maxVal = LONG_MIN; // 因为后台测试数据中有int最小值
bool isValidBST(TreeNode* root)
```

- 确定终止条件

如果是空节点，仍是二叉搜索树

```cpp
if (root == nullptr) return true;
```

- 确定单层递归的逻辑

中序遍历，一直更新maxVal，一旦发现maxVal >= root->val，就返回false，**注意元素相同时候也要返回false**。

```cpp
bool left = isValidBST(root->left);         // 左

// 中序遍历，验证遍历的元素是不是从小到大
if (maxVal < root->val) maxVal = root->val; // 中
else return false;

bool right = isValidBST(root->right);       // 右
return left && right;
```

整体代码如下：

```cpp
class Solution2
{
 public:
	long long maxVal = LONG_MIN; // 因为后台测试数据中有int最小值
	bool isValidBST(TreeNode* root)
	{
		if (root == nullptr) return true;

		bool left = isValidBST(root->left);
		// 中序遍历，验证遍历的元素是不是从小到大
		if (maxVal < root->val) maxVal = root->val;
		else return false;
		bool right = isValidBST(root->right);

		return left && right;
	}
};
```

以上代码是因为后台数据有int最小值测试用例，所以都把maxVal改成了longlong最小值。

如果测试数据中有 longlong的最小值，怎么办？

不可能在初始化一个更小的值了吧。 建议避免 初始化最小值，如下方法取到最左面节点的数值来比较。

代码如下：

```cpp
class Solution {
public:
    TreeNode* pre = nullptr; // 用来记录前一个节点
    bool isValidBST(TreeNode* root) {
        if (root == NULL) return true;
        bool left = isValidBST(root->left);

        if (pre != NULL && pre->val >= root->val) return false;
        pre = root; // 记录前一个节点

        bool right = isValidBST(root->right);
        return left && right;
    }
};
```

### 今日总结

前三题都做出来了，第四题掉陷阱里了。**判断二叉搜索树不能单纯的比较左节点小于中间节点，右节点大于中间节点**。