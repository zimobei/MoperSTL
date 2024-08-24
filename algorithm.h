#ifndef MOPER_STL_ALGORITHM_H
#define MOPER_STL_ALGORITHM_H

#include <cstring> // memmove()
#include <random> // std::uniform_int_distribution��rand()
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
// ���޸����еĲ���
// 
// 
//***************************************************************


//***********************************************************************************************************
// all_of
// ���һԪν�� pred �Ƿ�Է�Χ [first, last) ������Ԫ�ط��� true 
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
// ���һԪν�� pred �Ƿ�Է�Χ [first, last) ������һ��Ԫ�ط��� true
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
// ���һԪν�� pred �Ƿ񲻶Է�Χ [first, last) ���κ�Ԫ�ط��� true
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
// ��˳��Ӧ�ø����ĺ������� f �������÷�Χ [first, last) ��ÿ���������Ľ��
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
// ���ط�Χ [first, last) �������ض��б��׼��Ԫ����
// �������� value ��Ԫ��
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
// ���ط�Χ [first, last) �������ض��б��׼��Ԫ����
// ����ν�� pred ���䷵�� true ��Ԫ��
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
// �������� value ��Ԫ��
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
// ����ν�� pred ���䷵�� true ��Ԫ��
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
// ����ν�� pred ���䷵�� false ��Ԫ��
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
// ������Χ [first1, last1 - (last2 - first2)) ��Ԫ�������� [first2, last2) ���״γ���
// Ԫ���� operator== �Ƚ�
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
// ������Χ [first1, last1 - (last2 - first2)) ��Ԫ�������� [first2, last2) ���״γ���
// Ԫ���ø����Ķ�Ԫν�� pred �Ƚ�
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
// �ڷ�Χ [first, last) ������ count ����ͬԪ�ص����У�ÿ�������ڸ�����ֵ value 
// �� operator== �Ƚ�Ԫ��
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
// �ڷ�Χ [first, last) ������ count ����ͬԪ�ص����У�ÿ�������ڸ�����ֵ value 
// �ø����Ķ�Ԫν�� pred �Ƚ�Ԫ��
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
// �ڷ�Χ [first1, last1) ����������Ԫ������ [first2, last2)
// �� operator== �Ƚ�Ԫ��
//***********************************************************************************************************

// find_end �� forward_iterator_tag �汾
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

// find_end �� bidirectional_iterator_tag �汾
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
// �ڷ�Χ [first1, last1) ����������Ԫ������ [first2, last2)
// �ø����Ķ�Ԫν�� pred �Ƚ�Ԫ��
//***********************************************************************************************************

// find_end �� forward_iterator_tag �汾
// �ø����Ķ�Ԫν�� pred �Ƚ�Ԫ��
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

// find_end �� bidirectional_iterator_tag �汾
// �ø����Ķ�Ԫν�� pred �Ƚ�Ԫ��
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
// �ڷ�Χ [first1, last1) ��������Χ [first2, last2) �е��κ�Ԫ��
// �� operator== �Ƚ�Ԫ��
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
// �ڷ�Χ [first1, last1) ��������Χ [first2, last2) �е��κ�Ԫ��
// �ø����Ķ�Ԫν�� pred �Ƚ�Ԫ��
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
// �ڷ�Χ [first, last) ������������̵ĵ�ͬԪ��
// �� operator== �Ƚ�Ԫ��
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
// �ڷ�Χ [first, last) ������������̵ĵ�ͬԪ��
// �ø����Ķ�Ԫν�� p �Ƚ�Ԫ��
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
// �������Զ�����Χ��һ���� [first1, last1) �������һ���� [first2,last2) ���� ���׸���ƥ���
// �� operator== �Ƚ�Ԫ��
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
// �������Զ�����Χ��һ���� [first1, last1) �������һ���� [first2,last2) ���� ���׸���ƥ���
// �ø����Ķ�Ԫν�� p �Ƚ�Ԫ��
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
// �������Զ�����Χ��һ���� [first1, last1) �������һ���� [first2,last2) ���壬���׸���ƥ���
// ���ṩ last2��ʹ�� first2 + (last1 - first1) ��Ϊlast2 
// �� operator== �Ƚ�Ԫ��
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
// �������Զ�����Χ��һ���� [first1, last1) �������һ���� [first2,last2) ���壬���׸���ƥ���
// ���ṩ last2��ʹ�� first2 + (last1 - first1) ��Ϊlast2 
// �ø����Ķ�Ԫν�� pred �Ƚ�Ԫ��
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
// �����Χ [first1, last1) �ͷ�Χ [first2, last2) ��ȣ����� true �����򷵻� false
// �� operator== �Ƚ�Ԫ��
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
// �����Χ [first1, last1) �ͷ�Χ [first2, last2) ��ȣ����� true �����򷵻� false
// �����Ķ�Ԫν�� pred �Ƚ�Ԫ��
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
// �����Χ [first1, last1) �ͷ�Χ [first2, first2 + (last1 - first1)) ��ȣ����� true �����򷵻� false
// �� operator== �Ƚ�Ԫ��
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
// �����Χ [first1, last1) �ͷ�Χ [first2, first2 + (last1 - first1)) ��ȣ����� true �����򷵻� false
// �����Ķ�Ԫν�� pred �Ƚ�Ԫ��
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
// ��С/������
// 
// 
//***************************************************************


