[TOC]



## 字符串

1. 构造

    ```c++
    // 头文件其实已经包含在 iostream 中了
    #include <string>
    using std::string;
    
    // 无参构造
    string xxx;
        
    // count + 字符
    string xxx(count, char);
    
    // C 字符串 + [count]
    string xxx(cstr, count);
    
    // string 对象 + [pos] + [count](拷贝) 
    string xxx(string, pos, count);
    ```

1. 常用操作

    ```c++
    // string 转 cstr, 使用 printf() 打印
    s.data();
    s.c_str();
    
    // 判空
    s.empty();
    
    // 字符数/长度
    s.size();
    s.length();
    
    // 字符串末尾添加字符
    s.push_back(char);
    
    // 字符串末尾附加内容
    s.append(count, char);
    s.append(cstr);
    s.append(string);
    s.append(string, pos, count);
    
    // 寻找子串, 返回类型 size_t, 找不到返回 string::npos
    s.find(string, pos=0);
    s.find(char, pos=0);
    // 从主串的 pos 开始查找 子串的前 count 个字符
    s.find(cstr, pos, count);
    
    
    
    
    // 遍历1
    for (size_t i=0; i<string.size(); ++i) {
        ...
    }
    
    // 遍历2(增强 for 循环), auto 自动推导类型, 此处用 char 也可以; & 引用直接操作元素本身, 避免复制
    for (auto& ch : string) {
      ...  
    }
       
    // 遍历3(迭代器), 此处 auto 推导出的类型为 string::iterator
    auto i = string.begin();
    while (i != string.end()) {
        ...
    }
    ```



## Vector

1. 构造

    ```c++
    #include <vector>
    using std::vector;
    
    // 无参构造
    vector<类型> xxx;
    
    // 有参构造, 指定长度, 初始化为 默认值(整数为0, 对象看构造函数)
    vector<类型> xxx(size);
    
    /**********************************************************/
    // 通过迭代器(地址)方式初始化 vector 对象
    // 迭代器 左闭右开 [arr, arr+5)
    // 此处可以用 string迭代器 初始化 vector<char>
    vector<类型> xxx(arr, arr+5);
    /**********************************************************/
    
    
    // 通过列表创建 vector 对象
    vector<类型> xxx{..., ..., ..., ...};
    ```

1. 基本操作

    ```c++
    // 判空
    v.empty();
    
    // 元素个数
    v.size();
        
    // 容量
    v.capacity();
    
    // 在最后一个元素的后面添加元素
    // 放满时: 1.开辟空间(2倍); 2.allocator分配; 3.复制，再添加新元素; 4.回收原空间
    // 扩容策略不同平台有差异
    v.push_back();
        
    // 删除最后一个元素 
    v.pop_back();
    
    // 清空所有元素, 不会回收空间
    v.clear();
    
    // 释放 vector 容器中多余的空间
    v.shrink_to_fit();
       
    // 开辟空间, 不初始化元素, 节省开销
    v.reserve()
    
    
    
        
        
        
    // 遍历1
    for (size_t i=0; i<v.size(); ++i) {
        ...
    }
    
    // 遍历2(增强 for 循环), auto 自动推导类型; & 引用直接操作元素本身, 避免复制
    for (auto& i : v) {
      ...  
    }
       
    // 遍历3(迭代器), 此处 auto 推导出的类型为 vector<int>::iterator
    auto i = v.begin();
    while (i != v.end()) {
        ...
    }
        
    ```

1. Vector 底层实现 (**`面试必考`**)

    1. 由 3 个指针构成
    1. `_start` 指向当前数组中第一个元素存放的位置 
    1. `_finish` 指向当前数组中最后一个元素存放的下一个位置 
    1. `_end_of_storage` 指向当前容器存放的最后一个元素的下一个位置
    1. vector 中的元素存在 堆上
    
     ![image-20230908175603277](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/image-20230908175603277.png)
    
    



