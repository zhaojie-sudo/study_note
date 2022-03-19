# stack and queue
[232.用栈实现队列](https://leetcode-cn.com/problems/implement-queue-using-stacks/)
```cpp
class MyQueue {
public:
    MyQueue() { }
    
    void push(int x) {
        staIn.push(x);
    }
    
    int pop() {
        int temp = peek();
        staOut.pop();
        return temp;
    }
    
    int peek() {
        if (staOut.empty()) {
            while(!staIn.empty()) {
                staOut.push(staIn.top());
                staIn.pop();
            }
        } 
        return staOut.top();
    }
    
    bool empty() {
        return staIn.empty() && staOut.empty();
    }
    stack<int> staIn; // push
    stack<int> staOut;  // pop peek
};
```

[225. 用队列实现栈](https://leetcode-cn.com/problems/implement-stack-using-queues/)  
这个题多留意 
```cpp
class MyStack {
public:
    MyStack() {}
    
    void push(int x) {
        que.push(x);
    }
    
    int pop() {
        int len = que.size();
        while (len > 1) {
            que.push(que.front());
            que.pop();
            len--;
        }
        int temp = que.front();
        que.pop();
        return temp;
    }
    
    int top() {
        int temp = pop();
        que.push(temp);
        return temp;
    }
    
    bool empty() {
        return que.empty();
    }
    queue<int> que;
};
```
[20. 有效的括号](https://leetcode-cn.com/problems/valid-parentheses/)
```cpp
switch (expression) {
    case constant-expression  :
       statement(s);
       break; // 可选的
    case constant-expression  :
       statement(s);
       break; // 可选的
  
    // 您可以有任意数量的 case 语句
    default : // 可选的
       statement(s);
}
```
解法一
```cpp
bool isValid(string s) {
    if (s.size() == 0) return true;
    stack<char> sta;

    for (int i = 0; i < s.size(); i++) {
        if (s[i] == '(' || s[i] == '{' || s[i] == '[')
            sta.push(s[i]);
        else {
            switch (s[i]) {
                case ')' :
                    if (sta.empty() || sta.top() != '(')
                        return false;
                    break;
                case '}' :
                    if (sta.empty() || sta.top() != '{')
                        return false;
                    break;
                case ']' :
                    if (sta.empty() || sta.top() != '[')
                        return false;
                    break;
            }
            sta.pop();
        }
    }
    return sta.empty();
}
```
解法二
```cpp
bool isValid(string s) {
    stack<char> stack;
    for (int i = 0; i < s.length(); i++)
    {
        if(stack.empty())
            stack.push(s[i]);
        else if (s[i] - stack.top() > 2 || s[i] - stack.top() <= 0)
            stack.push(s[i]);
        else
            stack.pop();
    }

    return stack.empty();
}
```
[150. 逆波兰表达式求值](https://leetcode-cn.com/problems/evaluate-reverse-polish-notation/)
```cpp
int evalRPN(vector<string>& tokens) {
    if (tokens.size() == 0) return 0;
    stack<int> sta;
    for (string c : tokens) {
        if (c == "+" || c == "-" || c == "*" || c == "/") {
            int num2 = sta.top();
            sta.pop();
            int num1 = sta.top();
            sta.pop();

            if (c == "+") 
                sta.push(num1 + num2);
            else if (c == "-")
                sta.push(num1 - num2);
            else if (c == "*")
                sta.push(num1 * num2);
            else
                sta.push(num1 / num2);
            
        } else {
            sta.push(stoi(c));
        }
    }
    return sta.top();
}
```
[239. 滑动窗口最大值](https://leetcode-cn.com/problems/sliding-window-maximum/)
单调队列
```cpp
deque<int> que;
void mypush(int num) {
    while (!que.empty() && que.back() < num) {
        que.pop_back();
    }
    que.push_back(num);
}
vector<int> maxSlidingWindow(vector<int>& nums, int k) {
    vector<int> result;
    if (nums.size() == 0 || k > nums.size()) return result;
    for (int i = 0; i < k; i++) {
        mypush(nums[i]);
    }
    result.push_back(que.front());
    for (int i = k; i < nums.size(); i++) {
        if (nums[i - k] == que.front()) {
            que.pop_front();
        }
        mypush(nums[i]);
        result.push_back(que.front());
    }
    return result;
}
```
[347.前 K 个高频元素](https://leetcode-cn.com/problems/top-k-frequent-elements/)  
优先级队列 `priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;`
解法一 快排
```cpp
static bool cmp(const pair<int, int>& left, const pair<int, int>& right) {
    return left.second > right.second;
}
vector<int> topKFrequent(vector<int>& nums, int k) {
    vector<int> result;
    unordered_map<int, int> map;
    for (int num : nums) {
        map[num]++;
    }
    vector<pair<int, int>> vec;
    for (auto pair : map) {
        vec.push_back(pair);
    }
    sort(vec.begin(), vec.end(), cmp);
    for (int i = 0; i < k; i++) {
        result.push_back(vec[i].first);
    }
    return result;
}
```
解法二 优先级队列
```cpp
// 小顶堆
class mycomparison {
public:
    bool operator()(const pair<int, int>& lhs, const pair<int, int>& rhs) {
        return lhs.second > rhs.second;
    }
};
vector<int> topKFrequent(vector<int>& nums, int k) {
    // 要统计元素出现频率
    unordered_map<int, int> map; // map<nums[i],对应出现的次数>
    for (int i = 0; i < nums.size(); i++) {
        map[nums[i]]++;
    }

    // 对频率排序
    // 定义一个小顶堆，大小为k
    priority_queue<pair<int, int>, vector<pair<int, int>>, mycomparison> pri_que;

    // 用固定大小为 k 的小顶堆，扫面所有频率的数值
    for (unordered_map<int, int>::iterator it = map.begin(); it != map.end(); it++) {
        pri_que.push(*it);
        if (pri_que.size() > k) { // 如果堆的大小大于了K，则队列弹出，保证堆的大小一直为k
            pri_que.pop();
        }
    }

    // 找出前K个高频元素，因为小顶堆先弹出的是最小的，所以倒序来输出到数组
    vector<int> result(k);
    for (int i = k - 1; i >= 0; i--) {
        result[i] = pri_que.top().first;
        pri_que.pop();
    }
    return result;
}
```