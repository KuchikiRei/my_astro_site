---
title: C++实现银行家算法
published: 2026-06-19
description: ''
image: ''
tags: [OS]
category: 'OS'
draft: false 
lang: ''
---

### 出现背景
用来**避免**操作系统在资源调度中出现的**死锁**问题。并由此诞生的安全性检测，用来进行模拟资源分配。在资源分配给进程之前，判断当前系统是否可以找到满足条件的安全队列。
> 死锁: 请求资源的进程的不到必要的资源，并且自身占有其它进程所请求的资源，却不释放所导致的系统资源卡死。


### 属性分析
每个进程拥有: **Max, Allocation**属性，前者代表进程申请的每种资源的最大值，后者代表进程当前已经占有的各种资源数量。多个进程**Max**属性会构成二维**Max**矩阵，多个进程**Allocation**属性会构成二维**Allocation**矩阵。  
计算机拥有: **Availbale**，用于记录当前计算机中每种资源所拥有的数量。

### 安全性检查
实现逻辑:
1. 由Max矩阵与Allocation矩阵相减，得到进程当前剩余需求的二维**Need**矩阵。  
2. 创建**Available**的副本**work**用于模拟资源调度。
3. 将当前所有进程的状态信息标记为**false**并记录在一维**finish**矩阵中，等待调用。
4. 在二维**Need**矩阵中循环查找满足条件`work[i] >= Need[~][i]`的进程，分配并回收资源至**work**矩阵中，将该进程记录进满足的输出队列**safeSequence**中，同时将该进程的状态信息标记为**true**修改对应的**finish**矩阵中。
5. 循环 **步骤4** 直至全部进程状态被标记为**true**或者找不到符合的目标进程时，退出程序，并根据程序进行判断。

### 参考代码
```cpp
#include <iostream>
#include <vector>

using namespace std;

const int MAX_PROCESS = 5;
const int MAX_RESOURCE = 3;

void need(vector<vector<int>> &Max, vector<vector<int>> &Allocation,
          vector<vector<int>> &Need) {
  for (int i = 0; i < MAX_PROCESS; i++) {
    for (int j = 0; j < MAX_RESOURCE; j++) {
      Need[i][j] = Max[i][j] - Allocation[i][j];
    }
  }
}

bool isSafe(vector<int> &Available, vector<vector<int>> &Allocation,
            vector<vector<int>> &Need, vector<int> &safeSequence) {
  int n = Allocation.size();
  int m = Available.size();

  vector<bool> finish(n, false);
  vector<int> work = Available;
  safeSequence.clear();

  int count = 0;
  while (count < n) {
    bool found = false;
    for (int i = 0; i < n; i++) 
      if (!finish[i]) {
        bool canAllocate = true;
        for (int j = 0; j < m; j++) {
          if (work[j] < Need[i][j]) {
            canAllocate = false;
            break;
          }
        }

        if (canAllocate) {
          for (int j = 0; j < m; j++) {
            work[j] += Allocation[i][j];
          }
          finish[i] = true;
          count++;
          found = true;
          safeSequence.push_back(i);
        }
      }
      if (!found) return false;
    }
  return true;
}

int main() {
  vector<int> Available = {3, 3, 2};
  vector<vector<int>> Max = {
      {7, 5, 3}, {3, 2, 2}, {9, 0, 2}, {2, 2, 2}, {4, 3, 3}};
  vector<vector<int>> Allocation = {
      {0, 1, 0}, {2, 0, 0}, {3, 0, 2}, {2, 1, 1}, {0, 0, 2}};

  vector<vector<int>> Need(MAX_PROCESS, vector<int>(MAX_RESOURCE));
  need(Max, Allocation, Need);

  vector<int> safeSequence;
  if (isSafe(Available, Allocation, Need, safeSequence)) {
    cout << "safe:";
    for (int i = 0; i < safeSequence.size(); i++)
      cout << safeSequence[i] << ' ';
    cout << endl;
  } else {
    cout << "note safe" << endl;
  }
}

```