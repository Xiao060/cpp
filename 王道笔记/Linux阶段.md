# Linux

## 文件映射

## IO 多路复用_select

### 使用

1. 申请资源/创建监听集合: `fdset xxx`
    1. `void FD_CLR(int fd, fdset* set)`: 删除一个

2. 初始化集合: `void FD_ZERO(fdset* set)`

3. 增加监听: `void FD_SET(int fd, fdset* set)`

4. 进程调用 select (OS 轮询, 进程等待)
    1. `int select(int maxfd, fdset* rdset, fdset* wrset, fdset* excepset, struct timeval* timeout);`

    2. 返回值为 3 个就绪集合中的 fd 总数

    3. **maxfd** 为最大的文件描述符 + 1

    4. 读/写/异常集合, 没有填 `NULL`, 均为 **传入传出参数**, select 会将其修改为 就绪集合, 故 2/3 两步应放在循环内;  
        若 W 端关闭, 则 R 端立即返回 0, select 永远处于就绪状态, 故 读集合 就绪后需要对每个 R 端进行检查

    5. timeout 为单次轮询的最长时间, `NULL` 表示一直等

5. 文件描述符就绪, 返回就绪集合
    1. `void FD_ISSET(int fd, fdset* set)`: 检查是否存在

### 底层原理

1. 1024 bit 的位图

2. 1024即为一个进程默认能够打开的最多的文件数量

### 运行流程

1. 将监听集合 由 **用户态栈帧上** 拷贝到 **内核态**

2. 内核轮询 [0, maxfd -1]

3. 轮询直到某 fd 就绪, 得到就绪集合

4. 将就绪集合 由 内核态 拷贝回 用户态

### select 缺陷 (与 epoll 区别, 面试重点)

1. 上限 1024, 不好修改

2. 大量内核 与 用户态之间的 数据拷贝

3. 监听 与 就绪集合 耦合

4. 就绪检查不合理, 当海量连接少量就绪时 需要遍历所有连接, 依次判断是否就绪(FD_ISSET)

## 权限

## 进程相关命令

## 进程优先级

## 创建进程_system

## 创建进程_fork

## 创建进程_exec

## 孤儿进程_wait/waitpid

## 进程终止

## 守护进程

## gdb 调试

## 进程间通信_有名管道(named pipe)

### 概述

1. 有名 即 在文件系统中存在, but 该文件只能用于通信, 不能存储数据, 也不能用 vim 打开

2. 创建有名管道文件 `makefifo xxx`

3. named pipe 通信方式 为 半双工, but 一般单工使用, 使用 2 条 单工管道组成 1 条 全双工管道

### 使用

1. `open(filename, mode)`
    1. 打开模式: `O_RDONLY` / `O_WRONLY` 二选一;  
        若以 `O_RDWR` 方式打开, 则为非阻塞方式半双工通信

    2. 2 个进程 打开 2 个管道文件时 注意打开**顺序**, 获取资源的顺序不对会导致 <mark>死锁</mark>  
        例:  
        进程 1 先打开管道 A 读端, 后打开 B 写端;  
        进程 2 先打开管道 B 读端, 后打开 A 写端;  
        此时 进程 1/2 的 open 都被阻塞在第一步, 无法继续向下进行
2. `read()`
    1. 管道为空 且 W 端未关, 则<mark>阻塞</mark>, 类似设备文件 <------> 磁盘文件非空直接返回 0
    2. 管道为空 且 W 端已关, 则 读到文件终止符, 直接返回
3. `write()`
    1. 写完立刻返回, 写满会引发阻塞
    2. R 端已关, 写入会触发 `SIGPIPE`, 异常终止
4. `close()`

## 进程间通信_无名管道

只适合父子进程间通信

### 方式 1 (库函数)

![](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309182203589.png)

1. 打开管道: `FILE* popen(const char* command, const char* type);`
    1. 根据 **command**, 启动一个子进程 (让子进程执行命令, 并将父子进程连通)
    2. 父子进程间存在一条通道
    3. type 表示 父进程管道的类型  
        `r` 表示 父读子写, 即重定向子进程的 **stdout**  
        `w` 表示 父写子读, 即重定向子进程的 **stdin**

2. 读写: `fread() / fwrite()`

3. 关闭管道: `fclose();`

### 方式 2 (系统调用)

![](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309182223327.png)

1. `int pipe(int pipefd[2]);`
    1. 数组作为参数 会退化为指针, 2 只是起提示作用
    2. 整数数组用于储存 父子进程通信的 fd
    3. 数组中 第 0 项 为 R 端, 第 1 项 为 W 端
    4. 管道为 半双工, but 一般 单工使用

2. 创建子线程: `fork()`

3. 父进程关闭一端, 子进程关闭另一端, 使其成为单工

### 性质 (同有名管道)

1. 读阻塞

2. 写阻塞

3. 写端关闭, 读端返回 0

4. 读端关闭, 写入引发 `SIGPIPE`, 异常终止

### 管道缺点

1. 当 n 个进程进行通信时, 需要建的管道量级为 n<sup>2</sup>
2. 管道存在 阻塞 问题

## 进程间通信_共享内存

