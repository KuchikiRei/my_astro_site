---
title: 一些算法知识点
published: 2026-06-21
description: ''
image: ''
tags: [algorithm]
category: 'C/C++'
draft: false 
lang: ''
---

### 常见算法

- [快速排序](https://zh.wikipedia.org/wiki/%E5%BF%AB%E9%80%9F%E6%8E%92%E5%BA%8F)
- [深度优先搜索(DFS)](https://zh.wikipedia.org/wiki/%E6%B7%B1%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2)
- [广度优先搜索(BFS)](https://zh.wikipedia.org/wiki/%E5%B9%BF%E5%BA%A6%E4%BC%98%E5%85%88%E6%90%9C%E7%B4%A2)
- [霍夫曼树(哈夫曼树)](https://zh.wikipedia.org/wiki/%E9%9C%8D%E5%A4%AB%E6%9B%BC%E7%BC%96%E7%A0%81)
- [Dijkstra(最短路径)](https://zh.wikipedia.org/wiki/%E6%88%B4%E5%85%8B%E6%96%AF%E7%89%B9%E6%8B%89%E7%AE%97%E6%B3%95)

### 快速排序
**实现原理:** 采用分治法，设置基准元素，并将原有数组划分为两个部分，一部分为小于基准元素的值，另一部分为大于基准元素的值，通过此操作将基准元素归位，随后对两个子数组递归进行相同操作，直至数组有序。

**特点:** **不稳定** 的，平均时间复杂度$`O(n logn)`$，最坏时间复杂度$`O(n^2)`$，空间复杂度$`O(logn)`$。

```cpp
/*
    对数组进行划分操作
*/
int partition(std::vector<int>& arr, int left, int right){
    int i = left, j = right;    // 左右两侧循环进行扫描
    while(i < j){               // 条件判断
        /*
            此处设置左侧第一个元素为基准元素
        */
        while(i < j && arr[i] <= arr[left])
            i++;                // 逐渐缩减范围
        while(i < j && arr[left] <= arr[j])
            j--;
        /*
            当左右两侧指针越界或者找到位置不合适的元素时，进行元素的交换
        */
        swap(arr[i], arr[j]);
    }
    swap(arr[i], arr[low])      // 将原来的基准元素放置到合适位置
    return i;                   // 返回更新后的两个数组的界限下标
}

/*
    递归操作
*/
void quick_sort(vector<int>& arr, int left, int right){
    if(left >= right) return;                   // 触底反弹
    int privot = partition(arr, left, right);   // 获取分割后的基准值
    
    quick_sort(arr, left, privot - 1);          // 对左数组进行分割
    quick_sort(arr, privot + 1, right);         // 对右数组进行分割
}
```

### 深度优先搜索
**实现原理:** 是一种基于递归的图遍历算法，通过邻接表获取节点的相邻信息，并标记已经访问的节点，确保每个节点都被遍历。  
**时间复杂度:** $O(V+E)$，只需要遍历每个节点和每条边一次便可。
```cpp
void dfs(int u, vector<vector<int>>& adj, vector<bool>& visited){
    visited[u] = true;

    for(int v: adj<u>)
        if(!visited[v]) dfs(v, adj, visited);
}
```

### 广度优先搜索
**实现原理:** 利用队列的**FIFO**特性，确保元素的逐个访问，并标记已经访问的元素，循环遍历，直至所有元素都被标记。  
**时间复杂度:** $O(V+E)$;  
**空间复杂度:** $O(V)$;
```cpp
void bfs(int start, vector<vector<int>>& adj, int numNodes){
    queue<int> q;
    vector<bool> visited(numNodes, false);

    q.push(start);
    visited[start] = true;

    while(!q.empty()){
        int u = q.front;
        q.pop();

        for(int v: adj[u]){
            if(!visited[v]){
                visited[v] = true;
                q.push(v);
            }
        }
    }
}
```

### 霍夫曼树
**构造过程:** 每次从待选取队列中选取两个值最小的元素，遵循左小右大原则，进行组合生成新的元素，并添加到原有队列中，循环此步骤，直至构成一棵树。