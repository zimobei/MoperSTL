# STL学习总结

## 前言

本项目为简易的 STL 库

由于C++ 的 STL 库内容较多，实现起来十分的苦难，因此本项目在实现过程中进行了许多参考：

[MyTinySTL]: https://github.com/Alinshans/MyTinySTL
[cppreference]: https://zh.cppreference.com/w/cpp
[侯捷-STL和泛型编程]: #

## 概念

C++ STL（standard Template Library）作为 C++  的标准模板库，有着良好的复用性、高性能等优点。

> 只是需要注意的是，尽管 C++ 是一种面向对象 OOP 的编程语言，但为了降低各个组件间的耦合度，使各个组件的使用更加灵活， STL 的内部实现使用了大量的泛型编程 GP 的编程思想

## 六大组件

- 算法：各种功能函数，负责处理数据
- 仿函数：本质为 struct / class，但可以通过 operator() 等操作符实现函数功能
- 容器：各种数据结构，负责存放数据
- 迭代器：连接容器与算法的桥梁
- 适配器：负责修饰容器或仿函数或迭代器接口
- 空间分配器：负责内存的配置与管理

## algorithm.h

此头文件实现的算法有：

| **不修改序列的操作**                                         |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| all_of                                                       | 检查一定范围之内，是否全部元素使得谓词为true (函数模板)      |
| any_of                                                       | 检查一定范围之内，存在元素使得谓词为true (函数模板)          |
| none_of                                                      | 检查一定范围之内，不存在元素使得谓词为true (函数模板)        |
| for_each                                                     | 将一个函数应用于某一范围的元素 (函数模板)                    |
| count  count_if                                              | 返回满足指定判别的元素数 (函数模板)                          |
| mismatch                                                     | 查找两个范围第一个不同元素的位置 (函数模板)                  |
| equal                                                        | 确定两个元素集合是否是相同的 (函数模板)                      |
| find                                                         | 查找满足特定条件的第一个元素 (函数模板)                      |
| find_if                                                      | 查找满足特定条件的第一个元素 (函数模板)                      |
| find_if_not                                                  | 查找满足特定条件的第一个元素 (函数模板)                      |
| find_end                                                     | 查找一定范围内最后出现的元素序列 (函数模板)                  |
| find_first_of                                                | 查找元素集合中的任意元素 (函数模板)                          |
| adjacent_find                                                | 查找彼此相邻的两个相同（或其它的关系）的元素 (函数模板)      |
| search                                                       | 查找一个元素区间 (函数模板)                                  |
| search_n                                                     | 在区间中搜索连续一定数目次出现的元素 (函数模板)              |
| **修改序列的操作**                                           |                                                              |
| copy  copy_if                                                | 将某一范围的元素复制到一个新的位置 (函数模板)                |
| copy_n                                                       | 复制一定数目的元素到新的位置 (函数模板)                      |
| copy_backward                                                | 按从后往前的顺序复制一个范围内的元素 (函数模板)              |
| move                                                         | 将某一范围的元素移动到一个新的位置 (函数模板)                |
| move_backward                                                | 按从后往前的顺序移动某一范围的元素到新的位置 (函数模板)      |
| fill                                                         | 将一个值赋给一个范围内的元素 (函数模板)                      |
| fill_n                                                       | 将一个值赋给一定数目的元素 (函数模板)                        |
| transform                                                    | 将一个函数应用于某一范围的元素 (函数模板)                    |
| generate                                                     | 赋值相继的函数调用结果给范围中的每个元素 (函数模板)          |
| generate_n                                                   | 赋值相继的函数调用结果给范围中的 N 个元素 (函数模板)         |
| remove                                                       | 移除满足特定标准的元素 (函数模板)                            |
| remove_if                                                    | 移除满足特定标准的元素 (函数模板)                            |
| remove_copy                                                  | 复制一个范围内不满足特定条件的元素 (函数模板)                |
| remove_copy_if                                               | 复制一个范围内不满足特定条件的元素 (函数模板)                |
| replace                                                      | 将所有满足特定条件的元素替换为另一个值 (函数模板)            |
| replace_if                                                   | 将所有满足特定条件的元素替换为另一个值 (函数模板)            |
| replace_copy                                                 | 复制一个范围内的元素，并将满足特定条件的元素替换为另一个值 (函数模板) |
| replace_copy_if                                              | 复制一个范围内的元素，并将满足特定条件的元素替换为另一个值 (函数模板) |
| swap                                                         | 交换两个对象的值 (函数模板)                                  |
| swap_ranges                                                  | 交换两个范围的元素 (函数模板)                                |
| iter_swap                                                    | 交换两个迭代器所指向的元素 (函数模板)                        |
| reverse                                                      | 将区间内的元素颠倒顺序 (函数模板)                            |
| reverse_copy                                                 | 将区间内的元素颠倒顺序并复制 (函数模板)                      |
| rotate                                                       | 将区间内的元素旋转 (函数模板)                                |
| rotate_copy                                                  | 将区间内的元素旋转并复制 (函数模板)                          |
| random_shuffle                                               | 将范围内的元素随机重新排序 (函数模板)                        |
| unique                                                       | 删除区间内连续重复的元素 (函数模板)                          |
| unique_copy                                                  | 删除区间内连续重复的元素并复制 (函数模板)                    |
| **划分操作**                                                 |                                                              |
| is_partitioned                                               | 判断区间是否被给定的谓词划分 (函数模板)                      |
| [partition](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-partition.html) | 把一个区间的元素分为两组 (函数模板)                          |
| [partition_copy](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-partition_copy.html) | 将区间内的元素分为两组复制到不同位置 (函数模板)              |
| [stable_partition](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-stable_partition.html) | 将元素分为两组，同时保留其相对顺序 (函数模板)                |
| [partition_point](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-partition_point.html) | 定位已划分的区域的划分点 (函数模板)                          |
| **排序操作**                                                 |                                                              |
| [is_sorted](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-is_sorted.html) | 检查区间元素是否按升序排列 (函数模板)                        |
| [is_sorted_until](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-is_sorted_until.html) | 找出最大的已排序子范围 (函数模板)                            |
| [sort](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-sort.html) | 将区间按升序排序 (函数模板)                                  |
| partial_sort                                                 | 将区间内较小的N个元素排序 (函数模板)                         |
| [partial_sort_copy](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-partial_sort_copy.html) | 对区间内的元素进行复制并部分排序 (函数模板)                  |
| stable_sort                                                  | 将区间内的元素排序，同时保持相等的元素之间的顺序 (函数模板)  |
| [nth_element](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-nth_element.html) | 将给定的区间部分排序，确保区间被给定的元素划分 (函数模板)    |
| **二分搜索操作（在已排序范围上）**                           |                                                              |
| [lower_bound](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-lower_bound.html) | 返回指向第一个不小于给定值的元素的迭代器 (函数模板)          |
| [upper_bound](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-upper_bound.html) | 返回指向第一个大于给定值的元素的迭代器 (函数模板)            |
| [binary_search](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-binary_search.html) | 判断一个元素是否在区间内 (函数模板)                          |
| [equal_range](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-equal_range.html) | 返回匹配特定键值的元素区间 (函数模板)                        |
| **集合操作（在已排序范围上）**                               |                                                              |
| [merge](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-merge.html) | 合并两个已排序的区间 (函数模板)                              |
| [inplace_merge](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-inplace_merge.html) | 就地合并两个有序的区间 (函数模板)                            |
| [includes](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-includes.html) | 如果一个集合是另外一个集合的子集则返回true (函数模板)        |
| [set_difference](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-set_difference.html) | 计算两个集合的差集 (函数模板)                                |
| [set_intersection](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-set_intersection.html) | 计算两个集合的交集 (函数模板)                                |
| [set_symmetric_difference](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-set_symmetric_difference.html) | 计算两个集合的对称差 (函数模板)                              |
| [set_union](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-set_union.html) | 计算两个集合的并集 (函数模板)                                |
| **堆操作**                                                   |                                                              |
| [is_heap](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-is_heap.html) | 检查给定的区间是否为一个堆 (函数模板)                        |
| [is_heap_until](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-is_heap_until.html) | 查找区间中为堆的最大子区间 (函数模板)                        |
| make_heap                                                    | 根据区间内的元素创建出一个堆 (函数模板)                      |
| [push_heap](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-push_heap.html) | 将元素加入到堆 (函数模板)                                    |
| [pop_heap](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-pop_heap.html) | 将堆中的最大元素删除 (函数模板)                              |
| [sort_heap](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-sort_heap.html) | 将堆变成一个排好序的区间 (函数模板)                          |
| **最小/最大操作**                                            |                                                              |
| [max](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-max.html) | 返回两个元素中的较大者 (函数模板)                            |
| [max_element](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-max_element.html) | 返回区间内的最大元素 (函数模板)                              |
| [min](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-min.html) | 返回两个元素中的较小者 (函数模板)                            |
| [min_element](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-min_element.html) | 返回区间内的最小元素 (函数模板)                              |
| [minmax](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-minmax.html) | 返回两个元素中的的较大者和较小者 (函数模板)                  |
| [minmax_element](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-minmax_element.html) | 返回区间内的最小元素和最大元素 (函数模板)                    |
| [lexicographical_compare](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-lexicographical_compare.html) | 如果按字典顺序一个区间小于另一个区间，返回true (函数模板)    |
| [is_permutation](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-is_permutation.html) | 判断一个序列是否为另一个序列的排列组合 (函数模板)            |
| [next_permutation](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-next_permutation.html) | 按字典顺序产生区间内元素下一个较大的排列组合 (函数模板)      |
| [prev_permutation](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-algorithm-prev_permutation.html) | 按字典顺序产生区间内元素下一个较小的排列组合                 |

