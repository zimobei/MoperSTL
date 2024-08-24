#ifndef MOPER_STL_ARRAY_H
#define MOPER_STL_ARRAY_H

#include <initializer_list>
#include "iterator.h"
#include "type_traits.h"
#include "utility.h"
#include "algorithm.h"

namespace MoperSTL {

template<class T, std::size_t N>
struct array {
	// 声明
	using value_type = typename T;
	using size_type = typename std::size_t;
	using difference_type = typename std::ptrdiff_t;
	using reference = typename value_type&;
	using const_reference = typename const value_type&;
	using pointer = typename value_type*;
	using const_pointer = typename const value_type*;
	using iterator = typename pointer;
	using const_iterator = typename const_pointer;
	using reverse_iterator = typename MoperSTL::reverse_iterator<iterator>;
	using const_reverse_iterator = typename MoperSTL::reverse_iterator<const_iterator>;
	// 成员变量
	T elements[N];
	// 迭代器
	iterator begin() noexcept { return iterator(elements); }
	const_iterator begin() const noexcept { return const_iterator(elements); }
	const_iterator cbegin() const noexcept { return begin(); }
	iterator end() noexcept { return iterator(elements + N); }
	const_iterator end() const noexcept { return const_iterator(elements + N); }
	const_iterator cend() const noexcept { return end(); }
	reverse_iterator rbegin() noexcept { return reverse_iterator(end()); }
	const_reverse_iterator rbegin() const noexcept { return const_reverse_iterator(end()); }
	const_reverse_iterator crbegin() const noexcept { return rbegin(); }
	reverse_iterator rend() noexcept { return reverse_iterator(begin()); }
	const_reverse_iterator rend() const noexcept { return const_reverse_iterator(begin()); }
	const_reverse_iterator crend() const noexcept { return rend(); }
	// 接口
	constexpr bool empty() const noexcept { return N == 0; }
	size_type size() const noexcept { return N; }
	constexpr size_type max_size() const noexcept { return N; }
	reference at(size_type pos) {
		if (!(pos < size())) throw std::out_of_range;
		else return elements[pos];
	}
	const_reference at(size_type pos) const {
		if (!(pos < size())) throw std::out_of_range;
		else return elements[pos];
	}
	T* data() noexcept { return elements; }
	const T* data() const noexcept { return elements; }
	reference front() { return elements[0]; }
	const_reference front() const { return elements[0]; }
	reference back() { return elements[N - 1]; }
	const_reference back() const { return elements[N - 1]; }
	reference operator[] (size_type pos) { return elements[pos]; }
	const_reference operator[](size_type pos) const { return elements[pos]; }
	void fill(const T& value) { MoperSTL::fill_n(elements, N, value); }
	void swap(array& other) noexcept(noexcept(MoperSTL::swap(std::declval<T&>(), std::declval<T&>()))) {
		MoperSTL::swap_ranges(elements, elements + N, other.elements);
	}

};

template<std::size_t I, class T, std::size_t N>
constexpr T& get(MoperSTL::array<T, N>& a) noexcept {
	static_assert(0 <= I, "array index can't less than zero");
	static_assert(I < N, "array index out of bounds");
	return a.elements[I];
}

template<std::size_t I, class T, std::size_t N >
constexpr T&& get(MoperSTL::array<T, N>&& a) noexcept {
	static_assert(0 <= I, "array index can't less than zero");
	static_assert(I < N, "array index out of bounds");
	return MoperSTL::move(a.elements[I]);
}

template<std::size_t I, class T, std::size_t N >
constexpr const T& get(const MoperSTL::array<T, N>& a) noexcept {
	static_assert(0 <= I, "array index can't less than zero");
	static_assert(I < N, "array index out of bounds");
	return a.elements[I];
}

template<class T, std::size_t N>
void swap(MoperSTL::array<T, N>& lhs, MoperSTL::array<T, N>& rhs) {
	lhs.swap(rhs);
}

template< class T, std::size_t N >
bool operator==(const MoperSTL::array<T, N>& lhs, const MoperSTL::array<T, N>& rhs) {
	for (std::size_t i = 0; i < N; ++i) {
		if (!(lhs.elements[i] == rhs.elements[i])) return false;
	}
	return true;
}

template< class T, std::size_t N >
bool operator!=(const MoperSTL::array<T, N>& lhs, const MoperSTL::array<T, N>& rhs) {
	return !(lhs == rhs);
}

template< class T, std::size_t N >
bool operator<(const MoperSTL::array<T, N>& lhs, const MoperSTL::array<T, N>& rhs) {
	return MoperSTL::lexicographical_compare(lhs.begin(), lhs.end(),
											 rhs.begin(), rhs.end());
}

template< class T, std::size_t N >
bool operator<=(const MoperSTL::array<T, N>& lhs, const MoperSTL::array<T, N>& rhs) {
	return !(rhs < lhs);
}

template< class T, std::size_t N >
bool operator>(const MoperSTL::array<T, N>& lhs, const MoperSTL::array<T, N>& rhs) {
	return rhs < lhs;
}

template< class T, std::size_t N >
bool operator>=(const MoperSTL::array<T, N>& lhs, const MoperSTL::array<T, N>& rhs) {
	return !(lhs < rhs);
}





}; /* MOPER_STL_ARRAY_H */

#endif /* MOPER_STL_ARRAY_H */
