---
title: 通过fstream库与sstream库实现对复杂文件的读取操作
published: 2026-07-08
description: ''
image: ''
tags: [C++]
category: 'docs'
draft: false 
lang: ''
---
# fstream
## C++下fstream库的使用
**fstream库** 可以支持文件的读取与写入操作。

### ifstream

提供文件的打开操作(无法进行修改)。

#### 创建文件变量
```cpp
/* 创建一个文件变量 file 来指向该文件 */
std::ifstream file(filename);
    
/* 等价于 */

std::ifstream file("data/filename.txt")
```

#### 使用is_open()判断程序打开与否

使用 **is_open()** 来进行判断文件是否成功打开，成功返回 **bool值 true** 反之返回 **bool值 false**。

```cpp
if(!file.is_open())
{
    std::cerr<<"文件打开失败"<<std::endl;
    return {};
}
```

#### 使用getline()进行整行的读取
```cpp
getline(file, line);
/* 从文件变量file中读取一行字符串到 line 中直至换行时停止读入 */

getline(file, line, ',')
/* 从文件中读取字符串，直至遇到逗号 ',' 停止读入 */
```

### ofstream
创建仅用于写入的文件流。

#### 尝试写入数据
```cpp
std::ofstream file(filename);
if(file.is_open()){
    std::cout << "尝试写入数据" << std::endl;
}
```

#### 使用close()关闭打开的文件
```cpp
file.close()
/* 关闭打开的文件 */
```

### fstream
使用fstream可以创建既可读又可写的对象。

# sstream
## C++下sstream库的使用
**sstream库** 可以对字符串进行流式操作。
### istringstream
只能读取字符串中的数据(类似 ifstream)。
### ostringstream
只能向字符串写入数据(类似 ofstream)。
### stringstream
最常用，既可以读也可以写。
### 使用str()获取流中的数据
从文件中读取一行数据并尝试打印得到的数据。
```cpp
std::ifstream file(filename);
if(file.is_open()){
    std::string line;
    if(getline(file, line)){
        std::istringstream iss(line);
        std::cout << iss.str();
    }
    file.close();
}
```
### 使用clear()清空流
如果想要重复使用同一个流，需要对流进行清空，否则第二次调用会失效。  
于是上面代码可以写作：
```cpp
std::ifstream file(filename);
if(file.is_open()){
    std::string line;
    if(getline(file, line)){
        std::istringstream iss(line);
        std::cout << iss.str();
    
        /* new */
        iss.clear();
    
    }
    file.close();
}
```

### 尝试进行字符串与数字的的转换
将数字流入字符串中
```cpp
int num = 12345;
std::ostringstream str;
str << num;

```