//***********************************************************************************************************
// min_element
// Ѱ�ҷ�Χ [first, last) �е���СԪ��
// �� operator< �Ƚ�Ԫ��
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
// Ѱ�ҷ�Χ [first, last) �е���СԪ��
// �� comp �Ƚ�Ԫ��
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
// ���� a �� b �Ľ�С��
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T> 
const T& min(const T& a, const T& b) {
    return b < a ? b : a;
}

//***********************************************************************************************************
// min
// ���� a �� b �Ľ�С��
// �� comp �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T, class Compare>
const T& min(const T& a, const T& b, Compare comp) {
    return comp(b, a) ? b : a;
}

//***********************************************************************************************************
// min
// ���� initializer_list ilist ��ֵ����С��
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T>
T min(std::initializer_list<T> t) {
    return *MoperSTL::min_element(t.begin(), t.end());
}

//***********************************************************************************************************
// min
// ���� initializer_list ilist ��ֵ����С��
// �� comp �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T, class Compare>
T min(std::initializer_list<T> t, Compare comp) {
    return *MoperSTL::min_element(t.begin(), t.end(), comp);
}

//***********************************************************************************************************
// max_element
// Ѱ�ҷ�Χ [first, last) �е����Ԫ��
// �� operator< �Ƚ�Ԫ��
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
// Ѱ�ҷ�Χ [first, last) �е����Ԫ��
// �� comp �Ƚ�Ԫ��
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
// ���� a �� b �Ľϴ���
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T> 
const T& max(const T& a, const T& b) {
    return a < b ? b : a;
}

//***********************************************************************************************************
// max
// ���� a �� b �Ľϴ���
// �� comp �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T, class Compare>
const T& max(const T& a, const T& b, Compare comp) {
    return comp(a, b) ? b : a;
}

//***********************************************************************************************************
// max
// ���� initializer_list ilist ��ֵ�������
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T>
T max(std::initializer_list<T> t) {
    return *MoperSTL::max_element(t.begin(), t.end());
}

//***********************************************************************************************************
// max
// ���� initializer_list ilist ��ֵ�������
// �� comp �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T, class Compare>
T max(std::initializer_list<T> t, Compare comp) {
    return *MoperSTL::max_element(t.begin(), t.end(), comp);
}

//***********************************************************************************************************
// minmax_element
// Ѱ�ҷ�Χ [first, last) ����С������Ԫ��
// �� operator< �Ƚ�Ԫ��
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
// Ѱ�ҷ�Χ [first, last) ����С������Ԫ��
// �� comp �Ƚ�Ԫ��
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
// ���ص� a �� b ��С�ͽϴ��ߵ�����
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T> 
MoperSTL::pair<const T&, const T&> 
minmax(const T& a, const T& b) {
    if (b < a)      return MoperSTL::pair<const T&, const T&>(b, a);
    else            return MoperSTL::pair<const T&, const T&>(a, b);
}

//***********************************************************************************************************
// minmax
// ���ص� a �� b ��С�ͽϴ��ߵ�����
// �� comp �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T, class Compare>
MoperSTL::pair<const T&, const T&> 
minmax(const T& a, const T& b, Compare comp) {
    if (comp(b, a))     return MoperSTL::pair<const T&, const T&>(b, a);
    else                return MoperSTL::pair<const T&, const T&>(a, b);
}

//***********************************************************************************************************
// minmax
// ���� initializer_list ilist ��ֵ����С�������
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T>
MoperSTL::pair<T, T> 
minmax(std::initializer_list<T> t) {
    auto p = MoperSTL::minmax_element(t.begin(), t.end());
    return MoperSTL::make_pair(*p.first, *p.second);
}

//***********************************************************************************************************
// minmax
// ���� initializer_list ilist ��ֵ����С�������
// �� comp �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T, class Compare>
MoperSTL::pair<T, T> 
minmax(std::initializer_list<T> t, Compare comp) {
    auto p = MoperSTL::minmax_element(t.begin(), t.end(), comp);
    return MoperSTL::make_pair(*p.first, *p.second);
}

//***********************************************************************************************************
// median
// ��������ֵ���м�ֵ
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T>
const T& median(const T& a, const T& b, const T& c) {
    if ((a < b && b < c) || (c < b && b < a)) return b;
    else if ((b < a && a < c) || (c < a && a < b)) return a;
    else return c;
}

//***********************************************************************************************************
// median
// ��������ֵ���м�ֵ
// �� comp �Ƚ�Ԫ��
//***********************************************************************************************************
template<class T, class Compare>
const T& median(const T& a, const T& b, const T& c, Compare comp) {
    if ((comp(a, b) && comp(b, c)) || (comp(c, b) && comp(b, a))) return b;
    else if ((comp(b, a) && comp(a, c)) || (comp(c, a) && comp(a, b))) return a;
    else return c;
}

//***********************************************************************************************************
// lexicographical_compare
// ����һ����Χ [first1, last1) �Ƿ��ֵ���С�ڵڶ�����Χ [first2, last2)
// �� operator< �Ƚ�Ԫ��
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
// ����һ����Χ [first1, last1) �Ƿ��ֵ���С�ڵڶ�����Χ [first2, last2)
// �� comp �Ƚ�Ԫ��
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
// �޸����еĲ���
// 
// 
//***************************************************************


