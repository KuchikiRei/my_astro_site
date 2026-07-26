---
title: JavaScript
published: 2026-07-20
description: ''
image: ''
tags: []
category: ''
draft: false 
lang: ''
---
# JavaScript 基础
JavaScript 是一门为网站添加交互性的编程语言。交互性体现在游戏，点检就或输入表单时的相应行为；动态的样式；动画等。

## JavaScript 的优势
JavaScript 本身相对简洁，但非常灵活，可以使用最低的成本来解锁超值的功能。例如：
- Web 浏览器内置的应用程序编程接口 (API) ，提供了丰富的功能，例如：动态创建 CSS 样式；从用户的摄像头采集和处理视频流，生成 3D 图形和音频样本。
- 允许开发者将来自其他内容提供商的功能整合到自己网站中的第三方 API。
- 能够应用于 HTML 加速网站和应用程序开发的第三方框架和库。

## Hello World!
让我们从最简单的开始，输出 "Hello World!"：
1. 打开测试站点的目录，创建一个名为 `scripts` 的新目录。然后在 scripts 目录中创建一个名为 `main.js` 的新文件，并保存。
2. 打开 `index.html` 文件，在结束标签 `</body>` 前添加下列代码:
    ```HTML
    <script src="scripts/main.js"></script>
    ```
3. 与 CSS 的`<link>` 元素的功能类似， 它将 JavaScript 引入以用作于 HTML (以及 CSS 和页面上的任何其他内容) 。
4. 将下列代码添加到 `scripts/main.js` 文件：
    ```JS
    const myHeading = document.querySelector("h1");
    myHeading.textContent = "Hello world!";
    ```
5. 确认保存了 HTML 和 JavaScript 文件。然后在浏览器中打开 `index.html`。 你会发现标题中的文字被替换为了 Hello World!

> Tips: 将 `script` 元素放在 HTML 文件的底部附近的原因是**浏览器会按照代码在文件中的顺序进行读取。**  
如果 JavaScript 先加载，并期望操纵还未加载的 HTML， 可能会出现问题。 

## JavaScript 速成课
### 变量
变量是存储值的容器。要声明变量，先输入 `let` 关键字，然后输入变量名：
```JS
let myVariable;
```
行尾的分号代表语句结束。同时 JavaScript 对大小写敏感，这意味着 `myVariable` 和 `myvariable` 是不同的。如果代码中有问题，检查一下大小写！  

声明变量后，可以给它赋值：
```JS
myVariable = "LINKONG";
```

在同一行内执行声明和赋值操作也是合法的：
```JS
let myVariable = "LINKONG";
```

你可以通过变量名获取值：
```JS
myVariable;
```

给变量赋值后，你可以修改变量的值：
```JS
let myVariable = "LINKONG";
myVariable = "KiKiLIN";
```

变量可以存储不同数据类型的值：  
| 变量 | 解释 | 示例 |
| :---: | :---: | :---: |  
| 字符串 | 字符串就是文本序列。用单引号或双引号括起来的值就是字符串。 | `let myVariable = 'LINKONG';` 或 `let myVariable = "LINKONG";` |
| 数字 | 数字周围没有引号。 | `let myVariable = 10;` |
| 布尔值 | 真/假值。单词 `true`/`false` 是不需要引号的特殊关键字。 | `let myVariable = true;`|  
| 数组 | 可以在单一引用中存储多个值的结构。 | `let myVariable =  [1, 'LINKONG', KiKiLIN, 10];` 像这样引用数组成员: `myVariable[0]`, `myVariable[1]`, 等等。|
| 对象 | 可以是任何内容。JavaScript 里的一切都是对象，对象能在变量中存储。 | `let myVariable = document.querySelector('h1');` 以及上面的示例都是。|  


