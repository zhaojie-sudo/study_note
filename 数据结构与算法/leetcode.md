# Leetcode刷题笔记

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
[204. 计数质数](https://leetcode-cn.com/problems/count-primes/)  
埃氏筛
```cpp
int countPrimes(int n) {
    vector<int> isPrime(n, 1);
    int ans = 0;
    for (int i = 2; i < n; ++i) {
        if (isPrime[i]) {
            ans += 1;
            if ((long long)i * i < n) {
                for (int j = i * i; j < n; j += i) {
                    isPrime[j] = 0;
                }
            }
        }
    }
    return ans;
}
```
线性筛
```cpp
int countPrimes(int n) {
    vector<int> primes;
    vector<int> isPrime(n, 1);
    for (int i = 2; i < n; ++i) {
        if (isPrime[i]) {
            primes.push_back(i);
        }
        for (int j = 0; j < primes.size() && i * primes[j] < n; ++j) {
            isPrime[i * primes[j]] = 0;
            if (i % primes[j] == 0) {
                break;
            }
        }
    }
    return primes.size();
}
```

[780. 到达终点](https://leetcode-cn.com/problems/reaching-points/)  
辗转相除的思想
```cpp
bool reachingPoints(int sx, int sy, int tx, int ty) {
    while (tx > sx && ty > sy) { /* 辗转相除法 拿较大的减去较小的 */
        if (tx == ty) {
            return false;
        } else if (tx > ty) {
            tx = tx % ty;
        } else {
            ty = ty % tx;
        }
    }

    if (tx == sx && ty == sy) return true;
    else if (tx == sx && ty > sy) {
        return ty % tx == sy % tx;
    } else if (ty == sy && tx > sx) {
        return tx % ty == sx % ty;
    } else {
        return false;
    }
}
```

[50. Pow(x, n)](https://leetcode-cn.com/problems/powx-n/)  
注意迭代写法 O(1)的空间复杂度
```cpp
double myPow(double x, int n) {
    if (n == 0) return 1;
    long long N = n;
    return N > 0 ? quick(x, N) : 1.0 / quick(x, -N);
}
double quick(double x, long long n) {
    double res = 1.0;
    double contribute = x;
    while (n > 0) {
        if (n % 2 == 1) {
            res *= contribute;
        }
        contribute *= contribute;
        n /= 2;
    }
    return res;
}
```

[剑指 Offer 62. 圆圈中最后剩下的数字](https://leetcode-cn.com/problems/yuan-quan-zhong-zui-hou-sheng-xia-de-shu-zi-lcof/)  
两种思路 队列模拟 会超时
数学 F(n,m) = (m + F(n - 1, m)) % n
```cpp
int lastRemaining(int n, int m) {
    if (n == 1) return 0;
    int res = 0;
    for (int i = 2; i <= n; i++) {
        res = (m + res) % i;
    }

    return res;
}
```

[462. 最少移动次数使数组元素相等 II](https://leetcode.cn/problems/minimum-moves-to-equal-array-elements-ii/)  
中位数
```cpp
int minMoves2(vector<int>& nums) {
    int res = 0;
    sort(nums.begin(), nums.end());

    int avg = nums[nums.size() / 2];
    for (auto num : nums) res += abs(num - avg);
    return res;
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

## 树状数组
[307. 区域和检索 - 数组可修改](https://leetcode-cn.com/problems/range-sum-query-mutable/)  
单点修改、区间查询  
参考资料  
[OI Wiki 树状数组](https://oi-wiki.org/ds/fenwick/)  
[算法学习笔记(2) : 树状数组](https://zhuanlan.zhihu.com/p/93795692)  
方法一 树状数组
```cpp
NumArray(vector<int>& num) : tree(num.size() + 1, 0), nums(num.begin(), num.end()) { /* 树状数组索引从 1 开始 */
    for (int i = 0; i < num.size(); i++) {
        add(i + 1, nums[i]);
    }
}

void update(int index, int val) {
    add(index + 1, val - nums[index]);
    nums[index] = val;
}

int sumRange(int left, int right) {
    return query(right + 1) - query(left);
}
private:
int lowBit(int x) { /* 求最低位的 1 */
    return x & -x;
}

void add(int index, int val) { 
    for (int i = index; i < tree.size(); i += lowBit(i)) {
        tree[i] += val;
    }
}

int query(int n) { /* 查询前 n 项和 */
    int sum = 0;
    for (int index = n; index >= 1; index -= lowBit(index)) {
        sum += tree[index];
    }
    return sum;
}

vector<int> nums;
vector<int> tree;
```

总结  
针对不同的题目，我们有不同的方案可以选择（假设我们有一个数组）：

- 数组不变，求区间和：「前缀和」、「树状数组」、「线段树」
- 多次修改某个数（单点），求区间和：「树状数组」、「线段树」
- 多次修改某个区间，输出最终结果：「差分」
- 多次修改某个区间，求区间和：「线段树」、「树状数组」（看修改区间范围大小）
- 多次将某个区间变成同一个数，求区间和：「线段树」、「树状数组」（看修改区间范围大小）   

这样看来，「线段树」能解决的问题是最多的，那我们是不是无论什么情况都写「线段树」呢？

答案并不是，而且恰好相反，只有在我们遇到第 4 类问题，不得不写「线段树」的时候，我们才考虑线段树。

因为「线段树」代码很长，而且常数很大，实际表现不算很好。我们只有在不得不用的时候才考虑「线段树」。

总结一下，我们应该按这样的优先级进行考虑：

- 简单求区间和，用「前缀和」
- 多次将某个区间变成同一个数，用「线段树」
- 其他情况，用「树状数组」  

方法二 线段树
参考资料  
[算法学习笔记(14): 线段树](https://zhuanlan.zhihu.com/p/106118909)  
[OI Wiki 线段树](https://oi-wiki.org/ds/seg/)  
```cpp
NumArray(vector<int>& num) : nums(num.begin(), num.end()), tree(4 * nums.size(), 0), mark(4 * nums.size(), 0) { 
        build(0, nums.size() - 1, 0);
    }
    
    void update(int index, int val) {
       change(index, index, val - nums[index], 0, nums.size() - 1, 0);
       nums[index] = val;
    }
    
    int sumRange(int left, int right) {
        return query(left, right, 0, nums.size() - 1, 0);
    }
    
private:
void build(int l, int r, int p) { /* 区间 [l, r] 当前节点 p */
    if (l == r) { // 叶子节点
        tree[p] = nums[l];
        return;
    }

    int mid = l + (r - l) / 2;
    build(l, mid, 2 * p + 1);
    build(mid + 1, r, 2 * p + 2);
    tree[p] = tree[2 * p + 1] + tree[2 * p + 2];
}

void push_down(int p, int len) {
    mark[2 * p + 1] += mark[p];
    mark[2 * p + 2] += mark[p];
    tree[2 * p + 1] += mark[p] * (len - len / 2);
    tree[2 * p + 2] += mark[p] * (len / 2);
    mark[p] = 0;
}

void change(int l, int r, int d, int cl, int cr, int p) { /* 目标区间 [l, r] 增加值 d 当前区间 [cl, cr] 当前节点 p */
    if (cr < l || cl > r) return; /* 当前区间和目标区间不相交 */
    else if (cl >= l && cr <= r) { /* 当前区间完全包括在目标区间 */
        tree[p] += (cr - cl + 1) * d;
        if (cr > cl) {
            tree[p] += d;
        }
    } else {
        int mid = cl + (cr - cl) / 2;
        push_down(p, cr - cl + 1);
        change(l, r, d, cl, mid, 2 * p + 1);
        change(l, r, d, mid + 1, cr, 2 * p + 2);
        tree[p] = tree[2 * p + 1] + tree[2 * p + 2];
    }
}

int query(int l, int r, int cl, int cr, int p) { /* 目标区间 [l, r] 当前区间 [cl, cr] 当前节点 p */
    if (cr < l || cl > r) return 0; /* 当前区间和目标区间不相交 */
    else if (cl >= l && cr <= r) { /* 当前区间完全包括在目标区间 */
        return tree[p];
    } else {
        int mid = cl + (cr - cl) / 2;
        push_down(p, cr - cl + 1);
        return query(l, r, cl, mid, 2 * p + 1) + query(l, r, mid + 1, cr, 2 * p + 2);
    }
}

vector<int> nums;
vector<int> tree;
vector<int> mark;
```
方法三 分块数组
```cpp
NumArray(vector<int>& num) : nums(num.begin(), num.end()) { 
    size = sqrt(nums.size());
    sum.resize((nums.size() - 1) / size + 1);
    for (int i = 0; i < nums.size(); i++) {
        sum[i / size] += nums[i];
    }
}

void update(int index, int val) {
    sum[index / size] += val - nums[index];
    nums[index] = val;
}

int sumRange(int left, int right) {
    int bl = left / size, il = left % size;
    int br = right / size, ir = right % size;
    int res = 0;
    if (bl == br) {
        return accumulate(nums.begin() + bl * size + il, nums.begin() + bl * size + ir + 1, 0);
    } else {
        // sum1
        int sum1 = accumulate(nums.begin() + bl * size + il, nums.begin() + bl * size + size, 0);
        // sum2
        int sum2 = accumulate(sum.begin() + bl + 1, sum.begin() + br, 0);
        // sum3
        int sum3 = accumulate(nums.begin() + br * size, nums.begin() + br * size + ir + 1, 0);
        return sum1 + sum2 + sum3;
    }

    return res;
}
private:
    vector<int> nums;
    int size;
    vector<int> sum;
```