其中大部分算法的实现并不困难，在此仅对几个算法进行介绍

**inplace_merge**

与 merge 算法不同，inplace_merge 算法需要在原地合并两个有序集合

为了提高性能，此算法需要考虑到是否申请缓冲空间

- 无缓冲空间

  1. 通过二分查找在左侧有序集合中找到第一个大于右侧有序集合第一个元素的元素 first

  2. 通过二分查找在右侧有序集合中找到第一个大于等于左侧有序集合 first 元素的元素 cut

  3. 此时从右侧有序集合的第一个元素到 cut 中的每个元素都一定小于左侧有序集合中 fisrt 右侧的所有元素。

     通过左旋，即可实现该部分的原地合并

  4. 循环重复上述操作

- 有缓冲空间

  - 缓冲空间大于等于左侧有序集合

    1. 将左侧有序集合 copy 到缓冲空间中
    2. 通过 merge 进行合并

  - 缓冲空间大于等于右侧有序集合

    1. 将右侧有序集合 copy 到缓冲空间中
    2. 通过 merge_backward 反向合并两个集合

  - 缓冲空间较小

    1. 将较长的集合分为两部分

    2. 通过二分查找在另一集合中找到大于等于该集合第一部分的元素

    3. 左旋

    4. 由于左右两集合均已排序好，因此在左旋后，左侧的两个小集合一定小于右侧的两个小集合。

       此时递归左右两个小集合进行重复操作，直到其中一侧有序集合小于等于缓冲空间为止

