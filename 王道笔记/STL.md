## set
### 特征
1. 不可重复
2. 默认按照元素进行升序排列
3. 底层实现 红黑树

### 构造
```c++
#include <set>
using std::set;

// 无参构造
set<int> number;

// 列表形式构造
set<int> number = {x, x, x, x, ...};  
    
// 迭代器构造, set<int>::iterator / auto

// 拷贝构造

```

### 遍历
```c++
set<int> number = {x, x, x, x, ...};  

// 迭代器, it 类型为 set<int>::iterator
auto it = number.begin();
while (it != number.end()) {
    xxxxx;
    ++it;
}

// 增强 for 循环, nu 为 int
for (auto& nu : number) {
    xxx;
}
```

### 基本操作
```c++
// 查找出现次数, 存在返回 1, 否则 0
xxx.count();

// 查找出现位置, 存在则返回 指向该元素的迭代器, 否则返回 尾后迭代器(end())
set<int>::iterator it = xxx.find()

/***************************************************************/

// 插入一个元素, 返回值为 pair<set<int>::iterator, bool> 
// 若已存在元素, 则插入失败
// pair 第一项为 指向元素的迭代器, 第二项表示 插入成功/失败
auto ret = xxx.insert(xx); 

// 插入一组元素, 参数为插入元素的 首地址 / 尾后地址
int arr[4] = {1, 2, 3, 4}:
xxx.insert(arr, arr+4);

// 插入列表
xxx.insert({1, 2, 3});

/***********************************************************/

// 不支持下表访问, 但是可以使用迭代器访问
// 不能利用迭代器修改(红黑树), but 可以先移除, 后添加
auto it = number.begin();
*(it + x);

// 移除元素, 参数为迭代器
xxx.erase(it);

```

## pair 
```c++
#include <utility>
using std::pair;

pair<int, string> number = {1, "Wangdao"};

// 接收两个元素, 返回 pair
make_pair()

// 取值
number.first;
number.second;

```

## map

### 特点
   1. 存放 key-value 类型
   2. key 唯一, key 相同则插入失败 (不覆盖)
   3. 默认情况下按照 key 进行排序

### 初始化
```c++
#include <map>
using std::map;

// 根据 key 去重, key 相同则插入失败 (不覆盖)
map<int, string> = {{1, "Hello"},
                    {2, "World"},
                    {3, "Wangdao"},
                    pair<int, string>(4, "hubei"),
                    make_pair(6, "shanghai")};
```

### 遍历 

```c++
// 迭代器, 类型为 map<int, string>::iterator
// it 为指向 pair 的迭代器 
auto it = xxx.begin();
while (it != xxx.end()) {
    it->first;
    it->second;
    ...
    ++it;
}

// 增强 for 循环
for (auto& nu : number) {
    nu.first;
    nu.second;
}

```

### 基本操作
```c++
// 查找出现次数, 参数为 key, 存在返回 1, 否则返回 0
xxx.count(key);

// 查找出现位置, 参数为 key
// 存在返回指向 pair 的 map 迭代器
// 不存在返回 尾后迭代器 (end())
xxx.find(key);

/*************************************************************/

// 插入一个元素
// 返回值为 pair, 类型为 pair<map<int, string>::iterator, bool>
// 第 1 个参数为 指向 pair 的 map 迭代器
// 插入成功, pair 第 1 项为指向插入元素的迭代器
// 插入失败, pair 第 1 项为指向已存在元素的迭代器 ???????
xxx.insert(pair<int, string>(7, "nanjing"));
xxx.insert(make_pair(7, "nanjing"));
xxx.insert({7, "nanjing"});

// 插入一组元素 (迭代器)
xxx.insert(xxx.begin(), xxx.end());

// 插入一组元素 (列表) 
xxx.insert({{x, xxx},
            {x, xxx},
            {x, xxx}});

/***************************************************************/

// 下标取值 (key 存在)
xxx.[key];

// 下标插入/修改 
// key 不存在, 把 key-"" 插入
xxx.[key]
xxx.[key] = value;

```