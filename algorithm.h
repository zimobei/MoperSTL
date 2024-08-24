#ifndef MOPER_STL_ALGORITHM_H
#define MOPER_STL_ALGORITHM_H

#include <cstring> // memmove()
#include <random> // std::uniform_int_distribution、rand()
#include <initializer_list> // std::initializer_list

#include "type_traits.h"
#include "iterator.h"
#include "utility.h"
#include "functional.h"
#include "memory.h"

namespace MoperSTL {


//***************************************************************
// 
// 
// 不修改序列的操作
// 
// 
//***************************************************************


//***********************************************************************************************************
// all_of
// 检查一元谓词 pred 是否对范围 [first, last) 中所有元素返回 true 
//***********************************************************************************************************
template <class InputIterator, class Predicate>
bool all_of(InputIterator first, InputIterator last, Predicate pred) {
    for (; first != last; ++first) {
        if (!pred(*first)) return false;
    }
    return true;
}

//***********************************************************************************************************
// any_of
// 检查一元谓词 pred 是否对范围 [first, last) 中至少一个元素返回 true
//***********************************************************************************************************
template <class InputIterator, class Predicate>
bool any_of(InputIterator first, InputIterator last, Predicate pred) {
    for (; first != last; ++first) {
        if (pred(*first)) return true;
    }
    return false;
}

//***********************************************************************************************************
// none_of
// 检查一元谓词 pred 是否不对范围 [first, last) 中任何元素返回 true
//***********************************************************************************************************
template <class InputIterator, class Predicate>
bool none_of(InputIterator first, InputIterator last, Predicate pred) {
    for (; first != last; ++first) {
        if (pred(*first)) return false;
    }
    return true;
}

//***********************************************************************************************************
// for_each
// 按顺序应用给定的函数对象 f 到解引用范围 [first, last) 中每个迭代器的结果
//***********************************************************************************************************
template<class InputIterator, class Function>
Function for_each(InputIterator first, InputIterator last, Function f) {
    for (; first != last; ++first) {
        f(*first);
    }
    return f;
}

//***********************************************************************************************************
// count
// 返回范围 [first, last) 中满足特定判别标准的元素数
// 计数等于 value 的元素
//***********************************************************************************************************
template<class InputIterator, class T>
typename iterator_traits<InputIterator>::difference_type
count(InputIterator first, InputIterator last, const T& value) {
    typename iterator_traits<InputIterator>::difference_type result = 0;
    for (; first != last; ++first) {
        if (*first == value) ++result;
    }
    return result;
}

//***********************************************************************************************************
// count_if
// 返回范围 [first, last) 中满足特定判别标准的元素数
// 计数谓词 pred 对其返回 true 的元素
//***********************************************************************************************************
template<class InputIterator, class Predicate>
typename iterator_traits<InputIterator>::difference_type
count_if(InputIterator first, InputIterator last, Predicate pred) {
    typename iterator_traits<InputIterator>::difference_type result = 0;
    for (; first != last; ++first) {
        if (pred(*first)) ++result;
    }
    return result;
}

//***********************************************************************************************************
// find
// 搜索等于 value 的元素
//***********************************************************************************************************
template<class InputIterator, class T>
InputIterator find(InputIterator first, InputIterator last, const T& value) {
    for (; first != last; ++first) {
        if (*first == value) return first;
    }
    return last;
}

//***********************************************************************************************************
// find_if
// 搜索谓词 pred 对其返回 true 的元素
//***********************************************************************************************************
template<class InputIterator, class Predicate>
InputIterator find_if(InputIterator first, InputIterator last, Predicate pred) {
    for (; first != last; ++first) {
        if (pred(*first)) return first;
    }
    return last;
}

//***********************************************************************************************************
// find_if_not
// 搜索谓词 pred 对其返回 false 的元素
//***********************************************************************************************************
template<class InputIterator, class Predicate>
InputIterator find_if_not(InputIterator first, InputIterator last, Predicate pred) {
    for (; first != last; ++first) {
        if (!pred(*first)) return first;
    }
    return last;
}

//***********************************************************************************************************
// search
// 搜索范围 [first1, last1 - (last2 - first2)) 中元素子序列 [first2, last2) 的首次出现
// 元素用 operator== 比较
//***********************************************************************************************************
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1 
search(ForwardIterator1 first1, ForwardIterator1 last1,
        ForwardIterator2 first2, ForwardIterator2 last2) {
    for (; first1 != last1; ++first1) {
        ForwardIterator1 it1 = first1;
        for (ForwardIterator2 it2 = first2; ; ++it1, ++it2) {
            if (it2 == last2) return first1;
            if (it1 == last1) return last1;
            if (!(*it1 == *it2)) break;
        }
    }
}

//***********************************************************************************************************
// search
// 搜索范围 [first1, last1 - (last2 - first2)) 中元素子序列 [first2, last2) 的首次出现
// 元素用给定的二元谓词 pred 比较
//***********************************************************************************************************
template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
ForwardIterator1 
search(ForwardIterator1 first1, ForwardIterator1 last1,
       ForwardIterator2 first2, ForwardIterator2 last2,
       BinaryPredicate pred) {
    for (; first1 != last1; ++first1) {
        ForwardIterator1 it1 = first1;
        for (ForwardIterator2 it2 = first2; ; ++it1, ++it2) {
            if (it2 == last2) return first1;
            if (it1 == last1) return last1;
            if (!pred(*it1, *it2)) break;
        }
    }
}

//***********************************************************************************************************
// search_n
// 在范围 [first, last) 中搜索 count 个等同元素的序列，每个都等于给定的值 value 
// 用 operator== 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class Size, class T>
ForwardIterator 
search_n(ForwardIterator first, ForwardIterator last,
         Size count, const T& value) {

    ForwardIterator result = first;
    std::size_t cur_count = 0;

    while (first != last) {
        if (*first == value) {
            ++cur_count;
            if (cur_count == count) return result;
            else ++first;
        } else {
            cur_count = 0;
            ++first;
            result = first;
        }
    }

    return last;
}

//***********************************************************************************************************
// search_n
// 在范围 [first, last) 中搜索 count 个等同元素的序列，每个都等于给定的值 value 
// 用给定的二元谓词 pred 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class Size, class T, class BinaryPredicate>
ForwardIterator 
search_n(ForwardIterator first, ForwardIterator last,
         Size count, const T& value,
         BinaryPredicate pred) {

    ForwardIterator result = first;
    std::size_t cur_count = 0;

    while (first != last) {
        if (pred(*first, value)) {
            ++cur_count;
            if (cur_count == count) return result;
            else ++first;
        } else {
            cur_count = 0;
            ++first;
            result = first;
        }
    }

    return last;
}

//***********************************************************************************************************
// find_end
// 在范围 [first1, last1) 中搜索最后的元素子列 [first2, last2)
// 用 operator== 比较元素
//***********************************************************************************************************

// find_end 的 forward_iterator_tag 版本
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1
__find_end(ForwardIterator1 first1, ForwardIterator1 last1,
           ForwardIterator2 first2, ForwardIterator2 last2,
           forward_iterator_tag, forward_iterator_tag) {
    if (first1 == last2) return last1;

    ForwardIterator1 result = last1;
    while (true) {
        ForwardIterator1 new_result = MoperSTL::search(first1, last1, first2, last2);
        if (new_result == last1) break;
        else {
            result = new_result;
            first1 = result;
            ++first1;
        }
    }
    return result;
}

// find_end 的 bidirectional_iterator_tag 版本
template <class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator1
__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
           BidirectionalIterator2 first2, BidirectionalIterator2 last2,
           bidirectional_iterator_tag, bidirectional_iterator_tag) {
    using reveseit1 = reverse_iterator<BidirectionalIterator1>;
    using reveseit2 = reverse_iterator<BidirectionalIterator2>;

    reveseit1 rfirst1(last1);
    reveseit2 rfirst2(last2);
    reveseit1 rlast1(first1);
    reveseit2 rlast2(first2);

    reveseit1 rresult = MoperSTL::search(rfirst1, rlast1, rfirst2, rlast2);
    if (rresult == rlast1) return last1;
    else {
        BidirectionalIterator1 result = rresult.base();
        MoperSTL::advance(result, -MoperSTL::distance(first2, last2));
        return result;
    }
}

template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator1
find_end(ForwardIterator1 first1, ForwardIterator1 last1,
         ForwardIterator2 first2, ForwardIterator2 last2) {
    return MoperSTL::__find_end(first1, last1, first2, last2, 
                                MoperSTL::__iterator_category<ForwardIterator1>(),
                                MoperSTL::__iterator_category<ForwardIterator2>());
}

//***********************************************************************************************************
// find_end
// 在范围 [first1, last1) 中搜索最后的元素子列 [first2, last2)
// 用给定的二元谓词 pred 比较元素
//***********************************************************************************************************

// find_end 的 forward_iterator_tag 版本
// 用给定的二元谓词 pred 比较元素
template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
ForwardIterator1
__find_end(ForwardIterator1 first1, ForwardIterator1 last1,
           ForwardIterator2 first2, ForwardIterator2 last2,
           forward_iterator_tag, forward_iterator_tag,
           BinaryPredicate pred) {
    if (first1 == last2) return last1;

    ForwardIterator1 result = last1;
    while (true) {
        ForwardIterator1 new_result = MoperSTL::search(first1, last1, first2, last2, pred);
        if (new_result == last1) break;
        else {
            result = new_result;
            first1 = result;
            ++first1;
        }
    }
    return result;
}

// find_end 的 bidirectional_iterator_tag 版本
// 用给定的二元谓词 pred 比较元素
template <class BidirectionalIterator1, class BidirectionalIterator2, class BinaryPredicate>
BidirectionalIterator1
__find_end(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
           BidirectionalIterator2 first2, BidirectionalIterator2 last2,
           bidirectional_iterator_tag, bidirectional_iterator_tag,
           BinaryPredicate pred) {
    using reveseit1 = reverse_iterator<BidirectionalIterator1>;
    using reveseit2 = reverse_iterator<BidirectionalIterator2>;

    reveseit1 rfirst1(last1);
    reveseit2 rfirst2(last2);
    reveseit1 rlast1(first1);
    reveseit2 rlast2(first2);

    reveseit1 rresult = MoperSTL::search(rfirst1, rlast1, rfirst2, rlast2, pred);
    if (rresult == rlast1) return last1;
    else {
        BidirectionalIterator1 result = rresult.base();
        MoperSTL::advance(result, -MoperSTL::distance(first2, last2));
        return result;
    }
}

template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
ForwardIterator1
find_end(ForwardIterator1 first1, ForwardIterator1 last1,
         ForwardIterator2 first2, ForwardIterator2 last2,
         BinaryPredicate pred) {
    return MoperSTL::__find_end(first1, last1, first2, last2,
                                MoperSTL::__iterator_category<ForwardIterator1>(), 
                                MoperSTL::__iterator_category<ForwardIterator2>(), pred);
}


//***********************************************************************************************************
// find_first_of
// 在范围 [first1, last1) 中搜索范围 [first2, last2) 中的任何元素
// 用 operator== 比较元素
//***********************************************************************************************************
template<class InputIterator, class ForwardIterator>
InputIterator
find_first_of(InputIterator first1, InputIterator last1,
              ForwardIterator first2, ForwardIterator last2) {
    for (; first1 != last1; ++first1) {
        for (ForwardIterator it = first2; it != last2; ++it) {
            if (*first1 == *it) return first1;
        }
    }
    return last1;
}

//***********************************************************************************************************
// find_first_of
// 在范围 [first1, last1) 中搜索范围 [first2, last2) 中的任何元素
// 用给定的二元谓词 pred 比较元素
//***********************************************************************************************************
template<class InputIterator, class ForwardIterator,
    class BinaryPredicate>
InputIterator
find_first_of(InputIterator first1, InputIterator last1,
              ForwardIterator first2, ForwardIterator last2,
              BinaryPredicate pred) {
    for (; first1 != last1; ++first1) {
        for (ForwardIterator it = first2; it != last2; ++it) {
            if (pred(*first1, *it)) return first1;
        }
    }
    return last1;
}

//***********************************************************************************************************
// adjacent_find
// 在范围 [first, last) 中搜索二个相继的等同元素
// 用 operator== 比较元素
//***********************************************************************************************************
template<class ForwardIterator>
ForwardIterator 
adjacent_find(ForwardIterator first, ForwardIterator last) {
    if (first == last) return last;
    for (ForwardIterator next_it = next(first); next_it != last; ++next_it, (void)++first) {
        if (*first == *next_it) return first;
    }
    return last;
}

//***********************************************************************************************************
// adjacent_find
// 在范围 [first, last) 中搜索二个相继的等同元素
// 用给定的二元谓词 p 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class BinaryPredicate>
ForwardIterator 
adjacent_find(ForwardIterator first, ForwardIterator last,
              BinaryPredicate pred) {
    if (first == last) return last;
    for (ForwardIterator next = next(first); next != last; ++next, ++first) {
        if (pred(*first == *next)) return first;
    }
    return last;
}

