---
layout: post
title: Markdown 语法总结
tags: [Syntax, Markdown]
---

[语法参考](https://www.markdowntutorial.com)

#### Italics and Bold
1. 斜体表示: \_text\_
2. 粗体表示: \*\*text\*\*
3. 斜体加粗: \*\*\_text\_\*\*


#### Headers
使用#可以表示1-6级不同的标题。一般来说，1级标题和6级标题应该谨慎使用。不能把标题加粗但是可以使用斜体字。


#### Links
可以对 Markdown 中的文本和 headers 使用 links，可以用斜体和粗体修饰，在 Markdown 中有2种不同的链接类型

1. 行内式：在[]中写入文本，在()中填写链接地址。For example:
```
[**_Visit Github!_**](https://github.com/zjjftnw)
```
2. 参考式：类似文章中的标注，直接抛出例子吧，很简单，一看就明白了。
```
    Here's [a link to something else][another place].
    Here's [yet another link][another-link].
    And now back to [the first link][another place].
    [another place]: www.github.com
    [another-link]: www.google.com
```


#### Images
创建图片的语法和创建链接的语法很相似。Images 也有2种方法可以使用。

1. 行内式
```
![Benjamin Bannekat](https://octodex.github.com/images/bannekat.png)
```
2. 参考式
```
![The second first father][Second Father]
[Second Father]:http://octodex.github.com/images/foundingfather_v2.png
```


#### Blockquotes
1. 如果需要对整段内容进行引用，只需要在段首添加">"即可。For example:
```
 > "In a few moments he was barefoot, his stockings folded in his pockets and his
 canvas shoes dangling by their knotted laces over his shoulders and, picking a
 pointed salt-eaten stick out of the jetsam among the rocks, he clambered down
 the slope of the breakwater."
```
2. 我们也可以对每一行添加">"，这样对跨多个段落引用非常有用。For example:
```
 > His words seemed to have struck some deep chord in his own nature. Had he spoken of himself, of himself as he was or wished to be?
 >
 > —Of whom are you speaking? Stephen asked at length.
 >
 > Cranly did not answer.
```
3. 块引用也可以包含其他的标记元素，如 Italics, Bold, Images and Links。


#### Lists
Markdown 可以创建2种不同类型的列表：有序列表和无序列表。有序列表使用"数字+点+空格"来表述`1. `，无序列表通过使用"\*+空格"来表述`* `。列表中的文本也可以使用其他的标记元素，如 Italics, Bold, Images and Links。列表当然也可以嵌套使用，我们需要记住的就是内部列表比外部列表要多缩进一个空格。有序列表和无序列表可以相互嵌套，但是最好不要超过三层。For example:

* unordered list:

```
* milk
* eggs 
* salmon 
```

* ordered list:

```
1. first
2. second
3. third
```

* nested lists

```
* Tintin
 * A reporter
 * Has poofy orange hair
 * Friends with the world's most awesome dog
* Haddock
 1. A sea captain
 2. Has a fantastic beard
 3. Loves whiskey
   * Possibly also scotch?
```
有几点值得注意：

1. 在其他的文本段落之后直接使用列表，即使使用 _soft breaks_ ，也不能实现换行，并且列表会直接接在文本之后，也就是列表无效了。所以，同样的多空一行就可以了。
2. 如果列表中的文本需要缩进对齐，则缩进一个空格就可以了。


#### Paragraphs
如果需要换行但又不想多空一行，可以在换行的位置输入2个空格+回车来完成（最好在编辑器中设置显示空格）。For example:
```
Do I contradict myself?··\\每个点代表一个空格
Very well then I contradict myself,··
```
结果：
```
Do I contradict myself?
Very well then I contradict myself,
```

这种软中断(_soft breaks_)最常见的引用是格式化在**Blockquotes**和**Lists**中的段落.
```
> first line··
> second lint

1. third line··
 hello world.
2. fourth line
```


### Table
Markdown 插入的表格，单元格中的内容默认左对齐；表头单元格中的内容会一直居中对齐（不同的实现可能会有不同表现）。注意，使用时发现，表格的语句上一行必须为空行，不然表格不生效。  
语法说明：

1. \|、-、:之间的多余空格会被忽略，不影响布局
2. 默认标题栏居中对齐，内容居左对齐
3. -:表示内容和标题栏居右对齐，:-表示内容和标题栏居左对齐，:-:表示内容和标题栏居中对齐
4. 内容和|之间的多余空格会被忽略，每行第一个|和最后一个|可以省略，-的数量至少有一个

For example:  
```
| 左对齐标题 | 居中对齐标题 | 右对齐标题 |
| :------| :------: | ------: |
| 短文本 | 中等文本 | 稍微长一点的文本 |
| 稍微长一点的文本 | 短文本 | 中等文本 |
```
渲染的效果：  

| 左对齐标题 | 居中对齐标题 | 右对齐标题 |
| :------| :------: | ------: |
| 短文本 | 中等文本 | 稍微长一点的文本 |
| 稍微长一点的文本 | 短文本 | 中等文本 |