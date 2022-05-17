# 二叉树笔记
## 结点定义
```cpp
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};
```
## 构建二叉树
目的：通过给定的数组得到二叉树

输入：数组（描述二叉树结构）

输出：二叉树根节点

思路：考虑到完全二叉树便于顺序存储的性质，因此
### 根据数组构建完全二叉树（数组）
```cpp
vector<int> compelete_binary_tree(vector<int> &nums) {
    if (nums.empty() || nums[0] == -1)
        return {};
    vector<int> result;
    result.push_back(nums[0]);
    int i = 1, j = 1;  // i 输入节点索引 nums，j 输出节点索引（待插入） result
    while (i < nums.size()) {
        // -1       表示输入数组的 null
        if (result[(j - 1) / 2] != -1) // 节点 j 的父节点索引为 (j - 1) / 2
            result.push_back(nums[i++]);  // 若父节点不空 则从 nums 里读取两个数存入
        else  {                             // 若父节点为空 则存入两个 -1
            result.push_back(-1);
            result.push_back(-1);
            j++;
        }
        j++;
    }
    if (result.size() % 2 == 0) // 确保每个节点（除叶子节点）都有左右孩子
        result.push_back(-1);
    return result;
}
```
### 根据完全二叉数组构建二叉树
```cpp
TreeNode *construct_binary_tree(vector<int> &nums) {
    if (nums.empty())
        return nullptr;

    vector<TreeNode *> TreVec(nums.size(), nullptr);
    for (int i = 0; i < TreVec.size(); i++)
        TreVec[i] = (nums[i] == -1) ? nullptr : new TreeNode(nums[i]);

    for (int i = 0; 2 * i + 2 < TreVec.size(); i++) // 节点 i 的右孩子索引为 2*i+2
        if (TreVec[i] != nullptr) {
            TreVec[i]->left = TreVec[2 * i + 1];
            TreVec[i]->right = TreVec[2 * i + 2];
        }

    return TreVec[0];
}
```
### 其他辅助函数
```cpp
// 层序遍历（用于检查构建的二叉树是否正确）
void read(TreeNode *root) {
    if (root == nullptr)
        return;
    queue<TreeNode *> que;
    que.push(root);
    while (que.size()) {
        int size = que.size();
        vector<int> vec;
        for (int i = 0; i < size; i++)  {
            TreeNode *cur = que.front();
            que.pop();
            if (cur != nullptr) {
                que.push(cur->left);
                que.push(cur->right);
                cout << cur->val << " ";
            }
            else
                cout << -1 << " ";
        }
        cout << endl;
    }
}
```
```cpp
// 释放new出来的内存
void deleteTree(TreeNode *root) {
    if (root == nullptr)
        return;
    queue<TreeNode *> que;
    que.push(root);
    while (que.size()) {
        int size = que.size();
        for (int i = 0; i < size; i++) {
            TreeNode *cur = que.front();
            if (cur) {
                if (cur->left)
                    que.push(cur->left);
                if (cur->right)
                    que.push(cur->right);
                delete cur;
                cur = nullptr;
            }
            que.pop();
        }
    }
    // cout << "删除成功" << endl;
    return;
}
```
## 遍历
遍历主要分为深度优先（前序，中序，后序）和广度优先（层序）

深度优先可以采用递归和迭代（栈）的方式，将给出递归，普通迭代，统一迭代的代码

层序遍历可以通过队列实现
### 深度优先
#### 递归
```cpp
void traversal(TreeNode* root, vector<int>& nums) {
    if (root == nullptr) return;
    // 中序遍历 前序，后序类似
    traversal(root -> left, nums);  // 左
    nums.push_back(root -> val);    // 中
    traversal(root -> right, nums); // 右
}
vector<int> Traversal(TreeNode *root) {
    vector<int> result;
    traversal(root, result);
    return result;
}
```
#### 普通迭代