//***********************************************************************************************************
// mismatch
// 返回来自二个范围：一个以 [first1, last1) 定义而另一个以 [first2,last2) 定义 的首个不匹配对
// 用 operator== 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2>
MoperSTL::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1, InputIterator1 last1,
         InputIterator2 first2, InputIterator2 last2) {
    while (first1 != last1 && first2 != last2 && *first1 == *first2) {
        ++first1;
        ++first2;
    }
    return MoperSTL::make_pair<InputIterator1, InputIterator2>(MoperSTL::move(first1), MoperSTL::move(first2));
}

//***********************************************************************************************************
// mismatch
// 返回来自二个范围：一个以 [first1, last1) 定义而另一个以 [first2,last2) 定义 的首个不匹配对
// 用给定的二元谓词 p 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class BinaryPredicate>
MoperSTL::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1, InputIterator1 last1,
         InputIterator2 first2, InputIterator2 last2,
         BinaryPredicate pred) {
    while (first1 != last1 && first2 != last2 && pred(*first1, *first2)) {
        ++first1;
        ++first2;
    }
    return MoperSTL::make_pair<InputIterator1, InputIterator2>(MoperSTL::move(first1), MoperSTL::move(first2));
}

//***********************************************************************************************************
// mismatch
// 返回来自二个范围：一个以 [first1, last1) 定义而另一个以 [first2,last2) 定义，的首个不匹配对
// 不提供 last2，使用 first2 + (last1 - first1) 作为last2 
// 用 operator== 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2>
MoperSTL::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1, InputIterator1 last1,
         InputIterator2 first2) {
    while (first1 != last1 && *first1 == *last1) {
        ++first1;
        ++first2;
    }
    return MoperSTL::make_pair<InputIterator1, InputIterator2>(MoperSTL::move(first1), MoperSTL::move(first2));
}

//***********************************************************************************************************
// mismatch
// 返回来自二个范围：一个以 [first1, last1) 定义而另一个以 [first2,last2) 定义，的首个不匹配对
// 不提供 last2，使用 first2 + (last1 - first1) 作为last2 
// 用给定的二元谓词 pred 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class BinaryPredicate>
MoperSTL::pair<InputIterator1, InputIterator2>
mismatch(InputIterator1 first1, InputIterator1 last1,
         InputIterator2 first2, BinaryPredicate pred) {
    while (first1 != last1 && pred(*first1, *last1)) {
        ++first1;
        ++first2;
    }
    return MoperSTL::make_pair<InputIterator1, InputIterator2>(MoperSTL::move(first1), MoperSTL::move(first2));
}

//***********************************************************************************************************
// equal
// 如果范围 [first1, last1) 和范围 [first2, last2) 相等，返回 true ，否则返回 false
// 用 operator== 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
           InputIterator2 first2, InputIterator2 last2) {

    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if (!(*first1 == *first2)) return false;
    }

    if (first1 == last1 && first2 == last2) return true;
    else return false;
}

//***********************************************************************************************************
// equal
// 如果范围 [first1, last1) 和范围 [first2, last2) 相等，返回 true ，否则返回 false
// 给定的二元谓词 pred 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1,
           InputIterator2 first2, InputIterator2 last2,
           BinaryPredicate pred) {

    for (; first1 != last1 && first2 != last2; ++first1, ++first2) {
        if (!pred(*first1 == *first2)) return false;
    }

    if (first1 == last1 && first2 == last2) return true;
    else return false;
}

//***********************************************************************************************************
// equal
// 如果范围 [first1, last1) 和范围 [first2, first2 + (last1 - first1)) 相等，返回 true ，否则返回 false
// 用 operator== 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2>
bool equal(InputIterator1 first1, InputIterator1 last1,
           InputIterator2 first2) {

    for (; first1 != last1; ++first1, ++first2) {
        if (!(*first1 == *first2)) return false;
    }

    return true;
}

//***********************************************************************************************************
// equal
// 如果范围 [first1, last1) 和范围 [first2, first2 + (last1 - first1)) 相等，返回 true ，否则返回 false
// 给定的二元谓词 pred 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class BinaryPredicate>
bool equal(InputIterator1 first1, InputIterator1 last1,
           InputIterator2 first2, BinaryPredicate pred) {

    for (; first1 != last1; ++first1, ++first2) {
        if (!pred(*first1 == *first2)) return false;
    }

    return true;
}


//***************************************************************
// 
// 
// 最小/最大操作
// 
// 
//***************************************************************


//***********************************************************************************************************
// min_element
// 寻找范围 [first, last) 中的最小元素
// 用 operator< 比较元素
//***********************************************************************************************************
template<class ForwardIterator>
ForwardIterator 
min_element(ForwardIterator first, ForwardIterator last) {
    if (first == last) return last;

    ForwardIterator result = first;
    while (++first != last) {
        if (*first < *result) result = first;
    }
    return result;
}

//***********************************************************************************************************
// min_element
// 寻找范围 [first, last) 中的最小元素
// 用 comp 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class Compare>
ForwardIterator 
min_element(ForwardIterator first, ForwardIterator last,
            Compare comp) {
    if (first == last) return last;

    ForwardIterator result = first;
    while (++first != last) {
        if (comp(*first, *result)) result = first;
    }
    return result;
}

//***********************************************************************************************************
// min
// 返回 a 与 b 的较小者
// 用 operator< 比较元素
//***********************************************************************************************************
template<class T> 
const T& min(const T& a, const T& b) {
    return b < a ? b : a;
}

//***********************************************************************************************************
// min
// 返回 a 与 b 的较小者
// 用 comp 比较元素
//***********************************************************************************************************
template<class T, class Compare>
const T& min(const T& a, const T& b, Compare comp) {
    return comp(b, a) ? b : a;
}

//***********************************************************************************************************
// min
// 返回 initializer_list ilist 中值的最小者
// 用 operator< 比较元素
//***********************************************************************************************************
template<class T>
T min(std::initializer_list<T> t) {
    return *MoperSTL::min_element(t.begin(), t.end());
}

//***********************************************************************************************************
// min
// 返回 initializer_list ilist 中值的最小者
// 用 comp 比较元素
//***********************************************************************************************************
template<class T, class Compare>
T min(std::initializer_list<T> t, Compare comp) {
    return *MoperSTL::min_element(t.begin(), t.end(), comp);
}

//***********************************************************************************************************
// max_element
// 寻找范围 [first, last) 中的最大元素
// 用 operator< 比较元素
//***********************************************************************************************************
template<class ForwardIterator>
ForwardIterator 
max_element(ForwardIterator first, ForwardIterator last) {
    if (first == last) return last;

    ForwardIterator result = first;
    while (++first != last) {
        if (*result < *first) result = first;
    }
    return result;
}

//***********************************************************************************************************
// max_element
// 寻找范围 [first, last) 中的最大元素
// 用 comp 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class Compare>
ForwardIterator 
max_element(ForwardIterator first, ForwardIterator last,
            Compare comp) {
    if (first == last) return last;

    ForwardIterator result = first;
    while (++first != last) {
        if (comp(*result, *first)) result = first;
    }
    return result;
}

//***********************************************************************************************************
// max
// 返回 a 与 b 的较大者
// 用 operator< 比较元素
//***********************************************************************************************************
template<class T> 
const T& max(const T& a, const T& b) {
    return a < b ? b : a;
}

//***********************************************************************************************************
// max
// 返回 a 与 b 的较大者
// 用 comp 比较元素
//***********************************************************************************************************
template<class T, class Compare>
const T& max(const T& a, const T& b, Compare comp) {
    return comp(a, b) ? b : a;
}

//***********************************************************************************************************
// max
// 返回 initializer_list ilist 中值的最大者
// 用 operator< 比较元素
//***********************************************************************************************************
template<class T>
T max(std::initializer_list<T> t) {
    return *MoperSTL::max_element(t.begin(), t.end());
}

//***********************************************************************************************************
// max
// 返回 initializer_list ilist 中值的最大者
// 用 comp 比较元素
//***********************************************************************************************************
template<class T, class Compare>
T max(std::initializer_list<T> t, Compare comp) {
    return *MoperSTL::max_element(t.begin(), t.end(), comp);
}

//***********************************************************************************************************
// minmax_element
// 寻找范围 [first, last) 中最小和最大的元素
// 用 operator< 比较元素
//***********************************************************************************************************
template<class ForwardIterator>
pair<ForwardIterator, ForwardIterator>
minmax_element(ForwardIterator first, ForwardIterator last) {
    pair<ForwardIterator, ForwardIterator> result(first, first);

    if (first == last) return result;

    while (++first != last) {
        if (*first < *result.first) {
            result.first = first;
        } else if (!(*first < *result.second)) {
            result.second = first;
        }
    }
    return result;
}

//***********************************************************************************************************
// minmax_element
// 寻找范围 [first, last) 中最小和最大的元素
// 用 comp 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class Compare>
pair<ForwardIterator, ForwardIterator>
minmax_element(ForwardIterator first, ForwardIterator last,
               Compare comp) {
    pair<ForwardIterator, ForwardIterator> result(first, first);

    if (first == last) return result;

    while (++first != last) {
        if (comp(*first, *result.first)) {
            result.first = first;
        } else if (!comp(*first, *result.second)) {
            result.second = first;
        }
    }
    return result;
}

//***********************************************************************************************************
// minmax
// 返回到 a 的 b 较小和较大者的引用
// 用 operator< 比较元素
//***********************************************************************************************************
template<class T> 
MoperSTL::pair<const T&, const T&> 
minmax(const T& a, const T& b) {
    if (b < a)      return MoperSTL::pair<const T&, const T&>(b, a);
    else            return MoperSTL::pair<const T&, const T&>(a, b);
}

//***********************************************************************************************************
// minmax
// 返回到 a 的 b 较小和较大者的引用
// 用 comp 比较元素
//***********************************************************************************************************
template<class T, class Compare>
MoperSTL::pair<const T&, const T&> 
minmax(const T& a, const T& b, Compare comp) {
    if (comp(b, a))     return MoperSTL::pair<const T&, const T&>(b, a);
    else                return MoperSTL::pair<const T&, const T&>(a, b);
}

//***********************************************************************************************************
// minmax
// 返回 initializer_list ilist 中值的最小和最大者
// 用 operator< 比较元素
//***********************************************************************************************************
template<class T>
MoperSTL::pair<T, T> 
minmax(std::initializer_list<T> t) {
    auto p = MoperSTL::minmax_element(t.begin(), t.end());
    return MoperSTL::make_pair(*p.first, *p.second);
}

//***********************************************************************************************************
// minmax
// 返回 initializer_list ilist 中值的最小和最大者
// 用 comp 比较元素
//***********************************************************************************************************
template<class T, class Compare>
MoperSTL::pair<T, T> 
minmax(std::initializer_list<T> t, Compare comp) {
    auto p = MoperSTL::minmax_element(t.begin(), t.end(), comp);
    return MoperSTL::make_pair(*p.first, *p.second);
}

//***********************************************************************************************************
// median
// 返回三个值的中间值
// 用 operator< 比较元素
//***********************************************************************************************************
template<class T>
const T& median(const T& a, const T& b, const T& c) {
    if ((a < b && b < c) || (c < b && b < a)) return b;
    else if ((b < a && a < c) || (c < a && a < b)) return a;
    else return c;
}

//***********************************************************************************************************
// median
// 返回三个值的中间值
// 用 comp 比较元素
//***********************************************************************************************************
template<class T, class Compare>
const T& median(const T& a, const T& b, const T& c, Compare comp) {
    if ((comp(a, b) && comp(b, c)) || (comp(c, b) && comp(b, a))) return b;
    else if ((comp(b, a) && comp(a, c)) || (comp(c, a) && comp(a, b))) return a;
    else return c;
}

//***********************************************************************************************************
// lexicographical_compare
// 检查第一个范围 [first1, last1) 是否按字典序小于第二个范围 [first2, last2)
// 用 operator< 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2>
bool 
lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, InputIterator2 last2) {
    for (; first1 != last1 && first2 != last2; ++first1, (void)++first2) {
        if (*first1 < *first2) return true;
        else if (*first2 < *first1) return false;
    }
    return first1 == first2 && first2 != last2;
}

//***********************************************************************************************************
// lexicographical_compare
// 检查第一个范围 [first1, last1) 是否按字典序小于第二个范围 [first2, last2)
// 用 comp 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class Compare>
bool 
lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
                        InputIterator2 first2, InputIterator2 last2,
                        Compare comp) {
    for (; first1 != last1 && first2 != last2; ++first1, (void)++first2) {
        if (comp(*first1, *first2)) return true;
        else if (comp(*first2, *first1)) return false;
    }
    return first1 == first2 && first2 != last2;
}


//***************************************************************
// 
// 
// 修改序列的操作
// 
// 
//***************************************************************


//***********************************************************************************************************
// copy
// 复制 [first, last) 所定义的范围中的元素到始于 result 的另一范围
//***********************************************************************************************************

// copy 普通版本
template<class InputIterator, class OutputIterator>
OutputIterator 
__copy(InputIterator first, InputIterator last, OutputIterator result) {
    while (first != last) {
        *result++ = *first++;
    }
    return result;
}