**sort**

C++ 的 sort 算法在总体上采用 快速排序，但快速排序的性能并不稳定。一方面是快速排序在递归时所选用的中间结点可能位于列表中间，也可能位于左侧或右侧，所以最糟情况下，快速排序的递归次数可能达到N次；另一方面是快速排序适合列表元素较多的情况，对于列表元素较少的情况，快速排序并不合适。

因此，sort 算法在整体上使用快速排序，但是在递归过程中，当列表长度较小时，便采用插入排序，当递归层数较多时，采用堆排序

**stable_sort **

stable_sort 与 sort 算法在描述上相差不大，不过是多个了稳定性而已，但在具体实现中，两算法却有着很大的区别

sort 算法采用了快速排序，而快速排序并不具备稳定性，因此并不适合用在 stable_sort 中

在 stable_sort 算法中，为了保证性能，需要考虑到是否申请缓冲内存

- 无缓冲空间
  1. 不断递归，当列表长度较小时，进行插入排序
  2. 对已经进行插入排序的两部分进行合并（同 inplace_merge 的无缓冲空间算法一致）
- 有缓冲空间
  - 列表长度大于缓冲空间长度
    1. 不断递归
  - 列表长度小于等于缓冲空间长度
    1. 以固定长度（16）为一步，对列表中每一步内的元素进行插入排序
    2. 从左到右，依次合并原列表中相邻两个步内有序元素到缓冲空间
    3. 从左到右，依次合并缓冲空间内相邻两个步内有序元素到原列表
    4. 不断重复上述操作，直到列表合并完成

