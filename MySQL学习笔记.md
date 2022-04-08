# MySQL 学习笔记

## 0. MySQL 基础知识

### SQL 语句分类
1. DQL 数据查询语句 select
2. DML 数据操作语句 insert delete update
3. DDL 数据定义语句 create drop alter
4. TCL 事务控制语句 rollback commit
5. DCL 数据控制语句 grant revoke

### MySQL 常见命令

1. source D:\bjpowernode.sql  导入数据库
2. desc <tablename>  show columns from <tablename> 查表的结构
3. SQL语句注释用 #

## DQL select 


**单表查询**

select * from * where * group by * having * order by * limit *
1. distinct 去重 对所有的列都起作用
2. limit 5 / limit 5, 5 
3. order by \<colname\>  可以多列 升序 asc 降序 desc
4. where 注意筛选出 null `select * from * where * is null`
    - null 参加数学运算会使表达式结果为 null
    - in (val1, val2) 指定搜索范围
    - not 支持对 in between exists 取反
    - like 模糊查询 不要把通配符使用在字符串的开头
        - '%'匹配任意字符串  包括 0 个字符
        - '_'匹配任意字符
5. where 过滤行 having 过滤分组

5. 字段拼接 concat() 去除空格 trim()
### mysql 正则表达式
1. regexp 指定正则表达式
    - .表示任一字符 
    - | 或 
    - 匹配特定字符 [123] 匹配 1 或 2 或 3
    - ^ 取反
    - -指定匹配范围 [1-9] [a-z]
    - 匹配特殊字符 \ \\.
2. binary 区分大小写    
3. 匹配字符类

### 单行处理函数
1. upper, lower 大小写
2. substr(str,起始下标,长度) 下标从 1开始
3. trim 去除首尾空格
4. str_to_date '%Y-%m-%d' 不需要使用 
    str_to_date('02-20-1981','%Y-%m-%d)
    date_format  %Y-%m-%d %h:%i:%s
    str_to_date 用于存数据 
    date_format 用于读数据
5. format(num,2) 加入千分位 可以保留小数
6. round  四舍五入
7. rand() 0~1 的随机数
8. isnull() 
9. case...when...then...else...end

### 多行处理函数 max,min,count,avg,sum
    多行处理函数不能出现在 where 后

### 分组查询 group by ... having
    select 后只能带 分组函数和参与分组的字段

**多表查询** 
1. 内连接 join ... on
2. 外连接 (left/right) join ... on

# 子查询
    嵌套select语句 可在select, from, where语句后

# union 合并集合
    要求查询的字段个数相同

# limit 分页
    limit 起始页码,页码长度 起始页码从0开始

## DDL create,drop,alter
    # create 
    1. 
    create table <tablename>(
        columnName dataType(length);
        columnName dataType(length);
    );
    2. 表复制
    create table <tablename> as select * from <tablename>;
    3. 默认值 字段后面加 default

    # drop
    drop table if exists <tablename>;

    # alter 增加,修改,删除表结构
    alter table <tablename> add columnName dataTypr(length);
    alter table <tablename> molify columnName dataTypr(length); % 改长度
    alter table <tablename> change oldcolumnName newcolumnName dataTypr(length); % 改字段
    alter table <tablename> drop columnName; % 

## DML insert,update,delete
    # insert into <tablename>
    1. insert into <tablename> (columnname,...) values(...,...);
    2. 将查询的数据直接放到已经存在的表中
    insert into emp_insert select * from emp where sal=3000;

    # update <tablename> set
    update <tablename> set <columnname1>='修改的值',... where...;

    # delete from <tablename>
    delete from <tablename> where...;

    # update,delete 都要加 where语句,否则就是对全表操作

    # 插入日期
    1. 按默认格式直接插入 '%Y-%m-%d'
    2. str_to_date
    3. now()

## constraint 
    # 分类
    1. not null 非空 直接加到字段后
    2. unique 唯一
    3. primary key 标识记录的唯一性
    4. foreign key
        constraint foreign key (column_name) reference <table_name> (colomn_name) 
        必须为 <table_name> 的主键

    1. 在表table_constraint查看约束
    select * from table_constraint where table_name=<tablename>;
    2. 约束分为列级约束,表级约束
        列级约束,直接加到字段后
        表级约束
        constraint <constraint_name>  constraint_type (column_name);
    3. 修改约束和修改字段语法一样 alter table <table_name> add/drop...

    # 级联更新,级联删除 on update/delete cascade
        先删除约束,再添加约束

## 存储引擎
    # 常用命令
    show engines\g 显示当前服务器支持哪些存储引擎

    # 常用存储引擎
    ## MyISAM 存储引擎 （最常用，适合大量数据读，少量数据更新）
    用格式文件（存储表结构） 数据文件（存储表数据） 索引文件 （存储索引）表示每个表
    可被转换成压缩 只读表来节省空间
    ## InnoDB存储引擎 （缺省，适合多的数据更新）
    支持事务
    支持外键及引用 级联删除和更新
    ## MEMORY存储引擎
    存储在内存中
    
## 事务
    # 
    事务（Transaction)
    开启事务（start transaction)
    回滚事务（rollback）
    提交事务（commit）
    set autocommit（禁用或启用事务的自动提交模式）
    # 只能回滚insert,delete,update语句 不能回滚select（无意义） create drop alter(无法回滚)
    # 自动提交模式
    # 多个客户端并发的访问一个表时，可能出现下面的一致性问题
    ## 脏读 
    一个事务开始读取某行数据 但是另外一个事务已经更新此数据但是没有及时提交
    ## 不可重复读 
    同一个事务，同一个读操作对同一个数据的前后两次读取产生不同的结果
    ## 幻像读
    同一个事务以前没有的行 由于其他事务的提交而出现的新行
    # 四个隔离级别
    ## 读未提交（read umcommitted)
    允许一个事务可以看到其他事务未提交的修改
    ## 读已提交（read committed）
    允许一个事务只能看到其他事务已经提交的修改，未提交的修改是看不见的
    ## 可重复读 （repeatable read)
    确保在一个事务执行两次相同的select语句 都能得到相同的结果
    ## 序列化（serializable)
    将一个事务与其他事务完全隔离