## 输入输出流

![](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309090952393.png)

1. 流的状态

    ```c++
    xxx.good();
    
    // 严重的系统级错误(不可恢复)
    xxx.bad();
    
    // 可恢复错误
    xxx.fail();
    
    // 流终止
    xxx.eof();
    
    /************************************************/
    
    // 重置流的状态, 但是不会清空缓冲区
    xxx.clear();
    
    // 清空缓冲区, 参数为空舍弃一个字符
    // count 表示舍弃的数量, delim 代表舍弃到的字符(包含该字符)
    xxx.ignore([count], [delim]);
    
    // 静态函数, cin 缓冲区最大值, 常用作 ignore 第 1 个参数
    #include <limits>
    std::numeric_limits<std::streamsize>::max();
    
    /************************************************/
    
    // 常用格式
    // `逗号表达式` 从左往右计算, 并以 最后一个表达式的值 作为 整个表达式的值
    while (cin >> xxx, !cin.eof()) {
        ...
    }
    ```

1. 流对象作为参数时必须使用引用, 因为流是表达对象语义, 它的拷贝构造函数已经删除, 无法完成拷贝

1. 缓冲机制
    1. 全缓冲
    1. 行缓冲: `cout` 既支持 行缓冲 也支持 满缓冲; `cin` 的返回值为 `cin`
    1. 非缓冲: `cerr` 

1. 禁止隐式转换: `explicit xxx`, 放在构造函数前

1. 操纵符

    ```c++
    // 完成换行，并刷新缓冲区
    endl;
        
    // 在输入后加上一个空字符，然后再刷新缓冲区
    ends;
    
    // 直接刷新缓冲区 
    flush;
    ```
    
     



## 文件 IO

1. 构造
    ```c++
    using std::ifstream;
    
    /************************************/
    // 1. 无参构造, 搭配 open 使用
    ifstream();
    
    // 例
    ifstream xxx;
    xxx.open(filename);
    ...;
    xxx.close(); 
    
    /************************************/
    
    // 2. 2 个参数, 1为文件名(推荐string), 2为打开模式
    explicit ifstream(const char* filename, openmode mode = in);
    explicit ifstream(const string & filename, openmode mode = in);
    ```
    
1. 文件模式 (位图)
    ```c++
    // 输入，读操作；如果文件不存在，打开失败
    std::ios::in;
    
    // 输出，写操作；如果文件不存在，则直接创建一个
    std::ios::out;
    
    // 追加
    std::ios::app;
    
    // 把游标位置设为末尾
    std::ios::ate;
    
    // 截断，如果打开的文件存在，其内容将被丢弃，其大小被截断为零
    std::ios::trunc;
    
    // 二进制，读取或写入文件的数据为二进制形式
    std::ios::binary;
    ```
    
1. 文件游标位置
   
    ```c++
    // 读模式获取文件游标位置
    xxx.tellg();
    
    // 读模式设置游标位置
    xxx.seekg(偏移量); 	 // 绝对位置
    xxx.seekg(偏移量, 锚点);	// 相对位置
    
    /***************************************/
    
    // 写模式获取文件游标位置
    xxx.tellp();
    // 写模式设置游标位置
    xxx.seekp();
    
    /***************************************/
    // 锚点
    std::ios::beg;	// 文件开头
    std::ios::cur;	// 当前位置
    std::ios::end;	// 文件末尾
    ```
    
1. 读写

    ```c++
    /************************************/
    // 读取
    
    // C 风格字符串
    xxx.getline(buf, sizeof(buf));
    // 兼容 C 风格字符串
    getline(xxx, string);
    
    // 读取指定字节数的数据
    read(cstr, count);
    
    /************************************/
    // 写入
    xxx << string;
    xxx.write(buff, strlen(buf));
    ```



## 字符串 IO