### 运算符
运算符是一种基于两个值 (或变量) 生成对应结果的数学符号。下面的运算符可以涵盖大部分情况：
| 运算符 | 解释 | 符号 | 示例 |
| :---: | :---: | :---: | :---: |
| 加 | 将两个数字相加或拼接两个字符串。 | `+` | `6 + 9;` `'Hello' + 'world';`|
| 减、乘、除 | 与基础算数一样 | `-`、`*`、`/` | `9 - 3;` `8 * 2;` `9 / 3;` |
| 赋值 | 上文中出现过：为变量赋值。 | `=` | `let myVariable = 'LINKONGH';` |
| 严格相等 | 测试两个值是否相等以及是否是相同的数据类型，并返回一个 `true`/`false` (布尔) 结果。 | `===` | `let myVariable = 3;` `myVariable === 4;` |
| 非、不等于 | 返回和先前逻辑上相反的值。非将 `true` 变为 `false` ，等等。当它和相等运算符一起使用时，否定运算符测试两个值是否不相等。 | `!`、`!==` | 对于"非"，基本表达式是 `true`，但结果返回的是 `false`，因为我们否定了这个值； `let myVariable =3;` `!(myVariable === 4);` "不等于"用不同的语法得出了基本上一样的结果。这里测试 `myVariable` 不等于 3。返回 `false`，因为 `myVariable` 等于 3；`let myVariable = 3;` `myVariable !== 3;`

### 条件语句
条件语句是用来测试表达式真假的代码结构。一个常用的条件语句是 `if...else` 语句。例如：
```JS
let name = "LINKONG";
if(name === "LINKONG"){
    alert("最喜欢 LINKONG 了！！！");
}
else {
    alert("是KiKiLIN来了...");
}
```
`if ()` 中的表达式是一个测试。用 (上文所提到的) 严格相等运算符来比较 `name` 变量与 `LINKONG` 字符串是否相等。如果返回 `true`，则运行第一个代码块；如果返回 `false`，则运行 `else` 关键字之后的第二个代码块。

### 函数
函数是一种可以将你希望重复使用的功能封装起来的方式。你可以将一段代码定义为一个函数，当你在代码中调用该函数名时，它会被执行。这是一种避免重复编写相同代码的好方式。在上文中我们已经提到了有关于函数的使用了。例如：
```JS
let myVariable = document.querySelector("h1");
```
```JS
alert("你好！");
```
`document.querySelector` 和 `alert` 是浏览器内置的函数。

当你发现有个像变量名，但是后面却跟着小括号 `()` 的不认识的东西，那么它很可能就是函数。函数通常接收参数：函数用来执行特定的任务。参数位于小括号内，多个参数之间用逗号分开。

比如 `alert()` 函数会在浏览器窗口中弹出一个警告框，但还应为其提供一个字符串参数，告诉他警告内要显示的内容。

我们当然也可以定义我们自己的函数。在下面的列子中，我们创建了一个接收两个数字参数的函数，并对这两个参数做乘法：
```JS
function multiply(num1, num2) {
    let result = num1 * num2;
    return result;
}
```
尝试在控制台中运行这个函数；并尝试多组数据。例如：
```JS
multply(4, 7);
multply(5, 8);
multply(0.5, 0.7);
```

> Tips: 
> 1. 在 HTML 页面中，按 `F12` 键打开浏览器开发者工具 (控制台) 。
> 2. 在弹出的面板中，切换到 Console（控制台） 标签页。
> 3. 将函数输入到控制台的输入框中，然后按回车键 (Enter) 。
> 4. 调用函数查看结果。

### 事件
事件处理器能为网页添加真正的交互。它们是监听浏览器活动的代码块，并在响应中运行代码。最明显的例子就是处理**点击事件**，当你用鼠标点击时，浏览器就会触发该事件。作为演示，在控制台中输入下面的代码，然后后点击网页的任意位置：
```JS
document.querySelector("html").addEventListener("click", function () {
    alert("不吃别扒拉！！！");
});
```
将事件处理器与元素绑定有许多种方式。在这里我们选择整体的 `<html>` 元素，然后调用了它的 `addEventListener()` 函数吗，并传递要监听的事件名 (`'click'`) 和事件发生时要运行的函数。

