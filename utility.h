#ifndef MOPER_STL_UTILITY_H
#define MOPER_STL_UTILITY_H

#include "type_traits.h"

namespace MoperSTL {

//***************************************************************
//
//						ǰ������
//
//***************************************************************

/*!
 * @brief  ʵ�̶ֹ���С�����������������Ϳ��������Ԫ��
 * @tparam ...Types �����ɵĶ�������
 */
//template <class... Types>
//class tuple;

template <class T1, class T2>
struct pair;

template <class T>
struct is_pair : std::false_type {};

template <class T1, class T2>
struct is_pair<MoperSTL::pair<T1, T2>> : std::true_type {};


//***************************************************************
//
//						������
//
//***************************************************************


/*!
 * @brief �����ڽ��ն��� tuple �����Ĳ�ͬ������������Ŀսṹ���ǩ����
 * @brief ��ʹ�� piecewise_construct_t �����ؼ���ÿ�� tuple ���������һ�� pair ��Ԫ�ء�
 * @brief ʹ�� piecewise_construct_t �����ؼ���ÿ�� tuple ����������鹹��һ��ָ�����͵��¶��󣬶�������Ϊ pair ��Ԫ�ء�
 */
struct piecewise_construct_t {};

/*!
 * @brief ���� std::piecewise_construct �ǿյĽṹ���ǩ���� std::piecewise_construct_t ��һ��ʵ��
 */
constexpr piecewise_construct_t piecewise_construct = piecewise_construct_t();


//***************************************************************
//
//						����
//
//***************************************************************

template < class T >
constexpr typename std::remove_reference<T>::type&& move(T&& t) noexcept {
	return static_cast<typename std::remove_reference<T>::type&&>(t);
}

template < class T >
constexpr T&& forward(typename std::remove_reference<T>::type& t) noexcept {
	return static_cast<T&&>(t);
}

template < class T >
constexpr T&& forward(typename std::remove_reference<T>::type&& t) noexcept {
	return static_cast<T&&>(t);
}

template < class T >
void swap(T& a, T& b) noexcept(std::is_nothrow_move_constructible<T>::value&& std::is_nothrow_move_assignable<T>::value) {
	auto tmp = move(a);
	a = move(b);
	b = move(tmp);
}

template < class T2, std::size_t N >
void swap(T2(&a)[N], T2(&b)[N]) noexcept(noexcept(swap(*a, *b))) {
	for (std::size_t i = 0; i < N; ++i) {
		swap(*a, *b);
		++a;
		++b;
	}
}

template < class T, class U = T >
T exchange(T& obj, U&& new_value) {
	T old_value = move(obj);
	obj = std::forward<U>(new_value);
	return old_value;
}

template < class T >
constexpr typename std::conditional<
	!std::is_nothrow_move_constructible<T>::value
	&& std::is_copy_constructible<T>::value,
	const T&, T&&>::type
	move_if_noexcept(T& x) noexcept {

	using return_type = typename std::conditional<
		!std::is_nothrow_move_constructible<T>::value
		&& std::is_copy_constructible<T>::value,
		const T&, T&&>::type;
	return static_cast<return_type>(x);
}

template < class T >
constexpr std::add_const_t<T>& as_const(T& t) noexcept {
	return t;
}

template < class T >
void as_const(const T&&) = delete;

template < class T >
typename std::add_rvalue_reference<T>::type declval() noexcept;

template <class T1, class T2>
constexpr pair<std::decay_t<T1>, std::decay_t<T2>> make_pair(T1&& t1, T2&& t2) {
	return pair<std::decay_t<T1>, std::decay_t<T2>>(t1, t2);
}

template <class T1, class T2>
constexpr bool operator==(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	return (lhs.first == rhs.first) && (lhs.second == rhs.second);
}

template <class T1, class T2>
constexpr bool operator< (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	if (lhs.first < rhs.first) return true;
	else if (rhs.first < lhs.first) return false;
	else if (lhs.second < rhs.second) return true;
	else return false;
}

template <class T1, class T2>
constexpr bool operator!=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	return !(lhs == rhs);
}

template <class T1, class T2>
constexpr bool operator> (const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	return rhs < lhs;
}

template <class T1, class T2>
constexpr bool operator>=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	return !(lhs < rhs);
}

template <class T1, class T2>
constexpr bool operator<=(const pair<T1, T2>& lhs, const pair<T1, T2>& rhs) {
	return !(rhs < lhs);
}

template <class T1, class T2>
void swap(pair<T1, T2>& lhs, pair<T1, T2>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
	lhs.swap(rhs);
}


