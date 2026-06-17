---
title: C++ nlohmann/json的基本操作
published: 2026-06-06
description: ''
image: ''
tags: [C++]
category: 'docs'
draft: false
lang: ''
---
**nlohmann/json库提供了一种格式用于存储，支持多种类型的格式存储读取**

### 解释了几种基础操作

* json文件的声明
* json数组中元素的插入和读取
* json对象的键值映射
* C++类与json类的相互转化

> github地址：https://github.com/nlohmann/json

**json文件的声明：**

`j = nlohmann::json();`

nlohmann::json几乎支持C++中所有类型


**创建测试变量：**

```c++
std::string a = "hello world";
int b = 10;
float c = 1.1;
```

**在声明时进行插入:**
```c++
j = nlohmann::json{
    {"a", a},
    {"b", b},
    {"c", c}
};
```
或者:
```c++
j = nlohmann::json();
j["a"] = a;
j["b"] = b;
j["c"] = c;
```

**从json变量中读取数据**
```c++
j.at("a").get_to(a);
j.at("b").get_to(b);
j.at("c").get_to(c);
```

**创建一个json数组**
声明
`nlohmann::json j = nlohmann::json::array();`
**插入操作：**
```c++
j.push_back(a);
j.push_back(b);
j.push_back(c);
显示长度：
j.size();
```

**在C++类中的自动调用**
```c++
class test{
private:
    std::string a;
    int b;
public:
    test(){
        std::cin >> a >> b;
    }
    ~test();
    
    //使用friend实现外部调用,实现自动转化
    friend void to_json(nlohmann::json & j, const test & t){
        j = nlohmann::json{
            {"a", t.a},
            {"b", t.b}
        };
    }

    friend void from_json(const nlohmann::json & j, test & t){
        j.at("a").get_to(t.a);
        j.at("b").get_to(t.b);
    }
};
```

**json对象的键值映射**
```c++
//创建一个json对象/

j = nlohmann::json::object();

//新建键对数组
const std::string arr[2] = {"a", "b"};
```
可以用于区分插入的数据,内部数据可以采用数组遍历的方式进行循环读取