刚刚我们传递给 `addEventListener()` 的函数被称为匿名函数，因为它没有名字，匿名函数还有另一种书写方式，称为**箭头函数**。箭头函数使用 `() =>` 而不是 `function ()`":
```JS
document.querySelector("html").addEventListener("click", () => {
    alert("不吃别扒拉！！！");
});
```

## 改造你的网站
现在我们已经具备了一些 JavaScript 基础，我们可以为此添加一些新特性。
### 添加一个图像切换器
使用 JavaScript 和 DOM API 特性交替显示两张图片。当用户点击图片时进行切换。

1. 选择一张你想在页面上展示的图片。理想情况下，这张照片的尺寸与之前添加的图片的尺寸尽可能相同。
2. 将这张照片保存在 `images` 目录中。
3. 将这张图片重命名为 img2.png。
4. 将下列的 JavaScript 代码添加到 `main.js` 文件中：
    ```JS
    const myImage = docunment.querySelector("img");

    myImage.onclick = () => {
        const mySrc = myImage.getAttribute("src");
        if (mySrc === "images/img1.png") {
            myImage.setAttribute("src", "images/img2.png");
        }
        else {
            myImage.setAttribute("src", "images/img1.png");
        }
    };
    ``` 
5. 保存所有文件并用浏览器打开 `index.html`。现在，当你点击图片时，会切换成另外的一张。

### 添加个性化欢迎信息

我们可以让用户在第一次访问站点时将页面标题修改为个性化欢迎信息。并使这个消息一直存在，名字信息会由 Web存储API 保存下来，即使是关闭页面之后再重新打开。我们还会添加一个选项，改变用户名字以更新欢迎信息。
1. 打开 `index.html`， 在 `<script>` 元素前添加以下代码：
    ```HTML
    <button>Change user</button>
    ```
2. 打开 `main.js`, 下列代码添加到文件的底部。此步骤我们将获取新按钮和标题的引用，并存储到变量中：
    ```JS
    let myButton = document.querySelector("button");
    let myHeading = document.querySelector("h1");
    ```

3. 添加下列设置个性化欢迎信息的函数。我们可以拭目以待其效果。
    ```JS
    function setUserName() {
        const myName = prompt("Please enter your name.");
        localStorage.setItem("name", myName);
        myHeading.textContent = 'OH ! WELCOME ${myName}';
    }
    ```
    `setUserName()` 函数包含一个 `prompt` 函数，与 `alert()` 类似会弹出一个对话框。`prompt()` 函数的功能更多，需要用户输入数据，并在用户点击确定后将数据存储在一个变量中。在这个例子中我们要求用户输入一个名字。接下来，代码调用 `localStorage` API，它允许我们将数据存储在浏览器中并供后续获取。我们使用 `localStorage` 的 `setItem()` 函数创建并存储一个 `'name'` 的数据项，并将它的值设置为包含用户名的 `myName` 变量。最后将标题的 `textContent` 属性设置为待用用户新设置的名字的字符串，

4. 在函数声明的后面添加下列条件语句块。我们称之为初始化代码，因为它在初始加载时开始工作。
    ```JS
    if(!!localStorage.getItem("name")) {
        setUserName();
    } else {
        const storeName = localStorage.getItem("name");
        myHeading.textContent = 'OH ! WELCOME ${storeName}';
    }
    ```

5. 设置按钮的 `onclick` 事件处理器。当按钮被点击时，运行 `setUserName()` 函数。以便用户可以通过点击按钮设置新的名字。
    ```JS
    myButton.onclick = function () {
        setUserName();
    };
    ```

### null 值合法化
null 是 JavaScript 中的一个特殊值，表示引用的值不存在。  
也可以不输入任何名字直接点击确认，此时标题仍然会显示为 OH ! WELCOME，要避免这些问题，应该检查用户没有输入空名字。更新 `setUserName()` 为：
```JS
function setUserName() {
    const myName = prompt("Please enter jour name.");
    if(!myName) {
        setUserName();
    } else {
        localStorage.setItem("name", myName);
        myHeading.textContent = 'OH ! WELCOME ${myName}';
    }
}
```