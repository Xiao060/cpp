# Markdown 

## 1.简介(what)

**Markdown** 是由  John Gruber 于 2004 年创建的一种轻量级**标记语言**, 除 markdown 外知名的标记语言还有 HTML / LaTeX. 

Markdown 发明的初衷是让人们可以编写更易于读写的 "html" , 而不用去记忆 html "复杂" 的格式化标记

## 2.为什么要使用 markdown (why)

1. 自身优势: 
    1. markdown 为纯文本文档, 可以利用 git 进行版本管理, 方便版本回退; 
    1. 跨平台, 不需要安装特定软件, 随便用一个文本编辑器便可打开
    1. markdown 对于代码拥有良好的支持, 是程序员记笔记的不二之选
    
1. 现实需要: 
    1. 很多项目的 README、开发文档、帮助文档、Wiki 等都是使用 markdown 写成的, 这要求程序员必须学习 markdown 的使用
    1. 国内的绝大多数社交平台(包括个人博客)都支持 markdown 语法, 即使不支持也可以很方便的将 markdown 转换为想要的格式. 若想在这些平台发布文章, markdown 可以免去多次排版的困扰



==**BUT**== markdown 也有一些缺点: 

1. 标准众多, 除了基本语法外, 还有PHP Markdown Extra / GitHub Flavored Markdown / CommonMark / MultiMarkdown 等扩展语法, 没有一个统一规范

1. 图片以附件形式存在, 分享时需要连同附件一起传输; 如果将图片放到云端图床上则需要购买OSS存储

1. 一些复杂的功能, 如 修改图片大小 / 合并单元格 等需要借助 HTML 来实现



## 3.工具推荐

1. 编辑器

    以下排名不分先后

    1. [**StackEdit**](https://stackedit.cn/): 在线 markdown 工具, 支持同步到 Gitee / GitHub, 支持发布文章到 WordPress ...
    1. [**Typora**](https://typoraio.cn/): 跨平台 markdown 收费软件, 价格 **89** 元, **所见即所得**的 md 编辑器, 但据用户反馈文件较大时会卡顿 
    1. **vscode + Markdown Preview Enhanced + Markdown All in One**: 免费跨平台 md 方案
    1. 其他 md 笔记软件: Vnote / Obsidian / Logseq / Joplin ...

    更详细的 md 编辑器对比可以看这篇文章 [**东瓜瓜瓜瓜的 md 编辑器对比**](https://zhuanlan.zhihu.com/p/208791140), 虽然距离文章发表已过去很长时间, 但任然具有一定的参考价值, 衷心提醒 ==**好的工具能够做到事半功倍, 但是再好的工具也不能弥补思想的匮乏**==
    
1. 图床推荐
    1. `SM.MS + PicGo`: 免费图床 
    1. `阿里云 OSS + PicGo`: 付费存储

## 4.基础语法 (how)

以下只是简单介绍了一些常用语法, 更详细的介绍推荐查看 [**Markdown 官方教程**](https://markdown.com.cn/)

### 4.1 标题

以 `#` + `空格` 标识, `#` 数量越多, 标题级别越低, 最多支持 ==6== 级标题

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309052226807.png" alt="标题" style="zoom: 67%;" />

---



### 4.2 列表

#### 4.2.1 有序列表

以 `数字` + `.` + `空格` 标识, 第一个数字 以 ==1== 开始, 其他数字随便

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/Snipaste_2023-09-05_22-33-08.png" alt="有序列表" style="zoom:80%;" />

---



#### 4.2.2 无序列表

以 `- 或 + 或 *` + `空格` 标识,  不建议混合使用

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309052247487.png" alt="无序列表" style="zoom:80%;" />

---



#### 4.2.3 任务列表(扩展语法)

以 `-` + `空格` + `[ ]` + `空格` 标识, 若中括号内为空格代表未完成, 为 ==x 或 X== 代表完成

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309060124301.png" alt="任务列表" style="zoom:80%;" />

---



### 4.3 引用

以 `>` + `空格` 标识

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/image-20230905225914136.png" alt="引用" style="zoom: 80%;" />

---



### 4.4 代码

#### 4.4.1 行内代码

 `` `代码` ``, 将代码用 1对==反引号==包起来 

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/image-20230905230615191.png" alt="行内代码" style="zoom:80%;" />

---



#### 4.4.2 围栏式代码块(扩展语法)

` ``` `, 在代码块上下两行分别用 ==3个反引号== 将其包起来, 第一个反引号后可以注明 代码块 的语言, markdown 会根据注明信息自动高亮 

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309052322882.png" alt="代码块" style="zoom:80%;" />

---



### 4.5 强调

#### 4.5.1 斜体

`*内容*`, 将要 斜体 的内容左右两侧各用 ==1个*== 包起来

![斜体](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309052337297.png)

---



#### 4.5.2 加粗

`**内容**`, 将要 加粗 的内容左右两侧各用 ==2个*== 包起来

![加粗](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309052334592.png)

---



#### 4.5.3 粗体+斜体

`***内容***`, 将要 加粗并斜体 的内容左右两侧各用 ==3个*== 包起来

![粗体+斜体](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/image-20230905234026771.png)

---



#### 4.5.4 高亮(扩展语法)

`==内容==`, 将要 高亮 的内容左右两侧各用 ==2个\=== 包起来

![高亮](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309052345248.png)

---



#### 4.5.5 删除线(扩展语法)

`~~内容~~`, 将要 添加删除线 的内容左右两侧各用 ==2个~== 包起来

![删除线](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309060117431.png)

---



### 4.6 分隔线

`*** 或 --- 或 ___`, 在单独一行使用 ==3个或多个 */-/_==, 建议在分割线上下各空一行

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309052350360.png" style="zoom: 67%;" />

---



### 4.7 链接

`[文本](超链接)`

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309060115890.png" alt="链接" style="zoom:80%;" />

---



### 4.8 图片

`![图片名称](图片链接)`, 其中链接支持 本地链接(绝对/相对路径) 和 网络链接, 图片名称可以省略

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309060107592.png" alt="图片" style="zoom:67%;" />

---



### 4.9 表格(扩展语法)

1. 前两行用来设置表格标题 及 每一列的对齐属性
    1. 每一列以 `|` 间隔
    1. 第二行第一列至少含有 `3 个 -`, 冒号位于减号左边为 `左对齐`, 右面为 `右对齐`, 两侧都有为 `居中对齐`, 冒号可省略

1. 第三行开始为表格内容, 无内容可省略 但 `|` 不能遗漏

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/aaaa.png" alt="表格" style="zoom: 67%;" />

---

