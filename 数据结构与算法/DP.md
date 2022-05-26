# 动态规划
## 0. 动态规划五部曲
1. 确定dp数组及下标含义
2. 确定递推公式
3. dp数组初始化
4. 确定遍历顺序
5. 举例验证
## 1. 背包问题
### 0-1背包
#### 0. 问题描述
有N件物品和一个最多能背重量为W的背包
第i件物品重量为weight[i],价值为value[i]
求这个背包所装物品(不可重复)的最大价值
#### 1. 确定dp数组及下标含义
dp[i][j] 表示从下标为[0-i]的物品里任意取，放进容量为j的背包，价值总和最大是多少。
#### 2. 确定递推公式
确定 dp[i][j] 时，有两种情况 放入物品i和不放入物品i
dp[i][j] = max(dp[i - 1][j], dp[i - 1][j - weight[i]] + value[i]);
#### 3. dp数组初始化
对 dp[0][j] 和 dp[i][0] 初始化
dp[0][j] j > weight[0] 时 应初始化为 value[0] 其他为 0
dp[i][0] 应初始为 0
#### 4. 确定遍历顺序
二维dp数组 先遍历物品、背包都是可以的
一维dp数组 只能先遍历物品 且要逆序遍历背包 也可定义临时 temp
// for (int j = 1; j <= bagWeight; j++) {  // 遍历背包
##### 一维dp
```cpp
void bag01Problem() {
        vector<int> weight = {1, 3, 4};
        vector<int> value = {15, 20, 30};
        int bagWeight = 4;

        // dp数组的定义
        int len = weight.size();
        vector<int> dp(bagWeight + 1, 0);

        // 遍历顺序 先遍历物品 先遍历背包都可以
        for (int i = 0; i < len; i++) {             // 遍历物品
            for (int j = bagWeight; j >= weight[i]; j--){ // 遍历背包
                if (j >= weight[i]) {
                    dp[j] = max(dp[j], dp[j - weight[i]] + value[i]);
                }
            }
        }

        for (int i = 0; i < len; i++) {
            for (int j = 0; j <= bagWeight; j++) {
                cout << dp[j] << " ";
            }
            cout << endl;
        }

        cout << dp[bagWeight] << endl;
    }
```

### 完全背包
#### 0. 问题描述
有N件物品和一个最多能背重量为W的背包
第i件物品重量为weight[i],价值为value[i]
求这个背包所装物品(可重复)的最大价值

和01背包相比, 只存在遍历顺序的不同
#### 遍历顺序
1. 遍历背包时, 需要从小到大遍历 才能重复取
2. 如果求组合数就是外层for循环遍历物品，内层for遍历背包。
先遍历物品，每个物品只会被添加一次
3. 如果求排列数就是外层for遍历背包，内层for循环遍历物品。
先遍历背包，每个物品会被添加多次
4. 纯完全背包(能不能) 两种遍历顺序都可以

### 多重背包
有N种物品和一个容量为V 的背包。第i种物品最多有Mi件可用，每件耗费的空间是Ci ，价值是Wi 。求解将哪些物品装入背包可使这些物品的耗费的空间 总和不超过背包容量，且价值总和最大。

可以转换成01背包问题
# leetcode 题目