//***********************************************************************************************************
// copy
// ���� [first, last) ������ķ�Χ�е�Ԫ�ص�ʼ�� result ����һ��Χ
//***********************************************************************************************************

// copy ��ͨ�汾
template<class InputIterator, class OutputIterator>
OutputIterator 
__copy(InputIterator first, InputIterator last, OutputIterator result) {
    while (first != last) {
        *result++ = *first++;
    }
    return result;
}

// copy Ϊ trivially_copy_assignable �����ṩ���ػ��汾
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
// ���� [first, last) ������ķ�Χ�е�Ԫ�ص�ʼ�� result ����һ��Χ
// ������ν�� pred ���䷵�� true ��Ԫ��
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
// �� count>0 ����׼ȷ��������ʼ�� first �ķ�Χ�� count ��ֵ��ʼ�� result �ķ�Χ
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
// �������� [first, last) �����巶Χ��Ԫ�أ������� result �ķ�Χ
// ��������Ԫ�أ����ȸ���ĩԪ�أ��������������˳��
//***********************************************************************************************************

// copy_backward ��ͨ�汾
template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2
__copy_backward(BidirectionalIterator1 first, BidirectionalIterator1 last,
                BidirectionalIterator2 result) {
    while (first != last) {
        *(--result) = *(--last);
    }
    return result;
}

// copy_backward Ϊ trivially_copy_assignable �����ṩ���ػ��汾
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
// �ƶ���Χ [first, last) �е�Ԫ�ص�ʼ�� result ����һ��Χ
// ����Ԫ�ؿ�ʼ��ε�ĩԪ��
// �˲������ƶ���Χ�е�Ԫ�ؽ���Ȼ�����ʺ����͵ĺϷ�ֵ�����������ƶ�ǰ��ֵ��ͬ
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
// �ƶ���Χ [first, last) �е�Ԫ�ص�ʼ�� result ����һ��Χ
// �������ƶ�Ԫ�أ����ȸ���ĩԪ�أ��������������˳��
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
// ���������ĵ�������ָ���Ԫ�ص�ֵ
//***********************************************************************************************************
template<class ForwardIterator1, class ForwardIterator2>
void 
iter_swap(ForwardIterator1 a, ForwardIterator2 b) {
    MoperSTL::swap(*a, *b);
}

//***********************************************************************************************************
// swap_ranges
// �ڷ�Χ [first1, last1) ��ʼ�� first2 ����һ��Χ�佻��Ԫ��
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
// Ӧ�ø����ĺ�������Χ [first, last) ���洢�����ʼ�� result ����һ��Χ
// Ӧ��һԪ���� op �� [first, last) ������ķ�Χ
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
// Ӧ�ø����ĺ�������Χ [first, last) ���洢�����ʼ�� result ����һ��Χ
// Ӧ�ö�Ԫ���� op �����Զ�����Χ��Ԫ�ضԣ�һ���� [first1, last1) ���壬����һ��ʼ�� first2 
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
// �� new_value �滻��Χ [first, last) �����е��� old_value ��Ԫ��
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
// �� new_value �滻��Χ [first, last) ������ν�� pred ���䷵�� true ��Ԫ��
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
// �������Է�Χ [first, last) ������Ԫ�ص�ʼ�� result �ķ�Χ
// ���� new_value  �滻���е��� old_value ��Ԫ��
// Դ��Ŀ�귶Χ�����ص�
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
// �������Է�Χ [first, last) ������Ԫ�ص�ʼ�� result �ķ�Χ
// ���� new_value �滻����ν�� pred �������� true ��Ԫ��
// Դ��Ŀ�귶Χ�����ص�
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
// ��ֵ������ value �� [first, last) �е�Ԫ��
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
// �� count > 0 ����ֵ������ value ��ʼ�� �ķ�Χ���� count ��Ԫ��
// �������κ���
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
// �Ը����������� gen �����ɵ�ֵ��ֵ��Χ [first, last) �е�ÿ��Ԫ��
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
// �� count>0 ����ֵ������������ gen �����ɵ�ֵ��ʼ�� first �ķ�Χ���� count ��Ԫ��
// �������κ���
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
// �ӷ�Χ [first, last) �Ƴ����е��� value ��Ԫ��
// �����ط�Χ�½�β��β�������
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
// �ӷ�Χ [first, last) �Ƴ����� pred ���������� true ��Ԫ��
// �����ط�Χ�½�β��β�������
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
// �������Է�Χ [first, last) ��Ԫ�ص�ʼ�� result ����һ��Χ
// �������е��� value ��Ԫ��
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
// �������Է�Χ [first, last) ��Ԫ�ص�ʼ�� result ����һ��Χ
// ��������ν�� pred ���䷵�� true ��Ԫ��
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
// ɾ����Χ [first, last) �������ظ���Ԫ��
// �����ط�Χ�����߼���β��β�������
// �� operator== �Ƚ�Ԫ��
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
// ɾ����Χ [first, last) �������ظ���Ԫ��
// �����ط�Χ�����߼���β��β�������
// �ø�����ν�� pred �Ƚ�Ԫ��
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
// ���Ʒ�Χ [first, last) ����������Ԫ�ص� result ����һ��Χ
// �� operator== �Ƚ�Ԫ��
//***********************************************************************************************************

// unique_copy �� forward_iterator_tag �汾
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

