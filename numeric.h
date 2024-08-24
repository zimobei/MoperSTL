#ifndef MOPER_STL_NUMERIC_H
#define MOPER_STL_NUMERIC_H

#include "utility.h"
#include "iterator.h"

namespace MoperSTL {

//***********************************************************************************************************
// iota
// 以始于 value 并重复地求值 ++value 的顺序递增值填充范围 [first, last) 
//***********************************************************************************************************
template< class ForwardIterator, class T >
void 
iota(ForwardIterator first, ForwardIterator last, T value) {
	while (first != last) {
		*first++ = value++;
	}
}

//***********************************************************************************************************
// accumulate
// 计算给定值 init 与给定范围 [first, last) 中元素的和
// 用 operator+
//***********************************************************************************************************
template< class InputIt, class T >
T 
accumulate(InputIt first, InputIt last, T init) {
	while (first != last) {
		init = MoperSTL::move(init) + *first++;
	}
	return init;
}

//***********************************************************************************************************
// accumulate
// 计算给定值 init 与给定范围 [first, last) 中元素的和
// 用二元函数 op 求和元素
//***********************************************************************************************************
template< class InputIt, class T, class BinaryOperation >
T 
accumulate(InputIt first, InputIt last, T init,
		   BinaryOperation op) {
	while (first != last) {
		init = op(MoperSTL::move(init), *first++);
	}
	return init;
}

//***********************************************************************************************************
// adjacent_difference
// 计算 [first, last) 范围中每对相邻元素的第二个和第一个的差，并写入它们到始于 d_first + 1 的范围
// 写入不修改的 *first 副本到 *d_first 
//***********************************************************************************************************
template< class InputIt, class OutputIt, class BinaryOperation >
OutputIt 
adjacent_difference(InputIt first, InputIt last,
					OutputIt d_first, BinaryOperation op) {
	if (first == last) return d_first;
	using value_t = typename MoperSTL::iterator_traits<InputIt>::value_type;
	value_t acc = *first;
	*d_first = acc;
	while (++first != last) {
		value_t val = *first;
		*++d_first = val - MoperSTL::move(acc);
		acc = MoperSTL::move(val);
	}
	return ++d_first;
}

//***********************************************************************************************************
// adjacent_difference
// 计算 [first, last) 范围中每对相邻元素的第二个和第一个的差，并写入它们到始于 d_first + 1 的范围
// 写入不修改的 *first 副本到 *d_first 
// 用二元函数 op 求和元素
//***********************************************************************************************************
template< class InputIt, class OutputIt >
OutputIt 
adjacent_difference(InputIt first, InputIt last,
					OutputIt d_first) {
	if (first == last) return d_first;

	using value_t = typename MoperSTL::iterator_traits<InputIt>::value_type;
	value_t acc = *first;
	*d_first = acc;
	while (++first != last) {
		value_t val = *first;
		*++d_first = op(val, MoperSTL::move(acc));
		acc = MoperSTL::move(val);
	}
	return ++d_first;
}

template< class InputIt1, class InputIt2, class T >
T 
inner_product(InputIt1 first1, InputIt1 last1,
			  InputIt2 first2, T init) {
	while (first1 != last1) {
		init = MoperSTL::move(init) + *first1 * *first2; 
		++first1;
		++first2;
	}
	return init;
}

template<class InputIt1, class InputIt2, class T, class BinaryOperation1, class BinaryOperation2>
T 
inner_product(InputIt1 first1, InputIt1 last1,
			  InputIt2 first2, T init,
			  BinaryOperation1 op1,
			  BinaryOperation2 op2) {
	while (first1 != last1) {
		init = op1(MoperSTL::move(init), op2(*first1, *first2)); 
		++first1;
		++first2;
	}
	return init;
}

template< class InputIt, class OutputIt >
OutputIt 
partial_sum(InputIt first, InputIt last, 
			OutputIt d_first) {
	if (first == last) return d_first;

	using value_t = typename MoperSTL::iterator_traits<InputIt>::value_type;
	value_t sum = *first;
	*d_first = sum;

	while (++first != last) {
		sum = MoperSTL::move(sum) + *first; 
		*++d_first = sum;
	}
	return ++d_first;
}

template< class InputIt, class OutputIt, class BinaryOperation >
OutputIt 
partial_sum(InputIt first, InputIt last,
			OutputIt d_first, BinaryOperation op) {
	if (first == last) return d_first;

	using value_t = typename MoperSTL::iterator_traits<InputIt>::value_type;
	value_t sum = *first;
	*d_first = sum;

	while (++first != last) {
		sum = op(MoperSTL::move(sum), *first);
		*++d_first = sum;
	}
	return ++d_first;
}

}

#endif /* MOPER_STL_NUMERIC_H */
