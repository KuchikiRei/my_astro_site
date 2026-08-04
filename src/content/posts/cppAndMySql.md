---
title: 在 Ubuntu 下使用 C++ 实现 MySql 基础操作
published: 2026-08-04
description: ''
image: ''
tags: []
category: ''
draft: false 
lang: ''
---
# 在 Ubuntu 下使用 C++ 实现 MySql 基础操作
## 前置条件
### 安装 C++ MySeql 驱动
在 Ubuntu 终端中执行下列命令:
```bash
sudo apt updata
sudo apt install libmysqlcppconn-dev
```
> 包含头文件: `<mysql_drver.h>` `<mysql_connection.h>` 

## 第一次链接到数据库
```cpp
#include <mysql_driver.h>
#include <mysql_connection.h>

#include <iostream>

int main(){
    sql::mysql::MySQL_Driver* driver;

    driver = sql::mysql::get_mysql_driver_instance();

    sql::Connection* conn = driver->connect(
        "tcp://127.0.0.1:3306",
        "root",
        "password"
    );

    conn->setSchema("test");
     
    std::cout << "connect success";
}
```
## 语句解释
### 定义驱动对象
单例模式创建 MySql 操作入口:
> 单例模式: 整个程序运行期间, 只允许存在一个对象。
```cpp
sql::MySQL_Driver* driver;
```
### 获取 MySql 驱动
```cpp
get_mysql_driver_instance();
```
### 与数据库建立连接
指针访问指针对象成员:
```cpp
driver->connect()
```
其中所包含参数:
- `"tcp://127.0.0.1:3306"` 服务器地址, 3306 是数据库的默认端口号。
>  在 MySql 中执行 `SHOW GLOBAL VARIABLES LIKE 'port';` 以获取端口。
- `"root"` 用户名。 
- `"password"` 数据库密码。
> Ubuntu 下可以直接使用 `sudo mysql` 直接进入。
> 但是 C++ 不能直接链接, 因此需要创建一个专用的链接用户。执行下面的语句可以创建一个用户:
> ```sql 
> CREATE USER 'cpp_user'@'localhost' IDENTIFIED BY '123456';
> ```
> 上述语句用于创建一个名为 cpp_user , 密码为 123456 的用户。对新创建的用户进行授权:
> ```sql
> GRANT ALL PRIVILEGES ON test.* TO 'cpp_user'@'localhost';
> ```
> 允许 cpp_user 操作 test数据库。刷新:
> ```sql
> FLUSH PRIVILEGES;
> ```
> 此后在代码中可以使用上述创建账号进行创建。

完成此步骤后 C++ 已经与 MySql 成功建立 TCP 链接。

### 选择需要使用的数据库
```cpp
conn->setSchema("test");
```
等价于:
```sql
USE test;
```
之后所有的操作都将使用 test数据库。
## 执行基础操作
### 创建 SQL 执行对象
```cpp
sql::PreparedStatement* stmt;
```
表示一条准备执行的 SQL语句。
### 插入数据
创建插入模板:
> 需要插入 `<cppconn/prepared_statement.h>` 头文件
```cpp
stmt = conn -> prepareStatement("INSERT INTO users(username, password) VALUES(?, ?)");
```
使用 `?` 作为插入占位符, 防止恶意输入。
### 填入插入数据
对占位符进行填充:
```cpp
stmt -> setString(1, username);
stmt -> setString(2, password);
```
占位符起始从 1 开始。

### 提交语句到数据库
将模板中的内容添加进数据库:
```cpp
stmt -> execute();
```

## 完整的测试用例
链接至数据库 test，并尝试向库中 users 表添加一条数据:
```cpp
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/prepared_statement.h>

#include <string>

int main(){
    sql::mysql::MySQL_Driver* driver;

    driver = sql::mysql::get_mysql_driver_instance();

    sql::Connection* conn = driver->connect(
        "tcp://127.0.0.1:3306",
        "cpp_user",
        "123456"
    );

    conn->setSchema("test");

    sql::PreparedStatement* stmt;

    stmt = conn -> prepareStatement("INSERT INTO users(username, password) VALUES(?, ?)");

    std::string username = "LINKONG";
    std::string password = "123456";

    stmt->setString(1, username);
    stmt->setString(2, password);

    stmt->execute();

    delete stmt;
    delete conn;
}
```