## 1 概述

1. 数据库

   功能: DS 持久化存储

   层次: 位于 内存 和 磁盘 之间

   ![](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202308281455924.png)

1. 分类

   按照存储的数据结构: 

   - ==表(关系)==: 由 行 和 列 组成 (使用 SQL 语言) ----------> ==关系==型数据库
   - 不适用表 --------> 非关系型数据库
     - 用户访问量大, 计算机性能弱
     - 业务需求, **时序**数据库 / 图

1. 常见数据库产品

   关系数据库

   -  Oracle 最可靠, 性能最好 ---------> 银行 ------> 昂贵
   - MySQL -------------> c/s 结构
   - PostgreSQL -------> 学术上

   非关系型数据库

   - Redis 内存数据库 ----------> key-valus -------> 缓存系统 6379端口
   - memcache
   - MongoDB ------> 文档

1. xxxx

   - **列**的属性(field, 域)决定表的==结构==
   - **行**对应某一个结构体类型的变量, 即表的==内容==
   - 增删改查 对象是 行
   - 列的操作: 定义
   - 行的操作: 数据操纵
   - 一行的子集是元组
   
1. 二级结构
   - datebase
   - table
   
   
   
   
   
## SQL 结构化查询语言

1. c / c++ 过程式语言

1. SQL ==声明式==语言 -------> 给一般用户设计

   ![](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202308281558568.png)

1. 操作列: 数据定义语言 DDL

1. 操作列: 数据操纵语言 DML

1. 服务端监听 3306 / 33060 端口

   - 命令行客户端
   - 图形化客户端
   - 代码客户端

### 命令行客户端

1. 数据类型

   ```mysql
   // 1.Numeric
   
   // 整数
   int
   
   // 定点数, 以0.01/0.001为单位
   
   // 浮点数
   float
   double
   
   
   // 2.Data and Time 单引号作为界定符
   DATA
   DATATIME
   TIMESTAMP
   
   // 3.String
   CHAR		// 定长字符串   CHAR(1)
   VARCHAR  	// 变长字符串   VARCHAR(10), 10 为上限
   BINARY
   BLOB		// 二进制文件
   TEXT		// 文本大文件
   
   ```

   

1. MySQL 管理命令, 无分号

   ```mysql
   quit
   
   //清理已经输入的命令(输入缓冲区)
   \ c
   
   // 切换当前 database
   use database_name
   
   ```

1. SQL 语句, 分号结尾, 关键字大小写不敏感

   ```mysql
   // 读类型, 返回值为表格
   
   //列出所有数据库
   show databases;
   
   // 创建 database
   create database database_name;
   
   // 列出当前 database
   select database();
   
   // 创建/定义一个表, 表整体属性 主键:primary key(列名)
   create table table_name (列名1 类型 额外属性, 列名2 类型 额外属性, ...., 表整体属性);
   
   // 查看表的详细信息
   describe table_name;
   desc table_name;
   
   
   
   
   
   // 往表中插入一行
   // 1.全部的 列值 都需要写
   insert into table_name values(列1值, 列2值, ...);
   // 2.可以只写部分 列值, 其他 列值 取 默认值
   insert into table_name (列1, 列2, ...) values(列1值, 列2值, ...);
   
   
   
   
   
   
   // 筛选行
   select * from where 条件表达式;
   <> 不等于
   NULL 不参与 比较运算
   时间 / 字符串可以比较大小
   
   // 筛选列
   select 列1, 列2, ... from table_name;
   
   
   // 对 select 结果排序, dec 只会对紧邻的列生效
   select * from table_name where 条件表达式 order by 列1, 列2, ...;
   select * from table_name where 条件表达式 order by 列1, 列2, ... desc;
   
   // 对 select 结果分页(限制显示数量)
   select * from table_name limit 3;
   
   // NULL 空值判断
   is null
   is not null
   
   // 模糊匹配 通配符 wildcard ----> 效率低
   % 任意字符串
   - 任意一个字符
   like
   
   // 聚集函数, 结果不是表的子集, 而是一些统计信息, 在 select 函数之后执行
   // 统计数量, (*) 不统计全为空的行, (列1) 不统计为 null 的列1
   count()
   max()
   min()
   avg()
   // 分组聚集
   group by()
   聚集之后再筛选, 功能类似 where, 只是筛选时机不同
   ... having 选择条件;
   
   
   // 多表连接
   // 1.笛卡尔积
   // 2.内连接, 前提:两个表中有同样的字段, 描述相同的属性
   select ... from table1 inner join table2 on ... 
   // 3.嵌套子查询, 类似 inner join
   select ... from table1 where ... in (select ...)
   // 4.左外连接, 将 左表有 右表无 的显示出来
   select ... from table1 left outer join table2 on ... 
   // 5.右外连接, 将 右表有 左表无 的显示出来
   select ... from table1 right outer join table2 on ... 
   // 6.全连接, mysql 不支持, 需要通过 union 联合
   select ... from table1 left outer join table2 on ... 
   union
   select ... from table1 right outer join table2 on ... ;
   
   
   
   
   
   
   
   // 更新数据, 假如表中存在重复行, update 会影响所有重复行
   update table_name set 列名 = 值 where ... ;
   
   
   
   
   // 删除数据, 性能差, 业务上一般设置一个 tomb(墓碑), 0未删除, 1删除
   delete from table_name where ... ;
   // 删除表, 并新建相同结构的空表, 数据定义语言
   truncate table_name;
   
   
   
   // 调整表的结构, 不建议, 业务上一般新建一个表用来储存新的属性, 或预留列
   // 显示表的信息, 类似 desc
   show creat table table_name;
   // 新增一列
   alter table table_name add (列名 类型, ...);
   // 删除一列
   alter table table_name drop 列名;
   // 修改一列
   alter table table_name change 列名1 列名2 类型;
   
   
   
   // 修改名字
   rename table table_name1 to table_name2;
   
   
   
   
   // 约束, 限制某一列的取值
   // 1.域约束, 只看本列的属性  
   NOT NULL, 数据类型
   // 2.实体约束, 看表中所有行
   // 2.1 unqine key 唯一键, 可以有多个, 用来描述业务中不允许重复的逻辑
   create table table_name (列名1 int 额外属性, 列名2 类型 额外属性, ...., unique key(列名));
   // 2.2 primary key 主键, 可以一列也可以多列, 但一般一列; 且一张表最多一个主键; 主键一般和业务无关, 最好用一个无用整数, 可使用 auto_increment(自动增长)
   create table table_name (列名1 int auto_increment, 列名2 类型 额外属性, ...., primary key(列名1));
   
   
   // .参照约束, 一个表对另一个表的约束
   
   
   
   ```
   
   ![image-20230829104922809](https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/image-20230829104922809.png)

