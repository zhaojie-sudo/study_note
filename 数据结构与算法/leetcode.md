# Leetcode刷题笔记（代码随想录）
## 数组
### 二分查找

[704.二分查找](https://leetcode-cn.com/problems/binary-search/)

给定一个无重复的有序数组 nums, 查找等于给定值 target 的元素的索引，找不到返回 -1
```cpp
int search(vector<int>& nums, int target) {
        if (nums.empty())
            return -1;
        int left = 0, right = nums.size() - 1; // nums.size()=0可能会有问题
        while (left <= right)                  // 若left==right 也能退出
        {
            int mid = left + (right - left) / 2;
            if (nums[mid] == target)
                return mid;
            else if (nums[mid] > target) // 左边
                right = mid - 1;
            else // 右边
                left = mid + 1;
        }

        return -1;
    }
```
搜索区间为 [left,right] 因此循环终止条件 left<=right 

[34. 在排序数组中查找元素的第一个和最后一个位置](https://leetcode-cn.com/problems/find-first-and-last-position-of-element-in-sorted-array/)

给定一个有重复的有序数组 nums, 查找等于给定值 target 的第一个, 最后一个元素的索引, 找不到返回 -1
```cpp
vector<int> searchRange(vector<int>& nums, int target) {
        if(nums.empty())
            return {-1, -1};
            
        int left = 0, right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left) / 2;

            if (nums[mid] > target)
                right = mid - 1;
            else if (nums[mid] < target)
                left = mid + 1;
            else
                right = mid;
        }
        int first=-1;
        if (nums[left] == target)
            first = left;
        else
            first = -1;

        right = nums.size() - 1;
        while (left < right)
        {
            int mid = left + (right - left + 1) / 2;  // 注意为什么要加一

            if (nums[mid] < target)
                left = mid + 1;
            else if (nums[mid] > target)
                right = mid - 1;
            else
                left = mid;
        }
        int secord=-1;
        if (nums[right] == target)
            secord = right;
        else
            secord = -1;

        return {first,secord};
    }
```
和[704.二分查找](https://leetcode-cn.com/problems/binary-search/)类似 但要注意最右边元素是如何匹配的(mid中为什么要加1)
### 双指针
[27.移除元素](https://leetcode-cn.com/problems/remove-element/)

给定一个数组 nums 和一个值 val，原地移除所有数值等于 val 的元素，并返回移除后数组的新长度。
不要使用额外的数组空间，你必须仅使用 O(1) 额外空间并原地修改输入数组。
元素的顺序可以改变。你不需要考虑数组中超出新长度后面的元素。
```cpp
 int removeElement(vector<int>& nums, int val) {
        int n = nums.size();
        if(n==0)
            return n;

        int fast = 0, slow = 0;
        for (; fast < n;fast++)
            if(nums[fast]!=val)
                    nums[slow++] = nums[fast];
               
        return slow;
    }
```

[844. 比较含退格的字符串](https://leetcode-cn.com/problems/backspace-string-compare/)

给定 s 和 t 两个字符串，当它们分别被输入到空白的文本编辑器后，请你判断二者是否相等。# 代表退格字符。
如果相等，返回 true ；否则，返回 false 。
注意：如果对空文本输入退格字符，文本继续为空。

```cpp
bool backspaceCompare(string s, string t)
    {
        change(s);
        change(t);
        return s==t;
    }
    void change(string &s)
    {
        int slow = 0;
        for (int fast = 0; fast < s.size(); fast++)
            if (s[fast] != '#')
                s[slow++] = s[fast];
            else if(slow>0)
                slow--;
        s.resize(slow);
    }
```
### 滑动窗口
[209. 长度最小的子数组](https://leetcode-cn.com/problems/minimum-size-subarray-sum/)

给定一个含有 n 个正整数的数组和一个正整数 target 。
找出该数组中满足其和 ≥ target 的长度最小的 连续子数组 [numsl, numsl+1, ..., numsr-1, numsr] ，并返回其长度。如果不存在符合条件的子数组，返回 0 。

```cpp
int minSubArrayLen(int target, vector<int>& nums) {
        int sum=0,length=nums.size()+1;
        int slow=0;
        for(int fast=0;fast<nums.size();fast++)
        {
            sum+=nums[fast];
            while(sum>=target)  // 保证sum<target
                {
                    length=length<fast-slow+1?length:fast-slow+1;
                    sum-=nums[slow++];
                }
        }                    
        return length>nums.size()?0:length;
```
窗口是指满足给定条件的连续子串
外层用 for 循环后，内层循环应该用 while 保证子串不满足窗口条件，从而需要 right++

[76. 最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring/)

给你一个字符串 s 、一个字符串 t 。返回 s 中涵盖 t 所有字符的最小子串。如果 s 中不存在涵盖 t 所有字符的子串，则返回空字符串 "" 。

```cpp
string minWindow(string s, string t)
    {
        if (s.size() < t.size())
            return "";
        if (s == t)
            return s;

        unordered_map<char, int> s_map, t_map;
        for (auto c : t)
            t_map[c]++;

        string res = s;
        int flag = 0;
        for (int left = 0, right = 0; right < s.size(); right++)
        {
            s_map[s[right]]++;
            if (isok(s_map, t_map))
            {
                flag = 1;
                while (isok(s_map, t_map))
                    s_map[s[left++]]--;
                // cout << res << " " << left << " " << right << endl;
                res = (res.size() < right - left + 2) ? res : s.substr(left - 1, right - left + 2);
            }
        }

        return (flag == 1) ? res : "";
    }

    bool isok(unordered_map<char, int> &s_map, unordered_map<char, int> &t_map)
    {
        for (auto it = t_map.begin(); it != t_map.end(); it++)
            if (s_map[it->first] < it->second)
                return false;

        return true;
    }
```
## 链表