## utility.h

此头文件实现了**pair**与几个常用函数

| **类**                                                       |                                                     |
| ------------------------------------------------------------ | --------------------------------------------------- |
| pair                                                         |                                                     |
| **函数**                                                     |                                                     |
| swap                                                         | 交换两个对象的值 (函数模板)                         |
| [exchange](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-exchange.html) | 以新值替换参数，并返回其先前值 (函数模板)           |
| [forward](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-forward.html) | 转发函数参数 (函数模板)                             |
| move                                                         | 获得右值引用 (函数模板)                             |
| [move_if_noexcept](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-move_if_noexcept.html) | 若移动构造函数不抛出则获得右值引用 (函数模板)       |
| [as_const](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-as_const.html) | 获得到其参数的 const 引用 (函数模板)                |
| [declval](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-declval.html) | 在不求值语境中获取到其参数的引用 (函数模板)         |
| [make_pair](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-pair-make_pair.html) | 创建一个根据参数类型所定义类型的pair对象 (函数模板) |
| [operator==  operator!=  operator<  operator<=  operator>  operator>=](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-pair-operator_cmp.html) | 按字典序比较 pair 中的值 (函数模板)                 |
| [std::swap(std::pair)](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-pair-swap2.html) | 特化 std::swap 算法 (函数模板)                      |
| [std::get(std::pair)](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-pair-get.html) | 访问 pair 的一个元素                                |

## numeric.h

