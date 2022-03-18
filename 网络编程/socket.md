# Socket 网络编程

## 0. 问题
1. socket 编程头文件定义
2. sockaddr sockaddr_in 区别

# Chapter1 基础知识

## 套接字常用函数
### 服务器端
1. socket 创建套接字

```c
#include <sys/socket.h>

// 成功返回文件描述符，失败返回 -1
int socket(int domain, int type, int protocol);
```

domain 协议族信息

1. PF_INET  IPv4 协议族
2. PF_INET6  IPv6 协议族
3. PF_LOCAL
4. PF_PACKET
5. PF_IPX

type 数据传输类型

1. SOCK_STREAM 面向连接的套接字

    可靠的、按序传递的、基于字节的、面向连接的套接字

2. SOCK_DGRAM 面向消息的套接字

    不可靠的、不按序传递的、以数据的高速传输为目的的套接字

protocol 协议信息

    在前两个参数已经可以确定协议时，可以取 0

2. bind 为创建好的套接字绑定IP地址和端口号

```c
#include <sys/socket.h>

// 成功返回 0，失败返回 -1
int bind(int sockfd, struct sockaddr *myaddr, socklen_t addrlen);
```

3. listen 等待连接

```c
#include <sys/socket.h>

// 成功返回 0，失败返回 -1
int listen(int sockfd, int backlog);
```
backlog 连接请求等待队列长度

4. accept 接受连接

```c
#include <sys/socket.h>

// 成功返回文件描述符，失败返回 -1
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
```


### 客户端

1. connect 请求连接

```c
#include <sys/socket.h>

// 成功返回 0，失败返回 -1
int connect(int sockfd, struct sockaddr *serv_addr, socklen_t addrlen);
```

## 文件操作函数
1. open 打开文件以读写

```c
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> // 提供文件控制函数

// 成功时返回文件描述符，失败时返回 -1
int open(const char *path, int flag);
```

path 文件名字符串地址 

flag 文件打开模式

    1. O_CREAT 必要时创建
    2. O_TRUNG 删除全部现有数据
    3. O_APPEND 维持现有数据，保存到其后面
    4. O_RDONLY 只读
    5. O_WRONLY 只写
    6. O_RDWR 读写

2. close 关闭文件

```c
#include <unistd.h>

// 成功返回 0，失败返回 -1
int close(int fd);
```

fd 需要关闭文件的文件描述符

3. write 向文件传输数据

```c
#include <unistd.h>

// 成功返回写入字节数，失败返回 -1
ssize_t write(int fd, const void *buf, size_t nbytes);
```

fd 数据传输对象文件描述符
buf 带传输数据缓存地址
buf -> fd

4. read 接收数据

```c
#include <unistd.h>

// 成功返回接收字节数，失败返回 -1
ssize_t read(int fd, const void *buf, size_t nbytes);
```

fd -> buf

## 数据结构
```c
struct sockaddr_in {
    sa_family_t sin_family; // 地址族 AF
    uint16_t sin_port;  // 16 位端口号
    struct in_addr sin_addr; // 32 位 IP 地址 
    char sin_zero[8]; // 不使用
};

struct in_addr {
    In_addr_t s_addr; // 32 位 IP 地址 
};

struct sockaddr {
    sa_family_t sin_family; // 地址族
    char sa_data[14]; // 地址信息
}
```

sin_family 协议族所适用的地址族
1. AF_INET // IPv4 网络协议使用的地址族
2. AF_INET6
3. AF_LOCAL

sockaddr_in / sockaddr 结构体的大小都是 15 字节 

sin_zero[8] 必须填充 0

sa_data[14] 保存 IP 地址和端口号，剩余填充 0

## 字节序转换函数
```c
#include <arpa/inet.h> // 提供地址转换

unsigned short htons(unsigned short); // h 代表主机字节序
unsigned short ntohs(unsigned short); // n 代表网络字节序
unsigned long htons(unsigned long);  // s short 2 字节 端口号转换
unsigned long ntohs(unsigned long); // l long 4 字节 IP 地址转换
```

```c
#include <arpa/inet.h>

// 成功返回 32 位大端序整数型值，失败返回 INADDR_NONE
in_addr_t inet_addr(const char * string);   // char* -> u32int_t

// 成功返回 1， 失败返回 0
int inet_aton(const char* string, struct in_addr* addr); // 与 inet_addr 作用一样，效率更好，结果直接存到 传入参数 addr 中

// 成功返回转换的字符串地址值，失败返回 -1
char* inet_ntoa(struct in_addr adr);

// 将每个字节初始化为同一值，如
memset(&addr, 0, sizeof(addr));
```

INADDR_ANY 自动获取服务器端的 IP 地址

## hello_server.c

```c
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(char* message);

int main(int argc, char* argv[]) {
    int serv_sock;
    int clnt_sock;

    struct sockaddr_in serv_addr;
    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size;

    char message[] = "Hello World!";

    if (argc != 2) {
        printf("Usage : %s <port>\n", argv[0]);
        exit(1);
    }

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if (serv_sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if (bind(serv_sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("bind() error");

    if (listen(serv_sock, 5) == -1)
        error_handling("listen() error");

    clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*)&clnt_addr, &clnt_addr_size);
    if (clnt_sock == -1)
        error_handling("accept() error");

    write(clnt_sock, message, sizeof(message));
    close(clnt_sock);
    close(serv_sock);
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
    exit(1);
}
```

## hello_client.c