// copy 为 trivially_copy_assignable 类型提供的特化版本
template <class Input, class Output>
typename std::enable_if<
                        std::is_same_v<typename std::remove_const_t<Input>, Output> &&
                        std::is_trivially_copy_assignable_v<Output>
                        , Output*>::type
__copy(Input* first, Input* last, Output* result) {
    const auto n = static_cast<std::size_t>(last - first);
    if (n != 0) {
        std::memmove(result, first, n * sizeof(Output));
    }
    return result + n;
}

template<class InputIterator, class OutputIterator>
OutputIterator copy(InputIterator first, InputIterator last,
                    OutputIterator result) {
    return MoperSTL::__copy(first, last, result);
}

//***********************************************************************************************************
// copy_if
// 复制 [first, last) 所定义的范围中的元素到始于 result 的另一范围
// 仅复制谓词 pred 对其返回 true 的元素
//***********************************************************************************************************
template<class InputIterator, class OutputIterator, class UnaryPredicate>
OutputIterator copy_if(InputIterator first, InputIterator last,
                    OutputIterator result, UnaryPredicate pred) {
    while (first != last) {
        if (pred(*first)) {
            *result++ = *first;
        }
        ++first;
    }
    return result;
}

//***********************************************************************************************************
// copy_n
// 若 count>0 ，则准确复制来自始于 first 的范围的 count 个值到始于 result 的范围
//***********************************************************************************************************
template<class InputIterator, class Size, class OutputIterator>
OutputIterator copy_n(InputIterator first, Size count,
                      OutputIterator result) {
    if (count > 0) {
        for (Size i = 0; i < count; ++i) {
            *result++ = *first++;
        }
    }
    return result;
}

//***********************************************************************************************************
// copy_backward
// 复制来自 [first, last) 所定义范围的元素，到终于 result 的范围
// 以逆序复制元素（首先复制末元素），但保持其相对顺序
//***********************************************************************************************************

// copy_backward 普通版本
template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2
__copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last,
                BidirectionalIterator2 result) {
    while (first != last) {
        *(--result) = *(--last);
    }
    return result;
}

// copy_backward 为 trivially_copy_assignable 类型提供的特化版本
template <class Input, class Output>
typename std::enable_if<
                        std::is_same_v<std::remove_const_t<Input>, Output> &&
                        std::is_trivially_copy_assignable_v<Output>
                        , Output*>::type
__copy_backward(Input* first, Input* last, Output* result) {
    const auto n = static_cast<std::size_t>(last - first);
    if (n != 0) {
        result -= n;
        std::memmove(result, first, n * sizeof(Output));
    }
    return result;
}

template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 
copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last,
              BidirectionalIterator2 result) {
    return MoperSTL::__copy_backward(first, last, result);
}

//***********************************************************************************************************
// move
// 移动范围 [first, last) 中的元素到始于 result 的另一范围
// 从首元素开始逐次到末元素
// 此操作后被移动范围中的元素将仍然含有适合类型的合法值，但不必与移动前的值相同
//***********************************************************************************************************
template<class InputIterator, class OutputIterator>
OutputIterator 
move(InputIterator first, InputIterator last, OutputIterator result) {
    while (first != last) {
        *result++ = MoperSTL::move(*first++);
    }
    return result;
}

//***********************************************************************************************************
// move_backward
// 移动范围 [first, last) 中的元素到始于 result 的另一范围
// 以逆序移动元素（首先复制末元素），但保持其相对顺序
//***********************************************************************************************************
template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2 
move_backward(BidirectionalIterator1 first, BidirectionalIterator1 last,
              BidirectionalIterator2 result) {
    while (first != last) {
        *(--result) = MoperSTL::move(*(--last));
    }
    return result;
}

//***********************************************************************************************************
// iter_swap
// 交换给定的迭代器所指向的元素的值
//***********************************************************************************************************
template<class ForwardIterator1, class ForwardIterator2>
void 
iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
    MoperSTL::swap(*a, *b);
}

//***********************************************************************************************************
// swap_ranges
// 在范围 [first1, last1) 和始于 first2 的另一范围间交换元素
//***********************************************************************************************************
template<class ForwardIterator1, class ForwardIterator2>
ForwardIterator2 
swap_ranges(ForwardIterator1 first1, ForwardIterator1 last1,
            ForwardIterator2 first2) {
    while (first1 != last1) {
        MoperSTL::iter_swap(first1++, first2++);
    }
    return first2;
}

//***********************************************************************************************************
// transform
// 应用给定的函数到范围 [first, last) 并存储结果于始于 result 的另一范围
// 应用一元函数 op 到 [first, last) 所定义的范围
//***********************************************************************************************************
template<class InputIterator, class OutputIterator, class UnaryOperation>
OutputIterator 
transform(InputIterator first, InputIterator last,
          OutputIterator result, UnaryOperation op) {
    while (first != last) {
        *result++ = op(*first++);
    }
    return result;
}

//***********************************************************************************************************
// transform
// 应用给定的函数到范围 [first, last) 并存储结果于始于 result 的另一范围
// 应用二元函数 op 到来自二个范围的元素对：一个以 [first1, last1) 定义，而另一个始于 first2 
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class OutputIterator,
    class BinaryOperation>
OutputIterator 
transform(InputIterator1 first1, InputIterator1 last1,
          InputIterator2 first2, OutputIterator result,
          BinaryOperation op) {
    while (first1 != first2) {
        *result++ = op(*first1++, *first2++);
    }
    return result;
}

//***********************************************************************************************************
// replace
// 以 new_value 替换范围 [first, last) 中所有等于 old_value 的元素
//***********************************************************************************************************
template<class ForwardIterator, class T>
void 
replace(ForwardIterator first, ForwardIterator last,
        const T& old_value, const T& new_value) {
    for (; first != last; ++first) {
        if (*first == old_value)  *first = new_value;
    }
}

//***********************************************************************************************************
// replace_if
// 以 new_value 替换范围 [first, last) 中所有谓词 pred 对其返回 true 的元素
//***********************************************************************************************************
template<class ForwardIterator, class Predicate, class T>
void 
replace_if(ForwardIterator first, ForwardIterator last,
           Predicate pred, const T& new_value) {
    for (; first != last; ++first) {
        if (pred(*first)) *first = new_value;
    }
}

//***********************************************************************************************************
// replace_copy
// 复制来自范围 [first, last) 的所有元素到始于 result 的范围
// 并以 new_value  替换所有等于 old_value 的元素
// 源与目标范围不能重叠
//***********************************************************************************************************
template<class InputIterator, class OutputIterator, class T>
OutputIterator 
replace_copy(InputIterator first, InputIterator last,
             OutputIterator result,
             const T& old_value, const T& new_value) {
    for (; first != last; ++first, ++result) {
        if (*first == old_value) {
            *result = new_value;
        } else {
            *result = *first;
        }
    }
}

//***********************************************************************************************************
// replace_copy_if
// 复制来自范围 [first, last) 的所有元素到始于 result 的范围
// 并以 new_value 替换所有谓词 pred 对其满足 true 的元素
// 源与目标范围不能重叠
//***********************************************************************************************************
template<class InputIterator, class OutputIterator, class Predicate, class T>
OutputIterator 
replace_copy_if(InputIterator first, InputIterator last,
                OutputIterator result,
                Predicate pred, const T& new_value) {
    for (; first != last; ++first, ++result) {
        if (pred(*first)) {
            *result = new_value;
        } else {
            *result = *first;
        }
    }
}

//***********************************************************************************************************
// fill
// 赋值给定的 value 给 [first, last) 中的元素
//***********************************************************************************************************
template<class ForwardIterator, class T>
void 
fill(ForwardIterator first, ForwardIterator last,
     const T& value) {
    for (; first != last; ++first) {
        *first = value;
    }
}

//***********************************************************************************************************
// move_backward
// 若 count > 0 ，则赋值给定的 value 给始于 的范围的首 count 个元素
// 否则不做任何事
//***********************************************************************************************************
template<class OutputIterator, class Size, class T>
OutputIterator 
fill_n(OutputIterator first, Size count, const T& value) {
    for (Size i = 0; i < count; ++i) {
        *first++ = value;
    }
    return first;
}

//***********************************************************************************************************
// generate
// 以给定函数对象 gen 所生成的值赋值范围 [first, last) 中的每个元素
//***********************************************************************************************************
template<class ForwardIterator, class Generator>
void 
generate(ForwardIterator first, ForwardIterator last,
         Generator gen) {
    while (first != last) {
        *first++ = gen();
    }
}

//***********************************************************************************************************
// generate_n
// 若 count>0 ，则赋值给定函数对象 gen 所生成的值给始于 first 的范围的首 count 个元素
// 否则不做任何事
//***********************************************************************************************************
template<class OutputIterator, class Size, class Generator>
OutputIterator 
generate_n(OutputIterator first, Size count, Generator gen) {
    for (Size i = 0; i < count; ++i) {
        *first++ = gen();
    }
    return first;
}

//***********************************************************************************************************
// remove
// 从范围 [first, last) 移除所有等于 value 的元素
// 并返回范围新结尾的尾后迭代器
//***********************************************************************************************************
template<class ForwardIterator, class T>
ForwardIterator 
remove(ForwardIterator first, ForwardIterator last,
       const T& value) {
    for (ForwardIterator it = first; it != last; ++it) {
        if (!(*it == value)) {
            *first++ = MoperSTL::move(*it);
        }
    }
    return first;
}

//***********************************************************************************************************
// remove_if
// 从范围 [first, last) 移除所有 pred 对于它返回 true 的元素
// 并返回范围新结尾的尾后迭代器
//***********************************************************************************************************
template<class ForwardIterator, class Predicate>
ForwardIterator 
remove_if(ForwardIterator first, ForwardIterator last,
          Predicate pred) {
    for (ForwardIterator it = first; it != last; ++it) {
        if (!pred(*it)) {
            *first++ = MoperSTL::move(*it);
        }
    }
    return first;
}

//***********************************************************************************************************
// remove_copy
// 复制来自范围 [first, last) 的元素到始于 result 的另一范围
// 忽略所有等于 value 的元素
//***********************************************************************************************************
template<class InputIterator, class OutputIterator, class T>
OutputIterator 
remove_copy(InputIterator first, InputIterator last,
            OutputIterator result, const T& value) {
    for (; first != last; ++first) {
        if (!(*first == value)) {
            *result++ = *first;
        }
    }
    return result;
}

//***********************************************************************************************************
// remove_copy_if
// 复制来自范围 [first, last) 的元素到始于 result 的另一范围
// 忽略所有谓词 pred 对其返回 true 的元素
//***********************************************************************************************************
template<class InputIterator, class OutputIterator, class Predicate>
OutputIterator 
remove_copy_if(InputIterator first, InputIterator last,
               OutputIterator result, Predicate pred) {
    for (; first != last; ++first) {
        if (!pred(*first)) {
            *result++ = *first;
        }
    }
    return result;
}


//***********************************************************************************************************
// unique
// 删除范围 [first, last) 内连续重复的元素
// 并返回范围的新逻辑结尾的尾后迭代器
// 用 operator== 比较元素
//***********************************************************************************************************
template<class ForwardIterator>
ForwardIterator 
unique(ForwardIterator first, ForwardIterator last) {
    for (ForwardIterator it = first; it != last; ++it) {
        if (!(*it == *first)) {
            *++first = MoperSTL::move(*it);
        }
    }
    return ++first;
}

//***********************************************************************************************************
// unique
// 删除范围 [first, last) 内连续重复的元素
// 并返回范围的新逻辑结尾的尾后迭代器
// 用给定的谓词 pred 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class BinaryPredicate>
ForwardIterator 
unique(ForwardIterator first, ForwardIterator last,
       BinaryPredicate pred) {
    for (ForwardIterator it = first; it != last; ++it) {
        if (!pred(*it, *first)) {
            *++first = MoperSTL::move(*it);
        }
    }
    return ++first;
}

//***********************************************************************************************************
// unique_copy
// 复制范围 [first, last) 内无连续的元素到 result 的另一范围
// 用 operator== 比较元素
//***********************************************************************************************************

// unique_copy 的 forward_iterator_tag 版本
template<class InputIterator, class OutputIterator>
OutputIterator
__unique_copy(InputIterator first, InputIterator last,
              OutputIterator result, forward_iterator_tag) {
    *result = *first;
    while (++first != last) {
        if (!(*result == *first)) *++result = *first;
    }
    return ++result;
}

// unique_copy 的 output_iterator_tag 版本
// 由于 output iterator 只能进行只读操作，所以不能有 !(*result == *first) 这样的判断
template<class InputIterator, class OutputIterator>
OutputIterator
__unique_copy(InputIterator first, InputIterator last,
              OutputIterator result, output_iterator_tag) {
    auto value = *first;
    *result = value;
    while (++first != last) {
        if (!(value == *first)) {
            value = *first;
            *++first = value;
        }
    }
    return ++result;
}