// unique_copy �� output_iterator_tag �汾
// ���� output iterator ֻ�ܽ���ֻ�����������Բ����� !(*result == *first) �������ж�
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
// ���Ʒ�Χ [first, last) ����������Ԫ�ص� result ����һ��Χ
//  �ø����Ķ�Ԫν�� pred �Ƚ�Ԫ��
//***********************************************************************************************************

// unique_copy �� forward_iterator_tag �汾
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

// unique_copy �� output_iterator_tag �汾
// ���� output iterator ֻ�ܽ���ֻ�����������Բ����� !(*result == *first) �������ж�
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
// ��ת [first, last) ��Χ�е�Ԫ��˳��
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
// �� [first, last) ��Χ��Ԫ�صķ�ת�汾���Ƶ� result ����һ��Χ
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
// ���� [first, last) �е�Ԫ�أ�ʹmiddle��Ϊ�·�Χ����Ԫ��
// 
// ������
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
// ���� [first, last) �е�Ԫ�ص� result ����һ��Χ
// ʹ middle Ϊ�·�Χ����Ԫ��
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
// �������
// 
// 
//***************************************************************


//***********************************************************************************************************
// is_permutation
// �����ڷ�Χ [first1, last1) ��Ԫ�ص����У�ʹ�ø÷�Χ���� [first2,last2) ���򷵻� true
// �� operator== �Ƚ�Ԫ��
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
// �����ڷ�Χ [first1, last1) ��Ԫ�ص����У�ʹ�ø÷�Χ���� [first2,last2) ���򷵻� true
// �� pred �Ƚ�Ԫ��
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
// �任��Χ [first, last) Ϊ�������а������ operator< ���ֵ�����¸�����
//***********************************************************************************************************
template<class BidirectionalIterator>
bool
next_permutation(BidirectionalIterator first, BidirectionalIterator last) {
    if (MoperSTL::distance(first, last) < 2) return false;

    BidirectionalIterator cur = MoperSTL::prev(last);
    BidirectionalIterator pr = MoperSTL::prev(cur);
    // �Ӻ���ǰ������Ѱ�ҵ�һ�� *pr < *cur �����
    while (pr != first && !(*pr < *cur)) {
        --pr;
        --cur;
    }
    if (!(*pr < *cur)) {
        if (pr == first) MoperSTL::reverse(first, last);
        return false;
    }
    // �� [cur, last) ��Ѱ�Ҵ��� *pr ����СԪ��
    // ����ǰ�� while ѭ����֪��[cur, last) ����������Ԫ�أ�ǰ��Ԫ��һ�����ڵ��ں��Ԫ��
    // ��ˣ����ҵ��ĵ�һ������ *pr ��Ԫ�ؼ�Ϊ [cur, last) �д��� *pr ����СԪ��
    for (cur = MoperSTL::prev(last); !(*pr < *cur); --cur);
    MoperSTL::iter_swap(pr, cur);
    MoperSTL::reverse(MoperSTL::next(pr), last);
    return true;
}

//***********************************************************************************************************
// next_permutation
// �任��Χ [first, last) Ϊ�������а������ comp ���ֵ�����¸�����
//***********************************************************************************************************
template<class BidirectionalIterator, class Compare>
bool
next_permutation(BidirectionalIterator first, BidirectionalIterator last,
                 Compare comp) {
    if (MoperSTL::distance(first, last) < 2) return false;

    BidirectionalIterator cur = MoperSTL::prev(last);
    BidirectionalIterator pr = MoperSTL::prev(cur);
    // �Ӻ���ǰ������Ѱ�ҵ�һ�� *pr < *cur �����
    while (pr != first && !comp(*pr, *cur)) {
        --pr;
        --cur;
    }
    if (!comp(*pr, *cur)) {
        if (pr == first) MoperSTL::reverse(first, last);
        return false;
    }
    // �� [cur, last) ��Ѱ�Ҵ��� *pr ����СԪ��
    // ����ǰ�� while ѭ����֪��[cur, last) ����������Ԫ�أ�ǰ��Ԫ��һ�����ڵ��ں��Ԫ��
    // ��ˣ����ҵ��ĵ�һ������ *pr ��Ԫ�ؼ�Ϊ [cur, last) �д��� *pr ����СԪ��
    for (cur = MoperSTL::prev(last); !comp(*pr, *cur); --cur);
    MoperSTL::iter_swap(pr, cur);
    MoperSTL::reverse(MoperSTL::next(pr), last);
    return true;
}

//***********************************************************************************************************
// prev_permutation
// �任��Χ [first, last) Ϊ�������а������ operator< ���ֵ�����ϸ�����
//***********************************************************************************************************
template<class BidirectionalIterator>
bool
prev_permutation(BidirectionalIterator first, BidirectionalIterator last) {
    if (MoperSTL::distance(first, last) < 2) return false;

    BidirectionalIterator cur = MoperSTL::prev(last);
    BidirectionalIterator pr = MoperSTL::prev(cur);
    // �Ӻ���ǰ������Ѱ�ҵ�һ�� *cur < *pr �����
    while (pr != first && !(*cur < *pr)) {
        --pr;
        --cur;
    }
    if (!(*cur < *pr)) {
        if (pr == first) MoperSTL::reverse(first, last);
        return false;
    }
    // �� [cur, last) ��Ѱ��С�� *pr �����Ԫ��
    // ����ǰ�� while ѭ����֪��[cur, last) ����������Ԫ�أ����Ԫ��һ�����ڵ���ǰ��Ԫ��
    // ��ˣ����ҵ��ĵ�һ������ *pr ��Ԫ�ؼ�Ϊ [cur, last) �д��� *pr ����СԪ��
    for (cur = MoperSTL::prev(last); !(*cur < *pr); --cur);
    MoperSTL::iter_swap(pr, cur);
    MoperSTL::reverse(MoperSTL::next(pr), last);
    return true;
}

