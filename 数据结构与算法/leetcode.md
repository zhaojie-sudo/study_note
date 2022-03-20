# Leetcode刷题笔记
## 位运算
[面试题 01.01. 判定字符是否唯一](https://leetcode-cn.com/problems/is-unique-lcci/)  
如果字符范围不限 应该选择 `unordered_set`

如果是ASCLL码 可以考虑用数组做哈希表 `int hash[256]`

如果是 26 个小写字母 可以考虑做 位运算
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

还有一种不限字符范围的解法
sort 再遍历 这种很稳定