template<class InputIterator, class OutputIterator>
OutputIterator 
unique_copy(InputIterator first, InputIterator last,
            OutputIterator result) {
    return MoperSTL::__unique_copy(first, last, result, MoperSTL::__iterator_category<OutputIterator>());
}

//***********************************************************************************************************
// unique_copy
// 复制范围 [first, last) 内无连续的元素到 result 的另一范围
//  用给定的二元谓词 pred 比较元素
//***********************************************************************************************************

// unique_copy 的 forward_iterator_tag 版本
template<class InputIterator, class OutputIterator, class BinaryPredicate>
OutputIterator
__unique_copy(InputIterator first, InputIterator last,
              OutputIterator result, BinaryPredicate pred,
              forward_iterator_tag) {
    *result = *first;
    while (++first != last) {
        if (!pred(*result, *first)) *++result = *first;
    }
    return ++result;
}

// unique_copy 的 output_iterator_tag 版本
// 由于 output iterator 只能进行只读操作，所以不能有 !(*result == *first) 这样的判断
template<class InputIterator, class OutputIterator, class BinaryPredicate>
OutputIterator
__unique_copy(InputIterator first, InputIterator last,
              OutputIterator result, BinaryPredicate pred,
              output_iterator_tag) {
    auto value = *first;
    *result = value;
    while (++first != last) {
        if (!pred(value, *first)) {
            value = *first;
            *++first = value;
        }
    }
    return ++result;
}

template<class InputIterator, class OutputIterator, class BinaryPredicate>
OutputIterator 
unique_copy(InputIterator first, InputIterator last,
            OutputIterator result, BinaryPredicate pred) {
    return MoperSTL::__unique_copy(first, last, result, pred, MoperSTL::__iterator_category<OutputIterator>());
}

//***********************************************************************************************************
// reverse
// 反转 [first, last) 范围中的元素顺序
//***********************************************************************************************************
template<class BidirectionalIterator>
void 
reverse(BidirectionalIterator first, BidirectionalIterator last) {
    while ((first != last) && (first != --last)) {
        MoperSTL::iter_swap(first++, last);
    }
}

//***********************************************************************************************************
// reverse_copy
// 将 [first, last) 范围中元素的反转版本复制到 result 的另一范围
//***********************************************************************************************************
template<class BidirectionalIterator, class OutputIterator>
OutputIterator 
reverse_copy(BidirectionalIterator first, BidirectionalIterator last,
             OutputIterator result) {
    while (first != last) {
        *result++ = *--last;
    }
    return result;
}

//***********************************************************************************************************
// rotate
// 左旋 [first, last) 中的元素，使middle成为新范围的首元素
// 
// 举例：
// [1, 2, 3, 4, 5, 6, 7, 8, 9, 10]
// rotate(2, 5, 8)
// [1, 5, 6, 7, 2, 3, 4, 8, 9, 10]
//***********************************************************************************************************
template<class ForwardIterator>
ForwardIterator
rotate(ForwardIterator first, ForwardIterator middle,
       ForwardIterator last) {

    if (middle == first) return last;
    else if (middle == last) return first;

    ForwardIterator next = middle;
    ForwardIterator result = first;
    bool has_result = false;
    while (first != last) {
        MoperSTL::iter_swap(first++, next++);
        if (next == last) {
            next = middle;
            if (!has_result) {
                result = first;
                has_result = true;
            }
        }
        else if (first == middle) middle = next;
    }
    return result;
}

//***********************************************************************************************************
// rotate_copy
// 复制 [first, last) 中的元素到 result 的另一范围
// 使 middle 为新范围的首元素
//***********************************************************************************************************
template<class ForwardIterator, class OutputIterator>
OutputIterator 
rotate_copy(ForwardIterator first, ForwardIterator middle,
            ForwardIterator last, OutputIterator result) {
    return MoperSTL::copy(first, middle, MoperSTL::copy(middle, last, result));
}


//***************************************************************
// 
// 
// 排列组合
// 
// 
//***************************************************************


//***********************************************************************************************************
// is_permutation
// 若存在范围 [first1, last1) 中元素的排列，使得该范围等于 [first2,last2) ，则返回 true
// 用 operator== 比较元素
//***********************************************************************************************************
template<class ForwardIterator1, class ForwardIterator2>
bool
is_permutation(ForwardIterator1 first1, ForwardIterator1 last1,
               ForwardIterator2 first2) {
    for (; first1 != last1; ++first1, (void)++first2) {
        if (!(*first1 == *first2)) break;
    }
    if (first1 == last1) return true;
    ForwardIterator2 last2 = MoperSTL::next(first2, MoperSTL::distance(first1, last1));
    for (ForwardIterator1 it = first1; it != last1; ++it) {
        if (MoperSTL::find(first1, it, *it) != it) continue;
        auto num = MoperSTL::count(first2, last2, *it);
        if (num == 0 || num != MoperSTL::count(it, last1, *it)) {
            return false;
        }
    }
    return true;
}

//***********************************************************************************************************
// is_permutation
// 若存在范围 [first1, last1) 中元素的排列，使得该范围等于 [first2,last2) ，则返回 true
// 用 pred 比较元素
//***********************************************************************************************************
template<class ForwardIterator1, class ForwardIterator2, class BinaryPredicate>
bool
is_permutation(ForwardIterator1 first1, ForwardIterator1 last1,
               ForwardIterator2 first2, BinaryPredicate pred) {
    for (; first1 != last1; ++first1, (void)++first2) {
        if (!(*first1 == *first2)) break;
    }
    if (first1 == last1) return true;
    ForwardIterator2 last2 = MoperSTL::next(first2, MoperSTL::distance(first1, last1));
    for (ForwardIterator1 it = first1; it != last1; ++it) {
        const auto target = *it;
        auto check = [target, &pred](const auto& value) -> bool { return pred(target, value); };
        if (MoperSTL::find_if(first1, it, check) != it) continue;
        auto num = MoperSTL::count_if(first2, last2, check);
        if (num == 0 || num != MoperSTL::count_if(it, last1, check)) {
            return false;
        }
    }
    return true;
}

//***********************************************************************************************************
// next_permutation
// 变换范围 [first, last) 为来自所有按相对于 operator< 的字典序的下个排列
//***********************************************************************************************************
template<class BidirectionalIterator>
bool
next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
    if (MoperSTL::distance(first, last) < 2) return false;

    BidirectionalIterator cur = MoperSTL::prev(last);
    BidirectionalIterator pr = MoperSTL::prev(cur);
    // 从后向前遍历，寻找第一个 *pr < *cur 的情况
    while (pr != first && !(*pr < *cur)) {
        --pr;
        --cur;
    }
    if (!(*pr < *cur)) {
        if (pr == first) MoperSTL::reverse(first, last);
        return false;
    }
    // 从 [cur, last) 中寻找大于 *pr 的最小元素
    // 根据前面 while 循环可知，[cur, last) 中相邻两个元素，前继元素一定大于等于后继元素
    // 因此，所找到的第一个大于 *pr 的元素即为 [cur, last) 中大于 *pr 的最小元素
    for (cur = MoperSTL::prev(last); !(*pr < *cur); --cur);
    MoperSTL::iter_swap(pr, cur);
    MoperSTL::reverse(MoperSTL::next(pr), last);
    return true;
}

//***********************************************************************************************************
// next_permutation
// 变换范围 [first, last) 为来自所有按相对于 comp 的字典序的下个排列
//***********************************************************************************************************
template<class BidirectionalIterator, class Compare>
bool
next_permutation(BidirectionalIterator first, BidirectionalIterator last,
                 Compare comp) {
    if (MoperSTL::distance(first, last) < 2) return false;

    BidirectionalIterator cur = MoperSTL::prev(last);
    BidirectionalIterator pr = MoperSTL::prev(cur);
    // 从后向前遍历，寻找第一个 *pr < *cur 的情况
    while (pr != first && !comp(*pr, *cur)) {
        --pr;
        --cur;
    }
    if (!comp(*pr, *cur)) {
        if (pr == first) MoperSTL::reverse(first, last);
        return false;
    }
    // 从 [cur, last) 中寻找大于 *pr 的最小元素
    // 根据前面 while 循环可知，[cur, last) 中相邻两个元素，前继元素一定大于等于后继元素
    // 因此，所找到的第一个大于 *pr 的元素即为 [cur, last) 中大于 *pr 的最小元素
    for (cur = MoperSTL::prev(last); !comp(*pr, *cur); --cur);
    MoperSTL::iter_swap(pr, cur);
    MoperSTL::reverse(MoperSTL::next(pr), last);
    return true;
}

//***********************************************************************************************************
// prev_permutation
// 变换范围 [first, last) 为来自所有按相对于 operator< 的字典序的上个排列
//***********************************************************************************************************
template<class BidirectionalIterator>
bool
prev_permutation(BidirectionalIterator first, BidirectionalIterator last) {
    if (MoperSTL::distance(first, last) < 2) return false;

    BidirectionalIterator cur = MoperSTL::prev(last);
    BidirectionalIterator pr = MoperSTL::prev(cur);
    // 从后向前遍历，寻找第一个 *cur < *pr 的情况
    while (pr != first && !(*cur < *pr)) {
        --pr;
        --cur;
    }
    if (!(*cur < *pr)) {
        if (pr == first) MoperSTL::reverse(first, last);
        return false;
    }
    // 从 [cur, last) 中寻找小于 *pr 的最大元素
    // 根据前面 while 循环可知，[cur, last) 中相邻两个元素，后继元素一定大于等于前继元素
    // 因此，所找到的第一个大于 *pr 的元素即为 [cur, last) 中大于 *pr 的最小元素
    for (cur = MoperSTL::prev(last); !(*cur < *pr); --cur);
    MoperSTL::iter_swap(pr, cur);
    MoperSTL::reverse(MoperSTL::next(pr), last);
    return true;
}

//***********************************************************************************************************
// prev_permutation
// 变换范围 [first, last) 为来自所有按相对于 comp 的字典序的上个排列
//***********************************************************************************************************
template<class BidirectionalIterator, class Compare>
bool
prev_permutation(BidirectionalIterator first, BidirectionalIterator last,
                 Compare comp) {
    if (MoperSTL::distance(first, last) < 2) return false;

    BidirectionalIterator cur = MoperSTL::prev(last);
    BidirectionalIterator pr = MoperSTL::prev(cur);
    // 从后向前遍历，寻找第一个 *cur < *pr 的情况
    while (pr != first && !comp(*cur, *pr)) {
        --pr;
        --cur;
    }
    if (!comp(*cur, *pr)) {
        if (pr == first) MoperSTL::reverse(first, last);
        return false;
    }
    // 从 [cur, last) 中寻找小于 *pr 的最大元素
    // 根据前面 while 循环可知，[cur, last) 中相邻两个元素，后继元素一定大于等于前继元素
    // 因此，所找到的第一个大于 *pr 的元素即为 [cur, last) 中大于 *pr 的最小元素
    for (cur = MoperSTL::prev(last); !comp(*cur, *pr); --cur);
    MoperSTL::iter_swap(pr, cur);
    MoperSTL::reverse(MoperSTL::next(pr), last);
    return true;
}

//***********************************************************************************************************
// random_shuffle
// 重排序给定范围 [first, last) 中的元素, 使得这些元素的每个排列拥有相等的出现概率
//***********************************************************************************************************
template<class RandomAccessIterator>
void
random_shuffle(RandomAccessIterator first, RandomAccessIterator last) {
    using difference = typename iterator_traits<RandomAccessIterator>::difference_type;

    for (difference i = last - first - 1; i > 0; --i) {
        MoperSTL::swap(first[i], first[std::rand() % (i + 1)]);
    }
}

//***********************************************************************************************************
// random_shuffle
// 重排序给定范围 [first, last) 中的元素, 使得这些元素的每个排列拥有相等的出现概率
// 随机数生成器为函数对象 rand
//***********************************************************************************************************
template<class RandomAccessIterator, class RandomNumberGenerator>
void
random_shuffle(RandomAccessIterator first, RandomAccessIterator last,
               RandomNumberGenerator&& rand) {
    using difference = typename iterator_traits<RandomAccessIterator>::difference_type;

    for (difference i = last - first - 1; i > 0; --i) {
        MoperSTL::swap(first[i], first[rand(i + 1)]);
    }
}

//***********************************************************************************************************
// shuffle
// 重排序给定范围 [first, last) 中的元素, 使得这些元素的每个排列拥有相等的出现概率
// 均匀随机数生成器为函数对象 rand
//***********************************************************************************************************
template<class RandomAccessIterator, class UniformRandomNumberGenerator>
void
shuffle(RandomAccessIterator first, RandomAccessIterator last,
        UniformRandomNumberGenerator&& rand) {

    using difference = typename iterator_traits<RandomAccessIterator>::difference_type;
    using distribution = std::uniform_int_distribution<difference>;
    using param = typename distribution::param_type;

    distribution Dis;
    for (difference i = last - first - 1; i > 0; --i) {
        MoperSTL::swap(first[i], first[Dis(rand, param(0, i))]);
    }
}





//***************************************************************
// 
// 
// 划分操作
// 
// 
//***************************************************************