| 函数                                                         |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| accumulate                                                   | 通过计算连续的部分和来计算指定范围中所有元素的总和（包括初始值），或计算通过使用指定二元运算而非求和运算获得的连续部分结果的结果总和。 |
| [adjacent_difference](ms-xhelp:///?method=page&id=f44e205d-d480-4336-b6a6-5af60ced58e3&vendor=Microsoft&topicVersion=140&topicLocale=ZH-CN) | 计算输入范围中每个元素与其前一元素之间的连续差值，并将结果输出到目标范围，或计算将差值运算替换为其他指定二元运算的一般化程序的结果。 |
| [inner_product](ms-xhelp:///?method=page&id=5b14ed8f-a284-442e-863c-7106e670fa5a&vendor=Microsoft&topicVersion=140&topicLocale=ZH-CN) | 计算两个范围的逐元素集乘积的总和并将总和添加到指定初始值，或计算将求和与乘积运算替换为其他指定二元运算的一般化程序的结果。 |
| [iota](ms-xhelp:///?method=page&id=ccde879c-5cf7-4963-bb91-e5455c3edd61&vendor=Microsoft&topicVersion=140&topicLocale=ZH-CN) | 存储一个起始值，从第一个元素开始，在间隔 **[first, last)** 内的每个元素中填充此值的连续递增值 ( **value++**)。 |
| [partial_sum](ms-xhelp:///?method=page&id=65f8180d-5f85-4b6a-bbb5-99bbe776f691&vendor=Microsoft&topicVersion=140&topicLocale=ZH-CN) | 计算输入范围中从第一个元素到第 i  个元素的一系列总和，并在目标范围的第 i  个元素中存储每个总和的结果，或计算将求和运算替换为其他指定二元运算的一般化程序的结果。 |

## functional.h

此算法进实现了几个常用的函数对象

| **算术运算**                                                 |                                 |
| ------------------------------------------------------------ | ------------------------------- |
| [plus](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-plus.html) | 实现x + y的函数对象 (类模板)    |
| [minus](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-minus.html) | 实现x - y的函数对象 (类模板)    |
| [multiplies](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-multiplies.html) | 实现x * y的函数对象 (类模板)    |
| [divides](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-divides.html) | 实现x / y的函数对象 (类模板)    |
| [modulus](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-modulus.html) | 实现x % y的函数对象 (类模板)    |
| [negate](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-negate.html) | 实现-x的函数对象 (类模板)       |
| **比较**                                                     |                                 |
| [equal_to](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-equal_to.html) | 实现x == y的函数对象 (类模板)   |
| [not_equal_to](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-not_equal_to.html) | 实现x != y的函数对象 (类模板)   |
| [greater](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-greater.html) | 实现x > y的函数对象 (类模板)    |
| [less](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-less.html) | 实现x < y的函数对象 (类模板)    |
| [greater_equal](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-greater_equal.html) | 实现x >= y的函数对象 (类模板)   |
| [less_equal](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-less_equal.html) | 实现x <= y的函数对象 (类模板)   |
| **逻辑运算**                                                 |                                 |
| [logical_and](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-logical_and.html) | 实现x && y的函数对象 (类模板)   |
| [logical_or](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-logical_or.html) | 实现x \|\| y的函数对象 (类模板) |
| [logical_not](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-logical_not.html) | 实现!x的函数对象 (类模板)       |
| **逐位运算**                                                 |                                 |
| [bit_and](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-bit_and.html) | 实现x & y的函数对象 (类模板)    |
| [bit_or](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-bit_or.html) | 实现x \| y的函数对象 (类模板)   |
| [bit_xor](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-utility-functional-bit_xor.html) | 实现x ^ y的函数对象 (类模板)    |
| bit_not                                                      | 实现~x的函数对象 (类模板)       |

## array.h

## vector.h

## deque.h

deque 为双向队列，是 queue 与 stack 的容器适配器（ queue 与 stack 均是通过 deque 实现）

## queue.h

## stack.h

## list.h

双向链表

## set.h

c++ 中，set 与 map 底层均是通过红黑树实现（头文件为 __rb_tree.h ）

## map.h

## unordered_set.h

c++ 中，unordered_set 与 unordered_map 底层通过哈希表实现（ __hash_tree.h ）

## unordered_map.h

## basic_string.h

## string.h

## iterator.h

| 迭代器类型                 |                                    |
| -------------------------- | ---------------------------------- |
| input_iterator_tag         | 输入迭代器InputIterator            |
| output_iterator_tag        | 输出迭代器OutputIterator           |
| forward_iterator_tag       | 向前迭代器ForwardIterator          |
| bidirectional_iterator_tag | 双向迭代器BidirectionIterator      |
| random_access_iterator_tag | 随机访问迭代器RandomAccessIterator |

**iterator_traits< Iterator >**

此为迭代器萃取器，负责萃取类型 Iterator 中的 

- iterator_category
- value_type
- difference_type
- pointer
- reference

五种类型

若 Iterator 中不存在这五种类型，则萃取失败



| 迭代器适配器          |
| --------------------- |
| reverse_iterator      |
| back_insert_iterator  |
| front_insert_iterator |
| insert_iterator       |
| move_iterator         |



| **适配器**                                                   |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| make_reverse_iterator                                        | 创建拥有从参数推出的类型的 [std::reverse_iterator](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-reverse_iterator.html) (函数模板) |
| [make_move_iterator](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-make_move_iterator.html) | 创建拥有从参数推出的类型的 [std::move_iterator](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-move_iterator.html) (函数模板) |
| [front_inserter](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-front_inserter.html) | 创建拥有从参数推出的类型的 [std::front_insert_iterator](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-front_insert_iterator.html) (函数模板) |
| [back_inserter](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-back_inserter.html) | 创建拥有从参数推出的类型的 [std::back_insert_iterator](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-back_insert_iterator.html) (函数模板) |
| [inserter](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-inserter.html) | 创建拥有从参数推出的类型的 [std::insert_iterator](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-insert_iterator.html) (函数模板) |
| **非成员函数**                                               |                                                              |
| [operator==  operator!=  operator<  operator<=  operator>  operator>=](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-move_iterator-operator_cmp.html) | 比较底层迭代器 (函数模板)                                    |
| [operator+](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-move_iterator-operator_2B.html) | 令迭代器前进 (函数模板)                                      |
| [operator-](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-move_iterator-operator-.html) | 计算二个迭代器适配器间的距离 (函数模板)                      |
| [operator==  operator!=  operator<  operator<=  operator>  operator>=](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-reverse_iterator-operator_cmp.html) | 比较底层迭代器 (函数模板)                                    |
| [operator+](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-reverse_iterator-operator_2B.html) | 令迭代器前进 (函数模板)                                      |
| [operator-](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-reverse_iterator-operator-.html) | 计算二个迭代器适配器间的距离 (函数模板)                      |
| [operator==  operator!=](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-istream_iterator-operator_cmp.html) | 比较两个 `istream_iterator` (函数模板)                       |
| [operator==  operator!=](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-istreambuf_iterator-operator_cmp.html) | 比较两个 `istreambuf_iterator` (函数模板)                    |
| **操作**                                                     |                                                              |
| [advance](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-advance.html) | 令迭代器前进给定的距离 (函数)                                |
| [distance](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-distance.html) | 返回二个迭代器间的距离 (函数)                                |
| [next](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-next.html) | 令迭代器自增 (函数)                                          |
| [prev](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-prev.html) | 令迭代器自减 (函数)                                          |
| **范围**                                                     |                                                              |
| [begin  cbegin](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-begin.html) | 返回指向容器或数组起始的迭代器 (函数)                        |
| [end  cend](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-end.html) | 返回指向容器或数组结尾的迭代器 (函数)                        |
| [rbegin  crbegin](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-rbegin.html) | 返回指向一个容器或数组的逆向迭代器 (函数)                    |
| [rend  crend](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-rend.html) | 返回容器或数组的逆向尾迭代器 (函数)                          |
| [size](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-size.html) | 返回容器或数组的大小 (函数)                                  |
| [empty](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-empty.html) | 检查容器是否为空 (函数)                                      |
| [data](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-iterator-data.html) | 获得指向底层数组的指针 (函数)                                |

## memory_pool.h

此为自实现内存池，在此用于帮助实现c++ allocator 

其内部实现思路为“哈希桶”

## memory.h



| 分配器                                                       |                                                              |
| ------------------------------------------------------------ | ------------------------------------------------------------ |
| allocator                                                    |                                                              |
| **未初始化存储**                                             |                                                              |
| uninitialized_copy                                           | 将范围内的对象复制到未初始化的内存区域 (函数模板)            |
| [uninitialized_copy_n](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-memory-uninitialized_copy_n.html) | 将指定数量的对象复制到未初始化的内存区域 (函数模板)          |
| [uninitialized_fill](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-memory-uninitialized_fill.html) | 复制一个对象到以范围定义的未初始化内存区域 (函数模板)        |
| [uninitialized_fill_n](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-memory-uninitialized_fill_n.html) | 复制一个对象到以起点和计数定义的未初始化内存区域 (函数模板)  |
| [uninitialized_move](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-memory-uninitialized_move.html) | 移动一个范围的对象到未初始化的内存区域 (函数模板)            |
| [uninitialized_move_n](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-memory-uninitialized_move_n.html) | 移动一定数量对象到未初始化内存区域 (函数模板)                |
| [uninitialized_default_construct](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-memory-uninitialized_default_construct.html) | 在范围所定义的未初始化的内存区域以默认初始化构造对象 (函数模板) |
| [uninitialized_default_construct_n](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-memory-uninitialized_default_construct_n.html) | 在起始和计数所定义的未初始化内存区域用[默认初始化](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-language-default_initialization.html)构造对象 (函数模板) |
| uninitialized_value_construct                                | 在范围所定义的未初始化内存中用[值初始化](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-language-value_initialization.html)构造对象 (函数模板) |
| [uninitialized_value_construct_n](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-memory-uninitialized_value_construct_n.html) | 在起始和计数所定义的未初始化内存区域以[值初始化](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-language-value_initialization.html)构造对象 (函数模板) |
| [destroy_at](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-memory-destroy_at.html) | 销毁在给定地址的对象 (函数模板)                              |
| [destroy](mk:@MSITStore:C:\Users\23362\Desktop\MOPER\编程\C++\API\cppreference-zh-20181014.chm::/chmhelp/cpp-memory-destroy.html) | 销毁一个范围中的对象 (函数模板)                              |
| destroy_n                                                    | 销毁范围中一定数量的对象                                     |
| **杂项**                                                     |                                                              |
| addressof                                                    |                                                              |

## exceptdef.h

此头文件封装了几个常用的异常函数

