time.h

**日期和时间工具**

### 类型

| 类型  | 说明  | 说明  | 例子  |
| --- | --- | --- | --- |
| [tm](https://zh.cppreference.com/w/c/chrono/tm "c/chrono/tm") | `结构体` , 类似 python 中的时间元祖 | int tm_sec 秒, \[0, 59\]<br>int tm_min 分, \[0, 59\]<br>int tm_hour 时, \[0, 59\]<br>int tm_yday 日, \[1, 31\]<br>int tm_mon 月, ==\[0, 11\]==<br>int tm_year 年, ==自1900 年后经过的年份==<br>int tm_wday 一周的第几天, ==\[0, 6\]->\[日, ..., 六\]==<br>int tm_yday 一年的第几天, ==\[0, 365\]==<br>int tm_isdst 夏时令 | 12<br>49<br>15<br>12<br>6<br>123<br>3<br>192<br>0<br>(2023.7.12.15.49.12) |
| [time_t](https://zh.cppreference.com/w/c/chrono/time_t "c/chrono/time t") | `时间戳` , 即从1970年1月1日经过的秒数 | 64bits 整数, win 即为 long long |     |
| [clock_t](https://zh.cppreference.com/w/c/chrono/clock_t "c/chrono/clock t") | 从时点开始的处理器时间类型<br>(typedef) |     |     |
| [timespec](https://zh.cppreference.com/w/c/chrono/timespec "c/chrono/timespec") (C11) | 单位为秒和纳秒的时间<br>(结构体) |     |     |

### [](#)函数

| 函数  | 作用  | 使用方式 |
| --- | --- | --- |
| 时间操纵 |     |     |
| [difftime()](https://zh.cppreference.com/w/c/chrono/difftime "c/chrono/difftime") | 计算时间差 |     |
| [time()](https://zh.cppreference.com/w/c/chrono/time "c/chrono/time") | 返回当前的 `时间戳` , 并将其储存到参数所在位置(参数为==引用型==),<br>返回类型为 time_t (64bit 整数 / long long) | 1\. time_t secs = time(NULL);<br>2\. time_t secs;<br>    time(&secs); |
| [localtime](https://zh.cppreference.com/w/c/chrono/localtime "c/chrono/localtime")<br>[localtime_r](https://zh.cppreference.com/w/c/chrono/localtime "c/chrono/localtime") (C23)<br>[localtime_s](https://zh.cppreference.com/w/c/chrono/localtime "c/chrono/localtime") (C11) | 接收 `time_t` 时间戳(==引用型==), 返回 `tm` 类型的结构体==指针== | time_t secs = time(NULL);<br>tm * time_tm = localtime(&secs); |
| [gmtime](https://zh.cppreference.com/w/c/chrono/gmtime "c/chrono/gmtime")<br>[gmtime_r](https://zh.cppreference.com/w/c/chrono/gmtime "c/chrono/gmtime") (C23)<br>[gmtime_s](https://zh.cppreference.com/w/c/chrono/gmtime "c/chrono/gmtime") (C11) | 接收 `time_t` 时间戳(==引用型==), 返回 `tm` 类型的结构体==指针==<br>(格林尼治标准时间) | 用法同 localtime() |
| [mktime](https://zh.cppreference.com/w/c/chrono/mktime "c/chrono/mktime") | 接收 `tm` 结构体==指针==, 返回 ==time_t== 时间戳, 错误返回 ==-1== |     |
| [clock](https://zh.cppreference.com/w/c/chrono/clock "c/chrono/clock") | 返回未加工的程序启动时开始经过的处理器时间<br>(函数) |     |
| [timespec_get](https://zh.cppreference.com/w/c/chrono/timespec_get "c/chrono/timespec get") (C11) | 返回基于给定时间基底的日历时间<br>(函数) |     |
| [timespec_getres](https://zh.cppreference.com/w/c/chrono/timespec_getres "c/chrono/timespec getres") (C23) | 返回基于给定时间基底的日历时间的分辨率<br>(函数) |     |
| 格式转换(文本显示) |     |     |
| [asctime](https://zh.cppreference.com/w/c/chrono/asctime "c/chrono/asctime") (C23 中弃用)<br>[asctime_s](https://zh.cppreference.com/w/c/chrono/asctime "c/chrono/asctime") (C11) | 将 `struct tm` 对象转换成文本表示<br>(函数) |     |
| [ctime](https://zh.cppreference.com/w/c/chrono/ctime "c/chrono/ctime") (C23 中弃用)<br>[ctime_s](https://zh.cppreference.com/w/c/chrono/ctime "c/chrono/ctime") (C11) | 将 `struct time_t` 对象转换成文本表示<br>(函数) |     |
| [strftime](https://zh.cppreference.com/w/c/chrono/strftime "c/chrono/strftime") | 将 `struct tm` 对象转换成自定义文本表示<br>(函数) |     |
| `<wchar.h>` |     |     |
| [wcsftime](https://zh.cppreference.com/w/c/chrono/wcsftime "c/chrono/wcsftime") (C95) | 将 `struct tm` 对象转换成自定义宽字符文本表示<br>(函数) |     |

### [](#)常量

|     |     |
| --- | --- |
| 在标头 `<time.h>` 定义 |     |
| [CLOCKS\_PER\_SEC](https://zh.cppreference.com/w/c/chrono/CLOCKS_PER_SEC "c/chrono/CLOCKS PER SEC") | 处理器每秒的时间计数<br>(宏常量) |