## 1. 其他
[96.不同的二叉搜索树](https://leetcode-cn.com/problems/unique-binary-search-trees/)

递推公式的确定

[1262. 可被三整除的最大和](https://leetcode-cn.com/problems/greatest-sum-divisible-by-three/)
```cpp
int maxSumDivThree(vector<int>& nums) {
    vector<int> dp(3, 0);
    vector<int> temp(3, 0);
    for (int i = 0; i < nums.size(); i++) {
        for (int j = 0; j < 3; j++) {
            temp[j] = dp[j] + nums[i];
        }

        for (int j = 0; j < 3; j++) {
            dp[temp[j] % 3] = max(dp[temp[j] % 3], temp[j]);
        }
    }

    return dp[0];
}
```

## 2. 背包问题

### 2.1 01背包
[494. 目标和](https://leetcode-cn.com/problems/target-sum/)

1. 只需考虑 target > 0 的情况

2. 求 sum 可以减小 dp 数组大小， 还可以判断 target 和 sum 的大小关系

3. 递推公式 `dp[j] = dp[j - nums[i]] + dp[j + nums[i]]`

4. 注意初始化 `dp[nums[0]] = (nums[0] == 0 ? 1 : 2);`

```cpp
int findTargetSumWays(vector<int>& nums, int target) {
    int sum = 0;
    for (int num : nums) {
        sum += num;
    }
    // 1. 求 sum 可以减小 dp 数组大小， 还可以判断 target 和 sum 的大小关系
    if (target > sum || target < -sum) return 0;  

    vector<int> dp(sum + 1, 0); // 2. 只需要考虑 target > 0 的情况

    dp[nums[0]] = (nums[0] == 0 ? 1 : 2);
    vector<int> temp(dp.begin(), dp.end());

    for (int i = 1; i < nums.size(); i++) {
        for (int j = 0; j <= sum; j++) {
            // 3. j - nums[i] < 0 时，取 temp[nums[i] - j]
            int left = j < nums[i] ? temp[nums[i] - j] : temp[j - nums[i]]; 
            int right = j + nums[i] > sum ? 0 : temp[j + nums[i]];
            dp[j] = left + right;
        }
        for (int j = 0; j <= sum; j++) {
            temp[j] = dp[j];
        }
    }
    return target < 0 ? dp[-target] : dp[target];  // 2. 只需要考虑 target > 0 的情况
}
```

[474.一和零](https://leetcode-cn.com/problems/ones-and-zeroes/)

递推公式 `dp[j][k] = max(dp[j][k], dp[j - zeroNum][k - oneNum] + 1)`

初始化 `dp[j][k] = 0`

```cpp
int findMaxForm(vector<string>& strs, int m, int n) {
    vector<vector<int>> dp(m + 1, vector<int>(n + 1, 0));

    for (int i = 0; i < strs.size(); i++) {
        string s = strs[i];
        int zeroNum = 0;
        for (auto c : s) {
            if (c == '0') {
                zeroNum++;
            }
        }
        int oneNum = s.size() - zeroNum;
        
        for (int j = m; j >= zeroNum; j--) {
            for (int k = n; k >= oneNum; k--) {
                dp[j][k] = max(dp[j][k], dp[j - zeroNum][k - oneNum] + 1);
            }
        }
    }

    return dp[m][n];
}
```
### 2.2 完全背包
[518. 零钱兑换 II](https://leetcode-cn.com/problems/coin-change-2/)

[377. 组合总和 Ⅳ](https://leetcode-cn.com/problems/combination-sum-iv/)

可以看出是完全背包，但是不好判断是先遍历背包还是先遍历物品

考虑物品为 {1, 5} 若先遍历物品 则只会记录 {1，5} 不会记录 {5，1} 求的是组合数

若先遍历背包 则 {1，5} {5，1} 都会记录 求的是排列数

```cpp
int change(int amount, vector<int>& coins) {
    vector<int> dp(amount + 1, 0);

    dp[0] = 1; // 初始化 
    for (int i = 0; i < coins.size(); i++) {  // 先遍历物品，后遍历背包，求组合数
        for (int j = coins[i]; j <= amount; j++) {
            dp[j] += dp[j - coins[i]];
        }
    }
    
    /* for (int j = 0; j <= amount; j++) {
        for (int i = 0; i < coins.size(); i++) {  // 先遍历背包，后遍历物品，求排列数
            if (j >= coins[i]) {
                dp[j] += dp[j - coins[i]];
            }
        }
    } */
    return dp[amount];
}
```

[139.单词拆分](https://leetcode-cn.com/problems/word-break/)

递推公式 `dp[j] = dp[j] || dp[j - wordDict[i].size()]`

初始化 `dp[0] = 1`

截取子串 `string string::substr(size_t pos, size_t len)`

unordered_map 的查找 `set.find(str) != set.end()`
```cpp
bool wordBreak(string s, vector<string>& wordDict) {
    vector<bool> dp(s.size() + 1, 0);
    dp[0] = 1;

    unordered_set<string> set(wordDict.begin(), wordDict.end());
    for (int j = 1; j <= s.size(); j++) {
        for (int i = 0; i < wordDict.size(); i++) {
            if (j >= wordDict[i].size()) {
                string str = s.substr(j - wordDict[i].size(), wordDict[i].size());
                if (set.find(str) != set.end())
                    dp[j] = dp[j] || dp[j - wordDict[i].size()];     
            }
        }
    }

    return dp[s.size()];
}
```

## 2. 打家劫舍
[213.打家劫舍II](https://leetcode-cn.com/problems/house-robber-ii/)

考虑到了抢头和抢尾两种情况，但是没想到构造一个函数来处理
```cpp
int rob(vector<int>& nums) {
    if (nums.size() == 0) return 0;
    if (nums.size() == 1) return nums[0];
    int result1 = robRange(nums, 0, nums.size() - 2); // 情况二
    int result2 = robRange(nums, 1, nums.size() - 1); // 情况三
    return max(result1, result2);
}
// 198.打家劫舍的逻辑
int robRange(vector<int>& nums, int start, int end) {
    if (end == start) return nums[start];
    vector<int> dp(nums.size());
    dp[start] = nums[start];
    dp[start + 1] = max(nums[start], nums[start + 1]);
    for (int i = start + 2; i <= end; i++) {
        dp[i] = max(dp[i - 2] + nums[i], dp[i - 1]);
    }
    return dp[end];
}
```

[337.打家劫舍 III](https://programmercarl.com/0337.%E6%89%93%E5%AE%B6%E5%8A%AB%E8%88%8DIII.html)

树形DP

注意递推公式
```cpp
int rob(TreeNode* root) {
    if (root == nullptr) return 0;
    vector<int> result = dp(root);

    return max(result[0], result[1]);
}
// dp[0] 表示不抢根节点 dp[1] 表示抢根节点
vector<int> dp(TreeNode* root){
    if (root == nullptr) return {0, 0};
    vector<int> left = dp(root->left);
    vector<int> right = dp(root->right);

    return {max(left[0], left[1]) + max(right[0], right[1]), root->val + left[0] + right[0]};
}
```

## 3. 买卖股票
[121. 买卖股票的最佳时机](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock/)

只有两种状态 持有股票、不持有股票

注意递推公式 只能购买一次股票
```
dp[0] = max(temp[0], temp[1] + prices[i]);
dp[1] = max(-prices[i], temp[1]);
```
[122.买卖股票的最佳时机II](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-ii/)

注意递推公式 可以购买多次股票
```
dp[0] = max(temp[0], temp[1] + prices[i]);
dp[1] = max(temp[0] - prices[i], temp[1]);
```

```cpp
int maxProfit(vector<int>& prices) {
    if (prices.size() == 0) return 0;
    vector<int> dp(2, 0);
    dp[1] = -prices[0];
    vector<int> temp(dp.begin(), dp.end());
    for (int i = 1; i < prices.size(); i++) {
        dp[0] = max(temp[0], temp[1] + prices[i]);
        // dp[1] = max(temp[0] - prices[i], temp[1]);
        dp[1] = max(-prices[i], temp[1]);
        temp[0] = dp[0]; temp[1] = dp[1];
    }
    return max(dp[1], dp[0]);
    }
```

[123.买卖股票的最佳时机III](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/)

一共5种状态

0. 没有操作
1. 第一次买入
2. 第一次卖出
3. 第二次买入
4. 第二次卖出
```cpp
int maxProfit(vector<int>& prices) {
    int times = 2;
    int len = prices.size();

    vector<int> dp(2 * times + 1, 0);
    for (int j = 1; j <= times; j++){
        dp[2 * j - 1] = -prices[0];  // 1. 为什么要这样初始化
    }
    for (int i = 1; i < len; i++){
        for (int j = 1; j <= times; j++){
            dp[2 * j - 1] = max(dp[2 * j - 2] - prices[i], dp[2 * j - 1]);
            dp[2 * j] = max(dp[2 * j - 1] + prices[i], dp[2 * j]);
        }
    }
    return dp[2 * times]; // 2. 为什么要返回这个
}
```

[309.最佳买卖股票时机含冷冻期](https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-cooldown/)

一共4种状态

0：状态一 买入股票状态（今天买入股票，或者是之前就买入了股票然后没有操作）

1：状态二 两天前就卖出了股票，度过了冷冻期，一直没操作，今天保持卖出股票状态

2：状态三 今天卖出了股票

3：状态四 今天为冷冻期状态，但冷冻期状态不可持续，只有一天！

```cpp
int maxProfit(vector<int>& prices) {
    if (prices.size() <= 1) return 0;

    vector<int> dp(4, 0);
    dp[0] = 0; // 不持有股票
    dp[1] = 0; // 冷静期
    dp[2] = 0; // 卖出
    dp[3] = -prices[0]; // 持有

    for (int i = 1; i < prices.size(); i++) {
        int temp = dp[1];
        dp[1] = dp[2];
        dp[2] = dp[3] + prices[i];
        dp[3] = max(dp[3], max(temp - prices[i], dp[0] - prices[i]));
        dp[0] = max(dp[0], temp);
    }
    int max = 0;
    for (int i = 0; i < 4; i++) {
        max = max > dp[i] ? max :dp[i];
    }
    return max;
}
```

## 4. 子序列问题
一般dp[j]的定义是以j为结尾的0-j数组相关属性
[1143.最长公共子序列](https://leetcode-cn.com/problems/longest-common-subsequence/)
```cpp
int longestCommonSubsequence(string text1, string text2) {
    if (text1.size() == 0 || text2.size() == 0) return 0;
    vector<vector<int>> dp(text1.size(), vector<int>(text2.size(), 1));
    for (int i = 0; i < text1.size() && text1[i] != text2[0]; i++) {  
        dp[i][0] = 0;
    }
    for (int j = 0; j < text2.size() && text1[0] != text2[j]; j++) {
        dp[0][j] = 0;
    }

    for (int i = 1; i < text1.size(); i++) {
        for (int j = 1; j < text2.size(); j++) {
            if (text1[i] == text2[j]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = max(dp[i - 1][j - 1], max(dp[i][j - 1], dp[i - 1][j]));
            }
        }
    }
    return dp[text1.size() - 1][text2.size() - 1];
}
```
[115.不同的子序列](https://leetcode-cn.com/problems/distinct-subsequences/)
```cpp
int numDistinct(string s, string t) {
    if (s.size() < t.size() || t.size() == 0) return 0;
    vector<vector<unsigned int>> dp(s.size(), vector<unsigned int>(t.size(), 0));
    dp[0][0] = s[0] == t[0] ? 1 : 0;
    for (int i = 1; i < s.size(); i++) {
        dp[i][0] = (s[i] == t[0]  ? dp[i - 1][0] + 1 : dp[i - 1][0]);
    }

    for (int i = 1; i < s.size(); i++) {
        for (int j = 1; j < t.size() && j <= i; j++) {
            dp[i][j] = s[i] == t[j] ? dp[i - 1][j - 1] : 0;
            dp[i][j] += dp[i - 1][j];
        }
    }
    return dp[s.size() - 1][t.size() - 1];
}
```
[583. 两个字符串的删除操作](https://leetcode-cn.com/problems/delete-operation-for-two-strings/)
1. dp[i][j] 表示word1 0 - i 向 word2 0 ~ j  转化的最少操作数
2. 注意初始化和递推公式
```cpp
int minDistance(string word1, string word2) {
    if (word1.size() == 0 || word2.size() == 0) return word1.size() + word2.size();
    vector<vector<int>> dp(word1.size(), vector<int>(word2.size(), INT_MAX));
    dp[0][0] = word1[0] == word2[0] ? 0 : 2;
    for (int i = 1; i < word1.size(); i++) {
        dp[i][0] = word1[i] == word2[0] ? i : dp[i - 1][0] + 1;
        // cout << dp[i][0] << " ";
    }
    for (int j = 1; j < word2.size(); j++) {
        dp[0][j] = word1[0] == word2[j] ? j : dp[0][j - 1] + 1;
        // cout << dp[0][j] << " ";
    }

    for (int i = 1; i < word1.size(); i++) {
        for (int j = 1; j < word2.size(); j++) {
            if (word1[i] == word2[j]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j], dp[i][j - 1]) + 1;
            }
            // cout << dp[i][j] << " ";
        }
        // cout << endl;
    }
    return dp[word1.size() - 1][word2.size() - 1];
}
```
[72. 编辑距离](https://leetcode-cn.com/problems/edit-distance/)
1. dp[i][j] 表示word1 0 - i 向 word2 0 ~ j  转化的最少操作数
2. 注意初始化和递推公式
   
```cpp
int minDistance(string word1, string word2) {
    if (word1.size() == 0 || word2.size() == 0) return word1.size() + word2.size();
    vector<vector<int>> dp(word1.size(), vector<int>(word2.size(), INT_MAX));
    dp[0][0] = word1[0] == word2[0] ? 0 : 1;
    for (int i = 1; i < word1.size(); i++) {
        dp[i][0] = word1[i] == word2[0] ? dp[i - 1][0] : dp[i - 1][0] + 1;
        // cout << dp[i][0] << " ";
    }
    for (int j = 1; j < word2.size(); j++) {
        dp[0][j] = word1[0] == word2[j] ? dp[0][j - 1] : dp[0][j - 1] + 1;
        // cout << dp[0][j] << " ";
    }

    for (int i = 1; i < word1.size(); i++) {
        for (int j = 1; j < word2.size(); j++) {
            if (word1[i] == word2[j]) {
                dp[i][j] = dp[i - 1][j - 1];
            } else {
                dp[i][j] = min(dp[i - 1][j -1], min(dp[i - 1][j], dp[i][j - 1])) + 1;
            }
            // cout << dp[i][j] << " ";
        }
        // cout << endl;
    }
    return dp[word1.size() - 1][word2.size() - 1];
}
```
[647. 回文子串](https://leetcode-cn.com/problems/palindromic-substrings/)
1. dp[i][j] 表示子串 i ~ j (i <= j) 是不是回文
2. 递推公式
    ```cpp
    if (j <= i + 1) {
        dp[i][j] = s[i] == s[j];
    } else {
        dp[i][j] = s[i] == s[j] ? dp[i + 1][j - 1] : 0;
    }
    ```

```cpp
int countSubstrings(string s) {
    if (s.size() <= 1) return s.size();
    vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));

    int result = 0;
    for (int i = s.size() - 1; i >= 0; i--) {
        for (int j = i; j < s.size(); j++) {
            if (j <= i + 1) {
                dp[i][j] = s[i] == s[j];
            } else {
                dp[i][j] = s[i] == s[j] ? dp[i + 1][j - 1] : 0;
            }
            result += dp[i][j];
        }
    }
    return result;
}
```
[516.最长回文子序列](https://leetcode-cn.com/problems/longest-palindromic-subsequence/)
1. dp[i][j] 表示子序列 i ~ j (i <= j) 最长子序列长度
2. 递推公式
    ```cpp
    if (j <= i + 1) {
        dp[i][j] = s[i] == s[j] ? j - i + 1 : 1;  // 注意 s[i] != s[j] dp[i][j] = 1
    } else {
        if (s[i] == s[j]) {
            dp[i][j] = dp[i + 1][j - 1] + 2;
        } else {
            dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
        }
    }
    ```
3. 递归顺序
    从上到下，从左往右
4. 可以继续优化 一维dp
```cpp
int longestPalindromeSubseq(string s) {
    if (s.size() <= 1) return s.size();
    vector<vector<int>> dp(s.size(), vector<int>(s.size(), 0));

    for (int i = s.size() - 1; i >= 0; i--) {
        for (int j = i; j < s.size(); j++) {
            if (j <= i + 1) {
                dp[i][j] = s[i] == s[j] ? j - i + 1 : 1;
            } else {
                if (s[i] == s[j]) {
                    dp[i][j] = dp[i + 1][j - 1] + 2;
                } else {
                    dp[i][j] = max(dp[i][j - 1], dp[i + 1][j]);
                }
            }
        }
    }
    return dp[0][s.size() - 1];
}
```

[剑指 Offer 60. n个骰子的点数](https://leetcode.cn/problems/nge-tou-zi-de-dian-shu-lcof/)
```cpp
vector<double> dicesProbability(int n) {
    vector<double> dp(6 * n + 1, 0.0);
    for (int j = 1; j <= 6; j++) {
        dp[j] = 1.0 / 6;
    }

    for (int i = 2; i <= n; i++) {
        for (int j = 6 * i; j >= 0; j--) {
            double sum = 0.0;
            for (int k = 1; k <= 6 && j - k >= 0; k++) sum += dp[j - k];
            dp[j] = sum / 6;
        }
    }

    return vector<double>(dp.begin() + n, dp.end());
}
```