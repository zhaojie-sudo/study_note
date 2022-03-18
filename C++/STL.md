# 侯捷 STL
1. 源代码 GNU 2.91
2. 为什么 list 不能使用 ::sort() 排序 

::sort() 内部实现上 使用随机访问迭代器 RandomAccessIterator
3. 所有的算法 最终涉及元素本身的操作 就是比大小
4. 模板 类模板 函数模板 运算符重载 特化 偏特化 ？？？
## STL 六大组件
- 容器 Containers
- 分配器 Allocators
- 算法 Algorithms
- 迭代器 Iterators
- 适配器 Adapters
- 仿函数 Functors
## 容器
- 序列容器
    - Array
    - Vector
    - Deque
    - List
    - Forward-List
- 关系容器
    - Set / Multiset
    - Map / Multimap
    - Unordered Set / Multiset
    - Unordered Map / Multimap

1. multimap 不可用 [] 做 insert
## 分配器
1. 不应该直接使用分配器
