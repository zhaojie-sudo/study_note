# Leetcode刷题笔记
## 位运算
[693. 交替位二进制数](https://leetcode-cn.com/problems/binary-number-with-alternating-bits/)
思路

对输入 nn 的二进制表示右移一位后，得到的数字再与 nn 按位异或得到 aa。当且仅当输入 nn 为交替位二进制数时，aa 的二进制表示全为 11（不包括前导 00）。这里进行简单证明：当 aa 的某一位为 11 时，当且仅当 nn 的对应位和其前一位相异。当 aa 的每一位为 11 时，当且仅当 nn 的所有相邻位相异，即 nn 为交替位二进制数。

将 aa 与 a + 1a+1 按位与，当且仅当 aa 的二进制表示全为 11 时，结果为 00。这里进行简单证明：当且仅当 aa 的二进制表示全为 11 时，a + 1a+1 可以进位，并将原最高位置为 00，按位与的结果为 00。否则，不会产生进位，两个最高位都为 11，相与结果不为 00。

结合上述两步，可以判断输入是否为交替位二进制数。
```cpp
bool hasAlternatingBits(int n) {
    long a = n ^ (n >> 1);
    return (a & (a + 1)) == 0;
}
```
[面试题 01.01. 判定字符是否唯一](https://leetcode-cn.com/problems/is-unique-lcci/)     
1. 如果字符范围不限 应该选择 `unordered_set`

2. 如果是ASCLL码 可以考虑用数组做哈希表 `int hash[256]`

3. 如果是 26 个小写字母 可以考虑做 位运算   
    1. int 4字节 long long 8字节 32 bit / 64 bit
    2. `bit & (1 << dist` 判断bit 第 dist 是不是 1
    3. `bit |= (1 << dist)` bit 第 dist 置 1
```cpp
bool isUnique(string astr) {
    if (astr.size() == 0) {
        return true;
    }
    
    // 假设只有 a - z 26 个字符， 可以用 int 做位运算
    int bit = 0;
    int dist = 0;
    for (char c : astr) {
        dist = c - 'a';
        if (bit & (1 << dist)) {
            return false;
        }
        bit |= (1 << dist);
    }
    return true;
}
```
4. 还有一种不限字符范围的解法  
sort 再遍历 这种很稳定


[136. 只出现一次的数字](https://leetcode-cn.com/problems/single-number/)  
位运算
1. a^a = 0
2. a^0 = 0
3. a^b^c = a^c^b
```cpp
int singleNumber(vector<int>& nums) {
    int result = 0;
    for (int num : nums) {
        result ^= num;
    }

    return result;
}
```


## 其他
[161.多数元素](https://leetcode-cn.com/problems/majority-element/)
1. 哈希表
2. sort
```cpp
int majorityElement(vector<int>& nums) {
    sort(nums.begin(), nums.end());
    return nums[nums.size() / 2];
}
```
3. 随机法
```cpp
int majorityElement(vector<int>& nums) {
    // 随机法
    while (1) {
        int index = rand() % nums.size();
        int count = 0;
        for (int i = 0; i < nums.size(); i++) {
            if (nums[i] == nums[index]) {
                count++;
            }
        }
        if (count > nums.size() / 2) {
            return nums[index];
        }
    }
    return -1; // 
}
```
4. morry
```cpp
int majorityElement(vector<int>& nums) {
    // 投票法
    int count = 0;
    int result = -1;
    for (int i = 0; i < nums.size(); i++) {
        if (count == 0) {
            result = nums[i];
        }
        if (result == nums[i]) {
            count++;
        } else {
            count--;
        }
    }
    return result; // 
}
```


[剑指 Offer 03. 数组中重复的数字](https://leetcode-cn.com/problems/shu-zu-zhong-zhong-fu-de-shu-zi-lcof/)
原地排序
```cpp
int findRepeatNumber(vector<int>& nums) {
    for (int i = 0; i < nums.size(); i++) {
        while (nums[i] != i) {
            int index = nums[i];
            if (nums[index] == index) {
                return index;
            } else {
                int temp = nums[index];
                nums[index] = index;
                nums[i] = temp;
            }
        }
    }
    return -1;
}
```


[1606. 找到处理最多请求的服务器](https://leetcode-cn.com/problems/find-servers-that-handled-most-number-of-requests/)
模拟 + 有序集合 + 优先级队列
set priority_queue 的用法

```cpp
vector<int> busiestServers(int k, vector<int>& arrival, vector<int>& load) {
    // available 用于存放空闲处理器
    set<int> available;
    for (int i = 0; i < k; i++) {
        available.insert(i);
    }

    // busy 用于存放正在忙碌得处理器得 结束时间 和 编号 
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> busy;

    // request 记录每个处理器 处理请求数
    vector<int> request(k, 0);

    for (int i = 0; i < arrival.size(); i++) {
        while (!busy.empty() && busy.top().first <= arrival[i]) {
            available.insert(busy.top().second);
            busy.pop();
        }
        if (available.empty()) {
            continue;
        }
        auto p = available.lower_bound(i % k);
        if (p == available.end()) {
            p = available.begin();
        }
        request[*p]++;
        busy.emplace(arrival[i] + load[i], *p);
        available.erase(p);
    }

    vector<int> res;
    int maxValue = 0;
    for (int i = 0; i < k; i++) {
        maxValue = max(maxValue, request[i]);
    }
    for (int i = 0; i < k; i++) {
        if (request[i] == maxValue) {
            res.push_back(i);
        }
    } 

    return res;
}
```
## 字典树
[440. 字典序的第K小数字](https://leetcode-cn.com/problems/k-th-smallest-in-lexicographical-order/)
```cpp
// 包括 cur 
int step(int cur, long n) {
    int steps = 0;
    long left = cur;
    long right = cur;  /* 为什么这样声明 */ 

    while (left <= n) {
        steps += min(right, n) - left + 1;
        left *= 10;
        right = right * 10 + 9;
    } 
    return steps;
} 

int findKthNumber(int n, int k) {
    int cur = 1;
    k--;
    while (k > 0) {
        int steps = step(cur, n);
        // cout << k << " " <<  cur << " " << steps << endl;
        if (k >= steps) {  /* 注意 为什么取 >= */
            cur++;
            k -= steps;
        } else {
            cur = cur * 10;
            k--;
        }
    } 
    return cur;
}
```

## 前缀和
非常适合用于求静态数组的区间和（一维、二维）  
参考 [前缀和](https://www.cnblogs.com/-Ackerman/p/11162651.html)

[661. 图片平滑器](https://leetcode-cn.com/problems/image-smoother/)
```cpp
vector<vector<int>> imageSmoother(vector<vector<int>>& img) {
    int m = img.size();
    int n = img[0].size();
    vector<vector<int>> sum(m + 1, vector<int> (n + 1, 0));
    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + img[i - 1][j - 1];
        }
    }

    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            // 注意 left right top bottom 的定义
            int left = max(0, i - 1);
            int right = min(i + 1, m - 1);
            int top = max(0, j - 1);
            int bottom = min(n - 1, j + 1);

            int count = (right - left + 1) * (bottom - top + 1);
            int Sum = sum[right + 1][bottom + 1] - sum[left][bottom + 1] - sum[right + 1][top] + sum[left][top];
            img[i][j] = Sum / count;
        }
    }

    return img;
}
```

## 数学
[172. 阶乘后的零](https://leetcode-cn.com/problems/factorial-trailing-zeroes/) 
```cpp
int trailingZeroes(int n) {
    int count = 0;
    while (n != 0) {
        n = n / 5;
        count += n;
    }
    return count;
}
```

## 哈希表
[454. 四数相加 II](https://leetcode-cn.com/problems/4sum-ii/)
```cpp
int fourSumCount(vector<int>& nums1, vector<int>& nums2, vector<int>& nums3, vector<int>& nums4) {
    unordered_map<int, int> map1;
    for (int a : nums1)
        for (int b : nums2)
            map1[a + b]++;

    int count = 0;
    for (int c : nums3)
        for (int d : nums4)
        {
            auto it = map1.find(0 - c - d);
            if (it != map1.end())
                count+=it->second;
        }

    return count;
}
```