---
title: Linux下通过C++调用POSIX线程库实现经典多线程问题
published: 2026-06-17
description: ''
image: ''
tags: [OS]
category: 'OS'
draft: false 
lang: ''
---

### [生产者消费者问题](https://zh.wikipedia.org/wiki/%E7%94%9F%E4%BA%A7%E8%80%85%E6%B6%88%E8%B4%B9%E8%80%85%E9%97%AE%E9%A2%98)

本质是为了解决多个线程在信号量机制的协调下，实现有序协作，确保在单一时刻内只有一个线程能够访问修改缓冲区内的数据。

### [信号量机制](https://zh.wikipedia.org/wiki/%E4%BF%A1%E5%8F%B7%E9%87%8F)

在计算机中使用原子级操作，实现对计算机资源的计数。
> 原子级操作：在计算机的控制下，将内存地址中的数据值进行增加或删除，同时将该步骤封装成为一个完整的步骤，不可被打断，此区间内任何其余操作都将被屏蔽
#### 信号量机制下的核心操作
**Somephore**: 申请计数器，设置计数器的大小。

**P**: 申请操作，申请一个资源，并将资源数量 **-1**，如果此时资源数量为 **0**, 那么暂时阻塞该线程。

**V**: 释放操作, 释放一个资源，并将资源数量 **+1**，并唤醒因为资源不足而被P操作阻塞的线程。

#### Linux下的POSIX信号量库

相关对应操作:  
Somephore: sem_t  
P: sem_wait();  
V: sem_post();

### 生产者消费者问题的详细解决
#

* 通过定义当前剩余空位置以及已有位置来定义缓冲区，节约系统资源，无需消耗过多资源来进行资源的判断。
```cpp
sem_t full, empty;
```
* 定义互斥锁，确保在一个时刻只有一个线程可以进行操作。
```cpp
sem_t mutex;
```

在线程执行的过程中，首先需要查看是否拥有足够的相对应的资源，然后申请互斥锁，如果申请成功，那么进行函数段的运行；运行结束后，在进行互斥锁的释放，同时释放生产出来的资源。如此循环直至，因为**P**操作申请不到足够的资源而阻塞。
* 定义生产者函数，申请空闲位置，申请成功后申请互斥锁，在申请到互斥锁后进行函数段内的操作；函数段内的操作完成后释放互斥锁，同时释放生产出的代码。
```cpp
void productor(){
    sem_wait(&empty); //只要有空位置就进行申请
    sem_wait(&mutex); //申请互斥锁

    /*
        执行的程序段
    */

    sem_post(&mutex); //释放互斥锁
    sem_post(&full);  //释放生产出来的资源
}
```
* 定义消费者函数，申请已有位置，申请成功后申请互斥锁，在申请到互斥锁后进行函数段内的操作；函数段内的操作完成后释放互斥锁，同时释放消耗后的位置。
```cpp
void consumer(){
    sem_wait(&full); //只要有产品就进行申请
    sem_wait(&mutex); //申请互斥锁

    /*
        执行的程序段
    */

    sem_post(&mutex); //释放互斥锁
    sem_post(&full);  //释放消耗后的位置
}
```
#

### 初始化
使用`sem_init`初始化未命名信号量。  
**参考格式**:`sem_init(sem_t *sem, int pshared, unsigned int value)`  
**sem**: 申请的信号量;  
**pshared**: 控制信号量的范围,(**0**代表线程间共享，**非0**代表进程间共享)。  
**value**: 信号量的初始值。  
在**main**函数中对缓冲区以及互斥锁进行初始化:
```cpp
sem_init(&mutex, 0, 1); //初始化互斥锁
sem_init(&full, 0, 0);  //初始化已有产品
sem_init(&empty, 0, N); //初始化空位置的值为N
```

### 将代码段封装成为单个线程

添加头文件库`phread.h`。

#### 创建线程
使用`pshared_t`创建线程。
```cpp
pshared_t p, c; //使用pshared_t作变量类型，创建两个线程p,c
```

##### 对已有代码段进行封装
对原有代码段进行更改：
```cpp
void *productor(void *arg){
    while(true){
        sem_wait(&empty);
        sem_wait(&mutex);

        /*
            执行的程序段
        */

        sem_post(&mutex);
        sem_post(&full);
    }
}
```
较原有代码更改后对函数类型进行了更改，重定义为`void*`，同时允许接收一个参数`arg`，代表需要使用该程序段的线程，允许函数的复用。  
在`main`中使用'pshared_create()'对代码段进行封装。  
**参考格式**:
```cpp
pthread_create(pthread_t *thread, const pthread_attr_t *attr, void*(*start_routine)(void*), void *arg),
```
**thread**: 线程名称。  
**attr**: 线程属性，通常使用`NULL`传递默认参数。
**start_routine**: 接收封装完成的线程函数，该函数类型必须为`void*`。  
**arg**: 传递给线程的参数，无则填`NULL`。
```cpp
pthread_creat(p, NULL, productor, NULL);
```
完成对**生产者**函数的封装，同理完成对消费者函数的封装。
```cpp
void *consumer(void *arg){
    while(true){
        sem_wait(&full);
        sem_wait(&mutex);

        /*
            执行的程序段
        */

        sem_post(&mutex);
        sem_post(&empty);
    }
}
```
在main中封装:
```cpp
pthread(c, NULL, consumer, NULL);
```

为保证程序健壮性，设置监管程序:
`pthread_join()`，用于在线程结束时回收资源。  
**参考格式**:`pthread_join(pthread_t thread, void **retval)`。  
**retval**：用于接收可能存在的`void *`类型的返回值(没有就是`NULL`)。
```cpp
pthread_join(c, NULL);
pthread_join(p, NULL);
```

### 参考实例
附完整的伪代码:
```cpp
#include <thread.h>
#include <semaphore.h>

#define N 5

sem_t mutex, full, empty;

void *productor(void *arg){
    while(true){
        sem_wait(&empty);
        sem_wait(&mutex);

        //执行的代码段

        sem_post(&mutex);
        sem_post(&full);
    }
}

void *consumer(void *arg){
    while(true){
        sem_wait(&full);
        sem_wait(&mutex);

        //执行的代码段

        sem_post(&mutex);
        sem_post(&empty);
    }
}

int main(){
    sem_init(&mutex, 0, 1);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, N);

    pthread_t p, c;
    pthread_create(p, NULL, productor, NULL);
    pthread_create(c, NULL, consumor, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);
}