## 索引
    # MyISAM InnoDB 采用B+树作为索引结构
    # 主键 unique都会默认添加索引
    # 什么时候需要给字段添加索引
        1. 表中该字段数据量庞大
        2. 经常被检索 出现在where后
        3. 经常被DML的字段不建议添加索引
    #
    创建索引
        1. create unique index 索引名 on 表名（列名）
        2. alter table 表名 add unique index 索引名（列名）
    查看索引
    使用索引
    删除索引

## 视图

## DEA命令

## 设计范式
    
# 原理
## 基础架构
- Server
    - 连接器 建立、管理连接、权限认证
    - 分析器 词法分析、语法分析
    - 优化器 执行计划生成、索引选择（多个索引，选择索引，多个连接，选择连接）
    - 执行器 检查权限、操作引擎、返回结果
- 存储引擎 存储数据、提供读写接口
    - InnoDB
    - MyISAM
    - Memory
## 日志系统
- redo log InnoDB独有 binlog 是Mysql Server层实现的，所有引擎都可以使用
- redo log 物理日志 "在某个数据页上做了什么修改“
    binlog 逻辑日志 记录原始逻辑 ”给id = 2这一行的c字段加1“
- redo log 循环写 空间固定会用完 binlog 可以追加写入

0. 找到需要更新的行
1. 更新操作记录到redo log中， redo log处于prepare状态
2. 生成更新操作的binlog 写入磁盘
3. redo log改成commit状态，更新完成

## 事务隔离
事务特性 ACID
- 原子性
- 一致性
- 隔离性
- 持久性
多个事务同时执行时，可能出现的问题
- 脏读
- 不可重复读
- 幻读
事务隔离级别
- 读未提交 直接返回记录上的最新值
- 读已提交 在每个**SQL语句开始执行**时创建一个视图，访问结果以视图结果为准
- 可重复读 在**事务启动**时创建一个视图，访问结果以视图结果为准
- 串行化 加锁

## 索引
常见模型
- 哈希表 只适用 等值查询
- 有序数组 适用 等值查询、区间查询 更新数据效率低 只适用静态存储
- 平衡二叉树  -> 平衡多叉树 **为了减少磁盘寻址时间**
- 跳表
- LSM树
InnoDB索引模型B+树
- 主键索引 聚簇索引  叶子节点存的是整行数据
- 非主键索引 二级索引 叶子节点存的是主键的值
基于非主键索引的查询需要多扫描一颗索引树

覆盖索引  
`select * from T where k between 3 and 5`  检索 k 索引树3次 回表两次
`select ID from T where k between 3 and 5` 检索 k 索引树 3 次 不需要回表

最左前缀原则

索引下推  
在索引遍历过程中，对索引中包含的字段先做判断，直接过滤掉不满足条件的记录，减少回表次数

## 锁
分类
- 全局锁  
    - 整个数据库加锁 处于只读状态 flush tables with read lock
    - 适用场景 全库逻辑备份
    - 官方自带逻辑备份工具 mysqldump 使用参数-single-transaction 导入数据之前就会启动一个事务 确保拿到一致性视图
- 表级锁
- 行锁


 
