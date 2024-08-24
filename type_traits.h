#ifndef MOPER_STL_TYPE_TRAITES_H
#define MOPER_STL_TYPE_TRAITES_H

#include <type_traits>

namespace MoperSTL {

/* is_iterator<>
 * 
 * @brief 
 * �����ж�template�����Ƿ����iterator��׼
 *�����Ƿ����iterator_category��value_type��difference_type��pointer��reference�������ͣ�
 * ������ϣ�����ȡ����������
 * 
 * ����ͨ��is_iterator<Iterator>::value�õ��жϽ��(true��ʾ����iterator��׼��false��ʾ������)
 */
template < typename _Iterator, typename = std::void_t<> >
struct is_iterator : public std::false_type {};

template <typename _Iterator>
struct is_iterator<_Iterator,
	std::void_t<typename _Iterator::iterator_category,
	typename _Iterator::value_type,
	typename _Iterator::difference_type,
	typename _Iterator::pointer,
	typename _Iterator::reference>> : std::true_type
{
	using iterator_category = typename _Iterator::iterator_category;
	using value_type = typename _Iterator::value_type;
	using difference_type = typename _Iterator::difference_type;
	using pointer = typename _Iterator::pointer;
	using reference = typename _Iterator::reference;
};



}; /* MoperSTL */

#endif /* MOPER_STL_TYPE_TRAITES_H */