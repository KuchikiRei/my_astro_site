---
title: C++下fstream库的使用
published: 2026-07-08
description: ''
image: ''
tags: [C++]
category: 'docs'
draft: false 
lang: ''
---

# C++下iostream库的使用
**fstream库** 可以支持文件的打开操作。其内容包含两个子库 **ifstream库** 与 **ofstream库**。

## ifstream

提供文件的打开操作(无法进行修改)。

### 创建文件变量
```cpp
/* 创建一个文件变量 file 来指向该文件 */
std::ifstream file(filename);
    
/* 等价于 */

std::ifstream file("data/filename.txt")
```

### 使用is_open()判断程序打开与否

使用 **is_open()** 来进行判断文件是否成功打开，成功返回 **bool值 true** 反之返回 **bool值 false**。

```cpp
if(!file.is_open())
{
    std::cerr<<"文件打开失败"<<std::endl;
    return {};
}
```

### 使用getline()进行整行的读取
```cpp
getline(file, line);
/* 从文件变量file中读取一行字符串到 line 中直至换行时停止读入 */

getline(file, line, ',')
/* 从文件中读取字符串，直至遇到逗号 ',' 停止读入 */
```

## ofstream
创建仅用于写入的文件流

### 尝试写入数据
```cpp
std::ofstream file(filename);
if(file.is_open()){
    std::cout << "尝试写入数据" << std::endl;
}
```

### 使用close()关闭打开的文件
```cpp
file.close()
/* 关闭打开的文件 */
```