1. aa
    ```c++
    #include <sstream>
    using std::istringstream;
    
    // 将字符串转换为其他类型
    istringstream xxx(string);
    xxx >> ... >> ...;
    
    /************************************/
    
    #include <sstream>
    using std::ostringstream;
    
    // 将其他类型转换为字符串类型
    ostringstream xxx;
    xxx << ... << ...;
    
    cout << xxx.str() << endl;
    ```

## 日志

### 概述

```c++
// 日志布局 
#include <log4cpp/Layout.hh>
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>

log4cpp::BasicLayout();						// 默认的格式
log4cpp::PatternLayout();					// 定制化格式
布局对象.setConversionPattern("...");

目的地对象.setLayout(布局对象);

/* 	布局
%%  表示百分号
%c  表示Category对象的名字
%d  表示日期，还有更细粒度的
	%d{%H:%M:%S,%l}
	%d{%d %m %Y %H:%M:%S,%l}
%m  表示日志本身
%n  表示换行符
%p  表示优先级
/*

/***********************************************************************/

// 日志目的地 
// 可以设置多个目的地
// 每一个目的地 Appender 都需要设置一个布局 Layout (1 对 1, 否则段错误)
#include <log4cpp/Appender.hh>
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>

log4cpp::OstreamAppender(..., &cout);
log4cpp::FileAppender(..., filename);
log4cpp::RollingFileAppender(..., filename, 				// 回卷文件
                             maxFileSize = 10*1024*1024, 	// 每个文件大小
                             maxBackupIndex = 1, ...);		// 备份的回卷文件个数

源对象.addAppender(目的地对象);

/**********************************************************************/    

// 创建模块对象, 日志记录器（来源）
#include <log4cpp/Category.hh>

log4cpp::Category::getRoot();			// root 对象
log4cpp::Category::getInstance();		// 叶对象

// 使用 categroy 对象必须先创建 root 对象, 再创建叶对象
// 如果没有显式创建根对象，直接去创建叶对象也会自动创建出一个根对象(建议显式创建，因为显式创建根对象可以设置根对象的优先级、目的地)
// 子Category 继承 父Category 的 优先级/目的地

/***********************************************************************/

// 设置 日志系统 优先级 
#include <log4cpp/Priority.hh>

源对象.setPriority();

// 日志系统有一个优先级 A, 日志信息也有一个优先级 B
// 只有 B 高于或等于 A, 日志系统才会记录这条日志, 否则就将这条日志信息过滤掉

/*********************************************************************/

log4cpp::Category::shutdown();	
```
![](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202309111445616.png)

### 头文件
```c++
// 头文件

// 设置 布局 的头文件
#include <log4cpp/BasicLayout.hh>
#include <log4cpp/PatternLayout.hh>

// 设置 目的地 的头文件
#include <log4cpp/OstreamAppender.hh>
#include <log4cpp/FileAppender.hh>
#include <log4cpp/RollingFileAppender.hh>

// 设置 源 的头文件
#include <log4cpp/Category.hh>

// 设置 优先级 的头文件
#include <log4cpp/Priority.hh>
```



### 1.创建 布局对象 并 设置布局

```c++
// 1.创建 布局对象 并 设置布局
log4cpp::BasicLayout();						// 默认的格式, 不需要再单独设置
log4cpp::PatternLayout();					// 定制化格式, 需设置布局
布局对象.setConversionPattern("%d %c [%p]: %m%n");
    
/*	布局
%%  表示百分号
%c  表示Category对象的名字
%d  表示日期，默认 {%Y-%m-%d %H:%M:%S,%l}
	%d{%H:%M:%S,%l}
	%d{%d %m %Y %H:%M:%S,%l}
%m  表示日志本身
%n  表示换行符
%p  表示优先级
/*
```



### 2.创建 目的地对象 并 绑定布局    