1. 特点
    1. 最快的 IPC (InterProcess communication);  
    2. 打破了部分 内存隔离性, 让不同进程的虚拟页映射到同一物理页;  
    3. 不需拷贝;

2. 步骤
    1. 让 OS 分配 共享的物理内存  
        `int shmget(key_t key, size_t size, int shmflag);`

        1. 返回 共享内存 id
        2. key 用于不同进程  定位 同一页共享内存  
            key = 0 (IPC_PRIVATE) 表示为 私有共享内存, 适用于父子进程 (`shmget() / shmat() / fork() ...`)
        3. size 为虚拟内存大小, 取 页的整数倍, 即 **n \* 4096B**
        4. shmflag 为 `IPC_CREAT | 0600`, 表示 不存在则创建 且 用户自己可读可写

    2. 让共享的 物理内存 加载到 进程地址空间 (分配虚拟内存)  
        `void* shmat(int shmid, const char* shmaddr, int shmflag);`

        1. 返回 虚拟内存首地址
        2. shmaddr 为 NULL
        3. shmflag 为 0

    3. 进程访问分配的内存

    4. 释放虚拟内存  
        `int shmdt(const void* shmaddr);`

### 缺点

存在竞争条件(race condition), 即 两个并发的执行流访问共享资源时 寄存器数据 跟不上 内存变量  

```shell
#单核运行
taskset -c 0 ...
```

### 补充

```shell
## 查看已存在的共享内存
ipcs 

## 删除共享内存, 延迟删除, nattach 为 0 时真正删除
ipcrm -a            ## 全删 
ipcrm -m shmid
ipcrm -M key
```

## 进程间通信_信号

### 特点

1. 信号是 软件层面 的 事件机制
2. 事件分为 同步 / 异步
3. 硬件层面 的是 中断
4. 信号的目标 总是 进程

### 信号处理阶段

1. 产生信号
    1. 硬件产生, 异步: `ctrl + c` / `ctrl + \`
    2. 硬件产生, 同步: `除 0 错误`
    3. 软件产生, 异步: `kill`
    4. 软件产生, 同步: `abort()`  

2. 递送信号 (delivery)
    1. 中止: `Term`
    2. 忽略: `Ign`
    3. 中止并生成 Core 文件: `Core`
    4. 暂停: `Stop`
    5. 恢复: `Cont`

### 注册信号

即 修改信号的 默认递送行为

1. 函数 1.1 (可读性较差)  
    `void (*signal(int sig, void (*func)(int)))(int);`
    1. 返回值: 返回值为 void, 参数为 int 的 **函数指针**
    2. 参数1: 整数
    3. 参数2: 返回值为 void, 参数为 int 的 **函数指针**

2. 函数 1.2
    `typedef void (*sighandler_t)(int);`  
    `sighandler_t signal(int signum, sighandler_t handler);`
    1. handler 为用户自己定义的递送函数, 由 OS 调用, 是为回调函数
    2. handler 为 `SIG_DFL`, 即采用信号的 默认递送行为

3. 函数 2
    `int sigaction(int signum, const struct sigaction* act, struct sigaction* oldact);`  

    ```c++
    struct sigaction {
        void (*sa_handler)(int);
        void (*sa_sigaction)(int, siginfo_t*, void*);
        sigset_t sa_mask;
        int sa_flags;
        void (*sa_restorer)(void);
    } 
    ```

    1. act 为要设置的新属性; oldact 用来保存旧的属性, 不保存可填 NULL
    2. `struct sigaction` 结构
        1. `sa_handler / sa_sigaction` 为回调函数, 只能存在一个
        2. `sa_mask` 额外临时屏蔽
        3. `sa_flags`  属性
            1. `0` 使用回调函数 1
            2. `SA_SIGINFO` 使用回调函数 2 传递 info 信息
            3. `SA_RESTART` 自动重启低速设备
            4. `SA_RESETHAND` 生效一次
            5. `SA_NODEFER` 递送时不屏蔽本信号

### 信号递送的核心数据结构

1. mask 掩码, 表示 某个过程 是否屏蔽了 某个信号
2. pending 位图, 表示 是否存在未决信号
3. 信号传入, 首先看 mask 是否屏蔽了该信号  
    若没有屏蔽, 则直接递送;  
    若屏蔽了, 则 将其先 移入 pending; 当 mask 从 有-->空 时, 看 pending, 有则取出递送
    ![](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/Snipaste_2023-09-18_23-54-29.png)

## signal 性质

1. 一次注册, 永久生效
2. 在递送信号时, 会**临时**屏蔽**本信号**, 不会屏蔽其他信号  
    sigprocmask 加上后是永久屏蔽
3. 进程因为**低速系统调用**而阻塞, 信号传递完成后会**自动重启**  
    低速系统调用指 有可能陷入永久阻塞的系统调用, 如 `read()`

## sigaction 默认性质

1. 一次注册, 永久生效 --------------> `SA_RESETHAND`
2. 递送过程临时屏蔽不能信号 ---------> `SA_NODEFER`
3. **不会** 自动重启低速设备 -------> `SA_RESTART`

## 多线程创建子线程

## 多线程子线程的终止

## 多线程线程的取消

## 多线程资源清理

## 互斥

## 死锁

## 同步
