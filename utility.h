#ifndef MOPER_STL_UTILITY_H
#define MOPER_STL_UTILITY_H

#include "type_traits.h"

namespace MoperSTL {

//***************************************************************
//
//						前置声明
//
//***************************************************************

/*!
 * @brief  实现固定大小的容器，它保有类型可以相异的元素
 * @tparam ...Types 所容纳的多种类型
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
//						辅助项
//
//***************************************************************


/*!
 * @brief 用于在接收二个 tuple 参数的不同函数间消歧义的空结构体标签类型
 * @brief 不使用 piecewise_construct_t 的重载假设每个 tuple 参数各变成一个 pair 的元素。
 * @brief 使用 piecewise_construct_t 的重载假设每个 tuple 参数用于逐块构造一个指定类型的新对象，而它将成为 pair 的元素。
 */
struct piecewise_construct_t {};

/*!
 * @brief 常量 std::piecewise_construct 是空的结构体标签类型 std::piecewise_construct_t 的一个实例
 */
constexpr piecewise_construct_t piecewise_construct = piecewise_construct_t();


//***************************************************************
//
//						函数
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
//						pair类
//
//***************************************************************

template <class T1, class T2>
struct pair {

	// 内部类型

	using first_type = T1;
	using second_type = T2;

	// 内部成员

	T1 first;
	T2 second;

	// 构造函数

	//********************************************************
	// 默认构造函数
	// 值初始化 pair 的两个元素 first 和 second 
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
	// 以 x 初始化 first 并以 y 初始化 second
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
	// 以 std::forward<U1>(x) 初始化 first 并以 std::forward<U2>(y) 初始化 second
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
	// 以 p.first 初始化 first 并以 p.second 初始化 second
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
	//  以 std::forward<U1>(p.first) 初始化 first 并以 std::forward<U2>(p.second) 初始化 second 
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
	// 转发 first_args 的元素到 first 的构造函数并转发 second_args 的元素到 second 的构造函数
	// 这是能用于构造不可复制不可移动类型的 pair 的仅有的非默认构造函数
	//********************************************************
	//template <class... Args1, class... Args2>
	//pair(piecewise_construct_t,
	//	 tuple<Args1...> first_args,
	//	 tuple<Args2...> second_args) : first(first_args), second(second_args) {}

	//********************************************************
	// 复制构造函数为默认，且若两个元素的复制满足 constexpr 函数的要求则为 constexpr
	//********************************************************
	pair(const pair&) = default;

	//********************************************************
	// 移动构造函数为默认，且若两个元素的移动满足 constexpr 函数的要求则为 constexpr
	//********************************************************
	pair(pair&&) = default;

	//********************************************************
	// 赋值操作
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
	// swap操作
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
