---
title: 多进程通讯下的生产者消费者问题
published: 2026-06-18
description: ''
image: ''
tags: [OS]
category: 'OS'
draft: false 
lang: ''
---

### 概述
在本文章中，我们将继续使用**信号量机制**来进行多线程中的生产者消费者问题。
核心思想与线程间的通讯完全一样，但是进程间是没有办法访问同一个程序下的资源的，我们需要对地址进行操作，因此我们可以得到本文较上一篇文章多了如下部分: **进程的创建，共享内存的申请，如何在内存中申请可供不同进程访问的信号量**。

### 修改原有信号量机制
值得高兴的是修改原有信号量机制时，无需修改头文件库，下文中用到的`sem_t`，以及即将用到的`sem_open`均在`semaphore.h`库下。  
将原有的信号量变量转化为信号量指针:  
从:
> `sem_t mutex, full, empty`

转化为:
> `sem_t* mutex;`  
> `sem_t* full;`  
> `sem_t* empty;`

使用`sem_open`创建并初始化信号量，参考格式:  
`sem_t * sem_open(const char *name, int oflag, mode_t mode, unsigned int value);`
**name**: 信号量名称必须以 **/** 开头，且后面不能出现任何其余 **/**。  
**oflag**: 操作标志，提供参数:**O_CREAT**与 **O_CREAT | O_EXCL** (在`fcntl.h`库下),前者代表没有就进行创建，后者代表若已经存在，则退出程序，并报错，确保在系统中只有一个独特的信号量。O_EXIT
**mode**: 权限掩码，提供一个4位int类型数字，例如**0600**;
> 第一位:特殊权限， **0** 代表无特殊权限;  
> 第二位:文件所有者;  
> 第三位:同组用户;  
> 第四位:其它用户;  
> 核心权限: **1** 执行权限，**2** 写权限， **4** 读权限。   

**value**: 初始值的大小;

#### 进行初始化
'''cpp
    mutex = sem_open("/sem_mutex", O_CREAT, 0600, 1);
    full = sem_open("/sem_full", O_CREAT, 0600, 0);
    empty = sem_open("/sem_empty", O_CREAT, 0600, N);
'''

### 申请公共内存
具体操作:  
1. 申请标识符,通过调用`sys/mman.h`库下的`shm_open`进行初始化。  
参考格式: `int name = shm_open(const char *name, int oflag, mode_t mode)`,  
**name**: 共享内存在本地目录下存储的名称，必须以 **/** 开头，且不能有任何其余 **/**。   
**oflag**: 打开方式，**O_CREAT**:不存在则创建;**O_RDWR**:可读写;**O_RDONLY**:只读;**O_EXCL**:与O_CREAT同时使用时，如果检测到同名地址空间，则退出程序。  
**mode**: 权限掩码。  
2. 分配地址空间,通过调用`unistd.h`库下的`ftruncate`进行空间的申请。  
参考格式: `fturncate(int fd, off_t length)`,  
**fd**: 打开的文件描述符。  
**length**: 待申请的内存地址空间。
3. 内存地址的映射,通过调用`sys/mman.h库下的`mmap`等函数来进行映射操作。  
参考格式: `void *mmap(void *addr, size_t length, int prot, int flags, int fd, off_t offset);`
**addr**： 设定起始内存地址，通常设置为NULL，让内核自动分配。  
**length**: 映射地址长度。  
**prot**: 映射区域的权限，在`sys/mman.h`库下提供四种权限: **PROT_NONE**不可访问; **PROT_READ**可读; **PROT_WRITE**可写; **PORT_EXEC**可执行。  
**flags**: 控制映射类型，在`sys/mman.h`库下提供三种类型: **MAP_SHARED**:所有映射该文件的进程共享内存空间; **MAP_PRIVATE**:私有映射，是MAP_SHARED的逆操作;**MAP_ANONYMOUS**:匿名共享，用于为进程间共享的大块堆内存。  
**fd**: 文件描述符。  
**offset**: 文件偏移量，通常设置为**0**。

参考代码：
```cpp
#include <sys/mman.h>
#include <unistd.h>

int main(){
    int fd = shm_open("/shm_data", O_CREAT | O_RDWR, 0600);
    ftruncate(fd, sizeof(ShareData));
    ShareData* data = (ShareData*)mmap(NULL, sieof(ShareData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    data -> item = 0; // 并对映射的内存空间中的元素进行初始化
}
```

### 创建进程
使用`unistd.h`库下的`fork()`函数创建进程, 并利用PID来判断进程执行的代码段:
```cpp
    pid_t pid_productor = fork();
    if(pid_productor == 0){
        // 生产者对应的代码段
        exit(0);
    }else{
        pid_t pid_consumor = fork();
        if(pid_consumor == 0){
            // 消费者对应的代码段
            exit(0)
        }else{
            // 回收进程资源
        }
    }
```

#### 系统资源的回收
在父进程结束后，两个子进程并不会跟随结束，而是会继续进行，持续运行会造成系统资源的浪费，同时再次执行时，会导致原有公有内存和信号量的报错，因此我们需要进行系统资源的回收。
1. 进程的回收:
```cpp
    /*
        在本文中我们创建了两个进程，因此需要等待两个进程的结束
    */
    wait(NULL);
    wait(NULL);
```

2. 申请空间的回收:  
使用`semaphore.h`库下的`sem_unlink()`函数回收申请的信号量。 
```cpp
    sem_unlink("/sem_mutex");
    sem_unlink("/sem_full");
    sem_unlink("/sem_empty");
``` 
使用`sys/mman.h`库下的`shm_unlink()`函数回收申请的公共内存。
```cpp
    shm_unlink("/sem_data");
```
至此我们说完了所有有关的信息，下面是一个完整的演示示例。  
```cpp
#include <iostream>
#include <unistd.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

const int N = 5;

struct ShareData{
    int item;
};


sem_t *mutex;
sem_t *full;
sem_t *empty;

void productor(ShareData *data, sem_t *mutex, sem_t *full, sem_t *empty){
    while(true){
        sem_wait(empty);
        sem_wait(mutex);

        std::cout << data -> item++ << std::endl;

        sem_post(mutex);
        sem_post(full);
    }
}

void consumor(ShareData *data, sem_t *mutex, sem_t *full, sem_t *empty){
    while(true){
        sem_wait(full);
        sem_wait(mutex);

        std::cout << data -> item-- << std::endl;

        sem_post(mutex);
        sem_post(empty);
    }
}

int main(){

    mutex = sem_open("/sem_mutex", O_CREAT, 0600, 1);
    full = sem_open("/sem_full", O_CREAT, 0600, 0);
    empty = sem_open("/sem_empty", O_CREAT, 0600, N);

    int fd = shm_open("/shm_data", O_CREAT | O_RDWR, 0600);
    ftruncate(fd, sizeof(ShareData));
    ShareData* data = (ShareData*)mmap(NULL, sizeof(ShareData), PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    data -> item = 0;

    pid_t pid_productor = fork();
    if(pid_productor == 0){
        productor(data, mutex, full, empty);
        exit(0);
    }else{
        pid_t pid_consumor = fork();
        if(pid_consumor == 0){
            consumor(data, mutex, full, empty);
            exit(0)
        }else{
            wait(NULL);
            wait(NULL);
        }
    }

    sem_unlink("/sem_mutex");
    sem_unlink("/sem_full");
    sem_unlink("/sem_empty");

    shm_unlink("/sem_data");
}
```