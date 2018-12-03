---
layout: post
title: C++类型处理
tags: [C++, Syntax]
---

## 类型别名、auto 和 decltype


### 类型别名

定义类型别名有两种方法可以使用：  
1. 使用关键字 **typedef** ,就是相当于声明一个变量然后在最前面加上 **typedef** ，该变量就成为了类型别名：
```
typedef char *pstring;
const pstring cstr = 0;	//这里的基本数据类型时指针（char *），不能去尝试把类型别名替换成原先的样子(const char *cstr),这是完全错误的理解。
const pstring *ps;		//ps是一个指针，至向char的常量指针
```
2. 使用 **using** 关键之：
```
using mydouble = double;
```


### auto 类型说明符

使用 **auto** 能在一条语句中声明多个变量，但是所有的变量推断出的基本数据类型必须一致：
```
auto i = 0, *p = &i;//正确
auto sz = 0, pi = 3.14;//错误，类型不一致
```

在推导复合类型、常量类型时，有时候和初始值的类型并不完全一样，编译器会适当的改变结果类型使其更符合初始化规则。  
1. 当 _reference_ 被用作初始值时，真正参与初始化的是引用对象的值。此时，编译器以引用对象的值作为 **auto** 的类型：
```
int i = 0, &r = i;
auto a = r;//a 是 int，而不是 int &
```
2. **auto** 一般会忽略 top-level-const ，但是会保留 low-level-const。如果希望推导出的 **auto** 类型是 top-level-const ，需要明确指出 const。
```
int i = 0；
const int ci = i, &cr = ci;
auto b = ci;	//int，ci 的top-level-const 被忽略掉了
auto c = cr;	//int，根据第一条规则，真正参与初始化的是 ci，ci 本身是一个 top-level-const
auto d = &i；	//int *，这个不需要解释
auto e = &ci；	//const int *，常量对象取地址是一种 low-level-const
const auto f = ci;//int，auto 类型是int，但是有 const 明确指出，所以这里 f 的类型是 const int
```
3. 设置一个类型为**auto**的引用时，初始值中的 top-level-const 属性任然保留。和往常一样，给初始值绑定一个引用，则此时的 top-level-const 就变为 low-level-cosnt了。
```
auto &g = ci;	//const int
auto &h= 42;	//不能为非常量引用帮定字面值
const auto &j = 42;//int，可以为常量引用帮定字面值
```
4. 在一条语句中定义多个变量，符号 & 和 * 只从属于某个声明符，不是基本数据类型的一部分：
```
auto k = ci, &l = i;//true
auto &m = ci, *p = &ci;//true
auto &n = i, *p2 = &ci;//false
```


### decltype 类型指示符

返回操作数的数据类型，并不会实际求表达式或调用函数。  
1. 如果 decltype 使用的表达式是一个变量，则 decltype 返回该变量的类型（包括 top-level-const 和 reference）：
```
const int ci = 0, &cj = ci;
decltype(ci) x = 0;//const int x = 0;
decltype(cj) y = x;//const int &y = x;
```
2. 如果表达式的求值结果是左值，则 decltype 得到是该值的引用类型：
 * 解引用操作，将得到引用类型。
 * decltype((variable))的结果永远是引用。因为多了一层括号，编译器把它当作了一个表达式，同时变量是一种可以作为赋值语句左值的特殊表达式。