//***********************************************************************************************************
// is_partitioned
// 判断 [first, last) 中所有满足 pred 的元素都出现在不满足的元素怒前则返回 true
// 若 [first, last) 为空则返回 true
//***********************************************************************************************************
template<class InputIterator, class Predicate>
bool 
is_partitioned(InputIterator first, InputIterator last,
               Predicate pred) {
    for (; first != last; ++first) {
        if (!pred(*first)) break;
    }
    for (; first != last; ++first) {
        if (pred(*first)) return false;
    }
    return true;
}

//***********************************************************************************************************
// partition
// 重新排序范围 [first, last) 中的元素
// 谓词pred对其返回 true 的元素位于对其返回 false 的元素前方
// * 不保证相对顺序
// 返回指向第二组元素首元素的迭代器
//***********************************************************************************************************

// partition 的 forward_iterator_tag 版本
template <class ForwardIterator, class Predicate>
ForwardIterator
__partition(ForwardIterator first, ForwardIterator last,
            Predicate pred, forward_iterator_tag) {
    first = MoperSTL::find_if_not(first, last, pred);
    if (first == last) return first;

    for (ForwardIterator it = MoperSTL::next(first); it != last; ++it) {
        if (pred(*it)) {
            MoperSTL::iter_swap(it, first);
            ++first;
        }
    }
    return first;
}

// partition 的 bidirectional_iterator_tag 版本
template<class BidirectionalIterator, class Predicate>
BidirectionalIterator
__partition(BidirectionalIterator first, BidirectionalIterator last,
            Predicate pred, bidirectional_iterator_tag) {
    while (true) {
        while (first != last && pred(*first++)){}
        while (first != last && !pred(*--last)){}

        if (first == last) break;
        MoperSTL::iter_swap(first++, last);
    }
    return last;
}

template <class ForwardIterator, class Predicate>
ForwardIterator 
partition(ForwardIterator first, ForwardIterator last,
          Predicate pred) {
    MoperSTL::__partition(first, last, pred, MoperSTL::__iterator_category<ForwardIterator>());
}

//***********************************************************************************************************
// stable_partition
// 重新排序范围 [first, last) 中的元素
// 谓词pred对其返回 true 的元素位于对其返回 false 的元素前方
// * 保证相对顺序
// 返回指向第二组元素首元素的迭代器
//***********************************************************************************************************
template<class BidirectionalIterator, class Predicate>
BidirectionalIterator 
stable_partition(BidirectionalIterator first, BidirectionalIterator last,
                 Predicate pred) {
    first = MoperSTL::find_if_not(first, last, pred);
    if (first == last) return first;

    for (BidirectionalIterator it = MoperSTL::next(first); it != last; ++it) {
        if (pred(*it)) {
            MoperSTL::iter_swap(it, first);
            ++first;
        }
    }
    return first;
}

//***********************************************************************************************************
// partition_copy
// 复制范围 [first, last) 中的元素到两个范围
// 谓词pred对其返回 true 的元素复制到 out_true 范围
// 谓词pred对其返回 false 的元素复制到 out_false 范围
//***********************************************************************************************************
template <class InputIterator, class OutputIterator1, class OutputIterator2, class Predicate>
MoperSTL::pair<OutputIterator1, OutputIterator2>
partition_copy(InputIterator first, InputIterator last,
               OutputIterator1 out_true, OutputIterator2 out_false,
               Predicate pred) {
    for (; first != last; ++first) {
        if (pred(*first)) *out_true++ = *first;
        else *out_false++ = *first;
    }
    return MoperSTL::pair<OutputIterator1, OutputIterator2>(out_true, out_false);
}

//***********************************************************************************************************
// partition_point
// 检验划分范围 [first, last) ,并定位第一划分的结尾,即首个不满足 pred 的元素
// 若所有元素满足 pred 则为 last 
//***********************************************************************************************************

// partition_point 的 forward_iterator_tag 版本
template<class ForwardIterator, class Predicate>
ForwardIterator
__partition_point(ForwardIterator first, ForwardIterator last,
                  Predicate pred, forward_iterator_tag) {
    for (; first != last; ++first) {
        if (!pred(*first)) return last;
    }
    return last;
}

// partition_point 的 random_access_iterator_tag 版本
template<class RandomAccessIterator, class Predicate>
RandomAccessIterator
__partition_point(RandomAccessIterator first, RandomAccessIterator last,
                  Predicate pred, random_access_iterator_tag) {
    while (first < last) {
        RandomAccessIterator middle = first + (last - first) / 2;
        if (pred(*middle)) first = middle + 1;
        else last = middle;
    }
    return first;
}

template<class ForwardIterator, class Predicate>
ForwardIterator 
partition_point(ForwardIterator first, ForwardIterator last,
                Predicate pred) {
    return MoperSTL::__partition_point(first, last, pred, MoperSTL::__iterator_category<ForwardIterator>());
}


//***************************************************************
// 
// 
// 二分搜索操作（在已排序范围上）
// 
// 
//***************************************************************


//***********************************************************************************************************
// lower_bound
// 返回指向范围 [first, last) 中首个不小于（即大于或等于） value 的元素的迭代器
// 若找不到这种元素则返回 last
// 用 operator< 比较元素（即 element < value）
//***********************************************************************************************************
template<class ForwardIterator, class T>
ForwardIterator
lower_bound(ForwardIterator first, ForwardIterator last,
            const T& value) {
    return partition_point(first, last, [value](const auto& element) -> bool { return element < value; });
}

//***********************************************************************************************************
// lower_bound
// 返回指向范围 [first, last) 中首个不小于（即大于或等于） value 的元素的迭代器
// 若找不到这种元素则返回 last
// 用 comp 比较元素（即 comp(element, value)）
//***********************************************************************************************************
template<class ForwardIterator, class T, class Compare>
ForwardIterator
lower_bound(ForwardIterator first, ForwardIterator last,
            const T& value, Compare comp) {
    return partition_point(first, last, [value, &comp](const auto& element) -> bool { return comp(element, value); });
}

//***********************************************************************************************************
// upper_bound
// 返回指向范围 [first, last) 中首个大于 value 的元素的迭代器
// 若找不到这种元素则返回 last
// 用 operator< 比较元素（即 !(value < element)）
//***********************************************************************************************************
template<class ForwardIterator, class T>
ForwardIterator
upper_bound(ForwardIterator first, ForwardIterator last,
            const T& value) {
    return partition_point(first, last, [value](const auto& element) -> bool { return !(value < element); });
}

//***********************************************************************************************************
// upper_bound
// 返回指向范围 [first, last) 中首个大于 value 的元素的迭代器
// 若找不到这种元素则返回 last
// 用 comp 比较元素（即 !comp(value, element)）
//***********************************************************************************************************
template<class ForwardIterator, class T, class Compare>
ForwardIterator
upper_bound(ForwardIterator first, ForwardIterator last,
            const T& value, Compare comp) {
    return partition_point(first, last, [value, &comp](const auto& element) -> bool { return !comp(value, element); });
}

//***********************************************************************************************************
// equal_range
// 返回范围 [first, last) 中含有所有等价于 value 的元素的范围
// 用 operator< 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class T>
MoperSTL::pair<ForwardIterator, ForwardIterator>
equal_range(ForwardIterator first, ForwardIterator last,
            const T& value) {
    return make_pair(lower_bound(first, last, value),
                     upper_bound(first, last, value));
}

//***********************************************************************************************************
// equal_range
// 返回范围 [first, last) 中含有所有等价于 value 的元素的范围
// 用 comp 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class T, class Compare>
MoperSTL::pair<ForwardIterator, ForwardIterator>
equal_range(ForwardIterator first, ForwardIterator last,
            const T& value, Compare comp) {
    return make_pair(lower_bound(first, last, value, comp),
                     upper_bound(first, last, value, comp));
}

//***********************************************************************************************************
// binary_search
// 检查等价于 value 的元素是否出现于范围 [first, last) 中
// 用 operator< 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class T>
bool
binary_search(ForwardIterator first, ForwardIterator last,
              const T& value) {
    first = lower_bound(first, last, value);
    if (first == last || value < *first) return false;
    else return true;
}

//***********************************************************************************************************
// binary_search
// 检查等价于 value 的元素是否出现于范围 [first, last) 中
// 用 comp 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class T, class Compare>
bool
binary_search(ForwardIterator first, ForwardIterator last,
              const T& value, Compare comp) {
    first = lower_bound(first, last, value, comp);
    if (first == last || comp(value, *first)) return false;
    else return true;
}


//***************************************************************
// 
// 
// 堆操作
// 
// 
//***************************************************************


//***********************************************************************************************************
// __adjust_heap
// 从 parent 处向下调整调整范围 [first, last) 的最大堆
// parent 必须位于 [first, last) 范围中
// 用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator>
void 
__adjust_heap(RandomAccessIterator first, RandomAccessIterator last,
              RandomAccessIterator parent) {
    // left_index 记录 parent 左孩子下标
    auto left_index = (parent - first) * 2 + 1;
    // 只有当左孩子存在时才需要进行调整
    while (left_index < last - first) {
        // max_child 指向 parent 的最大子结点。默认指向左子节点
        RandomAccessIterator max_child = first + left_index;
        // 右孩子存在并且右孩子值大于左孩子值时,更新max_child
        if (left_index + 1 < last - first && *max_child < *(max_child + 1))
            ++max_child;
        // 比较 parent 与 max_child
        if (*parent < *max_child) {
            MoperSTL::iter_swap(parent, max_child);
            parent = max_child;
            left_index = (parent - first) * 2 + 1;
        } else break;
    }
}

//***********************************************************************************************************
// __adjust_heap
// 从 parent 处向下调整调整范围 [first, last) 的最大堆
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Compare>
void
__adjust_heap(RandomAccessIterator first, RandomAccessIterator last,
              RandomAccessIterator parent, Compare comp) {
    auto left_index = (parent - first) * 2 + 1;
    while (left_index < last - first) {
        RandomAccessIterator max_child = first + left_index;
        if (left_index + 1 < last - first && comp(*max_child, *(max_child + 1)))
            ++max_child;
        if (comp(*parent, *max_child)) {
            MoperSTL::iter_swap(parent, max_child);
            parent = max_child;
            left_index = (parent - first) * 2 + 1;
        } else break;
    }
}

//***********************************************************************************************************
// push_heap
// 插入位于位置 last-1 的元素到范围 [first, last-1) 所定义的最大堆中
// 用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator>
void 
push_heap(RandomAccessIterator first, RandomAccessIterator last) {
    RandomAccessIterator child = MoperSTL::prev(last);
    while (child > first) {
        RandomAccessIterator parent = (child - 1 - first) / 2;
        if (*parent < *child) {
            MoperSTL::iter_swap(parent, child);
            child = parent;
        }
    }
}

//***********************************************************************************************************
// push_heap
// 插入位于位置 last-1 的元素到范围 [first, last-1) 所定义的最大堆中
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Compare>
void 
push_heap(RandomAccessIterator first, RandomAccessIterator last,
          Compare comp) {
    RandomAccessIterator child = MoperSTL::prev(last);
    while (child > first) {
        RandomAccessIterator parent = (child - 1 - first) / 2;
        if (comp(*parent, *child)) {
            MoperSTL::iter_swap(parent, child);
            child = parent;
        }
    }
}

//***********************************************************************************************************
// pop_heap
// 删除最大堆中的最大数据(即位于 first 处的数据)，并调整最大堆
// 用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator>
void 
pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
    MoperSTL::iter_swap(first, --last); 
    MoperSTL::__adjust_heap(first, last, first);
}

//***********************************************************************************************************
// pop_heap
// 删除最大堆中的最大数据(即位于 first 处的数据)，并调整最大堆
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Compare>
void 
pop_heap(RandomAccessIterator first, RandomAccessIterator last,
         Compare comp) {
    MoperSTL::iter_swap(first, --last);
    MoperSTL::__adjust_heap(first, last, first, comp);
}

//***********************************************************************************************************
// make_heap
// 在范围 [first, last) 中构造最大堆
// 用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator>
void 
make_heap(RandomAccessIterator first, RandomAccessIterator last) {
    for (auto len = (last - first) / 2 - 1; len >= 0; --len) {
        MoperSTL::__adjust_heap(first, last, first + len);
    }
}

//***********************************************************************************************************
// make_heap
// 在范围 [first, last) 中构造最大堆
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Compare>
void 
make_heap(RandomAccessIterator first, RandomAccessIterator last,
          Compare comp) {
    for (auto len = (last - first) / 2 - 1; len >= 0; --len) {
        MoperSTL::__adjust_heap(first, last, first + len, comp);
    }
}

//***********************************************************************************************************
// sort_heap
// 转换最大堆 [first, last) 为以升序排序的范围
// 产生的范围不再拥有堆属性
// 用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator>
void 
sort_heap(RandomAccessIterator first, RandomAccessIterator last) {
    while (first != last) {
        MoperSTL::pop_heap(first, last--);
    }
}

