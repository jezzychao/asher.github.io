---
layout: post
title: 改善程序和设计的55个具体做法
tags： [C++]
---
## 设计声明

### 19.设计class应当以 build-in types 为标准。
设计时应该考虑到以下问题：
1. 新type的对象应该如何被创建和销毁？
2. 对象的初始化和赋值操作该有什么样的差别？
3. 新type的对象如果被passed by value ，意味着什么？copy construct 函数用来定义一个type的pass-by-value该如何实现。
4. 什么是新type的合法值？对class的成员变量而言，通常只有某些数值集是有效的。那些数值决定了class必须维护的约束条件，决定了成员函数必须进行的检查工作。也影响函数抛出的异常、以及极少被使用的函数异常明细列。
5. 新type是否需要配合某个继承图系？新type会受到继承体系的约束，影响到析构函数的声明是否为virtual。
6. 新type需要什么样的类型转换？隐式？显示？
7. 什么样的操作符和函数对新type是合理的？
8. 谁会使用新type的成员？这会决定哪些函数应该声明为private，哪些是public，哪些是protected。
9. 什么是新type的“未申明接口”（undeclared interface）？它对效率、异常安全性以及资源运用提供何种保证?你在这些方面提供的保证将为你的class实现代码加上约束条件。
10. 新type是否具有一般化？决定是class 还是class tempate。
11. 是否真的需要一个新的type？如果只是定义新的derived class 以便为现有的class添加新机能，那么说不定单纯定义一或多个non-member函数或者templates，就可以达到目的。

### 20.对于内置类型以及STL的迭代器和函数对象，应该使用pass-by=value。
对于其他类型的对象包括用户自定义的类型，尽量应该使用pass-by-reference-to-const。因为在C++编译器的底层，references往往以pointer实现出来，pass不用reference通常意味着真正传递的是指针。

### 21.必须返回一个对象时，不能返回它的reference或pointer。
绝对不要返回pointer或reference指向一个local stack对象，或返回reference指向一个heap-allocated对象，或返回pointer或reference指向一个local static对象在同时需要多个这样的对象的情况下。

### 22.将成员变量声明为private。
这可赋予客户访问数据的一致性、可以细化微分访问控制、许诺约束条件获得保证，并提供class充分的弹性。protected并不比public更具有封装性。也就是说在继承体系中也要把成员变量声明为private，通过接口函数来访问。

### 23.宁可拿 non-member、non-friend 函数来替换 member 函数。
这样做可以增加封装性、包裹弹性(packaging flexiblity)和机能扩充性。面向对象守则要求数据尽可能的被封装。member 函数的封装性比 non-member 函数低。此外提供 non-member 函数可以允许 class 拥有较大的弹性，降低编译的相依存度，增加 class 的可延伸性。封装性可以通过能够访问数据的函数数量，作为一种粗糙的测量。越多的函数可以访问数据，数据的封装性就越低。For example:
```
//下列这种正是C++标准程序库的组织方式。
//头文件 webbrowser.h，自身类和核心机能 non-member 函数
namespace WebBrowserStuff
{
    class WebBrowser
    {
        public:
            void clearCache();
            void clearHistory();
            void removeCookies();
    };
    //non-member function
    void clearBrowser(WebBrowser &wb)
    {
        wb.clearCache();
        wb.clearHistory();
        wb.removeCookies();
    }
    //其它核心机能的 non-member function
}

//头文件 webbrowserbookmarks.h
namespace WebBrowserStuff
{
   //与书签相关的 WebBrowser 类的 non-member 函数
}

//头文件 webbrowsercookies.h
namespace WebBrowserStuff
{
   //与 cookie 相关的 WebBrowser 类的 non-member 函数
}
```

### 24.若所有参数皆需要类型装换，请使用non-member函数
如果需要为某个函数的所有参数进行（包括被this指针所致的那个隐式参数）类型装换，那么这个函数必须是 non-member。member 函数的反面是 non=member 函数，而不是 friend 函数.

### 25.关于 noexcept swap 函数
swap 主要涉及 default swap, member swap, non-member swap, std::swap特化版本, 以及对 swap 的调用问题。如果 default swap 提供的效率可接受，则不需要做额外的事情；若效率不足，可以为 class 或者 template class 提供一个 noexcept member swap 函数，高效的置换类型的对象值。
* 如果编写的是 template ，可以在template所在命名空间内提供一个 non-member swap ，并令它调用 member swap。
* 如果编写的是 class,可以为class 特例化std::swap，然后在函数内调用 member swap。当然也可以采用A的方式。

swap的调用采用统一的形式：
```
using std::swap;	//引入标准库中的所有 swap 函数作为候选函数；
swap(obj1,obj2);	//如果 obj 是和类类型相关的，则会将对应类的 swap 也加入到候选函数中，然后进行函数的精确匹配过程。
```
这种调用的形式基于 name lookup rules: 调用一个函数，如果该函数的形参类型是类类型/类类型的指针或引用，则会在类所在作用域中进行查找函数。