//template< size_t I, class T1, class T2 >
//constexpr std::tuple_element_t<I, std::pair<T1, T2> >& get(pair<T1, T2>& p) noexcept;
//
//template< size_t I, class T1, class T2 >
//constexpr const std::tuple_element_t<I, std::pair<T1, T2> >& get(const pair<T1, T2>& p) noexcept;
//
//template< size_t I, class T1, class T2 >
//constexpr std::tuple_element_t<I, std::pair<T1, T2> >&& get(std::pair<T1, T2>&& p) noexcept;
//
//template< size_t I, class T1, class T2 >
//constexpr const std::tuple_element_t<I, std::pair<T1, T2> >&& get(const std::pair<T1, T2>&& p) noexcept;

template <class T, class U>
constexpr T& get(std::pair<T, U>& p) noexcept {
	return p.first;
}

template <class T, class U>
constexpr const T& get(const std::pair<T, U>& p) noexcept {
	return p.first;
}

template <class T, class U>
constexpr T&& get(std::pair<T, U>&& p) noexcept {
	return move(p.first);
}

template <class T, class U>
constexpr const T&& get(const std::pair<T, U>&& p) noexcept {
	return move(p.first);
}

template <class T, class U>
constexpr T& get(std::pair<U, T>& p) noexcept {
	return p.second;
}

template <class T, class U>
constexpr const T& get(const std::pair<U, T>& p) noexcept {
	return p.second;
}

template <class T, class U>
constexpr T&& get(std::pair<U, T>&& p) noexcept {
	return move(p.second);
}

template <class T, class U>
constexpr const T&& get(const std::pair<U, T>&& p) noexcept {
	return move(p.second);
}



//***************************************************************
//
//						pair��
//
//***************************************************************

template <class T1, class T2>
struct pair {

	// �ڲ�����

	using first_type = T1;
	using second_type = T2;

	// �ڲ���Ա

	T1 first;
	T2 second;

	// ���캯��

	//********************************************************
	// Ĭ�Ϲ��캯��
	// ֵ��ʼ�� pair ������Ԫ�� first �� second 
	//********************************************************
	template <class U1 = T1, class U2 = T2,
			typename std::enable_if<
									std::_Is_implicitly_default_constructible<U1>::value &&
									std::_Is_implicitly_default_constructible<U2>::value
									, bool>::type = true>
	constexpr pair() : first(), second() {}

	template <class U1 = T1, class U2 = T2,
			typename std::enable_if<
									std::is_default_constructible_v<U1> &&
									std::is_default_constructible_v<U2> &&
									!(std::_Is_implicitly_default_constructible<U1>::value &&
									  std::_Is_implicitly_default_constructible<U2>::value)
									, bool>::type = false>
	explicit constexpr pair() : first(), second() {}

	//********************************************************
	// �� x ��ʼ�� first ���� y ��ʼ�� second
	//********************************************************
	template <class U1 = T1, class U2 = T2,
			typename std::enable_if<
									std::is_copy_constructible_v<U1> &&
									std::is_copy_constructible_v<U2> &&
									std::is_constructible_v<const U1&, T1> &&
									std::is_constructible_v<const U2&, T2>
									, bool>::type = true>
	constexpr pair(const U1& x, const U2& y) : first(x), second(y) {}

	template <class U1 = T1, class U2 = T2,
			typename std::enable_if<
									std::is_copy_constructible_v<U1> &&
									std::is_copy_constructible_v<U2> &&
									!(std::is_constructible_v<const U1&, T1> &&
									  std::is_constructible_v<const U2&, T2>)
									, bool>::type = false>
	explicit constexpr pair(const U1& x, const U2& y) : first(x), second(y) {}


	//********************************************************
	// �� std::forward<U1>(x) ��ʼ�� first ���� std::forward<U2>(y) ��ʼ�� second
	//********************************************************
	template <class U1, class U2,
			typename std::enable_if<
									std::is_constructible_v<T1, U1&&> &&
									std::is_constructible_v<T2, U2&&> &&
									std::is_constructible_v<U1&&, T1> &&
									std::is_constructible_v<U2&&, T2>
									, bool>::type = true>
	constexpr pair(U1&& x, U2&& y) : first(MoperSTL::forward<U1>(x)), second(MoperSTL::forward<U2>(y)) {}

	template <class U1, class U2,
			typename std::enable_if<
									std::is_constructible_v<T1, U1&&> &&
									std::is_constructible_v<T2, U2&&> &&
									!(std::is_constructible_v<U1&&, T1> &&
									  std::is_constructible_v<U2&&, T2>)
									, bool>::type = false>
	explicit constexpr pair(U1&& x, U2&& y) : first(MoperSTL::forward<U1>(x)), second(MoperSTL::forward<U2>(y)) {}