//***********************************************************************************************************
// sort_heap
// 转换最大堆 [first, last) 为以升序排序的范围
// 产生的范围不再拥有堆属性
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Compare>
void 
sort_heap(RandomAccessIterator first, RandomAccessIterator last,
          Compare comp) {
    while (first != last) {
        MoperSTL::pop_heap(first, last--, comp);
    }
}

//***********************************************************************************************************
// is_heap_until
// 检验范围 [first, last) 并寻找始于 first 且为最大堆的最大范围
// 用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator>
RandomAccessIterator
is_heap_until(RandomAccessIterator first, RandomAccessIterator last) {
    using dift = typename iterator_traits<RandomAccessIterator>::difference_type;

    const dift Size = MoperSTL::distance(first, last);
    if (Size >= 2) {
        for (dift i = 1; i < Size; ++i) {
            dift parent_index = (i - 1) / 2;
            if (*(first + parent_index) < *(first + i)) return first + i;
        }
    }
    return last;
}

//***********************************************************************************************************
// is_heap_until
// 检验范围 [first, last) 并寻找始于 first 且为最大堆的最大范围
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Compare>
RandomAccessIterator
is_heap_until(RandomAccessIterator first, RandomAccessIterator last,
              Compare comp) {
    using dift = typename iterator_traits<RandomAccessIterator>::difference_type;

    const dift Size = MoperSTL::distance(first, last);
    if (Size >= 2) {
        for (dift i = 1; i < Size; ++i) {
            dift parent_index = (i - 1) / 2;
            if (comp(*(first + parent_index), *(first + i))) return first + i;
        }
    }
    return last;
}

//***********************************************************************************************************
// is_heap
// 检查范围[first, last) 中的元素是否为最大堆
// 用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator>
bool 
is_heap(RandomAccessIterator first, RandomAccessIterator last) {
    return MoperSTL::is_heap_until(first, last) == last;
}

//***********************************************************************************************************
// is_heap
// 检查范围[first, last) 中的元素是否为最大堆
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Compare>
bool 
is_heap(RandomAccessIterator first, RandomAccessIterator last,
        Compare comp) {
    return MoperSTL::is_heap_until(first, last, comp) == last;
}


//***************************************************************
// 
// 
// 集合操作（在已排序范围上）
// 
// 
//***************************************************************


//***********************************************************************************************************
// merge
// 归并二个已排序范围 [first1, last1) 和 [first2, last2) 到始于 result 的一个已排序范围中
// 用 operator< 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator 
merge(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2,
      OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first2 < *first1) *result++ = *first2++;
        else  *result++ = *first1++;
    }
    if (first1 != last1) return MoperSTL::copy(first1, last1, result);
    else return MoperSTL::copy(first2, last2, result);
}

//***********************************************************************************************************
// merge
// 归并二个已排序范围 [first1, last1) 和 [first2, last2) 到始于 result 的一个已排序范围中
// 用 comp 比较元素
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator 
merge(InputIterator1 first1, InputIterator1 last1,
      InputIterator2 first2, InputIterator2 last2,
      OutputIterator result, Compare comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first2, *first1)) *result++ = *first2++;
        else  *result++ = *first1++;
    }
    if (first1 != last1) return MoperSTL::copy(first1, last1, result);
    else return MoperSTL::copy(first2, last2, result);
}

//***********************************************************************************************************
// merge_backward
// 反向归并二个已排序范围 [first1, last1) 和 [first2, last2) 到终于 result 的一个已排序范围中
// 用 operator< 比较元素
//***********************************************************************************************************
template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator1
merge_backward(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
               BidirectionalIterator2 first2, BidirectionalIterator2 last2,
               BidirectionalIterator1 result) {
    while (first1 != last1 && first2 != last2) {
        if (*MoperSTL::prev(last2) < *MoperSTL::prev(last1)) *--result = *--last1;
        else *--result = *--last2;
    }
    if (first1 != last1) return MoperSTL::copy_backward(first1, last1, result);
    else return MoperSTL::copy_backward(first2, last2, result);
}

//***********************************************************************************************************
// merge_backward
// 反向归并二个已排序范围 [first1, last1) 和 [first2, last2) 到终于 result 的一个已排序范围中
// 用 comp 比较元素
//***********************************************************************************************************
template<class BidirectionalIterator1, class BidirectionalIterator2, class Compare>
BidirectionalIterator1
merge_backward(BidirectionalIterator1 first1, BidirectionalIterator1 last1,
               BidirectionalIterator2 first2, BidirectionalIterator2 last2,
               BidirectionalIterator1 result, Compare comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*MoperSTL::prev(last2), *MoperSTL::prev(last1))) *--result = *--last1;
        else *--result = *--last2;
    }
    if (first1 != last1) return MoperSTL::copy_backward(first1, last1, result);
    else return MoperSTL::copy_backward(first2, last2, result);
}

//***********************************************************************************************************
// inplace_merge
// 归并二个相继的已排序范围 [first, middle) 及 [middle, last) 为一个已排序范围 [first, last)的一个已排序范围中
// 用 operator< 比较元素
//***********************************************************************************************************

// 无缓冲区的情况下合并
template<class BidirectionalIterator>
void
__merge_without_buffer(BidirectionalIterator first,
                       BidirectionalIterator middle,
                       BidirectionalIterator last) {
    while (first != middle && middle != last) {
        first = MoperSTL::upper_bound(first, middle, *middle);
        if (first == middle) return;
        BidirectionalIterator cut = MoperSTL::lower_bound(middle, last, *first);
        first = MoperSTL::rotate(first, middle, cut);
        middle = cut;
    }
}

// 有缓冲区的情况下合并
template<class BidirectionalIterator, class Pointer, class Distance1, class Distance2>
void 
__merge_adaptive(BidirectionalIterator first, 
                 BidirectionalIterator middle,
                 BidirectionalIterator last,
                 Distance1 len1, Distance1 len2,
                 Pointer buffer, Distance2 buffer_size) {
    if (len1 <= len2 && len1 <= buffer_size) {
        Pointer buffer_end = MoperSTL::copy(first, middle, buffer);
        MoperSTL::merge(buffer, buffer_end, middle, last, first);
    } else if (len2 <= buffer_size) {
        Pointer buffer_end = MoperSTL::copy(middle, last, buffer);
        MoperSTL::merge_backward(first, middle, buffer, buffer_end, last);
    } else {
        BidirectionalIterator first_cut = first;
        BidirectionalIterator second_cut = middle;
        Distance1 len11 = 0;
        Distance1 len22 = 0;
        if (len1 > len2) {
            len11 = len1 / 2;
            MoperSTL::advance(first_cut, len11);
            second_cut = MoperSTL::lower_bound(middle, last, *first_cut);
            len22 = MoperSTL::distance(middle, second_cut);
        } else {
            len22 = len2 / 2;
            MoperSTL::advance(second_cut, len22);
            first_cut = MoperSTL::upper_bound(first, middle, *second_cut);
            len11 = MoperSTL::distance(first, first_cut);
        }
        BidirectionalIterator new_middle = MoperSTL::rotate(first_cut, middle, second_cut);
        MoperSTL::__merge_adaptive(first, first_cut, new_middle, len11, len22, buffer, buffer_size);
        MoperSTL::__merge_adaptive(new_middle, second_cut, last, len1 - len11, len2 - len22, buffer, buffer_size);
    }
}

template<class BidirectionalIterator>
void
inplace_merge(BidirectionalIterator first,
              BidirectionalIterator middle,
              BidirectionalIterator last) {
    if (first == middle || middle == last) return;
    using value_type = typename MoperSTL::iterator_traits<BidirectionalIterator>::value_type;
    const MoperSTL::pair<value_type*, std::ptrdiff_t> buffer = MoperSTL::get_temporary_buffer<value_type>(MoperSTL::distance(first, last));
    // 有缓冲区
    if (buffer.first != nullptr) {
        const auto len1 = MoperSTL::distance(first, middle);
        const auto len2 = MoperSTL::distance(middle, last);
        MoperSTL::__merge_adaptive(first, middle, last, len1, len2, buffer.first, buffer.second);
        // 释放缓冲区
        MoperSTL::return_temporary_buffer(buffer.first);
    }
    // 没有缓冲区
    else {
        MoperSTL::__merge_without_buffer(first, middle, last);
    }
}

//***********************************************************************************************************
// inplace_merge
// 归并二个相继的已排序范围 [first, middle) 及 [middle, last) 为一个已排序范围 [first, last)
// 用 comp 比较元素
//***********************************************************************************************************

// 无缓冲区的情况下合并
template<class BidirectionalIterator, class Compare>
void
__merge_without_buffer(BidirectionalIterator first,
                       BidirectionalIterator middle,
                       BidirectionalIterator last,
                       Compare comp) {
    while (first != middle && middle != last) {
        first = MoperSTL::upper_bound(first, middle, *middle, comp);
        if (first == middle) return;
        BidirectionalIterator cut = MoperSTL::lower_bound(middle, last, *first, comp);
        first = MoperSTL::rotate(first, middle, cut);
        middle = cut;
    }
}

// 有缓冲区的情况下合并
template<class BidirectionalIterator, class Pointer, class Distance1, class Distance2, class Compare>
void
__merge_adaptive(BidirectionalIterator first,
                 BidirectionalIterator middle,
                 BidirectionalIterator last,
                 Distance1 len1, Distance1 len2,
                 Pointer buffer, Distance2 buffer_size,
                 Compare comp) {
    if (len1 <= len2 && len1 <= buffer_size) {
        Pointer buffer_end = MoperSTL::copy(first, middle, buffer);
        MoperSTL::merge(buffer, buffer_end, middle, last, first, comp);
    } else if (len2 <= buffer_size) {
        Pointer buffer_end = MoperSTL::copy(middle, last, buffer);
        MoperSTL::merge_backward(first, middle, buffer, buffer_end, last, comp);
    } else {
        BidirectionalIterator first_cut = first;
        BidirectionalIterator second_cut = middle;
        Distance1 len11 = 0;
        Distance1 len22 = 0;
        if (len1 > len2) {
            len11 = len1 / 2;
            MoperSTL::advance(first_cut, len11);
            second_cut = MoperSTL::lower_bound(middle, last, *first_cut, comp);
            len22 = MoperSTL::distance(middle, second_cut);
        } else {
            len22 = len2 / 2;
            MoperSTL::advance(second_cut, len22);
            first_cut = MoperSTL::upper_bound(first, middle, *second_cut, comp);
            len11 = MoperSTL::distance(first, first_cut);
        }
        BidirectionalIterator new_middle = MoperSTL::rotate(first_cut, middle, second_cut);
        MoperSTL::__merge_adaptive(first, first_cut, new_middle, len11, len22, buffer, buffer_size, comp);
        MoperSTL::__merge_adaptive(new_middle, second_cut, last, len1 - len11, len2 - len22, buffer, buffer_size, comp);
    }
}

template<class BidirectionalIterator, class Compare>
void
inplace_merge(BidirectionalIterator first,
              BidirectionalIterator middle,
              BidirectionalIterator last,
              Compare comp) {
    if (first == middle || middle == last) return;
    using value_type = typename MoperSTL::iterator_traits<BidirectionalIterator>::value_type;
    const MoperSTL::pair<value_type*, std::ptrdiff_t> buffer = MoperSTL::get_temporary_buffer<value_type>(MoperSTL::distance(first, last));
    // 有缓冲区
    if (buffer.first != nullptr) {
        const auto len1 = MoperSTL::distance(first, middle);
        const auto len2 = MoperSTL::distance(middle, last);
        MoperSTL::__merge_adaptive(first, middle, last, len1, len2, buffer.first, buffer.second, comp);
        // 释放缓冲区
        MoperSTL::return_temporary_buffer(buffer.first);
    }
    // 没有缓冲区
    else {
        MoperSTL::__merge_without_buffer(first, middle, last, comp);
    }
}

//***********************************************************************************************************
// includes
// 若已排序范围 [first2, last2) 是已排序范围 [first1, last1) 的子序列则返回 true
// 两个范围都必须以 operator< 排序
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2>
bool 
includes(InputIterator1 first1, InputIterator1 last1,
         InputIterator2 first2, InputIterator2 last2) {
    while (first2 != last2 && first1 != last1) {
        if (*first2 < *first1) return false;
        if (!(*first1 < *first2)) ++first2;
    }
    if (first2 == last2) return true;
    else return false;
}

//***********************************************************************************************************
// inplace_merge
// 若已排序范围 [first2, last2) 是已排序范围 [first1, last1) 的子序列则返回 true
// 两个范围都必须以给定的比较函数 comp 排序
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class Compare>
bool 
includes(InputIterator1 first1, InputIterator1 last1,
         InputIterator2 first2, InputIterator2 last2,
         Compare comp) {
    while (first2 != last2 && first1 != last1) {
        if (comp(*first2, *first1)) return false;
        if (!comp(*first1, *first2)) ++first2;
    }
    if (first2 == last2) return true;
    else return false;
}