```c++
// 2.创建 目的地对象 并 绑定布局
log4cpp::OstreamAppender(..., &cout);
log4cpp::FileAppender(..., filename);
log4cpp::RollingFileAppender(..., filename, 				// 回卷文件
                             maxFileSize = 10*1024*1024, 	// 每个文件大小
                             maxBackupIndex = 1, ...);		// 备份的回卷文件个数
目的地对象.setLayout(布局对象);
```



### 3.创建 源对象 并 设置优先级 / 绑定目的地

```c++
// 3.创建 源对象 并 设置优先级 / 绑定目的地
log4cpp::Category::getRoot();			// root 对象
log4cpp::Category::getInstance();		// 叶对象
源对象.setPriority();
源对象.addAppender(目的地对象);
    
/*	优先级
Priority::EMERG;
Priority::FATAL;
Priority::ALERT;
Priority::CRIT;
Priority::ERROR;
Priority::WARN;
Priority::NOTICE;
Priority::INFO;
Priority::DEBUG
*/
```



### 4.输出日志

```c++
// 4.输出日志
...
```



### 5.日志系统退出

```c++
// 5.日志系统退出
log4cpp::Category::shutdown();
```



### 编译

```c++
// 编译
// g++ log4cpptest.cc -llog4cpp -lpthread
```



## 友元函数

使用 `friend` 关键字声明的函数即为友元函数, 该函数可以在类之外访问私有成员

1. 分类

    1. 普通函数
    
    1. 另一个类的成员函数 (不推荐)
        ```c++
        // B 是 A 的朋友, 即 A 中存在 friend xxx B::func(const A& xxx);
        
        // 1.A 做 前向声明
        // 2.B 定义，其中友元函数只声明(不加 friend)
        // 3.A 定义(不要忘记声明友元函数, 加 friend)
        // 4.类外实现 B 的友元成员函数
        
        /*	前向声明 
        1.只进行了前向声明的类不能创建对象
        2.可以用于定义指向这个类型的 ==指针== 和 ==引用==
        3.可以用于声明使用该类型作为 ==形参== 的函数
        */
        
        /*****************************************************************/
        
        // 1.原类 做 前向声明
        class A;
        
        // 2.友元函数类 定义，其中友元函数只声明(不加 friend)
        class B {
        public:
            xxx func(const A& xxx);
        	...
        }
        
        // 3.原类 定义
        class A {
        public:
            friend xxx B::func(const A& xxx);
            ...;
        }
        
        // 4.类外实现 友元成员函数
        xxx B::func(const A& xxx) {
            ...;
            ...;
        }
        
        ```
        
    1. 友元类
    
1. 友元特点
    1. 友元不受类中访问权限的限制
    1. 友元破坏了类的 封装性
    1. 不能滥用友元，友元的使用受到限制 (单向、不具备传递性、不能被继承)





## 运算符重载

### 概述

1. 规则
    1. 运算符重载时，其操作数型必须要是 **自定义类型**
    1. 其 **优先级** 和 **结合性** 还是固定不变的
    1. 操作符的 **操作数个数** 是保持不变的 
    1. 运算符重载时，**不能设置默认参数** (如果设置默认值, 其实也就是改变了操作数的个数)
    1. 逻辑与&& / 逻辑或|| 就 **不再具备短路求值特性**，进入函数体之前必须完成所有函数参数的计算，不推荐重载
    1. 不能臆造一个并不存在的运算符

1. 形式
    1. 友元: 不会修改 操作数值的运算符, `xxx& operator+(const xxx&, const xxx&);`; 特例: 输入/出流运算符
       1. **普通友元函数**: 
       2. 友元成员函数 
       3. 友元类

    2. 普通函数

    3. **成员函数**: 修改操作数值的运算符, 如 `+=`; 成员函数存在一个默认参数 `this` 指针



### `+=`

    ```c++
    // += 
    Complex& operator+=(const Complex& ) {};
    ```



### 自增运算符 `++`

