---
title: GSR 项目实现
published: 2026-07-08
description: ''
image: ''
tags: 
    - Ai
    - Graph Learning
    - GSR
category: 'Ai'
draft: false 
lang: ''
---

# 图学习 GSR 实验

## 1. 项目介绍

---

## 2. 数据集

获取项目数据集

### 2.1 IMDb
从小数据集 **[IMDb Non-Commercial Datasets | IMDb Developer](https://developer.imdb.com/non-commercial-datasets/)** 开始，
获取数据集信息。
![IMDb](images/GSR/IMDb.png)
对下载的数据集进行简单的解释:  
**title.akas.tsv.gz:** 存储电影在不同国家和语言下的别名(本项目不使用该文件)。  
**title.basics.tsv.gz:** 提供电影（Title）的基础信息。  
**title.crew.tsv.gz:** 提供电影的导演（Director）和编剧（Writer）信息。    
**title.episode.tsv.gz:** 提供电视剧（TV Series）与剧集（Episode）之间的对应关系。   
**title.principals.tsv.gz:** 提供电视剧（TV Series）与剧集（Episode）之间的关系信息。  
**title.ratings.tsv.gz:** 提供电影的 IMDb 用户评分信息。  
**name.basics.tsv.gz:** 提供人物（演员、导演、编剧等）的基础信息  
 

### 2.2 MovieLens
下载另一个数据集[MovieLens | GroupLens](https://grouplens.org/datasets/movielens/)，在这里由于设备硬件限制，我们选择最小的数据集(具有约约 9,000 部电影的共 10 万条用户评分记录)。
![MovieLens](images/GSR/MovieLens.png)
对下载后解压的数据集进行简单的解释:  
**links.csv:** 提供 MovieLens 与 IMDb 电影 ID 的映射关系，用于关联电影信息和用户评分数据。  
**movies.csv:** 提供通过`links.csv`才能找到对应的 **IMDb编号** ，以及电影标题，电影年号，电影类别。  
**ratings.csv:** 存储用户对电影的评分记录，包括评分用户、评分电影、评分分数以及评分时间。  
**tags.csv:** 存储用户对电影添加的自定义标签，用于描述电影的特点或个人印象。

---