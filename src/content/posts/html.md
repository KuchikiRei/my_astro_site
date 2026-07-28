---
title: HTML
published: 2026-07-19
description: ''
image: ''
tags: []
category: ''
draft: false 
lang: ''
---
# HTML 基础

## 第一个 HTML 文档

```html
<!doctype html>
<html lang="en-US">
  <head>
    <meta charset="utf-8" />
    <meta name="viewport" content="width=device-width" />
    <title>My first page</title>
  </head>
  <body>
    <img src="images/firefox-icon.png" alt="My test image" />
  </body>
</html>
```
- `<!doctype html>` 文档类型，用于保障文档正常读取。
- `<html></html>` 包含整个页面的所有内容， 通常包含 `lang` 属性，用于设置页面的主要语种。
- `<meta charset="utf-8">` 指定文档的编码格式。
- `<meta name="viewport" content="width=device-width">` 保证页面以当前设备页面宽度进行渲染，防止移动端浏览器以比当前设备页面宽度更宽的宽度渲染内容，导致内容缩小。
- `<title></title>` 设置页面的标题，显示在浏览器标签页上，同时作为收藏网页的描述文字。
- `<body></body>` 包含用户在访问页面时看到的全部内容。

## 嵌入图像

使用 `img` 元素插入图像。
```html
<img src="" alt="My test image" />
```
通过 `src` 属性将图片插入页面，包含待嵌入的图片文件路径。

同时包括一个 `alt` 属性，用于描述图像内容，用于图像无法被用户看见时的显示。

## 标题

标题元素用于指定内用的标题或者子标题，HTML包括六个级别的标题， 从`<h1>`到`<h6>`，通常最多使用到3-4级标题。
```html
<!-- 四个级别标题 -->
<h1>主标题</h1>
<h2>顶层标题</h2>
<h3>子标题</h3>
<h4>次子标题</h4>
```
> **提示：** 在HTML中，`<!--` 和 `-->` 中的任何内容都是 **HTML注释**， 注释内容不可见。

## 段落

使用 `<p>` 元素来指定段落，用于指定常规的文本内容。
```html
<p>这是一个段落</p>
```

## 列表
web 上有大量内容属于列表形式，HTML 为此提供了专用元素。列表标记至少包含两个元素，通常包含两种类型，有序列表和无序列表。

  1. **有序列表** 中项目的顺序并不重要，用`<ul>`元素包裹。
  2. **无序列表** 中项目的顺序并不重要，用`<ol>`元素包裹。

列表中的每个项目用一个列表项目元素 `<li>` 包裹。

## 链接
使用 `<a>` 元素将文本添加到链接中，步骤如下：

  1. 选取文本。
  2. 将文本包装在 `<a>` 元素内，像这样：
  ```html
  <a>这是一段添加了链接文字</a>
  ``` 
  3. 为 `<a>` 元素添加一个 `href` 属性，像这样：
  ```html
  <a href="">这是一段添加了连接的文字</a>
  ```
  4. 将属性值设置为具体的网址：
  ```html
  <a href="https://www.linkong.online/posts/html/">
  ```

## 属性
一个属性应该具有：

### 布尔属性