//***********************************************************************************************************
// prev_permutation
// �任��Χ [first, last) Ϊ�������а������ comp ���ֵ�����ϸ�����
//***********************************************************************************************************
template<class BidirectionalIterator, class Compare>
bool
prev_permutation(BidirectionalIterator first, BidirectionalIterator last,
                 Compare comp) {
    if (MoperSTL::distance(first, last) < 2) return false;

    BidirectionalIterator cur = MoperSTL::prev(last);
    BidirectionalIterator pr = MoperSTL::prev(cur);
    // �Ӻ���ǰ������Ѱ�ҵ�һ�� *cur < *pr �����
    while (pr != first && !comp(*cur, *pr)) {
        --pr;
        --cur;
    }
    if (!comp(*cur, *pr)) {
        if (pr == first) MoperSTL::reverse(first, last);
        return false;
    }
    // �� [cur, last) ��Ѱ��С�� *pr �����Ԫ��
    // ����ǰ�� while ѭ����֪��[cur, last) ����������Ԫ�أ����Ԫ��һ�����ڵ���ǰ��Ԫ��
    // ��ˣ����ҵ��ĵ�һ������ *pr ��Ԫ�ؼ�Ϊ [cur, last) �д��� *pr ����СԪ��
    for (cur = MoperSTL::prev(last); !comp(*cur, *pr); --cur);
    MoperSTL::iter_swap(pr, cur);
    MoperSTL::reverse(MoperSTL::next(pr), last);
    return true;
}

//***********************************************************************************************************
// random_shuffle
// �����������Χ [first, last) �е�Ԫ��, ʹ����ЩԪ�ص�ÿ������ӵ����ȵĳ��ָ���
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
// �����������Χ [first, last) �е�Ԫ��, ʹ����ЩԪ�ص�ÿ������ӵ����ȵĳ��ָ���
// �����������Ϊ�������� rand
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
// �����������Χ [first, last) �е�Ԫ��, ʹ����ЩԪ�ص�ÿ������ӵ����ȵĳ��ָ���
// ���������������Ϊ�������� rand
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
// ���ֲ���
// 
// 
//***************************************************************


//***********************************************************************************************************
// is_partitioned
// �ж� [first, last) ���������� pred ��Ԫ�ض������ڲ������Ԫ��ŭǰ�򷵻� true
// �� [first, last) Ϊ���򷵻� true
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
// ��������Χ [first, last) �е�Ԫ��
// ν��pred���䷵�� true ��Ԫ��λ�ڶ��䷵�� false ��Ԫ��ǰ��
// * ����֤���˳��
// ����ָ��ڶ���Ԫ����Ԫ�صĵ�����
//***********************************************************************************************************

// partition �� forward_iterator_tag �汾
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

// partition �� bidirectional_iterator_tag �汾
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
// ��������Χ [first, last) �е�Ԫ��
// ν��pred���䷵�� true ��Ԫ��λ�ڶ��䷵�� false ��Ԫ��ǰ��
// * ��֤���˳��
// ����ָ��ڶ���Ԫ����Ԫ�صĵ�����
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
// ���Ʒ�Χ [first, last) �е�Ԫ�ص�������Χ
// ν��pred���䷵�� true ��Ԫ�ظ��Ƶ� out_true ��Χ
// ν��pred���䷵�� false ��Ԫ�ظ��Ƶ� out_false ��Χ
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
// ���黮�ַ�Χ [first, last) ,����λ��һ���ֵĽ�β,���׸������� pred ��Ԫ��
// ������Ԫ������ pred ��Ϊ last 
//***********************************************************************************************************

// partition_point �� forward_iterator_tag �汾
template<class ForwardIterator, class Predicate>
ForwardIterator
__partition_point(ForwardIterator first, ForwardIterator last,
                  Predicate pred, forward_iterator_tag) {
    for (; first != last; ++first) {
        if (!pred(*first)) return last;
    }
    return last;
}

// partition_point �� random_access_iterator_tag �汾
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
// ����������������������Χ�ϣ�
// 
// 
//***************************************************************


//***********************************************************************************************************
// lower_bound
// ����ָ��Χ [first, last) ���׸���С�ڣ������ڻ���ڣ� value ��Ԫ�صĵ�����
// ���Ҳ�������Ԫ���򷵻� last
// �� operator< �Ƚ�Ԫ�أ��� element < value��
//***********************************************************************************************************
template<class ForwardIterator, class T>
ForwardIterator
lower_bound(ForwardIterator first, ForwardIterator last,
            const T& value) {
    return partition_point(first, last, [value](const auto& element) -> bool { return element < value; });
}