##### 前序遍历
注意入栈时，应先将右孩子入栈
```cpp
vector<int> preorderTraversal(TreeNode *root) {
    if (root == nullptr)
        return {};
    vector<int> result;
    stack<TreeNode *> sta;
    sta.push(root);

    while (!sta.empty()) {
        TreeNode *cur = sta.top();
        sta.pop();
        result.push_back(cur->val);

        if (cur->right)  // 空节点不入栈
            sta.push(cur->right);
        if (cur->left)
            sta.push(cur->left);
    }
    return result;
}
```
##### 中序遍历
没有完全理解
```cpp
vector<int> inorderTraversal(TreeNode *root) {
    vector<int> result;
    if (root == nullptr)
        return result;
    stack<TreeNode *> sta;
    TreeNode *cur = root; 
    while (cur != nullptr || sta.size()) {
        if (cur != nullptr) {
            sta.push(cur);
            cur = cur->left; // 找到最左边
        } else {
            cur = sta.top();
            sta.pop();
            result.push_back(cur->val); // 中
            cur = cur->right;      //右
        }
    }
    return result;
}
```
##### 后序遍历
后序遍历顺序时左右中，翻转下就是中右左，和前序遍历类似
```cpp
vector<int> postorderTraversal(TreeNode *root) {
    if (root == nullptr)
        return {};
    vector<int> result;
    stack<TreeNode *> sta;
    sta.push(root);

    while (!sta.empty()) {
        TreeNode *cur = sta.top();
        sta.pop();
        result.push_back(cur->val);

        if (cur->left) // 这里改下入栈顺序
            sta.push(cur->left);
        if (cur->right)
            sta.push(cur->right);
    }
    reverse(result.begin(), result.end());
    return result;
}
```
#### 统一迭代
主要想法是 做标记 使得入栈和读取分离
```cpp
vector<int> inorderTraversal(TreeNode *root) {
    if (root == nullptr)
        return {};
    vector<int> result;
    stack<TreeNode *> sta;
    sta.push(root);

    while (!sta.empty()) {
        TreeNode *cur = sta.top();
        if (cur) {
            sta.pop();
            // 中序遍历 其他类似
            if (cur->right)  // 右
                sta.push(cur->right);
            sta.push(cur);  // 中
            sta.push(nullptr);
            if (cur->left)  // 左
                sta.push(cur->left);
        } else {
            sta.pop();
            cur = sta.top();
            result.push_back(cur->val);
            sta.pop();
        }
    }
    return result;
}
```
### 广度优先（层序遍历）
利用队列
```cpp
// 注意返回类型
vector<vector<int>> levelOrder(TreeNode *root) {
    queue<TreeNode *> que;
    if (root != NULL)
        que.push(root);
    vector<vector<int>> result;
    while (!que.empty()) {
        int size = que.size();
        vector<int> vec;
        // 这里一定要使用固定大小size
        for (int i = 0; i < size; i++) {
            TreeNode *node = que.front();
            que.pop();
            vec.push_back(node->val);
            if (node->left)
                que.push(node->left);
            if (node->right)
                que.push(node->right);
        }
        result.push_back(vec);
    }
    return result;
}
```

# Leetcode