### 26.尽可能的延后变量定义式的出现时间。
* 避免无意义的 default 构造行为，通俗的说就是在给变量赋值的时候要使用构造函数，而不是先 default 构造再赋值的操作：
```
std::string s("helloworld");	//good
std::string s = "helloworld";	//bad,std::string的构造函数时explicit的，所以执行步骤是1.default ctor, 2.then call operator=;
								//如果遇到的类型构造是non explicit，则只执行一步构造操作；
std::string s;					//very bad;
s = "helloworld";
```
* 如果变量只在循环内使用，该如何定义？
```
//方法A: 定义于循环外
Widget w;
for(int i = 0 ; i != n ; ++i){
	w = 取决于i的值；
}

//方法B: 定义于循环内
for(int i = 0 ; i != n ; ++i){
	Widget w = 取决于i的值；
}
```
 成本比较：
 A：1个构造函数 + 1个析构函数 + n个赋值操作；同时w的作用域覆盖整个循环，有时会对程序的可理解性和易维护性造成冲突；
 B：n个构造函数 + n个析构函数；
 so:除非（1）我们知道赋值成本比"构造+析构"成本低，（2）除非你正在处理代码中效率高敏感的部分，否则应该使用B。


## 实现

### 27.尽量少做转型动作。
任何一个类型往往真的令编译器编译出运行期间执行的代码，也就是会编译额外的代码。
dynamic_cast的许多实现版本执行速度相当慢。
	1.如果转型是必须的，试着将它隐藏于某个函数背后。不要让用户自己做转型动作。
	2.使用C++-style(新式)转型，不要使用旧式的转型。
	
### 28.避免返回handles指向对象内部成分。
避免返回handles（包括引用，指针，迭代器）指向对象内部，这样可以增加封装性，帮助const成员函数的行为像个const,并且将发生dangling handles的可能性降至最低。

### 29.为“异常安全”而努力是值得的
异常安全函数(Exception=safe functions)即使异常抛出时也**不泄漏资源**或**不数据败坏**。
* **不泄漏资源**：以对象管理资源，建立资源管理类(resource management classes)。
* **不败坏数据**：在这里先引入3个术语定义：
 * **基本承诺**：如果异常被抛出，程序内的任何事物都任然保持在有效状态下。没有任何对象或数据会因此而败坏，所有对象都处于一种内部前后一致的状态。然而程序的现实状态不可预料。For example，在重新赋值背景图像的过程中抛出异常，背景图像可能是原来的图像或者是缺省的，客户无法预期会出现那种情况，但是这都是有效状态的。
 * **强烈保证**：程序操作如果抛出，程序会回复到操作之前的状态，不会改变原来的状态。
 * **不抛掷保证(nothrow)**：承诺绝不抛出异常。作用于内置类型上的所有操作都提供 nothrow 保证。函数的声明式并不能提供任何异常安全性保证，是由函数的实现决定的，无关声明。(关于 nothrow 的使用请查阅《C++ Primer》)
 
 _强烈保证_ 往往能够使用 _copy and swap_ 技术来实现，但 _强烈保证_ 并非对所有的函数都可实现或具备实现意义。
一般而言，我们会在 _基本承诺_ 和 _强烈保证_ 之间做出选择，因为我们很难在程序中完全没有调用任何一个可能抛出异常的函数，使用动态内存就意味着有可能抛出 _bad_alloc_ 异常。对于一个软件系统而言，要不就具备异常安全，要不就全然否定，没有所谓的局部异常安全。如果系统内有一个函数不具备异常安全性，整个系统就不具备了，因为调用不安全的函数会导致异常。

### 30.inline
inline只是对编译器的一个申请，并不是强制命令。表面上看似inline的函数是否是真的inline，取决于我们的建置环境，主要取决于编译器。
有时候虽然编译器有意愿inlining某个函数，还是可能为该函数生成一个函数本体。For example:
	```
	inline void f(){...}//假设编译器有意愿inlining该函数
	void (*pf)() = f;//pf指向f,因为这里需要取到函数f的地址，所以编译器必须为此函数生成一个outlined本体。
	...
	f();//这个调用将被inlined，是一个正常的调用
	pf();//这个调用不被inlined，调用的是outlined本体
	```
构造函数和析构函数往往是inlining的糟糕候选人，因为在构造和析构函数中编译器会为我们做其它的事情。
在程序的编译期间，Templates的具现化和inlining无关。如果将所有的Templates声明为inline,会引发代码膨胀。
**总结**： 
1. 将大多数inlining限制在小型、被频繁调用的函数身上。这可使以后的调试过程和二进制升级更容易，也可使潜在的代码膨胀问题最小化，使程序的速度提升机会最大化。
2. 不要只因为 function templates 出现在头文件中，就将他们声明为inline。