```c++
// 前置++, ++i 中 i 的值与 表达式值相同, 故返回值 为引用
// 效率更高, 推荐使用
Complex& operator++() {
++_real;
++_image;
return *this;
};
    
// 后置++, i++ 中 i  的值与 表达式值相同, 故返回值 不用引用
// 参数固定为 int
Complex operator++(int) {
    Complex tmp(*this);
    ++_real;
    ++_image;
    return tmp;
};
```



### 函数调用运算符 `()`

```c++
// 函数调用运算符 (), 第二个 () 填参数
// 重载了 函数调用运算符 的类的对象称为 函数对象
operator()() {
    
}

/*	函数对象相比普通函数的优势
1. 可以携带状态
2. 函数对象可以作为函数参数
3. 函数对象可以有更多的行为：
*/
/*--------------------------------------------------------*/
//	函数也可以看作对象
// 例: 
void func(int);
// fun 类型为 void (*)(int) 的函数指针

typedef void (*Function)(int);
Function p = func;
// 则 p 可以看作一个对象, 它所属的类为 Function
```



### 成员指针访问运算符  `.* / ->*`

```c++
// 成员指针访问运算符  (.* / ->*)

// 成员函数对象
struct FFF {
    void print() {}			// print() 为公有成员函数
}
typedef void (FFF::*MemberFunction)();

// 1 .* 成员指针访问运算符 形式1, 此处右操作数为指针
MemberFunction mf = &FFF::print;	// 此处 & 不能省略
FFF fff;							// 先有对象才能调用非静态成员函数
(fff.*mf)();						// 此处 * 不能省略

// 2 ->* 成员指针访问运算符 形式2, 此处右操作数为指针
// but 当 fp = nullptr 时 仍有可能正常运行(前提: 不访问数据成员)
MemberFunction fo = &FFF::print;
FFF* fp = new FFF();
fp->display();
(fp->*fo)();

// C+中“函数"多种形式：普通函数/函数指针/成员函数/成员函数指针/函数对象
// 将它们统称为可调用实体
```



### 下标访问运算符 `[]`

```c++
// 下标访问运算符 []

// 非 const 对象执行该函数
char& operator[](size_t idx) {
    if (idx < _capacity) {
        return _data[idx];
    } else {
        cout << "..." << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}

// 第 2 个 const 保证成员函数不能改变数据成员, 即 _capacity, _data 本身不能修改, but _data[idx] 可以改
// 第 1 个 const 才真正保证了不能修改 _data[idx]
// const 对象执行该函数
const char& operator[](size_t idx) const {
    if (idx < _capacity) {
        return _data[idx];
    } else {
        cout << "..." << endl;
        static char nullchar = '\0';
        return nullchar;
    }
}
```



### 输入输出流运算符 

```c++
// 输入输出流运算符 
// 不修改数据成员, 推荐友元函数
// but 考虑到 "cout << ...;" 格式, 必须使用 友元函数

ostream& operator<<(ostream& os, const Complex& rhs) {
    os << ...;
}
    
// 输入需要改变有操作数的值, 不加 const
istream& operator>>(istream& is, Complex& rhs) {
    is >> ...;
}

// 为了保证 输入的健壮性, 将上述 is >> ... 替换为 readIn(is, ...)
#include <limits>
void readIn(istream& is, int& num) {
    while (is >> num, !is.eof()) {
        if (is.bad()) {
            cout << "istream has broken!" << endl;
            return;
        } else if (is.fail()) {
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
    }
}
```



### 箭头运算符 `->`

```c++
// 箭头运算符 ->

Data* operator->() {
    return _pdata;
}

// 本质 (ml.operator->())->getData()
MiddleLayer ml(new Data);
ml->getData();    


// ml是一个局部对象，当函数执行完时，一定会被销毁, 就会自动调用析构函数，回收 ml 对象创建的堆上的 Data 对象, 因此可以认为 ml 是一个智能指针的锥形
    
// 智能指针的实现原理：通过对象的生命周期来管理资源。当对象被销毁，一定会自动调用析构函数，只要把析构函数设置好，就不会内存泄漏。

```



