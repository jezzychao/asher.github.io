---
layout: post
title: Markdown 语法总结
tags: [Syntax, Markdown]
---

[语法参考](https://www.markdowntutorial.com)

## Italics and Bold
1. Italics: \_text\_
2. Bold: \*\*text\*\*
3. Italics and Bold: \*\*\_text\_\*\*


## Headers
使用#可以表示1-6级不同的标题。一般来说，1级标题和6级标题应该谨慎使用。不能把标题加粗但是可以使用斜体字。


## Links
可以对 Markdown 中的文本和 headers 使用 links，可以用斜体和粗体修饰，在 Markdown 中有2种不同的链接类型((行内试和参考式))。
1. 在[]中写入文本，在()中填写链接地址。如\[\*\*\_Visit Github!\_\*\*](https://github.com/zjjftnw): [**_Visit Github!_**](https://github.com/zjjftnw)；
2. 直接抛出例子吧，很简单，一看就明白了。

 > Here's [a link to something else][another place].
 > Here's [yet another link][another-link].
 > And now back to [the first link][another place].

 > [another place]: www.github.com
 > [another-link]: www.google.com


## Images
创建图片的语法和创建链接的语法很相似。Images 也有2种方法(行内试和参考式)可以使用。
1. \!\[Benjamin Bannekat](https://octodex.github.com/images/bannekat.png)
2. 参考式不要忘记在最前方加上`!`,否则会变成 Links
 > \!\[The second first father][Second Father]
 > \[Second Father]:http://octodex.github.com/images/foundingfather_v2.png


### Blockquotes
If you need to call special attention to a quote from another source, or design a pull quote for a magazine article, then Markdown's blockquote syntax will be useful. A blockquote is a sentence or paragraph that's been specially formatted to draw attention to the reader.
For example:
I say:
\>"The sin of doing nothing is the deadliest of all the seven sins. It has been said that for evil men to accomplish their purpose it is only necessary that good men should do nothing."

You can also place a caret character on each line of the quote. This is particularly useful if your quote spans multiple paragraphs.For example:
> \>His words seemed to have struck some deep chord in his own nature. Had he spoken
of himself, of himself as he was or wished to be? Stephen watched his face for some
moments in silence. A cold sadness was there. He had spoken of himself, of his own
loneliness which he feared.
> \>
> \>—Of whom are you speaking? Stephen asked at length.
> \>
> \>Cranly did not answer.
Notice that even blank lines must contain the caret character. This ensures that the entire blockquote is grouped together.


## Lists
Markdown 可以创建2种不同类型的 Lists: unordered and ordered.
* unordered list: 

 > \* milk
 > \* eggs 
 > \* salmon 

* ordered list:

 > \1. first...
 > \2. second... 
 > \3. third...


## Code
```
#include<string>
```
