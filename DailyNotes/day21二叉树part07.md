## Day21: 二叉树part07

### 530.二叉搜索树的最小绝对差
[LeetCode](https://leetcode.cn/problems/minimum-absolute-difference-in-bst/)  [文章讲解](https://programmercarl.com/0530.%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E7%9A%84%E6%9C%80%E5%B0%8F%E7%BB%9D%E5%AF%B9%E5%B7%AE.html)  [视频讲解](https://www.bilibili.com/video/BV1DD4y11779/)

#### 题目描述：

给你一个二叉搜索树的根节点 `root` ，返回 **树中任意两不同节点值之间的最小差值** 。

差值是一个正数，其数值等于两值之差的绝对值。

**示例 1：**

![img](imgs/bst1.jpg)

> 输入：root = [4,2,6,1,3]
> 输出：1

#### 我的解法（直观解法）：

二叉搜索树采用中序遍历转换成有序数组，然后遍历一遍数组，就统计出来最小差值了

```C++
// 先中序遍历，然后取遍历符合条件的结果
class Solution
{
 private:
	vector<int> m_vec;

	void traversal(TreeNode* cur)
	{
		if (cur == nullptr) return;

		traversal(cur->left);
		m_vec.push_back(cur->val);
		traversal(cur->right);
	}

 public:
	int getMinimumDifference(TreeNode* root)
	{
		m_vec.clear();
		traversal(root);

		int result = INT_MAX;
		for (int i = 0; i < m_vec.size() - 1; ++i)
		{
			result = min(result, m_vec[i + 1] - m_vec[i]);
		}

		return result;
	}
};
```

#### 递归法：

在二叉搜素树中序遍历的过程中，用一个pre节点记录一下cur节点的前一个节点，进行判断

![530.二叉搜索树的最小绝对差](imgs/20210204153247458.png)

```C++

```


### 501.二叉搜索树中的众数

[LeetCode](https://leetcode.cn/problems/find-mode-in-binary-search-tree/)  [文章讲解](https://programmercarl.com/0501.%E4%BA%8C%E5%8F%89%E6%90%9C%E7%B4%A2%E6%A0%91%E4%B8%AD%E7%9A%84%E4%BC%97%E6%95%B0.html)  [视频讲解](https://www.bilibili.com/video/BV1fD4y117gp/)

#### 题目描述：

给你一个含重复值的二叉搜索树（BST）的根节点 `root` ，找出并返回 BST 中的所有 [众数](https://baike.baidu.com/item/众数/44796)（即，出现频率最高的元素）。

如果树中有不止一个众数，可以按 **任意顺序** 返回。

假定 BST 满足如下定义：

- 结点左子树中所含节点的值 **小于等于** 当前节点的值
- 结点右子树中所含节点的值 **大于等于** 当前节点的值
- 左子树和右子树都是二叉搜索树

**示例 1：**

![img](imgs/mode-tree.jpg)

> 输入：root = [1,null,2,2]
> 输出：[2]

#### 我的解法：

因为二叉搜索树的中序遍历是有序的，遍历的过程记录上一个节点，若与当前节点相同则众数的计数就加一。

```C++
class Solution
{
 private:
	TreeNode* pre = nullptr;
	vector<int> result;
	int max_count = 0;
	int count = 0;

	void traversal(TreeNode* cur)
	{
		if (cur == nullptr) return;

		// 左
		traversal(cur->left);

		// 中
		if (pre == nullptr) count++;
		else
		{
			if (cur->val == pre->val) count++;
			else count = 1;
		}

		if (count > max_count)
		{
			result.clear();
			result.push_back(cur->val);
			max_count = count;
		}
		else if (count == max_count)
		{
			result.push_back(cur->val);
		}
		pre = cur;

		// 右
		traversal(cur->right);
	}

 public:
	vector<int> findMode(TreeNode* root)
	{
		pre = nullptr;
		result.clear();
		max_count = 0;
		count = 0;

		traversal(root);
		return result;
	}
};
```

#### 拓展：

如果不是二叉搜索树，最直观的方法一定是把这个树都遍历了，用map统计频率，把频率排个序，最后取前面高频的元素的集合。

如果想直接对map中的value排序，还真做不到，C++中如果使用std::map或者std::multimap可以对key排序，但不能对value排序。所以要把map转化数组即vector，再进行排序，当然vector里面放的也是`pair<int, int>`类型的数据，第一个int为元素，第二个int为出现频率。

```C++
class Solution {
private:

void searchBST(TreeNode* cur, unordered_map<int, int>& map) { // 前序遍历
    if (cur == NULL) return ;
    map[cur->val]++; // 统计元素频率
    searchBST(cur->left, map);
    searchBST(cur->right, map);
    return ;
}
bool static cmp (const pair<int, int>& a, const pair<int, int>& b) {
    return a.second > b.second;
}
public:
    vector<int> findMode(TreeNode* root) {
        unordered_map<int, int> map; // key:元素，value:出现频率
        vector<int> result;
        if (root == NULL) return result;
        searchBST(root, map);
        vector<pair<int, int>> vec(map.begin(), map.end());
        sort(vec.begin(), vec.end(), cmp); // 给频率排个序
        result.push_back(vec[0].first);
        for (int i = 1; i < vec.size(); i++) {
            // 取最高的放到result数组中
            if (vec[i].second == vec[0].second) result.push_back(vec[i].first);
            else break;
        }
        return result;
    }
};
```

### 236. 二叉树的最近公共祖先

[LeetCode](https://leetcode.cn/problems/lowest-common-ancestor-of-a-binary-tree/)  [文章讲解](https://programmercarl.com/0236.%E4%BA%8C%E5%8F%89%E6%A0%91%E7%9A%84%E6%9C%80%E8%BF%91%E5%85%AC%E5%85%B1%E7%A5%96%E5%85%88.html)  [视频讲解](https://www.bilibili.com/video/BV1jd4y1B7E2/)

#### 题目描述：

给定一个二叉树, 找到该树中两个指定节点的最近公共祖先。

[百度百科](https://baike.baidu.com/item/最近公共祖先/8918834?fr=aladdin)中最近公共祖先的定义为：“对于有根树 T 的两个节点 p、q，最近公共祖先表示为一个节点 x，满足 x 是 p、q 的祖先且 x 的深度尽可能大（**一个节点也可以是它自己的祖先**）。”

**示例 1：**

![img](imgs/binarytree.png)

> 输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
> 输出：3
> 解释：节点 5 和节点 1 的最近公共祖先是节点 3 。

**示例 2：**

![img](imgs/binarytree.png)

> 输入：root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 4
> 输出：5
> 解释：节点 5 和节点 4 的最近公共祖先是节点 5 。因为根据定义最近公共祖先节点可以为节点本身。

#### 我的解法：

```C++

```

### 今日总结