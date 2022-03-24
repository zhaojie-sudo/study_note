# Leetcode刷题笔记
## 位运算
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