```c
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void error_handling(char* message);

int main(int argc, char* argv[]) {
    int sock;
    struct sockaddr_in serv_addr;
    char message[30];
    int str_len;

    if (argc != 3) {
        printf("Usage : %s <IP> <port>\n", argv[0]);
        exit(1);
    }

    sock = socket(PF_INET, SOCK_STREAM, 0);
    if (sock == -1)
        error_handling("socket() error");

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if (connect(sock, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) == -1)
        error_handling("connect() error!");

    str_len = read(sock, message, sizeof(message) - 1);
    if (str_len == -1)
        error_handling("read() error!");

    printf("Message from server: %s \n", message);
    close(sock);
    return 0;
}

void error_handling(char* message) {
    fputs(message, stderr);
    fputc('\n', stderr);
}
```

# Chapter2 TCP/UDP 
```cpp
#include <sys/socket.h>

// 成功时返回传输的字节数，失败时返回 -1
ssize_t sendto(int sock, void* buf, size_t nbytes, int flags, struct sockaddr* to, socklen_t len);

// 成功时返回接收的字节数，失败时返回 -1
ssize_t recvfrom(int sock, void* buf, size_t nbytes, int flags, struct sockaddr* from, socklen_t len);
```
flags 可选择参数 默认 0

sendto传输数据的三个过程
1. 向 UDP 套接字注册目标 IP 和端口号
2. 传输数据
3. 删除 UDP 套接字中注册的目标地址信息

注册了目标地址的套接字称为 connect 套接字，可用 connect 函数创建



# 半关闭

```cpp
#include <sys/socket.h>

// 成功返回 0，失败时返回 -1
int shutdown(int sock, int howto);
```

howto 
1. SHUT_RD
2. SHUT_WR
3. SHUT_RDWR

# DNS IP
```cpp
#include <netdb.h>

// 成功返回 hostent 结构体地址， 失败返回 NULL 指针
struct hostent* gethostbyname(const char* hostname);

// 成功返回 hostent 结构体地址， 失败返回 NULL 指针
struct hostent* gethostbyaddr(const char* addr, socklen_t len, int family);
// addr 含有 IP 地址信息的 in_addr 结构体指针, 需要强制类型转换

struct hostent {
    char* h_name;      // offical name
    char** h_aliases;   // alias list
    int h_addrtype;     // host address type
    int h_length;       // address length
    char** h_addr_list;     // address list
}

# 套接字的可选择项
```cpp
#include <sys/socket.h>

// 成功时返回 0， 失败时返回 -1
int getsockopt(int sock, int level, int optname, void* optval, socklen_t* optlen);

// 成功时返回 0， 失败时返回 -1
int setsockopt(int sock, int level, int optname, void* optval, socklen_t* optlen);
```

1. level 要查看的可选择的协议层
    1. SOL_SOCKET 套接字相关通用可选项
        1. SO_TYPE 查看套接字类型 只读
        2. SO_SNDBUF SO_RCVBUF 输入输出缓存大小
        3. SO_REUSEADDR 地址复用
    2. IPPROT_IP  IP 协议相关事项
    3. IPPROTO_TCP TCP 协议相关事项
        1. TCP_NODELAY Nagle算法
2. optname 要查看的可选项名
3. optval 保存查看结果的缓冲地址值
4. optlen 向 optval 传递的缓存大小， 保存通过第四个参数返回的可选项信息的字节数

# 多进程服务器端

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

```cpp
#include <signal.h>

// 为了在产生信号时调用，返回之前注册的函数指针
void (*signal(int signo, void(*func) (int )))(int); //

#include <unistd.h>

// 返回 0 或以秒为单位的距 SIGALRM 信号所剩时间
unsigned int alarm(unsiged int seconds); 
```

1. SIGALRM 已到通过 alarm 函数注册的时间
2. SIGINT 输入 ctrl + c
3. SIGCHLD 子进程终止

```cpp
#include <signal.h>

// 成功返回 0， 失败返回 -1
int sigaction(int signo, const struct sigaction* act, const sigaction* oldact);
// act 第一个参数的信号处理器信息
// 获取此前注册的信号处理函数指针，不需要则传递 0

struct sigaction {
    void (*sa_haldler)(int);
    sigset_t sa_mask;
    int sa_flags;
}

// sigemptyset(&actsa_mask);
```

# 进程间通信
```cpp
#include <unistd.h>

// 成功返回 0， 失败返回 -1
int pipe(int filedes[2]);
// filedes[0] 通过管道接收数据使用的文件描述符
// filedes[1] 通过管道传输数据使用的文件描述符
```
# IO 复用
## select

select 函数的调用方法和顺序
1. 设置文件描述符

    使用 fd_set 数组变量 监视 读、写、异常
    ```c
    FD_ZERO(fd_set* fdset);  // 
    FD_SET(int fd, fd_set* fdset);
    FD_CLR(int fd, fd_set* fdset);
    FD_ISSET(int fd, fd_set* fdset);
    ```
2. 指定监视范围
    ```c
    #include <sys/select.h>
    #include <sys/time.h>

    // 成功时返回大于 0 的值，失败时返回 -1
    int select(int maxfd, fd_set* readset, fd_set* writeset, fd_set* exceptset, const struct timeval* timeout);
    // 发生错误时返回 -1，超时返回 0， 因关注的事件返回时，返回大于 0 的值，该值为发生事件的文件描述符数
    ```
3. 设置超时

    select函数的最后一个参数是 timeval 结构体
    ```c
    struct timeval {
        long tv_sec;  // seconds
        long tv_usec;  // microseconds
    }
    ```
4. 调用 select 函数
5. 查看调用结果
