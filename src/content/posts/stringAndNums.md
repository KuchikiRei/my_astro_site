---
title: 字符串与数字的转化
published: 2026-07-09
description: ''
image: ''
tags: [C++]
category: 'docs'
draft: false 
lang: ''
---

# 将字符串转化为指定类型的数字
- string  $ \rightarrow $ int 
    - ```cpp
        std::string s = "123";
        int i;

        /* std to int */
        i = stoi(string);
        ```

- string  $ \rightarrow $ long 
    - ```cpp
        std::string s = "123";
        long i;

        /* std to long */
        i = stol(string);
        ```
- string  $ \rightarrow $  long long
    - ```cpp
        std::string s = "123";
        long long i;

        /* std to long long */
        i = stoll(string);
        ```
- string  $ \rightarrow $ float
    - ```cpp
        std::string s = "123.4";
        float i;

        /* std to float */
        i = stof(string);
        ```
- string  $ \rightarrow $ double
    - ```cpp
        std::string s = "123.4";
        double i;

        /* std to double */
        i = stod(string);
        ```
- string  $ \rightarrow $ long double
    - ```cpp
        std::string s = "123.4";
        long double i;

        /* std to long double */
        i = stold(string);
        ```
# 数字转换为字符串
- 数字 $ \rightarrow $ string
    - ```cpp
        int i = 100;
        std::string s = std::to_string(i);
        ```