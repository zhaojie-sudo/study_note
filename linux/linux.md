# Linux

## 基础知识
1. 软链接 相当于快捷方式 目录、文件均可以创建软链接 源文件要用绝对路径
    语法 `ln -s 路径 软链接名字`
    
    硬链接 相当于引用 只能对文件创建硬链接
    语法 `ln  路径 软链接名字`
2. 文件权限、用户、用户组
    1. chmod 改变文件权限 
    操作对象 u 用户 g 同组用户 o 其他用户 a 所有用户
    权限 执行 x 1 读 r 2 写 w 4
    chmod [who] [+ - =] [mode] 文件名
    2. chown 指定文件所有者
    3. chgrp 改变文件或目录所属群组
3. 查找或替换
    1. find 
    文件名 find 路径 -name  文件名
    大小 find 路径 -size  范围  // + 大于 - 小于 = 等于 
    文件类型 find 路径 -type  类型 // 普通文件 f 目录 d 符号链接 l 块设备文件 b 字符设备文件 c socket文件 s 管道 p
    2. grep 按文件内容查找 -r
    grep -r '查找关键字' 路径
    3. \* 匹配0-n个字符 ？匹配1个字符

  
## 系统编程
1. MMU memory mapping unit
    - 虚拟内存与物理内存的映射
    - 设置修改内存访问级别
2. 环境变量

    引入环境变量表 `extern char** envirn;` 以NULL结尾
3. 创建子进程
```c
#include<unistd.h>

pid_t fork();
pid_t getpid(); // 当前进程ID
pid_t getppid(); // 当前进程父进程ID
uid_t getuid();
gid_t getgid();
```
4. gdb调试

gdb只能跟踪一个进程，一定要在fork函数调用之前设置才有效
```c
set follow-fork-mode child // 命令设置gdb在fork之后跟踪子进程。
set follow-fork-mode parent // 设置跟踪父进程。
```

5. exec函数族
    - l (list)			命令行参数列表
    - p (path)			搜素file时使用path变量
    - v (vector)			使用命令行参数数组
    - e (environment)	使用环境变量数组,不使用进程原有的环境变量，设置新加载程序运行的环境变量

```c
execl("/bin/ls", "ls", "-l", "-F", NULL);
int execl(const char *path, const char *arg, ...); // 加载一个进程， 通过 路径+程序名 来加载。
execlp("ls", "ls", "-l", "-F", NULL);
int execlp(const char *file, const char *arg, ...); // 加载一个进程，借助 PATH 环境变量

int execle(const char *path, const char *arg, ..., char *const envp[]);
int execv(const char *path, char *const argv[]);
int execvp(const char *file, char *const argv[]);
int execve(const char *path, char *const argv[], char *const envp[]);
```

6. wait/waitpid

wait函数的作用
- 阻塞等待子进程退出 
- 回收子进程残留资源 
- 获取子进程结束状态(退出原因)。

```cpp
#include <sys/wait.h>

// 成功返回终止的子进程 ID, 失败时返回 -1
pid_t wait(int* staloc);

// 成功返回终止的子进程 ID 或 0, 失败时返回 -1
pid_t waitpid(pid_t pid, int* statloc, int options);
```
WIFEXITED 子进程正常终止返回 true

WEXITSTATUS 返回子进程的返回值

waitpid 参数说明
1. pid 等待终止的目标子进程的 pid, 若为 -1, 则和 wait 函数相同, 等待所有子进程
2. statloc
3. options 常量 WNOHANG 即使没有等待终止的子进程 也不会阻塞 退出返回 0


## makefile
1. 编译当前文件夹下所有.c .cpp文件
```mak
# wildcard 模式匹配
src_c = $(wildcard *.c)
# patsubst 模式替换
obj_c = $(patsubst %.c, %.o, $(src_c))
ans_c = $(patsubst %.c, %, $(src_c))

src_cpp = $(wildcard *.cpp)
obj_cpp = $(patsubst %.cpp, %.o, $(src_cpp))
ans_cpp = $(patsubst %.cpp, %, $(src_cpp))

all: $(ans_c) $(ans_cpp)

# $^ 第一个依赖 $@ 目标
%: %.c
	gcc $^ -o $@
%.o: %.c
	gcc -c $^ -o $@

%: %.cpp
	g++ $^ -o $@
%.o: %.cpp
	g++ -c $^ -o $@

.PHONY: clean
clean: 
	rm *.o $(ans_c) $(ans_cpp)
```