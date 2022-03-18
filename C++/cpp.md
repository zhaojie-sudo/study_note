# cpp
1. 数组是内置数据类型 其长度是编译时就确定的 因此是constexpr
2. new的内存要记得delete
5. parameter形参,argument 实参
6. 计算机1s大概处理的n的规模 
    O(n) 5e8 O(n^2)2.25e4 O(nlogn) 2e7
7. 递归算法的时间、空间复杂度分析
    时间复杂度 递归次数*每次递归的操作数 // 函数、二叉树
    空间复杂度 递归深度*递归函数内部申请内存 
8. 快速幂、斐波那契数列的实现
9. 内存对齐
10. ACM模式 刷完代码随想录以后 刷剑指offer ACM模式
11. 代码随想录相关 
    人生苦短，我用vim
    解密互联网大厂研发流程
    程序员简历模板
    大厂面试流程注意事项
12. 

# 其他
## Tips
1. 文件结束符 Windows Ctrl+Z Linux Ctrl+D

## Windows 终端常用命令
1. 跳转盘符 
首先要跳转对应磁盘 如`D:\` 然后`cd` 对应目录
2. `Tab`自动补全 只能补全当前路径下的目录和文件
3. `dir` 查看当前路径下的目录和文件
4. `tree` 当前路径的目录层次结构
5. `cls` 清屏
6. `md/mkdir` 创建目录 `rd` 删除目录
7. `del` 删除文件
8. `type` 创建空白文件/查看文件内容
9. `echo` 创建非空文件 `echo content > filename`
## Windows/Linux 系统编译运行C/C++程序
使用 GNU g++ 编译器
### 编译过程
1. 预处理 -E 生成.ii文件 `g++ -E helloworld.cpp -o helloworld.ii`
2. 编译 -S 生成.s文件 `g++ -S helloworld.ii -o helloworld.s`
3. 汇编 -c 生成.o文件 `g++ -c helloworld.s -o helloworld.o`
4. 链接    生成 可执行文件(Windows 默认.exe/Linux 默认a.out) `g++  helloworld.o -o helloworld1`
5. 执行 Windows cppname.exe  Linux ./a.out
### 常用拓展名
1. .cpp c++源文件 需要预处理
2. .ii c++源文件 不需要预处理
3. .s 汇编语言代码
4. .o 目标文件
5. .a 静态库 .so 动态库
6. .h 头文件
### 编译选项

### 静态库制作

### 动态库制作