	//********************************************************
	// �� p.first ��ʼ�� first ���� p.second ��ʼ�� second
	//********************************************************
	template <class U1, class U2,
			typename std::enable_if<
									std::is_constructible_v<T1, const U1&> &&
									std::is_constructible_v<T2, const U2&> &&
									std::is_constructible_v<const U1&, T1> &&
									std::is_constructible_v<const U2&, T2>
									, bool>::type = true>
	constexpr pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

	template <class U1, class U2,
			typename std::enable_if<
									std::is_constructible_v<T1, const U1&> &&
									std::is_constructible_v<T2, const U2&> &&
									!(std::is_constructible_v<const U1&, T1> &&
									  std::is_constructible_v<const U2&, T2>)
									, bool>::type = false>
	explicit constexpr pair(const pair<U1, U2>& p) : first(p.first), second(p.second) {}

	//********************************************************
	//  �� std::forward<U1>(p.first) ��ʼ�� first ���� std::forward<U2>(p.second) ��ʼ�� second 
	//********************************************************
	template <class U1, class U2,
			typename std::enable_if<
									std::is_constructible_v<T1, U1&&> &&
									std::is_constructible_v<T2, U2&&> &&
									std::is_constructible_v<U1&&, T1> &&
									std::is_constructible_v<U2&&, T2>
									, bool>::type = true>
	constexpr pair(pair<U1, U2>&& p) : first(MoperSTL::forward<U1>(p.first)), second(MoperSTL::forward<U2>(p.second)) {}

	template <class U1, class U2,
			typename std::enable_if<
									std::is_constructible_v<T1, U1&&> &&
									std::is_constructible_v<T2, U2&&> &&
									!(std::is_constructible_v<U1&&, T1> &&
									  std::is_constructible_v<U2&&, T2>)
									, bool>::type = false>
	explicit constexpr pair(pair<U1, U2>&& p) : first(MoperSTL::forward<U1>(p.first)), second(MoperSTL::forward<U2>(p.second)) {}

	//********************************************************
	// ת�� first_args ��Ԫ�ص� first �Ĺ��캯����ת�� second_args ��Ԫ�ص� second �Ĺ��캯��
	// ���������ڹ��첻�ɸ��Ʋ����ƶ����͵� pair �Ľ��еķ�Ĭ�Ϲ��캯��
	//********************************************************
	//template <class... Args1, class... Args2>
	//pair(piecewise_construct_t,
	//	 tuple<Args1...> first_args,
	//	 tuple<Args2...> second_args) : first(first_args), second(second_args) {}

	//********************************************************
	// ���ƹ��캯��ΪĬ�ϣ���������Ԫ�صĸ������� constexpr ������Ҫ����Ϊ constexpr
	//********************************************************
	pair(const pair&) = default;

	//********************************************************
	// �ƶ����캯��ΪĬ�ϣ���������Ԫ�ص��ƶ����� constexpr ������Ҫ����Ϊ constexpr
	//********************************************************
	pair(pair&&) = default;

	//********************************************************
	// ��ֵ����
	//********************************************************
	template <typename std::enable_if<
									std::is_copy_assignable_v<T1> &&
									std::is_copy_assignable_v<T2>
									, bool>::type = true>
	pair& operator=(const pair& p) {
		this->first = p.first;
		this->second = p.second;
		return *this;
	}

	template <class U1, class U2,
			typename std::enable_if<
									std::is_assignable_v<T1&, const U1&> &&
									std::is_assignable_v<T2&, const U2&>
									, bool>::type = true>
	pair& operator=(const pair<U1, U2>& p) {
		this->first = p.first;
		this->second = p.second;
		return *this;
	}

	template <typename std::enable_if<
									std::is_move_assignable_v<T1> &&
									std::is_move_assignable_v<T2>
									, bool>::type = true>
	pair& operator=(pair&& p) noexcept(std::is_move_assignable_v<T1> && std::is_move_assignable_v<T2>) {
		this->first = MoperSTL::move(p.first);
		this->second = MoperSTL::move(p.second);
		return *this;
	}

	template <class U1, class U2,
			typename std::enable_if<
									std::is_assignable_v<T1&, U1> &&
									std::is_assignable_v<T2&, U2>
									, bool>::type = true>
	pair& operator=(pair<U1, U2>&& p) {
		this->first = MoperSTL::forward<U1>(p.first);
		this->second = MoperSTL::forward<U2>(p.second);
		return *this;
	}

	//********************************************************
	// swap����
	//********************************************************

	template <typename std::enable_if<
									std::_Is_swappable<T1>::value &&
									std::_Is_swappable<T2>::value
									, bool>::type = true>
	void swap(pair& other) noexcept(
									noexcept(swap(first, other.first)) &&
									noexcept(swap(second, other.second))
		) {
		swap(first, other.first);
		swap(second, other.second);
	}

};



}; /* MoperSTL */

#endif /* MOPER_STL_UTILITY_H */
