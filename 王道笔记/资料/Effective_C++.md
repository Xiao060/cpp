# Effective C++

## 让自己习惯 C++

### 01. 视 C++ 为一个语言联邦 (C、Object-Oriented C++、Template C++、STL)

### 02. 宁可以编译器替换预处理器 (尽量以 `const`、`enum`、`inline` 替换 `#define`)

### 03. 尽可能使用 const

1. const 分类

    1. bitwise / physical constness (位/物理 常量)

        编译器使用的方式

    2. logical constness (逻辑常量)

    3. 避免 非 const 成员函数 与 const 成员函数 的代码重复, 可以使用 非 const 函数 调用 const 函数, 但是需要进行两次类型转换

        ```c++
        class Test {
        public:
            const char& operator[](size_t index) const {
                return ...;
            }

            char& operator[](size_t index) {
                return const_cast<char&> (static_cast<const Test&>(*this)[index])
            }
           
        private:
            char* _s;
        };            
        ```

2. [mutable](https://poe.com/s/yhMiwew5NK6WIUq3dBjW) 修饰类的成员变量, 使其在 const 成员函数中也可以修改

### 04. 确定对象被使用前已先被初始化

1. 类的构造函数 注意区分 **初始化(列表)** 与 **赋值**, 初始化列表性能 优于 赋值;  

2. 如果 成员变量类型为 内置类型, 其 初始化 与 赋值的性能相同, 但推荐初始化

3. 如果 数据成员 为 `const` / `references`, 则必须使用 初始化列表

4. 基类 先于 派生类 被初始化

5. 类内的数据成员以 **声明次序** 初始化

## 构造/析构/赋值运算

### 05. 了解 C++ 默默编写并调用哪些函数

1. 无参构造

2. 拷贝构造

3. 析构函数

4. 赋值运算符函数

    1. 若 数据成员 为 <mark>引用 / const</mark>, 则不会生成 默认的 赋值运算符函数

    2. 若 基类的 赋值运算符函数 <mark>私有</mark>, 则 派生类不会生成 默认的 赋值运算符函数

### 06. 若不想使用编译器自动生成的函数, 就应该明确拒绝 <div id="06" ></div>

若 不想 使用 拷贝 / 赋值函数

1. 将 拷贝 / 赋值 函数 声明 为私有, 并且不需要实现;  
    若使用 会导致 连接错误;

2. 创建一个 不含数据成员的基类, 将其 拷贝 / 赋值 函数设为 <mark>私有</mark>, 并用自己的类 继承它;  
    若调用, 会在编译期出错;  
    but 可能导致多重继承

### 07. 为多态基类声明 virtual 析构函数

1. 如果 基类 的析构函数 为 非 virtual, 且使用 基类指针 指向 派生类对象时, `delete 指针` 会导致 派生类的堆上空间泄漏

2. 若将 基类的析构函数 设为 virtual, 则 `delete 指针` 时 因为 多态 会调用派生类的析构函数;  

    派生类析构函数执行过程:

    1. 派生类析构函数

    2. 成员子对象析构函数

    3. 基类子对象析构函数, 其 执行顺序 与 继承顺序 相反

3. 若 基类析构函数设为 virtual, 则 基类 所占空间 需要包含 <mark>vfptr(虚函数指针)</mark>;  

    其指向 <mark>vtable(虚函数表)</mark>, 虚表中储存 虚函数人口地址

4. 若 class 不被其他类 继承, 则 为了 节省空间 不建议设置 virtual 析构函数

5. 若 class 含有任何 virtual 函数, 析构函数 也应设为 virtual

6. 因为 STL 的析构函数均为 非 virtual 类型, 所以 安全起见 不要继承 STL 或 其他含有 非 virtual 析构 的类

### 08. 别让异常逃离析构函数 <mark>????</mark>

1. 析构函数应该吞下不传播异常, 或者结束程序, 而不是吐出异常

2. 如果要处理异常应该在非析构的普通函数处理

    ![](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202310012138526.png)

### 09. 绝不在构造和析构过程中调用 virtual 函数

1. 调用 派生类构造函数 函数时 会先调用 基类构造构造函数, 因为此时 派生类还未构造完成, 所以此时的 virtual 还不是 虚函数, 或者说 此时的 **对象类型是 基类**, 所以执行的 virtual 函数 其实是 基类的 函数

2. 执行 虚构函数时 也是一样, 先调用 派生类析构函数, 然后调用成员子对象析构函数, 最后调用 基类子对象析构函数; 析构函数 执行时 会先确定它的 对象类型, 若在 基类析构函数中 执行 virtual 函数, 则执行的是 基类的 虚函数

3. 故 应该确保 构造函数 / 析构函数 内 不要 **直接 / 间接** 调用 virtual 函数

4. 若 需要在 构造期间记录日志, 则 日志函数不要设为 virtual, 且 日志信息 直接由 派生类传递给 基类的 构造函数(派生类初始化列表), 基类在构造函数中调用 日志函数

   ![](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202310012206436.png)

### 10. 令 `operator=` 返回一个 `reference to *this`  

1. 目的是为了使其支持 连锁赋值, 及 `a = b = c = 15;`

2. 不仅适应于 `=` 而且适用于 `+= / -= / *= / ...`

### 11. 在 `operator=` 中处理 自我赋值

1. 赋值运算符 时 考虑 自我复制, 即加入 **等同测试** `this != &rhs`, 此处可保证 自我复制的安全性;  
    but new 可能导致 异常安全性 问题

2. 使用 copy and swap 可以解决 异常安全性 问题

    ![](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202310012328943.png)

### 12. 赋值对象时应确保复制 “对象内的所有成员变量” 及 “所有 base class 成分”

1. 派生类对象 构造函数中 若没有 显式调用 基类构造, 则会隐式调用 基类的默认构造函数(不推荐);  

    若 基类的默认构造函数 不存在 / 私有, 则报错

2. 复制运算符函数同理, 建议 手动调用 基类的 赋值运算符函数

## 资源管理

### 13. 以对象管理资源 (RAII)

1. 获得资源后 立刻放入 管理对象 (`auto_ptr / shared_ptr`)

2. 管理对象 运用析构确保 资源被释放

3. `auto_ptr` 在代码层面存在缺陷, 当执行 拷贝 / 赋值 时会发生 **资源所有权** 的转移

4. `unique_ptr` 是 <mark>独享所有权</mark> 的智能指针, 支持对象语义(不允许 拷贝 / 赋值) 与 移动语义

5. `shared_ptr` 是 <mark>共享所有权</mark> 的智能指针, 支持值语义(拷贝 / 赋值) 与 移动语义;  

    原理: 引用计数  

    but 循环引用会出现 <mark>内存泄漏</mark>

6. 智能指针 析构函数 默认执行 `delete ...` 操作;  

    若 资源储存在数组中, 建议使用 vector 等 STL;  

    若 资源释放方式 不为 delete, 例 `f.close()`, 需要自定义 <mark>删除器</mark>(auto_ptr 不存在);  

    [自定义删除器](https://poe.com/s/iCsv48AzrkR8USqSQvsN) 可以通过 **函数 / 函数对象(重载了函数调用运算符) / lambda** 实现  

### 14. 在资源管理类中小心 copying 行为

1. 复制 RAII 对象必须一并复制它所管理的资源, 故资源的 copying 行为决定 RAII 对象的 copying 行为

2. RAII 常采用的 复制行为:

    1. 禁止拷贝 (设为私有 / 继承 uncopyable 类, 见 [06](#06))

    2. 引用计数 (shared_ptr)

    3. 深度拷贝 (资源为字符串)

    4. 转移 资源所有权 (类似 auto_ptr)

### 15. 在资源管理类中提供对原始资源 (raw resources) 的访问

1. 往往 需要在 资源管理类(智能指针)外 访问原始资源

    1. 显式转换, 例 shared_ptr 的 get 函数 (<mark>推荐</mark>)

    2. 隐式转换, 例 自定义类型转换函数, `xxxx operator xxxx() const { ...; }` ()

### 16. 成对使用 new 和 delete 时要采取相同形式

![](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202310082018683.png)

1. `new` 步骤

    1. 使用 `operator new` 申请空间, 空间未被 **类型化**, 底层 调用 `malloc`

    2. 调用 **构造函数 初始化**数据成员

    3. 返回 相应类型的 指针

2. `delete` 步骤

    1. 调用析构函数, 回收 数据成员 申请的资源 (堆空间)

    2. 使用 `operator delete` 回收对象所占空间, 底层 `free`

3. `new` 中使用 `[]` 则 `delete []`  
    `new` 中无 `[]` 则 `delete`

### 17. 以独立语句将 newed 对象存储于 (置入) 智能指针

1. 例 `func(shared_ptr<xxxx>, yyyy);`

    1. 该语句分为 3 部分, 但是 执行顺序未定

        - `xxxx` 的构造

        - `shared_ptr` 的构造

        - `yyyy` 的构造

    2. 若 `xxxx` 构造完成后, 执行 `yyyy` 出错, 则 可能导致 `xxxx` 的资源泄漏

2. 建议 将 `shared_ptr(xxxx)` 写成一条独立语句

## 设计与声明

### 18. 让接口容易被正确使用, 不易被误用

1. 正确 使用

    1. 保持接口的一致性

        例 `STL` 都具有 `size()` 等接口

2. 阻止 误用

    1. 防止 使用接口时 输入参数 出现乱序的行为, 可以将参数设为不同的 自定义类型, 即 <mark>外覆类型</mark> (wrapper types)

        例: `func(int year, int month, int day);` 改为 `func(Year(2023), Month(12), Day(15));`

    2. 防止 使用接口时 输入参数 出现 无效值行为, 可以 使用 <mark>类内静态函数</mark> **预先定义有效的值**

        ```c++
        class Month {
        public:
            static Month Jan() { return Month(1); }
            ...;

        private:
            explicit Month(int m);
        };

        // 使用接口
        func(Year(2023), Month::Jan(), Day(15));
        ```

    3. 当函数 返回 堆上数据的指针时, 为避免资源泄漏, 建议返回 <mark>智能指针</mark>

        例: `xxx* func();` 改为 `shared_ptr<xxx> func();`

    4. 通过 `const` 限制 返回值类型, 防止 对 返回值 赋值

        例: `const xxx operator*();` 防止 对 `a * b` 进行赋值

### 19. 设计 class 犹如设计 type

1. 创建、销毁 (new / new [] / delete / delete [])

2. 初始化、赋值 (拷贝构造 / 赋值运算符函数)

3. 值传递

4. 合法值 (错误检查)

5. 继承关系

    1. 继承其他类

    2. 被其他类继承, 需要 将 析构函数 设为 `virtual`

6. 隐式转换

7. 一般化

### 20. 宁以 pass-by-reference-to-const 替换 pass-by-value

前者通常更高效、避免切割问题 (slicing problem) , 但不适用于内置类型、STL迭代器、函数对象)

### 21. 必须返回对象时, 别妄想返回其 reference (绝不返回 pointer 或 reference 指向一个 local stack 对象, 或返回 reference 指向一个 heap-allocated 对象, 或返回 pointer 或 reference 指向一个 local static 对象而有可能同时需要多个这样的对象。)

### 22. 将成员变量声明为 private (为了封装、一致性、对其读写精确控制等)

### 23. 宁以 non-member、non-friend 替换 member 函数 (可增加封装性、包裹弹性 (packaging flexibility) 、机能扩充性)

### 24. 若所有参数 (包括被this指针所指的那个隐喻参数) 皆须要类型转换, 请为此采用 non-member 函数

### 25. 考虑写一个不抛异常的 swap 函数

## 实现

### 26. 尽可能延后变量定义式的出现时间 (可增加程序清晰度并改善程序效率)

### 27. 尽量少做转型动作 (旧式：`(T)expression`、`T(expression)`；新式：`const_cast<T>(expression)`、`dynamic_cast<T>(expression)`、`reinterpret_cast<T>(expression)`、`static_cast<T>(expression)`、；尽量避免转型、注重效率避免 dynamic_casts、尽量设计成无需转型、可把转型封装成函数、宁可用新式转型)

### 28. 避免使用 handles (包括 引用、指针、迭代器) 指向对象内部 (以增加封装性、使 const 成员函数的行为更像 const、降低 “虚吊号码牌” (dangling handles, 如悬空指针等) 的可能性)

### 29. 为 “异常安全” 而努力是值得的 (异常安全函数 (Exception-safe functions) 即使发生异常也不会泄露资源或允许任何数据结构败坏, 分为三种可能的保证：基本型、强列型、不抛异常型)

### 30. 透彻了解 inlining 的里里外外 (inlining 在大多数 C++ 程序中是编译期的行为；inline 函数是否真正 inline, 取决于编译器；大部分编译器拒绝太过复杂 (如带有循环或递归) 的函数 inlining, 而所有对 virtual 函数的调用 (除非是最平淡无奇的) 也都会使 inlining 落空；inline 造成的代码膨胀可能带来效率损失；inline 函数无法随着程序库的升级而升级)

### 31. 将文件间的编译依存关系降至最低 (如果使用 object references 或 object pointers 可以完成任务, 就不要使用 objects；如果能够, 尽量以 class 声明式替换 class 定义式；为声明式和定义式提供不同的头文件)

## 继承 与 面向对象设计

### 32. 确定你的 public 继承塑模出 is-a (是一种) 关系 (适用于 base classes 身上的每一件事情一定适用于 derived classes 身上, 因为每一个 derived class 对象也都是一个 base class 对象)

### 33. 避免遮掩继承而来的名字 (可使用 using 声明式或转交函数 (forwarding functions) 来让被遮掩的名字再见天日)

### 34. 区分接口继承和实现继承 (在 public 继承之下, derived classes 总是继承 base class 的接口；pure virtual 函数只具体指定接口继承；非纯 impure virtual 函数具体指定接口继承及缺省实现继承；non-virtual 函数具体指定接口继承以及强制性实现继承)

### 35. 考虑 virtual 函数以外的其他选择 (如 Template Method 设计模式的 non-virtual interface (NVI) 手法, 将 virtual 函数替换为 “函数指针成员变量”, 以 `tr1::function` 成员变量替换 virtual 函数, 将继承体系内的 virtual 函数替换为另一个继承体系内的 virtual 函数)

### 36. 绝不重新定义继承而来的 non-virtual 函数

### 37. 绝不重新定义继承而来的缺省参数值, 因为缺省参数值是静态绑定 (statically bound) , 而 virtual 函数却是动态绑定 (dynamically bound)

### 38. 通过复合塑模 has-a (有一个) 或 “根据某物实现出” (在应用域 (application domain) , 复合意味 has-a (有一个) ；在实现域 (implementation domain) , 复合意味着 is-implemented-in-terms-of (根据某物实现出) )

### 39. 明智而审慎地使用 private 继承 (private 继承意味着 is-implemented-in-terms-of (根据某物实现出) , 尽可能使用复合, 当 derived class 需要访问 protected base class 的成员, 或需要重新定义继承而来的时候 virtual 函数, 或需要 empty base 最优化时, 才使用 private 继承)

### 40. 明智而审慎地使用多重继承 (多继承比单一继承复杂, 可能导致新的歧义性, 以及对 virtual 继承的需要, 但确有正当用途, 如 “public 继承某个 interface class” 和 “private 继承某个协助实现的 class”；virtual 继承可解决多继承下菱形继承的二义性问题, 但会增加大小、速度、初始化及赋值的复杂度等等成本)

## 模板 与 泛型编程

### 41. 了解隐式接口和编译期多态 (class 和 templates 都支持接口 (interfaces) 和多态 (polymorphism) ；class 的接口是以签名为中心的显式的 (explicit) , 多态则是通过 virtual 函数发生于运行期；template 的接口是奠基于有效表达式的隐式的 (implicit) , 多态则是通过 template 具现化和函数重载解析 (function overloading resolution) 发生于编译期)

### 42. 了解 typename 的双重意义 (声明 template 类型参数是, 前缀关键字 class 和 typename 的意义完全相同；请使用关键字 typename 标识嵌套从属类型名称, 但不得在基类列 (base class lists) 或成员初值列 (member initialization list) 内以它作为 base class 修饰符)

### 43. 学习处理模板化基类内的名称 (可在 derived class templates 内通过 `this->` 指涉 base class templates 内的成员名称, 或藉由一个明白写出的 “base class 资格修饰符” 完成)

### 44. 将与参数无关的代码抽离 templates (因类型模板参数 (non-type template parameters) 而造成代码膨胀往往可以通过函数参数或 class 成员变量替换 template 参数来消除；因类型参数 (type parameters) 而造成的代码膨胀往往可以通过让带有完全相同二进制表述 (binary representations) 的实现类型 (instantiation types) 共享实现码)

### 45. 运用成员函数模板接受所有兼容类型 (请使用成员函数模板 (member function templates) 生成 “可接受所有兼容类型” 的函数；声明 member templates 用于 “泛化 copy 构造” 或 “泛化 assignment 操作” 时还需要声明正常的 copy 构造函数和 copy assignment 操作符)

### 46. 需要类型转换时请为模板定义非成员函数 (当我们编写一个 class template, 而它所提供之 “与此 template 相关的” 函数支持 “所有参数之隐式类型转换” 时, 请将那些函数定义为 “class template 内部的 friend 函数”)

### 47. 请使用 traits classes 表现类型信息 (traits classes 通过 templates 和 “templates 特化” 使得 “类型相关信息” 在编译期可用, 通过重载技术 (overloading) 实现在编译期对类型执行 if...else 测试)

### 48. 认识 template 元编程 (模板元编程 (TMP, template metaprogramming) 可将工作由运行期移往编译期, 因此得以实现早期错误侦测和更高的执行效率；TMP 可被用来生成 “给予政策选择组合” (based on combinations of policy choices) 的客户定制代码, 也可用来避免生成对某些特殊类型并不适合的代码)

## 定制 new / delete

### 49. 了解 new-handler 的行为 (set\_new\_handler 允许客户指定一个在内存分配无法获得满足时被调用的函数；nothrow new 是一个颇具局限的工具, 因为它只适用于内存分配 (operator new) , 后继的构造函数调用还是可能抛出异常)

### 50. 了解 new 和 delete 的合理替换时机 (为了检测运用错误、收集动态分配内存之使用统计信息、增加分配和归还速度、降低缺省内存管理器带来的空间额外开销、弥补缺省分配器中的非最佳齐位、将相关对象成簇集中、获得非传统的行为)

### 51. 编写 new 和 delete 时需固守常规 (operator new 应该内涵一个无穷循环, 并在其中尝试分配内存, 如果它无法满足内存需求, 就应该调用 new-handler, 它也应该有能力处理 0 bytes 申请, class 专属版本则还应该处理 “比正确大小更大的 (错误) 申请”；operator delete 应该在收到 null 指针时不做任何事, class 专属版本则还应该处理 “比正确大小更大的 (错误) 申请”)

### 52. 写了 placement new 也要写 placement delete (当你写一个 placement operator new, 请确定也写出了对应的 placement operator delete, 否则可能会发生隐微而时断时续的内存泄漏；当你声明 placement new 和 placement delete, 请确定不要无意识 (非故意) 地遮掩了它们地正常版本)

## 杂项讨论

### 53. 不要轻忽编译器的警告

### 54. 让自己熟悉包括 TR1 在内的标准程序库 (TR1, C++ Technical Report 1, C++11 标准的草稿文件)

### 55. 让自己熟悉 Boost (准标准库)