//***********************************************************************************************************
// lower_bound
// ����ָ��Χ [first, last) ���׸���С�ڣ������ڻ���ڣ� value ��Ԫ�صĵ�����
// ���Ҳ�������Ԫ���򷵻� last
// �� comp �Ƚ�Ԫ�أ��� comp(element, value)��
//***********************************************************************************************************
template<class ForwardIterator, class T, class Compare>
ForwardIterator
lower_bound(ForwardIterator first, ForwardIterator last,
            const T& value, Compare comp) {
    return partition_point(first, last, [value, &comp](const auto& element) -> bool { return comp(element, value); });
}

//***********************************************************************************************************
// upper_bound
// ����ָ��Χ [first, last) ���׸����� value ��Ԫ�صĵ�����
// ���Ҳ�������Ԫ���򷵻� last
// �� operator< �Ƚ�Ԫ�أ��� !(value < element)��
//***********************************************************************************************************
template<class ForwardIterator, class T>
ForwardIterator
upper_bound(ForwardIterator first, ForwardIterator last,
            const T& value) {
    return partition_point(first, last, [value](const auto& element) -> bool { return !(value < element); });
}

//***********************************************************************************************************
// upper_bound
// ����ָ��Χ [first, last) ���׸����� value ��Ԫ�صĵ�����
// ���Ҳ�������Ԫ���򷵻� last
// �� comp �Ƚ�Ԫ�أ��� !comp(value, element)��
//***********************************************************************************************************
template<class ForwardIterator, class T, class Compare>
ForwardIterator
upper_bound(ForwardIterator first, ForwardIterator last,
            const T& value, Compare comp) {
    return partition_point(first, last, [value, &comp](const auto& element) -> bool { return !comp(value, element); });
}

//***********************************************************************************************************
// equal_range
// ���ط�Χ [first, last) �к������еȼ��� value ��Ԫ�صķ�Χ
// �� operator< �Ƚ�Ԫ��
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
// ���ط�Χ [first, last) �к������еȼ��� value ��Ԫ�صķ�Χ
// �� comp �Ƚ�Ԫ��
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
// ���ȼ��� value ��Ԫ���Ƿ�����ڷ�Χ [first, last) ��
// �� operator< �Ƚ�Ԫ��
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
// ���ȼ��� value ��Ԫ���Ƿ�����ڷ�Χ [first, last) ��
// �� comp �Ƚ�Ԫ��
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
// �Ѳ���
// 
// 
//***************************************************************


//***********************************************************************************************************
// __adjust_heap
// �� parent �����µ���������Χ [first, last) ������
// parent ����λ�� [first, last) ��Χ��
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class RandomAccessIterator>
void 
__adjust_heap(RandomAccessIterator first, RandomAccessIterator last,
              RandomAccessIterator parent) {
    // left_index ��¼ parent �����±�
    auto left_index = (parent - first) * 2 + 1;
    // ֻ�е����Ӵ���ʱ����Ҫ���е���
    while (left_index < last - first) {
        // max_child ָ�� parent ������ӽ�㡣Ĭ��ָ�����ӽڵ�
        RandomAccessIterator max_child = first + left_index;
        // �Һ��Ӵ��ڲ����Һ���ֵ��������ֵʱ,����max_child
        if (left_index + 1 < last - first && *max_child < *(max_child + 1))
            ++max_child;
        // �Ƚ� parent �� max_child
        if (*parent < *max_child) {
            MoperSTL::iter_swap(parent, max_child);
            parent = max_child;
            left_index = (parent - first) * 2 + 1;
        } else break;
    }
}

//***********************************************************************************************************
// __adjust_heap
// �� parent �����µ���������Χ [first, last) ������
// �� comp �Ƚ�Ԫ��
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
// ����λ��λ�� last-1 ��Ԫ�ص���Χ [first, last-1) �������������
// �� operator< �Ƚ�Ԫ��
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
// ����λ��λ�� last-1 ��Ԫ�ص���Χ [first, last-1) �������������
// �� comp �Ƚ�Ԫ��
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
// ɾ�������е��������(��λ�� first ��������)������������
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class RandomAccessIterator>
void 
pop_heap(RandomAccessIterator first, RandomAccessIterator last) {
    MoperSTL::iter_swap(first, --last); 
    MoperSTL::__adjust_heap(first, last, first);
}

//***********************************************************************************************************
// pop_heap
// ɾ�������е��������(��λ�� first ��������)������������
// �� comp �Ƚ�Ԫ��
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
// �ڷ�Χ [first, last) �й�������
// �� operator< �Ƚ�Ԫ��
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
// �ڷ�Χ [first, last) �й�������
// �� comp �Ƚ�Ԫ��
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
// ת������ [first, last) Ϊ����������ķ�Χ
// �����ķ�Χ����ӵ�ж�����
// �� operator< �Ƚ�Ԫ��
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
// ת������ [first, last) Ϊ����������ķ�Χ
// �����ķ�Χ����ӵ�ж�����
// �� comp �Ƚ�Ԫ��
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
// ���鷶Χ [first, last) ��Ѱ��ʼ�� first ��Ϊ���ѵ����Χ
// �� operator< �Ƚ�Ԫ��
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
// ���鷶Χ [first, last) ��Ѱ��ʼ�� first ��Ϊ���ѵ����Χ
// �� comp �Ƚ�Ԫ��
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
// ��鷶Χ[first, last) �е�Ԫ���Ƿ�Ϊ����
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class RandomAccessIterator>
bool 
is_heap(RandomAccessIterator first, RandomAccessIterator last) {
    return MoperSTL::is_heap_until(first, last) == last;
}

