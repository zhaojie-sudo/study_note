# kmp 算法

**next 数组**

kmp 算法最重要的就是其 next 数组的求法,不同 next 数组的定义对应着不同求 next 数组的算法。

我们这里采取的是代码随想录中的定义 [28.substr][1]

next[i] 表示第0~i字符最长相同前后缀的长度

前缀: 从第0个字符开始到某一个字符(不包括最后一个字符)结束的连续子串
后缀: 从某一个字符(不包括第0个字符)开始到最后一个字符结束的连续子串

如字符串s="abcabf", 其对应next数组为{0,0,0,1,2,0}

**next数组的构建**

```cpp
void getNext(int *next, const string &s)
{
    int j = 0;
    next[0] = j;
    for (int i = 1; i < s.size(); i++)
    {
        while (j > 0 && s[i] != s[j])
            j = next[j - 1]; // 这步最难理解，为什么这步叫回溯
        if (s[i] == s[j])
            j++;
        next[i] = j;
    }
}
```

理解这段代码的关键在于理解j和next[j]的含义

我们知道next[j]的意思是字符串0~j最长相同前后缀的长度

那么j的含义呢？ 我们可以注意到，进入第5行的for循环后，每一步的j实际上是上一步的next[i],即j=next[i-1]

那么j的含义就是上一个字符串所对应的最大相同前后缀的长度

又因为字符串s的索引是从0开始计算的，那么s[j]就是下一个待匹配的字符

如果 `s[i]=s[j]` 那么从0~i这个字符串的最长前后缀长度就是`j++`

如果 s[i]！=s[j] 那么我们实际上要做的就是 拿字符串0~j 与字符串0~i做匹配 

现在发现 s[i]！=s[j] 根据next数组的定义 就不难想出 `j=next[j-1]`了

**主函数substr**

~~~cpp
int substr(string haystack, string needle)
{
    if (needle.size() == 0)
        return 0;
    const int SIZE = needle.size();
    int next[SIZE];
    getNext(next, needle);
    int j = 0;
    for (int i = 0; i < haystack.size(); i++)
    {
        while (j > 0 && haystack[i] != needle[j])
            j = next[j - 1];
        if (haystack[i] == needle[j])
            j++;
        if (j == needle.size())
            return (i - needle.size() + 1);
    }
    return -1;
}
~~~

**nextval数组**









[1]: <https://programmercarl.com/0028.%E5%AE%9E%E7%8E%B0strStr.html#%E5%85%B6%E4%BB%96%E8%AF%AD%E8%A8%80%E7%89%88%E6%9C%AC>