<img src="https://xiao060.oss-cn-hangzhou.aliyuncs.com/md/202308281754862.png" style="zoom:100%;" />



## 安装 MariaDB

```mariadb
sudo pacman -Ss mariadb
sudo pacman -S mariadb

// 启动服务前, 执行
sudo mariadb-install-db --user=mysql --basedir=/usr --datadir=/var/lib/mysql
// 若出错, 则说明 /var/lib/mysql 文件已存在, 需要先删除
sudo rm -rvf /var/lib/mysql


// 启动服务
systemctl start mariadb

// 初始化 安全选项
mariadb-secure-installation

// 切换到 root 用户
su

// 进入 MDB 命令行界面
mariadb
-------------------------------------
// 添加用户密码
create user 'xiao'@'%' identified by 'xiao060';
// 赋予用户权限
grant all privileges on *.* to 'xiao'@'%' with grant option;
// 刷新权限
flush privileges;
// 退出 MDB 命令行
\q
------------------------------------

// 重启服务
systemctl restart mariadb

// 回到普通用户
exit

```



## MySQL 库函数

```c
#include <mysql/mysql.h>

// ubuntu 下载 usr/include/mysql 头文件(函数声明, 结构体定义); 动态库, 静态库(*.so, *.a) 
sudo apt install libmysqlclient-dev
    
// 链接 gcc ... -lmysqlclient

    
    
    
// 申请内存并初始化，参数填 NULL, MYSQL 是 handle (句柄)
MYSQL* mysql_init(NULL);

// 连接到MySQL服务端, 出错返回值为 NULL
MYSQL* mysql_real_connect(MYSQL* mysql, 
                          const char* host, 
                          const char* user, 
                          const char* passwd, 
                          const char* db, 
                          unsigned int port, 
                          const char* unix_socket, 
                          unsigned long client_flag);
/*
host ---------> "localhost" 
user ---------> "root" 
passwd -------> 密码 
db -----------> 数据库名 
port ---------> 0 
unix_socket --> NULL 
client_flag -> 0
*/  
    
// 获取报错原因
const char * mysql_error(MYSQL * mysql);



// 不管数据在 MySQL 是什么类型, 在 c 中全是字符串类型

// 执行SQL语句
int mysql_query(MYSQL* mysql, const char* stmt_str);

// 将查询结果存入 返回值 中, 返回值 底层可以理解为 二维字符数组
MYSQL_RES* mysql_store_result(MYSQL* mysql);

    
/***********************************************************    
  **读完之后必须先执行 mysql_store_result 才能执行下一次 query**
***********************************************************/

// 返回 查询结果的 行数
my_ulonglong mysql_num_rows(MYSQL_RES *result);

// 返回 查询结果的 列数
unsigned int mysql_num_fields(MYSQL_RES *result);

// 从 查询结果 当中取出一行, MYSQL_ROW 字符数组
MYSQL_ROW mysql_fetch_row(MYSQL_RES *result);

// 释放 MYSQL_RES 的内存空间
void mysql_free_result(MYSQL_RES *result);




//关闭 MYSQL 连接
mysql_close(mysql);
```