//***********************************************************************************************************
// set_union
// 求并集
// 将 [first1, last1) 与 [first2, last2) 中元素的并集存放到 result 中
// 两个范围都必须以 operator< 排序
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator 
set_union(InputIterator1 first1, InputIterator1 last1,
          InputIterator2 first2, InputIterator2 last2,
          OutputIterator result) {
    for (; first1 != last1 && first2 != last2; ++result) {
        *result = MoperSTL::min(*first1, *first2);
        if (!(*result < *first1)) ++first1;
        if (!(*result < *first2)) ++first2;
    }
    if (first1 != last1) return MoperSTL::copy(first1, last1, result);
    else return MoperSTL::copy(first2, last2, result);
}

//***********************************************************************************************************
// set_union
// 求并集
// 将 [first1, last1) 与 [first2, last2) 中元素的并集存放到 result 中
// 两个范围都必须以给定的比较函数 comp 排序
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator 
set_union(InputIterator1 first1, InputIterator1 last1,
          InputIterator2 first2, InputIterator2 last2,
          OutputIterator result, Compare comp) {
    for (; first1 != last1 && first2 != last2; ++result) {
        *result = MoperSTL::min(*first1, *first2, comp);
        if (!comp(*result, *first1)) ++first1;
        if (!comp(*result, *first2)) ++first2;
    }
    if (first1 != last1) return MoperSTL::copy(first1, last1, result);
    else return MoperSTL::copy(first2, last2, result);
}

//***********************************************************************************************************
// set_intersection
// 求交集
// 将 [first1, last1) 与 [first2, last2) 中元素的交集存放到 result 中
// 两个范围都必须以 operator< 排序
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator 
set_intersection(InputIterator1 first1, InputIterator1 last1,
                 InputIterator2 first2, InputIterator2 last2,
                 OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) ++first1;
        else if (*first2 < *first1) ++first2;
        else {
            *result++ = *first1;
            ++first1;
            ++first2;
        }
    }
    return result;
}

//***********************************************************************************************************
// set_intersection
// 求交集
// 将 [first1, last1) 与 [first2, last2) 中元素的交集存放到 result 中
// 两个范围都必须以给定的比较函数 comp 排序
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator 
set_intersection(InputIterator1 first1, InputIterator1 last1,
                 InputIterator2 first2, InputIterator2 last2,
                 OutputIterator result, Compare comp) {
    while (first1 != last1 && first2 != last2) {
         if (comp(*first1, *first2)) ++first1;
         else if (comp(*first2, *first1)) ++first2;
         else {
            *result++ = *first1;
            ++first1;
            ++first2;
        }
    }
    return result;
}

//***********************************************************************************************************
// set_intersection
// 求差
// 将 [first1, last1) 与 [first2, last2) 中元素的差存放到 result 中
// 两个范围都必须以 operator< 排序
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator 
set_difference(InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, InputIterator2 last2,
               OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) *result++ = *first1++;
        else {
            if (!(*first2 < *first1)) ++first1;
            ++first2;
        }
    }
    if (first1 != last1) MoperSTL::copy(first1, last1, result);
    return result;
}

//***********************************************************************************************************
// set_intersection
// 求差
// 将 [first1, last1) 与 [first2, last2) 中元素的差存放到 result 中
// 两个范围都必须以给定的比较函数 comp 排序
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator 
set_difference(InputIterator1 first1, InputIterator1 last1,
               InputIterator2 first2, InputIterator2 last2,
               OutputIterator result, Compare comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first1, *first2)) *result++ = *first1++;
        else {
            if (!comp(*first2, *first1)) ++first1;
            ++first2;
        }
    }
    if (first1 != last1) MoperSTL::copy(first1, last1, result);
    return result;
}

//***********************************************************************************************************
// set_symmetric_difference
// 求对称差
// 将 [first1, last1) 与 [first2, last2) 中元素的对称差存放到 result 中
// 两个范围都必须以 operator< 排序
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class OutputIterator>
OutputIterator 
set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first1 < *first2) *result++ = *first1++;
        else if (*first2 < *first1) *result++ = *first2++;
        else {
            ++first1;
            ++first2;
        }
    }
    if (first1 != last1) return MoperSTL::copy(first1, last1, result);
    else return MoperSTL::copy(first2, last2, result);
}

//***********************************************************************************************************
// set_symmetric_difference
// 求对称差
// 将 [first1, last1) 与 [first2, last2) 中元素的对称差存放到 result 中
// 两个范围都必须以给定的比较函数 comp 排序
//***********************************************************************************************************
template<class InputIterator1, class InputIterator2, class OutputIterator, class Compare>
OutputIterator 
set_symmetric_difference(InputIterator1 first1, InputIterator1 last1,
                         InputIterator2 first2, InputIterator2 last2,
                         OutputIterator result, Compare comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first1, *first2)) *result++ = *first1++;
        else if (comp(*first2, *first1)) *result++ = *first2++;
        else {
            ++first1;
            ++first2;
        }
    }
    if (first1 != last1) return MoperSTL::copy(first1, last1, result);
    else return MoperSTL::copy(first2, last2, result);

}


//***************************************************************
// 
// 
// 排序操作
// 
// 
//***************************************************************


//***********************************************************************************************************
// partial_sort
// 采用堆排序重排元素，使得范围 [first, middle) 含有范围 [first, last) 中已排序的 middle - first 个最小元素
// 不保证保持相等的元素顺序
// 范围 [middle, last) 中剩余的元素顺序未指定
//  用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator>
void
partial_sort(RandomAccessIterator first,
             RandomAccessIterator middle,
             RandomAccessIterator last) {
    MoperSTL::make_heap(first, middle);
    for (RandomAccessIterator it = middle; it != last; ++it) {
        if (*it < *first) {
            MoperSTL::iter_swap(first, it);
            MoperSTL::__adjust_heap(first, middle, first);
        }
    }
    MoperSTL::sort_heap(first, middle);
}

//***********************************************************************************************************
// partial_sort
// 采用堆排序重排元素，使得范围 [first, middle) 含有范围 [first, last) 中已排序的 middle - first 个最小元素
// 不保证保持相等的元素顺序
// 范围 [middle, last) 中剩余的元素顺序未指定
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Compare>
void
partial_sort(RandomAccessIterator first,
             RandomAccessIterator middle,
             RandomAccessIterator last,
             Compare comp) {
    MoperSTL::make_heap(first, middle);
    for (RandomAccessIterator it = middle; it != last; ++it) {
        if (comp(*it, *first)) {
            MoperSTL::iter_swap(first, it);
            MoperSTL::__adjust_heap(first, middle, first, comp);
        }
    }
    MoperSTL::sort_heap(first, middle, comp);
}

//***********************************************************************************************************
// partial_sort_copy
// 堆排序范围 [first, last) 中的某些元素，存储结果于范围 [d_first, d_last)
// 用 operator< 比较元素
//***********************************************************************************************************
template<class InputIterator, class RandomAccessIterator>
RandomAccessIterator
partial_sort_copy(InputIterator first, InputIterator last,
                  RandomAccessIterator result_first, RandomAccessIterator result_last) {
    if (first == last) return result_first;
    if (result_first == result_last) return result_last;

    RandomAccessIterator it = result_first;
    while (first != last && it != result_last) {
        *it++ = *first++;
    }
    MoperSTL::make_heap(result_first, it);
    for (; first != last; ++first) {
        if (*first < *result_first) {
            *result_first = *first;
            MoperSTL::__adjust_heap(result_first, it, result_first);
        }
    }
    MoperSTL::sort_heap(result_first, it);
    return it;
}

//***********************************************************************************************************
// partial_sort_copy
// 堆排序范围 [first, last) 中的某些元素，存储结果于范围 [d_first, d_last)
// 用 comp 比较元素
//***********************************************************************************************************
template<class InputIterator, class RandomAccessIterator, class Compare>
RandomAccessIterator
partial_sort_copy(InputIterator first, InputIterator last,
                  RandomAccessIterator result_first, RandomAccessIterator result_last,
                  Compare comp) {
    if (first == last) return result_first;
    if (result_first == result_last) return result_last;

    RandomAccessIterator it = result_first;
    while (first != last && it != result_last) {
        *it++ = *first++;
    }
    MoperSTL::make_heap(result_first, it, comp);
    for (; first != last; ++first) {
        if (comp(*first, *result_first)) {
            *result_first = *first;
            MoperSTL::__adjust_heap(result_first, it, result_first, comp);
        }
    }
    MoperSTL::sort_heap(result_first, it, comp);
    return it;
}

// 用于帮助 sort 函数判断何时使用插入排序
const static std::size_t __sort_max_size = 16;

//***********************************************************************************************************
// __insert_sort
// 插入排序 [first, last) 中的元素
// 用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator>
void
__insert_sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (first == last) return;

    for (RandomAccessIterator i = first + 1; i != last; ++i) {
        auto value = *i;
        RandomAccessIterator j = i;
        while (j != first && value < *(j - 1)) {
            *j = *(j - 1);
            --j;
        }
        *j = value;
    }
}

//***********************************************************************************************************
// __insert_sort
// 插入排序 [first, last) 中的元素
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Compare>
void
__insert_sort(RandomAccessIterator first, RandomAccessIterator last,
              Compare comp) {
    if (first == last) return;

    for (RandomAccessIterator i = first + 1; i != last; ++i) {
        auto value = *i;
        RandomAccessIterator j = i;
        while (j != first && comp(value, *(j - 1))) {
            *j = *(j - 1);
            --j;
        }
        *j = value;
    }
}

//***********************************************************************************************************
// __unguarded_partition
// 对[first, last) 中的元素做一趟快速排序, 并返回枢轴位置
// 用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class T>
RandomAccessIterator
__unguarded_partition(RandomAccessIterator first, RandomAccessIterator last,
                      T target) {
    while (true) {
        // 从前往后找到第一个不小于 target 的元素
        while (*first < target) ++first;
        // 从后往前找到第一个不大于 target 的元素
        while (target < *--last);
        // 如果此时 first 不处于 last 的前方，则排序完毕
        if (!(first < last)) return first;
        // 排序
        MoperSTL::iter_swap(first, last);
        ++first;
    }
}

//***********************************************************************************************************
// __unguarded_partition
// 对[first, last) 中的元素做一趟快速排序, 并返回枢轴位置
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class T, class Compare>
RandomAccessIterator
__unguarded_partition(RandomAccessIterator first, RandomAccessIterator last,
                      T target, Compare comp) {
    while (true) {
        // 从前往后找到第一个不小于 target 的元素
        while (comp(*first, target)) ++first;
        // 从后往前找到第一个不大于 target 的元素
        while (comp(target, *--last));
        // 如果此时 first 不处于 last 的前方，则排序完毕
        if (!(first < last)) return first;
        // 排序
        MoperSTL::iter_swap(first, last);
        ++first;
    }
}

//***********************************************************************************************************
// __intro_sort
// 内省式排序
// 首先进行 quick sort，当分割行为有恶化为二次方的倾向时，使用 heap sort
// 用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Size>
void
__intro_sort(RandomAccessIterator first, RandomAccessIterator last,
             Size depth) {
    if (last - first <= MoperSTL::__sort_max_size) return;

    if (depth == 0) {
        MoperSTL::partial_sort(first, last, last);
        return;
    } else {
        auto mid = MoperSTL::median(*first, *(first + (last - first) / 2), *(last - 1));
        RandomAccessIterator cur = MoperSTL::__unguarded_partition(first, last, mid);
        MoperSTL::__intro_sort(first, cur, depth - 1);
        MoperSTL::__intro_sort(cur, last, depth - 1);
    }
}

//***********************************************************************************************************
// __intro_sort
// 内省式排序
// 首先进行 quick sort，当分割行为有恶化为二次方的倾向时，使用 heap sort
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Size, class Compare>
void
__intro_sort(RandomAccessIterator first, RandomAccessIterator last,
             Size depth, Compare comp) {
    if (last - first <= MoperSTL::__sort_max_size) return;

    if (depth == 0) {
        MoperSTL::partial_sort(first, last, last, comp);
        return;
    } else {
        auto mid = MoperSTL::median(*first, *(first + (last - first) / 2), *(last - 1));
        RandomAccessIterator cur = MoperSTL::__unguarded_partition(first, last, mid, comp);
        MoperSTL::__intro_sort(first, cur, depth - 1, comp);
        MoperSTL::__intro_sort(cur, last, depth - 1, comp);
    }
}

//***********************************************************************************************************
// __lg
// 获取lg n （向下取整）
//***********************************************************************************************************
template<class Size>
inline Size __lg(Size n) {
    Size result;
    for (result = 0; n > 1; n >>= 1) ++result;
    return result;
}

//***********************************************************************************************************
// sort
// 检以升序排序范围 [first, last) 中的元素
// 不保证维持相等元素的顺序
// 用 operator< 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator>
void
sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (first != last) {
        MoperSTL::__intro_sort(first, last, MoperSTL::__lg(last - first) * 2);
        MoperSTL::__insert_sort(first, last);
    }
}

