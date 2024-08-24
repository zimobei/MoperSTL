#ifndef MOPER_STL_NUMERIC_H
#define MOPER_STL_NUMERIC_H

#include "utility.h"
#include "iterator.h"

namespace MoperSTL {

//***********************************************************************************************************
// iota
// ��ʼ�� value ���ظ�����ֵ ++value ��˳�����ֵ��䷶Χ [first, last) 
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
// �������ֵ init �������Χ [first, last) ��Ԫ�صĺ�
// �� operator+
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
// �������ֵ init �������Χ [first, last) ��Ԫ�صĺ�
// �ö�Ԫ���� op ���Ԫ��
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
// ���� [first, last) ��Χ��ÿ������Ԫ�صĵڶ����͵�һ���Ĳ��д�����ǵ�ʼ�� d_first + 1 �ķ�Χ
// д�벻�޸ĵ� *first ������ *d_first 
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
// ���� [first, last) ��Χ��ÿ������Ԫ�صĵڶ����͵�һ���Ĳ��д�����ǵ�ʼ�� d_first + 1 �ķ�Χ
// д�벻�޸ĵ� *first ������ *d_first 
// �ö�Ԫ���� op ���Ԫ��
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