### 解引用运算符 `*`

```c++
// 解引用运算符 *
Data& operator*() {
    return *_pdata;
}

// 本质 (ml.operator*()).getData()
MiddleLayer ml(new Data);
(*ml).getData(); 

    
// ml是一个局部对象，当函数执行完时，一定会被销毁, 就会自动调用析构函数，回收 ml 对象创建的堆上的 Data 对象, 因此可以认为 ml 是一个智能指针的锥形
    
// 智能指针的实现原理：通过对象的生命周期来管理资源。当对象被销毁，一定会自动调用析构函数，只要把析构函数设置好，就不会内存泄漏。
```


### 三层箭头 `->`

```c++
// ThirdLayer 重载 ->, 返回值为 MiddleLayer引用 而不是 指针
// 返回值若不加引用, 返回时会复制临时对象, 调用 MiddleLayer 默认拷贝构造(浅拷贝)
// 临时 _pdata 与 _pdata 同时指向 _data, 发生 double free  
MiddleLayer& operator->() {
    return *_ml;
}
    
// 
ThirdLayer tl(new MiddleLayer(new Data));
tl->getData();

// 本质 tl->getData(); 
(tl.operator->())->getData();
((tl.operator->()).opertor())->getData();

```

### 三层 解引用 `*`

```c++
// ThirdLayer 重载 *, 返回值为 MiddleLayer引用
MiddleLayer& operator*() {
    return *_ml;
}
    
// 
ThirdLayer tl(new MiddleLayer(new Data));
(*(*tl)).getData();

// 本质 (*tl).tlgetData(); 
(*(tl.operator*())).getData();
((tl.operator*()).operator*()).getData();


// 优化 ----> 只解引用一次进行 getData 的访问
// ThirdLayer 重载 *, 并将 该函数声明为 MiddleLayer 友元类
Data& operator*() {
    return *(*_ml)._pdata;
}

ThirdLayer tl(new MiddleLayer(new Data));
(*tl).getData();

```

### 类型转换函数

1. 其他类型 向 自定义类型 转换 (隐式转换)  
    先调用构造函数得到临时对象, 再赋值, 表层体现 只调用 赋值函数
2. 自定义类型 向 其他类型 转换
```c++
// 形式: operator 目标类型(){} 
/*  性质
1.成员函数
2.无 参数 / 返回类型 
4.在函数执行体中必须要返回目标类型的变量
*/

// Point ---> int
operator int() {
    return _ix + _iy;
}

// Point ---> Complex
operator Complex() {
    return Complex(_ix, _iy);
}

// 补充 Complex c; Point p; c = p
// 方式 1: Complex 重载 =
// 方式 2: Point 重载 类型转换
// 方式 3: Complex 中 定义 参数为 Point 的构造函数(隐式转换)

// 若 2 / 3 同时存在, 则 优先调用 类型转换, 后调用 特殊构造

// 若 特殊构造 参数无 const, 则 2 / 3 冲突
// 类型转换 参数为 this(即 Point), 特殊构造参数为 const Point& 


```


## 类域

### 全局作用域  
    在函数和其他类定义的外部定义的类（全局位置）称为全局类，绝大多数的C++类是定义在该作用域中，我们在前面定义的所有类都是在全局作用域中，全局类具有全局作用域

### 类作用域
    一个类可以定义在另一类的定义中，这是所谓嵌套类或者内部类


## 继承

### 概述
1. 继承的局限(不能继承)
   1. 构造 / 析构函数
   2. 用户重载的 `operator new` / `delete` 运算符
   3. 用户重载的 `operator=` 运算符
   4. 友元关系

2. 派生(继承)方式
   1. `public` 公有继承
   2. `protected` 保护型继承
   3. `private` 私有继承 
3. fdfs
4. 


### 1.吸收基类的成员

### 2.改造基类的成员

### 3.添加自己新的成员

