//***********************************************************************************************************
// sort
// 以升序排序范围 [first, last) 中的元素
// 不保证维持相等元素的顺序
// 用 comp 比较元素
//***********************************************************************************************************
template<class RandomAccessIterator, class Compare>
void
sort(RandomAccessIterator first, RandomAccessIterator last,
     Compare comp) {
    if (first != last) {
        MoperSTL::__intro_sort(first, last, MoperSTL::__lg(last - first) * 2, comp);
        MoperSTL::__insert_sort(first, last, comp);
    }
}

//***********************************************************************************************************
// stable_sort
// 以升序排序范围 [first, last) 中的元素
// 保证保持等价元素的顺序
// 用 operator< 比较元素
//***********************************************************************************************************

// 无缓冲区时合并算法
template<class RandomAccessIterator>
void
__inplace_stable_sort(RandomAccessIterator first,
                      RandomAccessIterator last) {
    const auto len = last - first;
    if (len < MoperSTL::__sort_max_size) {
        MoperSTL::__insert_sort(first, last);
    } else {
        RandomAccessIterator middle = MoperSTL::next(first, len / 2);
        MoperSTL::__inplace_stable_sort(first, middle);
        MoperSTL::__inplace_stable_sort(middle, last);
        MoperSTL::__merge_without_buffer(first, middle, last);
    }
}


template<class InputIterator, class OutputIterator>
OutputIterator
__move_merge(InputIterator first1, InputIterator last1,
             InputIterator first2, InputIterator last2,
             OutputIterator result) {
    while (first1 != last1 && first2 != last2) {
        if (*first2 < *first1) *result++ = MoperSTL::move(*first2++);
        else *result++ = MoperSTL::move(*first1++);
    }
    if (first1 != last1) return MoperSTL::move(first1, last1, result);
    else return MoperSTL::move(first2, last2, result);
}

template<class RandomAccessIterator1, class RandomAccessIterator2, class Distance>
void
__merge_sort_loop(RandomAccessIterator1 first, RandomAccessIterator1 last,
                  RandomAccessIterator2 result, Distance step_size) {
    const Distance two_step = 2 * step_size;
    while (last - first >= two_step) {
        result = MoperSTL::__move_merge(first, first + step_size,
                                        first + step_size, first + two_step,
                                        result);
        first += two_step;
    }
    step_size = MoperSTL::min(Distance(last - first), step_size);
    MoperSTL::__move_merge(first, first + step_size, 
                           first + step_size, last,
                           result);
}

template<class RandomAccessIterator, class Pointer>
void
__merge_sort_with_buffer(RandomAccessIterator first,
                         RandomAccessIterator last,
                         Pointer buffer) {
    using Distance = typename MoperSTL::iterator_traits<RandomAccessIterator>::difference_type;
    // 分而治之
    RandomAccessIterator it = first;
    while (it != last) {
        if (it + MoperSTL::__sort_max_size <= last) {
            MoperSTL::__insert_sort(it, it + MoperSTL::__sort_max_size);
            it += MoperSTL::__sort_max_size;
        } else {
            MoperSTL::__insert_sort(it, last);
            it = last;
        }
    }

    const Distance len = last - first;
    const Pointer buffer_end = buffer + len;
    Distance step_size = MoperSTL::__sort_max_size;

    while (step_size < len) {
        MoperSTL::__merge_sort_loop(first, last, buffer, step_size);
        step_size *= 2;
        MoperSTL::__merge_sort_loop(buffer, buffer_end, first, step_size);
        step_size *= 2;
    }


}

// 有缓冲区时合并算法 
template<class RandomAccessIterator, class Point, class Distance>
void
__stable_sort_adaptive(RandomAccessIterator first,
                       RandomAccessIterator last,
                       Point buffer, Distance buffer_size) {
    const auto len = (last - first + 1) / 2;
    const RandomAccessIterator middle = MoperSTL::next(first, len);
    if (len > buffer_size) {
        MoperSTL::__stable_sort_adaptive(first, middle, buffer, buffer_size);
        MoperSTL::__stable_sort_adaptive(first, middle, buffer, buffer_size);
    } else {
        MoperSTL::__merge_sort_with_buffer(first, middle, buffer);
        MoperSTL::__merge_sort_with_buffer(middle, last, buffer);
        const auto len1 = MoperSTL::distance(first, middle);
        const auto len2 = MoperSTL::distance(middle, last);
        MoperSTL::__merge_adaptive(first, middle, last, len1, len2, buffer, buffer_size);
    }
}

template<class RandomAccessIterator>
void
stable_sort(RandomAccessIterator first, RandomAccessIterator last) {
    if (first == last) return;
    using value_type = typename MoperSTL::iterator_traits<RandomAccessIterator>::value_type;
    const auto len = MoperSTL::distance(first, last);
    const pair<value_type*, std::ptrdiff_t> buffer = MoperSTL::get_temporary_buffer<value_type>(len);
    if (buffer.first != nullptr) {
        MoperSTL::__stable_sort_adaptive(first, last, buffer.first, buffer.second);
        MoperSTL::return_temporary_buffer(buffer.first);
    } else {
        MoperSTL::__inplace_stable_sort(first, last);
    }
}

//***********************************************************************************************************
// stable_sort
// 以升序排序范围 [first, last) 中的元素
// 保证保持等价元素的顺序
// 用 comp 比较元素
//***********************************************************************************************************

// 无缓冲区时合并算法
template<class RandomAccessIterator, class Compare>
void
__inplace_stable_sort(RandomAccessIterator first,
                      RandomAccessIterator last,
                      Compare comp) {
    const auto len = last - first;
    if (len < MoperSTL::__sort_max_size) {
        MoperSTL::__insert_sort(first, last, comp);
    } else {
        RandomAccessIterator middle = MoperSTL::next(first, len / 2);
        MoperSTL::__inplace_stable_sort(first, middle, comp);
        MoperSTL::__inplace_stable_sort(middle, last, comp);
        MoperSTL::__merge_without_buffer(first, middle, last, comp);
    }
}

template<class InputIterator, class OutputIterator, class Compare>
OutputIterator
__move_merge(InputIterator first1, InputIterator last1,
             InputIterator first2, InputIterator last2,
             OutputIterator result, Compare comp) {
    while (first1 != last1 && first2 != last2) {
        if (comp(*first2, *first1)) *result++ = MoperSTL::move(*first2++);
        else *result++ = MoperSTL::move(*first1++);
    }
    if (first1 != last1) return MoperSTL::move(first1, last1, result);
    else return MoperSTL::move(first2, last2, result);
}

template<class RandomAccessIterator1, class RandomAccessIterator2,
         class Distance, class Compare>
void
__merge_sort_loop(RandomAccessIterator1 first, RandomAccessIterator1 last,
                  RandomAccessIterator2 result, 
                  Distance step_size, Compare comp) {
    const Distance two_step = 2 * step_size;
    while (last - first >= two_step) {
        result = MoperSTL::__move_merge(first, first + step_size,
                                        first + step_size, first + two_step,
                                        result, comp);
        first += two_step;
    }
    step_size = MoperSTL::min(Distance(last - first), step_size);
    MoperSTL::__move_merge(first, first + step_size,
                           first + step_size, last,
                           result, comp);
}

template<class RandomAccessIterator, class Pointer, class Compare>
void
__merge_sort_with_buffer(RandomAccessIterator first,
                         RandomAccessIterator last,
                         Pointer buffer, Compare comp) {
    using Distance = typename MoperSTL::iterator_traits<RandomAccessIterator>::difference_type;
    // 分而治之
    RandomAccessIterator it = first;
    while (it != last) {
        if (it + MoperSTL::__sort_max_size <= last) {
            MoperSTL::__insert_sort(it, it + MoperSTL::__sort_max_size, comp);
            it += MoperSTL::__sort_max_size;
        } else {
            MoperSTL::__insert_sort(it, last, comp);
            it = last;
        }
    }

    const Distance len = last - first;
    const Pointer buffer_end = buffer + len;
    Distance step_size = MoperSTL::__sort_max_size;

    while (step_size < len) {
        MoperSTL::__merge_sort_loop(first, last, buffer, step_size, comp);
        step_size *= 2;
        MoperSTL::__merge_sort_loop(buffer, buffer_end, first, step_size, comp);
        step_size *= 2;
    }


}

// 有缓冲区时合并算法 
template<class RandomAccessIterator, class Point, 
         class Distance, class Compare>
void
__stable_sort_adaptive(RandomAccessIterator first,
                       RandomAccessIterator last,
                       Point buffer, Distance buffer_size,
                       Compare comp) {
    const auto len = (last - first + 1) / 2;
    const RandomAccessIterator middle = MoperSTL::next(first, len);
    if (len > buffer_size) {
        MoperSTL::__stable_sort_adaptive(first, middle, buffer, buffer_size, comp);
        MoperSTL::__stable_sort_adaptive(first, middle, buffer, buffer_size, comp);
    } else {
        MoperSTL::__merge_sort_with_buffer(first, middle, buffer, comp);
        MoperSTL::__merge_sort_with_buffer(middle, last, buffer, comp);
        const auto len1 = MoperSTL::distance(first, middle);
        const auto len2 = MoperSTL::distance(middle, last);
        MoperSTL::__merge_adaptive(first, middle, last, len1, len2, buffer, buffer_size, comp);
    }
}

template<class RandomAccessIterator, class Compare>
void
stable_sort(RandomAccessIterator first, RandomAccessIterator last,
            Compare comp) {
    if (first == last) return;
    using value_type = typename MoperSTL::iterator_traits<RandomAccessIterator>::value_type;
    const auto len = MoperSTL::distance(first, last);
    const pair<value_type*, std::ptrdiff_t> buffer = MoperSTL::get_temporary_buffer<value_type>(len);
    if (buffer.first != nullptr) {
        MoperSTL::__stable_sort_adaptive(first, last, buffer.first, buffer.second, comp);
        MoperSTL::return_temporary_buffer(buffer.first);
    } else {
        MoperSTL::__inplace_stable_sort(first, last, comp);
    }
}

//***********************************************************************************************************
// is_sorted_until
// 检验范围 [first, last) ，并寻找始于 first 且其中元素已以升序排序的最大范围
// 用 operator< 比较元素
//***********************************************************************************************************
template<class ForwardIterator>
ForwardIterator
is_sorted_until(ForwardIterator first, ForwardIterator last) {
    if (first == last) return last;
    ForwardIterator next = first;
    while (++next != last) {
        if (*next < *first) return next;
        else first = next;
    }
    return last;
}

//***********************************************************************************************************
// is_sorted_until
// 检验范围 [first, last) ，并寻找始于 first 且其中元素已以升序排序的最大范围
// 用 comp 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class Compare>
ForwardIterator
is_sorted_until(ForwardIterator first, ForwardIterator last,
                Compare comp) {
    if (first == last) return last;
    ForwardIterator next = first;
    while (++next != last) {
        if (comp(*next, *first)) return next;
        else first = next;
    }
    return last;
}

//***********************************************************************************************************
// is_sorted
// 检查 [first, last) 中的元素是否以不降序排序
// 用 operator< 比较元素
//***********************************************************************************************************
template<class ForwardIterator>
bool
is_sorted(ForwardIterator first, ForwardIterator last) {
    return MoperSTL::is_sorted_until(first, last) == last;
}

//***********************************************************************************************************
// is_sorted
// 检查 [first, last) 中的元素是否以不降序排序
// 用 comp 比较元素
//***********************************************************************************************************
template<class ForwardIterator, class Compare>
bool
is_sorted(ForwardIterator first, ForwardIterator last,
          Compare comp) {
    return MoperSTL::is_sorted_until(first, last, comp) == last;
}

//***********************************************************************************************************
// nth_element
// 以升序部分排序范围 [first, last)
// 使得对于任何范围 [first, nth) 中的 i 和任何范围 [nth, last) 中的 j
// 都满足条件 !(*j < *i)
//***********************************************************************************************************
template<class RandomAccessIterator>
void
nth_element(RandomAccessIterator first, RandomAccessIterator nth,
            RandomAccessIterator last) {
    while (last - first > 3) {
        auto mid = MoperSTL::median(*first, *(first + (last - first) / 2, *(last - 1)));
        RandomAccessIterator cur = MoperSTL::__unguarded_partition(first, last, mid);
        if (cur <= nth) first = cur;
        else last = cur;
    }
    MoperSTL::__insert_sort(first, last);
}

//***********************************************************************************************************
// nth_element
// 以升序部分排序范围 [first, last)
// 使得对于任何范围 [first, nth) 中的 i 和任何范围 [nth, last) 中的 j
// 都满足条件 comp(*j, *i) == false
//***********************************************************************************************************
template<class RandomAccessIterator, class Compare>
void
nth_element(RandomAccessIterator first, RandomAccessIterator nth,
            RandomAccessIterator last, Compare comp) {
    while (last - first > 3) {
        auto mid = MoperSTL::median(*first, *(first + (last - first) / 2, *(last - 1)), comp);
        RandomAccessIterator cur = MoperSTL::__unguarded_partition(first, last, mid, comp);
        if (cur <= nth) first = cur;
        else last = cur;
    }
    MoperSTL::__insert_sort(first, last, comp);
}


}; /* MoperSTL */

#endif /* MOPER_STL_ALGORITHM_H */
