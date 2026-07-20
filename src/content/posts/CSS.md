---
title: CSS
published: 2026-07-19
description: ''
image: ''
tags: []
category: ''
draft: false 
lang: ''
---
# CSS 基础

## 什么是CSS
css (层叠样式表)是为web内容添加样式代码。用于选择性地为 HTML 元素添加样式。

来对页面添加一个最简单的样式，下列地 CSS 代码选择了所有的段落文本，并将它们设置为红色。
```css
p {
    color: red;
}
```
创建一个文件夹，并将其命名为 `styles`， 在 `styles` 文件夹中将文件保存为 `styles.css`。

1. 选择一个 HTML 文件，在文档头部(`<head>`和`</head>`之间)添加如下代码。
    ```html
    <link href="你的文件路径(类似styles/style.css)" rel="stylesheet" />
    ```
2. 保存 HTML 文件，并用浏览器打开，查看其对应效果。

### CSS 规则集的解释
```css
p {
    color: red;
}
```
整个结构称为**规则集**，下面是各部分的名称：  

选择器：HTML 元素名位于规则集的开头。它定义了需要添加样式的元素(在上文中是`<p>`元素)。要给不同的元素添加样式，只需要更改选择器。  

声明：一条单独的规则(如`color: red;`)，用来指定为元素的哪个**属性**添加样式。

属性：为 HTML 元素添加样式的方式(上文中`color`就是`<p>`元素的属性)。在 CSS 中，可以选择要在规则中影响的属性。

属性值：位于属性的右侧，冒号后面就是**属性值**。从指定属性的可选值中选择一个值(例如除`red`外还有很多属性值可以用于`color`)。

## 字体和文本
让我们尝试在网页中添加更多的规则和信息，从而丰富我们的网页。
1. 尝试添加Google Fonts，在你的网站文档头部(`<head>`和`</head>`之间的任意位置)添加 `<link>` 元素。代码如下：
    ```html
    <link
    href="https://fonts.googleapis.com/css?family=Open+Sans"
    rel="stylesheet" />
    ```
    这段代码将你的页面链接到一个样式表，该样式表将 Open Sans 字体家族与你的网页一起加载。

2. 接下来我们将重置`style.css`中的内容。
3. 添加下列的几行代码
    ```css
    html {
        font-size: 10px; /* px 表示“像素（pixel）”: 基础字号为 10 像素 */
    font-family:
        "Noto Sans", sans-serif; /* 这应该是你从 Google Fonts 得到的其余输出。 */
    }
    ```
4. 接下来为 HTML 主体内的元素设置字号，同时将标题居中显示，然后扩充下方的规则集为正文设置行高和字间距，从而提高页面可读性。
    ```css
    h1 {
        font-size: 60px;
        text-align: center;
    }

    p,
    li {
        font-size: 16px;
        line-height: 2;
        letter-spacing: 1px;
    }
    ```

## 盒子模型
编写 CSS 的时候可以将大部分 HTML 元素看作若干堆叠的盒子。CSS 布局主要是基于盒子模型，每个在页面上占用空间的盒子都有类似的属性。
- `padding` (内边距) : 指内容周围空间。
- `broder` (边框) : 紧接着内边距的实线。
- `margin` (外边距) : 围绕元素边框外侧的空间。

### 更改页面颜色
```css
html {
  background-color: #00539f;
}
```
### 文档体样式
```css
body {
  width: 600px;
  margin: 0 auto;
  background-color: #ff9500;
  padding: 0 20px 20px 20px;
  border: 5px solid black;
}
```
在上文中我们在 `<body>` 中进行了元素的声明，我们来进行一下解释：
- `width: 600px;` 强制文档体永远保持 600 像素宽。
- `margin: 0 auto;` 当你在 `margin` 或 `padding` 这样的属性上设置两个值时，第一个值影响元素的上下方向(在这个例子中设置为 0)；第二个值影响左右方向。(这里，auto 是一个特殊的值，它将可用的水平空间平均分配给左边和右边)。你也可以使用一个，两个，三个或四个值。
- `background-color: #FF9500;` 如前文所述，指定元素的背景颜色。我们给 body 用了一种略微偏红的橘色以与深蓝色的 `<html>` 元素形成反差
- `padding: 0 20px 20px 20px;` 我们给内边距设置了四个值，目的是给内容四周留出一点空间。这一次我们不设置 body 上方的内边距，设置右边、下方、左边的内边距为 20 像素。值以上、右、下、左的顺序排列。与 margin 一样，你也可以使用一个，两个，三个或四个值。
- `border: 5px solid black;` 这是为边框的宽度、样式和颜色设置的值。在本例中，是 body 四周的一个 5 像素宽的纯黑色边框。
### 定位页面主标题并添加样式
```css
h1 {
  margin: 0;
  padding: 20px 0;
  color: #00539f;
  text-shadow: 3px 3px 1px black;
}
```
浏览器会对 h1 元素 (以及其他元素) 应用默认样式，可能会出现诸如正文顶部的难看间隙。这并不美观，因此我们可以对其设置`margin: 0;`覆盖浏览器的默认样式。

接下来我们将标题的上下内边距设置为 20 像素。

之后，我们将标题文本的背景颜色设置为和 HTML 的背景颜色一样的颜色。

最后，`text-shadow` 对元素的文本内容施加阴影。四个值分别为：
- 第一个像素值设置阴影与文本的**水平偏移量**: 右侧正值阴影水平方向移动的距离。
- 第二个像素值设置阴影与文本的**垂直偏移量**: 下方正值阴影水平方向移动的距离。
- 第三个值设置阴影的**模糊半径**。值越大产生的阴影越模糊。
- 第四个值设置阴影的基色。
### 图像居中
```css
img {
  display: block;
  margin: 0 auto;
}
```
最后，我们将图像居中使其让页面更加美观。可以服用 body 的 `margin: 0 auto`, 但是有一些差异，需要额外的设置来使 CSS 发挥作用。

`<body>` 元素是块级元素，因此会占据页面上的空间。页面上的其余元素会尊重为块级元素设置的边距。而图片是行级元素，所以为了使图像有外边距，我们必须使用 `display: block` 给予其块级行为。