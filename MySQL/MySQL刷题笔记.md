# 基础知识
1. select 会跳过值为 null 的记录  
[584. 寻找用户推荐人](https://leetcode.cn/problems/find-customer-referee/)
    ```mysql
    select name from customer where referee_id is null or referee_id != 2;
    ```
2. if / case when then hen then end  
[1873. 计算特殊奖金](https://leetcode.cn/problems/calculate-special-bonus/)  
- if(expression1, true, false)
    ```mysql
    SELECT employee_id, IF(employee_id % 2 = 0 || name like 'M%', 0, salary) AS bonus 
    FROM Employees
    ORDER BY employee_id;
    ```
- case when then when then end
    ```
    SELECT employee_id, (case when employee_id % 2 = 1 and name not like 'M%' then salary else 0 end) AS bonus 
    FROM Employees
    ORDER BY employee_id;
    ```
3. 字符串相关函数 concat upper left lower substring   
[1667. 修复表中的名字](https://leetcode.cn/problems/fix-names-in-a-table/)   
    ```
    select user_id, concat(upper(left(name, 1)), lower(substring(name, 2))) as name from Users order by user_id;
    ```
4. group_concat   
[1484. 按日期分组销售产品](https://leetcode.cn/problems/group-sold-products-by-the-date/)
    ```
    SELECT sell_date AS 'sell_date',
        COUNT(DISTINCT product) AS 'num_sold',
        GROUP_CONCAT(DISTINCT product 
            ORDER BY product ASC    #按照字典序排列，升序
            SEPARATOR ',')          #用','分隔
            AS 'products'    #组内拼接
    FROM Activities
    GROUP BY sell_date
    ORDER BY sell_date;
    ;
    ```
5. Datediff  
[1141. 查询近30天活跃用户数](https://leetcode.cn/problems/user-activity-for-the-past-30-days-i/)
    ```
    select activity_date as day, count(distinct user_id) as active_users 
    from Activity 
    where activity_date < "2019-07-27" and Datediff("2019-07-27", activity_date) < 30 
    group by activity_date;
    ```


