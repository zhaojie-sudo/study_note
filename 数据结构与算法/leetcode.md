# Leetcode刷题笔记

## 其他

[剑指 Offer 29. 顺时针打印矩阵](https://leetcode.cn/problems/shun-shi-zhen-da-yin-ju-zhen-lcof/)
```cpp
vector<int> result;
vector<int> spiralOrder(vector<vector<int>> &matrix)
{
    if (matrix.size() == 0 || matrix[0].size() == 0) return result;
    spiralOtder(matrix, 0, matrix[0].size() - 1, 0, matrix.size() - 1);
    return result;
}
void spiralOtder(vector<vector<int>> &matrix, int left, int right, int top, int bottom)
{
    if (left > right || top > bottom)
        return;
    if (left == right)
    {
        for (int i = top; i <= bottom; i++)
            result.push_back(matrix[i][right]);
        return;
    }
    if (top == bottom)
    {
        for (int i = left; i <= right; i++)
            result.push_back(matrix[top][i]);
        return;
    }
    for (int i = left; i < right; i++)
        result.push_back(matrix[top][i]);
    for (int i = top; i < bottom; i++)
        result.push_back(matrix[i][right]);
    for (int i = right; i > left; i--)
        result.push_back(matrix[bottom][i]);
    for (int i = bottom; i > top; i--)
        result.push_back(matrix[i][left]);
    spiralOtder(matrix, left + 1, right - 1, top + 1, bottom - 1);
    // cout << "hello" << endl;
}
```

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

## 数学
[剑指 Offer 14- II. 剪绳子 II](https://leetcode.cn/problems/jian-sheng-zi-ii-lcof/)
```cpp
int cuttingRope(int n) {
    if (n <= 3) {
        return n - 1;
    }

    //最大int 2147483647，为防止在某一次 mul乘3已经溢出，类型需要设为long
    long mul = 1;

    //3,3,3,3,3,4
    //3,3,3,3,3,3
    //3,3,3,3,3,2
    //3,3,3,3,3,1  X 此种情况算在和前面 3+1 和为 4
    while (n > 4) {
        //每次乘积后取余防止大数
        mul = mul * 3 % 1000000007;

        n -= 3;
    }
    return (int) (mul * n % 1000000007);
}
```

[剑指 Offer 43. 1～n 整数中 1 出现的次数](https://leetcode.cn/problems/1nzheng-shu-zhong-1chu-xian-de-ci-shu-lcof/)
```cpp
int countDigitOne(int n) {
    vector<int> count(10, 0);
    count[1] = 1;
    for (int i = 2; i < count.size(); i++) {
        count[i] = pow(10, i - 1) + 9 * count[i - 1] + count[i - 1];
        // cout << count[i] << " ";
    }
    // cout << endl;

    return countDigitOne(count, n);
}

int countDigitOne(const vector<int>& count, int n) {
    if (n == 0) return 0;
    if (n < 10) return 1;

    int res = 0;
    string str = to_string(n);        
    res += count[str.size() - 1];
    
    cout << res << endl;

    int num = n - (str[0] - '0') * pow(10, str.size() - 1);

    res += str[0] - '0' == 1 ? num + 1 : pow(10, str.size() - 1);
    if (str[0] - '0' > 1) {
        res += (str[0] - '0' - 1) * count[str.size() - 1];
    }

    // cout << n << " " << num << " " << res << endl;

    return res + countDigitOne(count, num);           
}
```
[剑指 Offer 44. 数字序列中某一位的数字](https://leetcode.cn/problems/shu-zi-xu-lie-zhong-mou-yi-wei-de-shu-zi-lcof/)
```cpp
int findNthDigit(int n) {
    if (n < 10) return n;

    vector<int> start(10, 0);  
    start[1] = 1;
    for (int i = 2; i < 10; i++) {
        start[i] = 9 * pow(10, i - 2) * (i - 1) + start[i - 1];
        // cout << start[i] << " ";
    }
    // cout << endl;

    int i = start.size() - 1;
    while (n < start[i]) i--;
    // cout << i << endl;

    int index = (n - start[i]) % i;
    // cout << index << endl;

    int num = pow(10, i - 1) + (n - start[i]) / i;
    // cout << num << endl;

    string str = to_string(num);
    // cout << str << endl;

    return str[index] - '0';
}
```
[剑指 Offer 49. 丑数](https://leetcode.cn/problems/chou-shu-lcof/)
```cpp
int nthUglyNumber(int n) {
    vector<int> dp(n + 1, 0);
    dp[1] = 1;
    int p2 = 1, p3 = 1, p5 = 1;
    for (int i = 2; i <= n; i++) {
        int num2 = dp[p2] * 2;
        int num3 = dp[p3] * 3;
        int num5 = dp[p5] * 5;

        dp[i] = min(num2, min(num3, num5));
        if (dp[i] == num2) p2++;
        if (dp[i] == num3) p3++;
        if (dp[i] == num5) p5++;
        // cout << num2 << " " << num3 << " " << num5 << " " << dp[i] << endl;
        // cout << p2 << " " << p3 << " " << p5 << " " << dp[i] << endl;
        // cout << "--------------" << endl;
    }

    return dp[n];
}
```
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