//***********************************************************************************************************
// is_heap
// ��鷶Χ[first, last) �е�Ԫ���Ƿ�Ϊ����
// �� comp �Ƚ�Ԫ��
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
// ���ϲ�������������Χ�ϣ�
// 
// 
//***************************************************************


//***********************************************************************************************************
// merge
// �鲢����������Χ [first1, last1) �� [first2, last2) ��ʼ�� result ��һ��������Χ��
// �� operator< �Ƚ�Ԫ��
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
// �鲢����������Χ [first1, last1) �� [first2, last2) ��ʼ�� result ��һ��������Χ��
// �� comp �Ƚ�Ԫ��
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
// ����鲢����������Χ [first1, last1) �� [first2, last2) ������ result ��һ��������Χ��
// �� operator< �Ƚ�Ԫ��
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
// ����鲢����������Χ [first1, last1) �� [first2, last2) ������ result ��һ��������Χ��
// �� comp �Ƚ�Ԫ��
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
// �鲢������̵�������Χ [first, middle) �� [middle, last) Ϊһ��������Χ [first, last)��һ��������Χ��
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************

// �޻�����������ºϲ�
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

// �л�����������ºϲ�
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
    // �л�����
    if (buffer.first != nullptr) {
        const auto len1 = MoperSTL::distance(first, middle);
        const auto len2 = MoperSTL::distance(middle, last);
        MoperSTL::__merge_adaptive(first, middle, last, len1, len2, buffer.first, buffer.second);
        // �ͷŻ�����
        MoperSTL::return_temporary_buffer(buffer.first);
    }
    // û�л�����
    else {
        MoperSTL::__merge_without_buffer(first, middle, last);
    }
}

//***********************************************************************************************************
// inplace_merge
// �鲢������̵�������Χ [first, middle) �� [middle, last) Ϊһ��������Χ [first, last)
// �� comp �Ƚ�Ԫ��
//***********************************************************************************************************

// �޻�����������ºϲ�
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

// �л�����������ºϲ�
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
    // �л�����
    if (buffer.first != nullptr) {
        const auto len1 = MoperSTL::distance(first, middle);
        const auto len2 = MoperSTL::distance(middle, last);
        MoperSTL::__merge_adaptive(first, middle, last, len1, len2, buffer.first, buffer.second, comp);
        // �ͷŻ�����
        MoperSTL::return_temporary_buffer(buffer.first);
    }
    // û�л�����
    else {
        MoperSTL::__merge_without_buffer(first, middle, last, comp);
    }
}

//***********************************************************************************************************
// includes
// ��������Χ [first2, last2) ��������Χ [first1, last1) ���������򷵻� true
// ������Χ�������� operator< ����
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
// ��������Χ [first2, last2) ��������Χ [first1, last1) ���������򷵻� true
// ������Χ�������Ը����ıȽϺ��� comp ����
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
// �󲢼�
// �� [first1, last1) �� [first2, last2) ��Ԫ�صĲ�����ŵ� result ��
// ������Χ�������� operator< ����
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
// �󲢼�
// �� [first1, last1) �� [first2, last2) ��Ԫ�صĲ�����ŵ� result ��
// ������Χ�������Ը����ıȽϺ��� comp ����
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
// �󽻼�
// �� [first1, last1) �� [first2, last2) ��Ԫ�صĽ�����ŵ� result ��
// ������Χ�������� operator< ����
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
// �󽻼�
// �� [first1, last1) �� [first2, last2) ��Ԫ�صĽ�����ŵ� result ��
// ������Χ�������Ը����ıȽϺ��� comp ����
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
// ���
// �� [first1, last1) �� [first2, last2) ��Ԫ�صĲ��ŵ� result ��
// ������Χ�������� operator< ����
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
// ���
// �� [first1, last1) �� [first2, last2) ��Ԫ�صĲ��ŵ� result ��
// ������Χ�������Ը����ıȽϺ��� comp ����
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
// ��ԳƲ�
// �� [first1, last1) �� [first2, last2) ��Ԫ�صĶԳƲ��ŵ� result ��
// ������Χ�������� operator< ����
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
// ��ԳƲ�
// �� [first1, last1) �� [first2, last2) ��Ԫ�صĶԳƲ��ŵ� result ��
// ������Χ�������Ը����ıȽϺ��� comp ����
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
// �������
// 
// 
//***************************************************************


//***********************************************************************************************************
// partial_sort
// ���ö���������Ԫ�أ�ʹ�÷�Χ [first, middle) ���з�Χ [first, last) ��������� middle - first ����СԪ��
// ����֤������ȵ�Ԫ��˳��
// ��Χ [middle, last) ��ʣ���Ԫ��˳��δָ��
//  �� operator< �Ƚ�Ԫ��
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
// ���ö���������Ԫ�أ�ʹ�÷�Χ [first, middle) ���з�Χ [first, last) ��������� middle - first ����СԪ��
// ����֤������ȵ�Ԫ��˳��
// ��Χ [middle, last) ��ʣ���Ԫ��˳��δָ��
// �� comp �Ƚ�Ԫ��
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
// ������Χ [first, last) �е�ĳЩԪ�أ��洢����ڷ�Χ [d_first, d_last)
// �� operator< �Ƚ�Ԫ��
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
// ������Χ [first, last) �е�ĳЩԪ�أ��洢����ڷ�Χ [d_first, d_last)
// �� comp �Ƚ�Ԫ��
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