[94.二叉树的中序遍历](https://leetcode-cn.com/problems/binary-tree-inorder-traversal/)

三种想法 递归 迭代 统一迭代 都实现一下

[101. 对称二叉树](https://leetcode-cn.com/problems/symmetric-tree/)

idea 
1. 在于想到对比左右子树的里侧和外侧
2. 不能用中序遍历的思想 如 1 2 null 2
3. 迭代的思想很好 同时入队 同时出队

```cpp
bool isSymmetric(TreeNode* root) {
    if (root == nullptr) return true;
    queue<TreeNode*> que;
    que.push(root -> left);
    que.push(root -> right);

    while (!que.empty()) {
        TreeNode* leftNode = que.front(); que.pop(); // 里侧和外侧要进行匹配
        TreeNode* rightNode = que.front(); que.pop();
        if (leftNode == nullptr && rightNode == nullptr) continue;
        if (leftNode && rightNode && leftNode -> val == rightNode -> val) {
            que.push(leftNode -> left);
            que.push(rightNode -> right);
            que.push(leftNode -> right);
            que.push(rightNode -> left);
        } else {
            return false;
        }
    }

    return true;
}
```

[222.完全二叉树的节点个数](https://leetcode-cn.com/problems/count-complete-tree-nodes/submissions/)

完全二叉树的子树必定有满二叉树 

满二叉树可由左右叶子节点的高度确定
```cpp
int countNodes(TreeNode* root) {
    if (root == nullptr) return 0;
    int leftHeight = 0;
    TreeNode* leftNode = root -> left;
    while (leftNode) {
        leftNode = leftNode -> left;
        leftHeight++;
    }
    int rightHeight = 0;
    TreeNode* rightNode = root -> right;
    while (rightNode) {
        rightNode = rightNode -> right;
        rightHeight++;
    }
    if (leftHeight == rightHeight) {
        return (2 << leftHeight) - 1;
    } else {
        return countNodes(root -> left) + countNodes(root -> right) + 1;
    }
}
```

[113. 路径总和 II](https://leetcode-cn.com/problems/path-sum-ii/)

回溯的想法
```cpp
void travesal(TreeNode* root, vector<int>& path, vector<vector<int>>& result, int target) {
    if (root == nullptr) return;
    path.push_back(root -> val);
    if (root -> val == target && root -> left == nullptr && root -> right == nullptr) {
        result.push_back(path);
    }

    if (root -> left) {
        travesal(root -> left, path, result, target - root -> val);
        path.pop_back();
    }
    if (root -> right) {
        travesal(root -> right, path, result, target - root -> val);
        path.pop_back();
    }
}
vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> result;
    if (root == nullptr) return result;
    vector<int> path;
    travesal(root, path, result, targetSum);
    return result;
}
```

[257. 二叉树的所有路径](https://leetcode-cn.com/problems/binary-tree-paths/)

回溯
```cpp
void travesal(TreeNode* cur, vector<int>& path, vector<string>& result) {
    if (cur == nullptr) return;
    path.push_back(cur -> val);
    if (cur -> left == nullptr && cur -> right == nullptr) {
        string sPath;
        for (int i = 0; i < path.size() - 1; i++) {
            sPath += to_string(path[i]);
            sPath += "->";
        }
        sPath += to_string(path[path.size() - 1]);
        result.push_back(sPath);
        return;
    }

    if (cur -> left) {
        travesal(cur -> left, path, result);
        path.pop_back();
    }
    if (cur -> right) {
        travesal(cur -> right, path, result);
        path.pop_back();
    }
}
vector<string> binaryTreePaths(TreeNode* root) {
    vector<string> result;
    if (root == nullptr) return result;
    vector<int> path;
    travesal(root, path, result);
    return result;
}
```
[105. 从前序与中序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-preorder-and-inorder-traversal/)

[106. 从中序与后序遍历序列构造二叉树](https://leetcode-cn.com/problems/construct-binary-tree-from-inorder-and-postorder-traversal/)

```cpp
TreeNode* buildTree(vector<int>& inorder, int left, int right, unordered_map<int, int>& map) {
    if (left > right) return nullptr;
    int rootIndex = left; // root 在 inordr 的索引
    for (int i = left; i <= right; i++) {
        rootIndex = map[inorder[rootIndex]] > map[inorder[i]] ? rootIndex : i;
    }
    TreeNode* root = new TreeNode(inorder[rootIndex]);
    root -> left = buildTree(inorder, left, rootIndex - 1, map);
    root -> right = buildTree(inorder, rootIndex + 1, right, map);
    return root;
}
TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    if (inorder.size() == 0) return nullptr;
    unordered_map<int, int> map;
    for (int i = 0; i < postorder.size(); i++) {
        map[postorder[i]] = i;
    }
    return buildTree(inorder, 0, inorder.size() - 1, map);
}
```
[98. 验证二叉搜索树](https://leetcode-cn.com/problems/validate-binary-search-tree/)

BST 中序遍历后严格递增
```cpp
bool isValidBST(TreeNode* root) {
    queue<int> que;
    stack<TreeNode*> sta;
    sta.push(root);

    while (!sta.empty()) {
        TreeNode* cur = sta.top();
        if (cur) {
            sta.pop();

            if (cur -> right) sta.push(cur -> right); // 右
            sta.push(cur); // 中
            sta.push(nullptr); 
            if (cur -> left) sta.push(cur -> left); // 左
        } else {
            sta.pop();
            cur = sta.top();
            sta.pop();

            que.push(cur -> val);
            if (que.size() >= 2) {
                if (que.front() >= que.back()) {
                    return false;
                }
                que.pop();
            }
        }
    }
    return true;
}
```

[501.二叉搜索树中的众数](https://leetcode-cn.com/problems/find-mode-in-binary-search-tree/)

怎么处理正数

```cpp
vector<int> findMode(TreeNode* root) {
    vector<int> res;
    if (root == nullptr) return res;
    stack<TreeNode*> sta;
    sta.push(root);

    queue<int> que;
    int timesTotal = 0;
    int times = 0;
    // 做中序遍历
    while (!sta.empty()) {
        TreeNode* cur = sta.top();
        if (cur) {
            sta.pop();
            if (cur -> right) sta.push(cur -> right);
            sta.push(cur);
            sta.push(nullptr);
            if (cur -> left) sta.push(cur -> left);
        } else {
            sta.pop();
            cur = sta.top();
            sta.pop();

            // 处理逻辑
            if (que.empty()) {
                que.push(cur -> val);
                times = 1;
                timesTotal = 1;
                res.push_back(cur -> val);
            } else {
                if (cur -> val == que.back()) {
                    times++;
                    if (times == timesTotal) {
                        res.push_back(cur -> val);
                    }
                    if (times > timesTotal) {
                        timesTotal = times;
                        res.clear();
                        res.push_back(cur -> val);
                    }
                } else {
                    times = 1;
                    que.push(cur -> val);
                    if (que.size() > 1) que.pop();
                    if (timesTotal == 1) {
                        res.push_back(cur -> val);
                    }
                }
            }
        }
    }

    return res;
}
```

[236. 二叉树的最近公共祖先](https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/)

后序遍历 p q 分别在最近公共祖先的两侧
```cpp
TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
    // 返回 p 和 q 的最近公共祖先
    if (root == p || root == q || root == nullptr) return root;
    TreeNode* left = lowestCommonAncestor(root -> left, p, q);
    TreeNode* right = lowestCommonAncestor(root -> right, p, q);

    if (left == nullptr && right == nullptr) return nullptr;
    if (left && right) return root;
    if (left) return left;
    if (right) return right;
    return root;
}
```

[450.删除二叉搜索树中的节点](https://leetcode-cn.com/problems/delete-node-in-a-bst/)
```cpp
TreeNode* deleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root;
    if (root -> val > key) {
        root -> left = deleteNode(root -> left, key);
        return root;
    } else if (root -> val < key) {
        root -> right = deleteNode(root -> right, key);
        return root;
    } else {
        TreeNode* rootLeft = root -> left;
        TreeNode* rootRight = root -> right;
        delete root;
        
        if (rootLeft && rootRight) {
            TreeNode* cur = rootRight;
            while (cur -> left) {
                cur = cur -> left;
            }
            cur -> left = rootLeft;
            return rootRight;
        } else if (rootLeft) {
            return rootLeft;
        } else if (rootRight) {
            return rootRight;
        }
    }
    
    return nullptr; 
}
```
[108.将有序数组转换为二叉搜索树](https://leetcode-cn.com/problems/convert-sorted-array-to-binary-search-tree/)

有序数组可以很简单的构造出平衡二叉树

```cpp
TreeNode* sortedArrayToBST(vector<int>& nums, int left, int right) {
    if (left > right) return nullptr;
    int mid = left + (right - left + 1) / 2;
    TreeNode* node = new TreeNode(nums[mid]);
    node -> left = sortedArrayToBST(nums, left, mid - 1);
    node -> right = sortedArrayToBST(nums, mid + 1, right);
    return node;
}
TreeNode* sortedArrayToBST(vector<int>& nums) {
    if (nums.empty()) return nullptr;
    return sortedArrayToBST(nums, 0, nums.size() - 1);
}
```

[652. 寻找重复的子树](https://leetcode-cn.com/problems/find-duplicate-subtrees/)  
二叉树序列化 + 哈希表 + dfs  
每棵不同子树的序列化结果都是唯一的。
```cpp
vector<TreeNode*> res;
unordered_map<string, int> umap;
string dfs(TreeNode* cur) {
    if (cur == nullptr) return "";
    string str = to_string(cur -> val) + "-" + dfs(cur -> left) + "-" + dfs(cur -> right);
    if (umap[str] == 1) {
        res.push_back(cur);
    }
    umap[str]++;
    return str;
}
vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    if (root == nullptr) return res;
    dfs(root);
    // cout << dfs(root) << endl;
    return res;
}
```
[449. 序列化和反序列化二叉搜索树](https://leetcode.cn/problems/serialize-and-deserialize-bst/)
```cpp
int index = 0;
int n;

// Encodes a tree to a single string.
string serialize(TreeNode* root) {
    if (root == nullptr) return "n";
    return to_string(root -> val) + "+" + serialize(root -> left) + "+" + serialize(root -> right);
}

// Decodes your encoded data to tree.
TreeNode* deserialize(const string& data) {
    n = data.size();
    if (index >= n) return nullptr;

    string temp = "";
    while (index < n && data[index] != '+') {
        temp += data[index];
        ++index;
    }

    ++index;
    if (temp == "n") return nullptr;
    // cout << data << endl;
    TreeNode* root = new TreeNode(stoi(temp));

    root -> left = deserialize(data);
    root -> right = deserialize(data);
    return root;
}
```

[110. 平衡二叉树](https://leetcode-cn.com/problems/balanced-binary-tree/)  
一种时间和空间复杂度都是O(n)的做法
```cpp
int height(TreeNode* root) {
    if (root == nullptr) return 0;
    int leftHeight = height(root -> left);
    int rightHeight = height(root -> right);
    if (leftHeight == -1 || rightHeight == -1 || abs(leftHeight - rightHeight) > 1) {
        return -1;
    }
    return max(leftHeight, rightHeight) + 1;
}
bool isBalanced(TreeNode* root) {
    if (root == nullptr) return true;
    return height(root) >= 0;
}
```

[剑指 Offer 26. 树的子结构](https://leetcode-cn.com/problems/shu-de-zi-jie-gou-lcof/)
```cpp
bool isSubStructure(TreeNode* A, TreeNode* B) {
    if (A == nullptr || B == nullptr) return false;
    if (A -> val == B -> val) {
        bool flag1 = B -> left == nullptr ? true : (A -> left && B -> left -> val == A -> left -> val && isSubStructure(A -> left, B -> left));
        bool flag2 = B -> right == nullptr ? true : A -> right && B -> right -> val == A -> right -> val && isSubStructure(A -> right, B -> right);
        // cout << A -> val << " " << flag1 << " " << flag2 << endl;
        if (flag1 && flag2) return true;
    } 
    return isSubStructure(A -> left, B) || isSubStructure(A -> right, B);
}
```