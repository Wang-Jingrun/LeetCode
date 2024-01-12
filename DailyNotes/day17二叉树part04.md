## Day17: 二叉树part04

### 110.平衡二叉树
[LeetCode](https://leetcode.cn/problems/balanced-binary-tree/)  [文章讲解](https://programmercarl.com/0110.%E5%B9%B3%E8%A1%A1%E4%BA%8C%E5%8F%89%E6%A0%91.html)  [视频讲解](https://www.bilibili.com/video/BV1Ug411S7my/)

#### 题目描述：

给定一个二叉树，判断它是否是高度平衡的二叉树。

本题中，一棵高度平衡二叉树定义为：

> 一个二叉树*每个节点* 的左右两个子树的高度差的绝对值不超过 1 。

**示例 1：**

![img](imgs/balance_1.jpg)

> 输入：root = [3,9,20,null,null,15,7]
> 输出：true

**示例 2：**

![img](imgs/balance_2.jpg)

> 输入：root = [1,2,2,3,3,null,null,4,4]
> 输出：false

#### 递归解法：

咋眼一看这道题目和[104.二叉树的最大深度](https://programmercarl.com/0104.二叉树的最大深度.html)很像，其实有很大区别。

这里强调一波概念：

- 二叉树节点的深度：指从根节点到该节点的最长简单路径边的条数。
- 二叉树节点的高度：指从该节点到叶子节点的最长简单路径边的条数。

但leetcode中强调的深度和高度很明显是按照节点来计算的，如图：

![110.平衡二叉树2](imgs/20210203155515650.png)

关于根节点的深度究竟是1 还是 0，不同的地方有不一样的标准，leetcode的题目中都是以节点为一度，即根节点深度是1。但维基百科上定义用边为一度，即根节点的深度是0，我们暂时以leetcode为准（毕竟要在这上面刷题）。

因为求深度可以从上到下去查 所以需要前序遍历（中左右），而高度只能从下到上去查，所以只能后序遍历（左右中）

而[104.二叉树的最大深度](https://programmercarl.com/0104.二叉树的最大深度.html)中求的是二叉树的最大深度，用的是后序遍历。**那是因为代码的逻辑其实是求的根节点的高度，而根节点的高度就是这棵树的最大深度，所以才可以使用后序遍历。**

```C++
class Solution
{
 public:
	int getHeight(TreeNode* node)
	{
		if (node == nullptr) return 0;

		int leftHeight = getHeight(node->left);
		if (leftHeight == -1) return -1;

		int rightHeight = getHeight(node->right);
		if (rightHeight == -1) return -1;
				
		int result;
		if (abs(leftHeight - rightHeight) > 1)
			// 如果当前传入节点为根节点的二叉树已经不是二叉平衡树了，还返回高度的话就没有意义了。
			// 因此返回 -1 作为标记
            // 一个递归完成了求高度和判断是否平衡两件事
			result = -1;
		else
			result = max(leftHeight, rightHeight) + 1;
		return result;
	}

	bool isBalanced(TreeNode* root)
	{
		return getHeight(root) != -1;
	}
};
```

### 257. 二叉树的所有路径
[LeetCode](https://leetcode.cn/problems/binary-tree-paths/)  [文章讲解](https://programmercarl.com/0257.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E6%89%80%E6%9C%89%E8%B7%AF%E5%BE%84.html)  [视频讲解](https://www.bilibili.com/video/BV1ZG411G7Dh/)

#### 题目描述：

给你一个二叉树的根节点 `root` ，按 **任意顺序** ，返回所有从根节点到叶子节点的路径。

**叶子节点** 是指没有子节点的节点。

**示例 1：**

![img](imgs/paths-tree.jpg)

> 输入：root = [1,2,3,null,5]
> 输出：["1->2->5","1->3"]

#### 递归+回溯：

在这道题目中涉及到回溯，因为要把路径记录下来，需要回溯来回退一个路径再进入另一个路径。前序遍历以及回溯的过程如图：

![257.二叉树的所有路径](imgs/20210204151702443.png)

先使用递归的方式，来做前序遍历。**要知道递归和回溯就是一家的，本题也需要回溯。**

##### 终止判断

在写递归的时候都习惯了这么写：

```C++
if (cur == NULL) {
    终止处理逻辑
}
```

但是本题的终止条件这样写会很麻烦，因为本题要找到叶子节点，就开始结束的处理逻辑了（把路径放进result里）。

**那么什么时候算是找到了叶子节点？** 是当 cur不为空，其左右孩子都为空的时候，就找到叶子节点。

所以本题的终止条件是：

```text
if (cur->left == NULL && cur->right == NULL) {
    终止处理逻辑
}
```

为什么没有判断cur是否为空呢，因为下面的逻辑可以控制空节点不入循环。

##### 终止处理的逻辑

使用 vector 结构path来记录路径，所以要把 vector 结构的path转为string格式，再把这个string 放进 result里。那么终止处理逻辑如下：

```cpp
if (cur->left == NULL && cur->right == NULL) { // 遇到叶子节点
    string sPath;
    for (int i = 0; i < path.size() - 1; i++) { // 将path里记录的路径转为string格式
        sPath += to_string(path[i]);
        sPath += "->";
    }
    sPath += to_string(path[path.size() - 1]); // 记录最后一个节点（叶子节点）
    result.push_back(sPath); // 收集一个路径
    return;
}
```

##### 确定单层递归逻辑

因为是前序遍历，需要先处理中间节点，中间节点就是我们要记录路径上的节点，先放进path中。

```
path.push_back(cur->val);
```

然后是递归和回溯的过程，上面说过没有判断cur是否为空，那么在这里递归的时候，如果为空就不进行下一层递归了。所以递归前要加上判断语句，下面要递归的节点是否为空，如下

```C++
if (cur->left) {
    getPath(cur->left, path, result);
}
if (cur->right) {
    getPath(cur->right, path, result);
}
```

此时还没完，递归完，要做回溯啊，因为path 不能一直加入节点，它还要删节点，然后才能加入新的节点。那么回溯要怎么回溯呢，一些同学会这么写，如下：

```cpp
if (cur->left) {
    getPath(cur->left, path, result);
}
if (cur->right) {
    getPath(cur->right, path, result);
}
path.pop_back();
```

这个回溯就有很大的问题，我们知道，**回溯和递归是一一对应的，有一个递归，就要有一个回溯**，这么写的话相当于把递归和回溯拆开了， 一个在花括号里，一个在花括号外。

**所以回溯要和递归永远在一起，世界上最遥远的距离是你在花括号里，而我在花括号外！**

那么代码应该这么写：

```C++
if (cur->left) {
    getPath(cur->left, path, result);
    path.pop_back(); // 回溯
}
if (cur->right) {
    getPath(cur->right, path, result);
    path.pop_back(); // 回溯
}
```

那么本题整体代码如下：

```C++
class Solution
{
 public:
	void getPath(TreeNode* cur, vector<int>& path, vector<string>& result)
	{
		// 写在这里，因为最后一个节点也要加入到path中
		// 因为结束条件不同了，相当于提早结束了
		path.push_back(cur->val);

		// 处理到叶子节点就开始结束逻辑
		if (cur->left == nullptr && cur->right == nullptr)
		{
			string sPath;

			// 将 path 里记录的路径转化为 string 格式
			for (int i = 0; i < path.size() - 1; ++i)
			{
				sPath += to_string(path[i]);
				sPath += "->";
			}
			sPath += to_string(path[path.size() - 1]); // 记录最后一个节点，即叶子节点
			result.push_back(sPath); // 收集一个路径
			return;
		}

		// 左
		if (cur->left)
		{
			getPath(cur->left, path, result);
			path.pop_back(); // 回溯
		}

		// 右
		if (cur->right)
		{
			getPath(cur->right, path, result);
			path.pop_back(); // 回溯
		}
	}

	vector<string> binaryTreePaths(TreeNode* root)
	{
		vector<string> result;
		vector<int> path;
		if (root == nullptr) return result;
		getPath(root, path, result);
		return result;
	}
};
```

如上的C++代码充分体现了回溯。

#### 精简版本（隐藏的回溯）

那么如上代码可以精简成如下代码：

```C++
class Solution2
{
 private:
	// 回溯隐藏在 string path 中，每次拷贝传值
	void traversal(TreeNode* cur, string path, vector<string>& result)
	{
		path += to_string(cur->val); // 中
		if (cur->left == nullptr && cur->right == nullptr)
		{
			result.push_back(path);
			return;
		}
		if (cur->left) traversal(cur->left, path + "->", result); // 左
		if (cur->right) traversal(cur->right, path + "->", result); // 右
	}

 public:
	vector<string> binaryTreePaths(TreeNode* root)
	{
		vector<string> result;
		string path;
		if (root == nullptr) return result;
		traversal(root, path, result);
		return result;

	}
};
```

如上代码精简了不少，也隐藏了不少东西。

注意在函数定义的时候`void traversal(TreeNode* cur, string path, vector<string>& result)` ，定义的是`string path`，每次都是复制赋值，不用使用引用，否则就无法做到回溯的效果。（这里涉及到C++语法知识）

那么在如上代码中，**貌似没有看到回溯的逻辑，其实不然，回溯就隐藏在`traversal(cur->left, path + "->", result);`中的 `path + "->"`。** 每次函数调用完，path依然是没有加上"->" 的，这就是回溯了。

为了把这份精简代码的回溯过程展现出来，可以试一试把：

```C++
if (cur->left) traversal(cur->left, path + "->", result); // 左  回溯就隐藏在这里
```

改成如下代码：

```C++
path += "->";
traversal(cur->left, path, result); // 左
```

即：

```cpp
if (cur->left) {
    path += "->";
    traversal(cur->left, path, result); // 左
}
if (cur->right) {
    path += "->";
    traversal(cur->right, path, result); // 右
}
```

此时就没有回溯了，这个代码就是通过不了的了。

如果想把回溯加上，就要 在上面代码的基础上，加上回溯，就可以AC了。

```cpp
if (cur->left) {
    path += "->";
    traversal(cur->left, path, result); // 左
    path.pop_back(); // 回溯 '>'
    path.pop_back(); // 回溯 '-'
}
if (cur->right) {
    path += "->";
    traversal(cur->right, path, result); // 右
    path.pop_back(); // 回溯 '>' 
    path.pop_back(); //  回溯 '-' 
}
```

**如果把 `path + "->"`作为函数参数就是可以的，因为并没有改变path的数值，执行完递归函数之后，path依然是之前的数值（相当于回溯了）**

```C++

```

### 404.左叶子之和
[LeetCode](https://leetcode.cn/problems/sum-of-left-leaves/)  [文章讲解](https://programmercarl.com/0404.%E5%B7%A6%E5%8F%B6%E5%AD%90%E4%B9%8B%E5%92%8C.html)  [视频讲解](https://www.bilibili.com/video/BV1GY4y1K7z8/)

#### 题目描述：

给定二叉树的根节点 `root` ，返回所有左叶子之和。

**示例 1：**

![img](imgs/leftsum-tree.jpg)

> 输入: root = [3,9,20,null,null,15,7] 
> 输出: 24 
> 解释: 在这个二叉树中，有两个左叶子，分别是 9 和 15，所以返回 24

#### 我的解法（递归法）：

这个图的左叶子之和是多少？

![404.左叶子之和](imgs/20210204151949672.png) 

**其实是0，因为这棵树根本没有左叶子！**

![图二](imgs/20220902165805.png)

**判断当前节点是不是左叶子是无法判断的，必须要通过节点的父节点来判断其左孩子是不是左叶子。**

因此，递归的同时传入 leftLeave 参数，标记该节点是不是它父节点的左节点。

```C++
class Solution
{
 private:
	int _sumOfLeftLeaves(TreeNode* cur, bool leftLeave)
	{
		if (cur->left == nullptr && cur->right == nullptr)
		{
			if (leftLeave)
				return cur->val;
			else
				return 0;
		}

		int leftSumOfLeftLeaves = 0, rightSumOfLeftLeaves = 0;
		if (cur->left != nullptr)
			leftSumOfLeftLeaves = _sumOfLeftLeaves(cur->left, true);

		if (cur->right != nullptr)
			rightSumOfLeftLeaves = _sumOfLeftLeaves(cur->right, false);

		return leftSumOfLeftLeaves + rightSumOfLeftLeaves;
	}

 public:
	int sumOfLeftLeaves(TreeNode* root)
	{
		if (root == nullptr) return 0;

		return _sumOfLeftLeaves(root, false);
	}
};
```

### 今日总结

今日第一第二题没独立完成：**二叉树高度和深度要区分清楚**，**一次递归对应一次回溯**。