// ���ڰ��� sort �����жϺ�ʱʹ�ò�������
const static std::size_t __sort_max_size = 16;

//***********************************************************************************************************
// __insert_sort
// �������� [first, last) �е�Ԫ��
// �� operator< �Ƚ�Ԫ��
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
// �������� [first, last) �е�Ԫ��
// �� comp �Ƚ�Ԫ��
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
// ��[first, last) �е�Ԫ����һ�˿�������, ����������λ��
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class RandomAccessIterator, class T>
RandomAccessIterator
__unguarded_partition(RandomAccessIterator first, RandomAccessIterator last,
                      T target) {
    while (true) {
        // ��ǰ�����ҵ���һ����С�� target ��Ԫ��
        while (*first < target) ++first;
        // �Ӻ���ǰ�ҵ���һ�������� target ��Ԫ��
        while (target < *--last);
        // �����ʱ first ������ last ��ǰ�������������
        if (!(first < last)) return first;
        // ����
        MoperSTL::iter_swap(first, last);
        ++first;
    }
}

//***********************************************************************************************************
// __unguarded_partition
// ��[first, last) �е�Ԫ����һ�˿�������, ����������λ��
// �� comp �Ƚ�Ԫ��
//***********************************************************************************************************
template<class RandomAccessIterator, class T, class Compare>
RandomAccessIterator
__unguarded_partition(RandomAccessIterator first, RandomAccessIterator last,
                      T target, Compare comp) {
    while (true) {
        // ��ǰ�����ҵ���һ����С�� target ��Ԫ��
        while (comp(*first, target)) ++first;
        // �Ӻ���ǰ�ҵ���һ�������� target ��Ԫ��
        while (comp(target, *--last));
        // �����ʱ first ������ last ��ǰ�������������
        if (!(first < last)) return first;
        // ����
        MoperSTL::iter_swap(first, last);
        ++first;
    }
}

//***********************************************************************************************************
// __intro_sort
// ��ʡʽ����
// ���Ƚ��� quick sort�����ָ���Ϊ�ж�Ϊ���η�������ʱ��ʹ�� heap sort
// �� operator< �Ƚ�Ԫ��
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
// ��ʡʽ����
// ���Ƚ��� quick sort�����ָ���Ϊ�ж�Ϊ���η�������ʱ��ʹ�� heap sort
// �� comp �Ƚ�Ԫ��
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
// ��ȡlg n ������ȡ����
//***********************************************************************************************************
template<class Size>
inline Size __lg(Size n) {
    Size result;
    for (result = 0; n > 1; n >>= 1) ++result;
    return result;
}

//***********************************************************************************************************
// sort
// ������������Χ [first, last) �е�Ԫ��
// ����֤ά�����Ԫ�ص�˳��
// �� operator< �Ƚ�Ԫ��
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
// ����������Χ [first, last) �е�Ԫ��
// ����֤ά�����Ԫ�ص�˳��
// �� comp �Ƚ�Ԫ��
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
// ����������Χ [first, last) �е�Ԫ��
// ��֤���ֵȼ�Ԫ�ص�˳��
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************

// �޻�����ʱ�ϲ��㷨
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
    // �ֶ���֮
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

// �л�����ʱ�ϲ��㷨 
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
// ����������Χ [first, last) �е�Ԫ��
// ��֤���ֵȼ�Ԫ�ص�˳��
// �� comp �Ƚ�Ԫ��
//***********************************************************************************************************

// �޻�����ʱ�ϲ��㷨
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
    // �ֶ���֮
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

// �л�����ʱ�ϲ��㷨 
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
// ���鷶Χ [first, last) ����Ѱ��ʼ�� first ������Ԫ������������������Χ
// �� operator< �Ƚ�Ԫ��
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
// ���鷶Χ [first, last) ����Ѱ��ʼ�� first ������Ԫ������������������Χ
// �� comp �Ƚ�Ԫ��
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
// ��� [first, last) �е�Ԫ���Ƿ��Բ���������
// �� operator< �Ƚ�Ԫ��
//***********************************************************************************************************
template<class ForwardIterator>
bool
is_sorted(ForwardIterator first, ForwardIterator last) {
    return MoperSTL::is_sorted_until(first, last) == last;
}

//***********************************************************************************************************
// is_sorted
// ��� [first, last) �е�Ԫ���Ƿ��Բ���������
// �� comp �Ƚ�Ԫ��
//***********************************************************************************************************
template<class ForwardIterator, class Compare>
bool
is_sorted(ForwardIterator first, ForwardIterator last,
          Compare comp) {
    return MoperSTL::is_sorted_until(first, last, comp) == last;
}

//***********************************************************************************************************
// nth_element
// �����򲿷�����Χ [first, last)
// ʹ�ö����κη�Χ [first, nth) �е� i ���κη�Χ [nth, last) �е� j
// ���������� !(*j < *i)
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
// �����򲿷�����Χ [first, last)
// ʹ�ö����κη�Χ [first, nth) �е� i ���κη�Χ [nth, last) �е� j
// ���������� comp(*j, *i) == false
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
