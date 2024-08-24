#ifndef MOPER_STL_VECTOR_H
#define MOPER_STL_VECTOR_H

#include <initializer_list>
#include "exceptdef.h"
#include "memory.h"
#include "algorithm.h"
#include "iterator.h"

namespace MoperSTL {

template<class T>
class __Vector_const_iterator {
public:
	using iterator_category = typename MoperSTL::random_access_iterator_tag;
	using value_type = typename T;
	using difference_type = typename std::ptrdiff_t;
	using pointer = typename const T*;
	using reference = typename const T&;
public:
	T* _Ptr;
public:
	__Vector_const_iterator() noexcept : _Ptr() {}
	__Vector_const_iterator(T* ptr) noexcept : _Ptr(ptr) {}

	reference operator*() const noexcept { return *_Ptr; }
	pointer operator->() const noexcept { return _Ptr; }
	__Vector_const_iterator& operator++() noexcept {
		MYSTL_DEBUG(_Ptr != nullptr);
		++_Ptr;
		return *this;
	}
	__Vector_const_iterator operator++(int) noexcept {
		__Vector_const_iterator tmp = *this;
		++*this;
		return tmp;
	}
	__Vector_const_iterator& operator--() noexcept {
		MYSTL_DEBUG(_Ptr != nullptr);
		--_Ptr;
		return *this;
	}
	__Vector_const_iterator operator--(int) noexcept {
		__Vector_const_iterator tmp = *this;
		--*this;
		return tmp;
	}
	__Vector_const_iterator& operator+=(const difference_type offest) noexcept {
		MYSTL_DEBUG(_Ptr != nullptr);
		_Ptr += offest;
		return *this;
	}
	__Vector_const_iterator operator+(const difference_type offest) noexcept {
		__Vector_const_iterator tmp = *this;
		tmp += offest;
		return tmp;
	}
	__Vector_const_iterator& operator-=(const difference_type offest) noexcept {
		return *this += -offest;
	}
	__Vector_const_iterator operator-(const difference_type offest) noexcept {
		__Vector_const_iterator tmp = *this;
		tmp -= offest;
		return tmp;
	}
	difference_type operator-(const __Vector_const_iterator& rhs) const noexcept {
		return static_cast<difference_type>(_Ptr - rhs._Ptr);
	}
	reference operator[](const difference_type offest) const noexcept {
		return *(*this + offest);
	}
	bool operator==(const __Vector_const_iterator& rhs) const noexcept {
		return _Ptr == rhs._Ptr;
	}
	bool operator<(const __Vector_const_iterator& rhs) const noexcept {
		return _Ptr < rhs._Ptr;
	}
	bool operator!=(const __Vector_const_iterator& rhs) const noexcept {
		return !(*this == rhs);
	}
	bool operator>(const __Vector_const_iterator& rhs) const noexcept {
		return rhs < *this;
	}
	bool operator<=(const __Vector_const_iterator& rhs) const noexcept {
		return !(rhs < *this);
	}
	bool operator>=(const __Vector_const_iterator& rhs) const noexcept {
		return !(*this < rhs);
	}
};

template<class T>
class __Vector_iterator : public __Vector_const_iterator<T> {
public:
	using iterator_category = typename MoperSTL::random_access_iterator_tag;
	using value_type = typename T;
	using difference_type = typename std::ptrdiff_t;
	using pointer = typename T*;
	using reference = typename T&;

	using Base = __Vector_const_iterator<T>;
public:
	reference operator*() const noexcept { 
		return const_cast<reference>(Base::operator*());
	}
	pointer operator->() const noexcept { 
		return this->_Ptr;
	}
	__Vector_iterator& operator++() noexcept {
		Base::operator++();
		return *this;
	}
	__Vector_iterator operator++(int) noexcept {
		__Vector_iterator tmp = *this;
		Base::operator++();
		return tmp;
	}
	__Vector_iterator& operator--() noexcept {
		Base::operator--();
		return *this;
	}
	__Vector_iterator operator--(int) noexcept {
		__Vector_iterator tmp = *this;
		Base::operator--();
		return tmp;
	}
	__Vector_iterator& operator+=(const difference_type offest) noexcept {
		Base::operator+=(offest);
		return *this;
	}
	__Vector_iterator operator+(const difference_type offest) noexcept {
		__Vector_iterator tmp = *this;
		tmp += offest;
		return tmp;
	}
	__Vector_iterator& operator-=(const difference_type offest) noexcept {
		Base::operator-=(offest);
		return *this;
	}
	__Vector_iterator operator-(const difference_type offest) noexcept {
		__Vector_iterator tmp = *this;
		tmp -= offest;
		return tmp;
	}
	reference operator[](const difference_type offest) const noexcept {
		return const_cast<reference>(Base::operator[](offest));
	}
};

template<class T, class Allocator = MoperSTL::allocator<T>>
class vector {
public:
	using value_type = typename T;
	using allocator_type = typename Allocator;
	using size_type = typename Allocator::size_type;
	using difference_type = typename Allocator::difference_type;
	using reference = typename value_type&;
	using const_reference = typename const value_type&;
	using pointer = typename Allocator::pointer;
	using const_pointer = typename Allocator::const_pointer;
	using iterator = typename value_type*;
	using const_iterator = typename const value_type*;
	using reverse_iterator = typename MoperSTL::reverse_iterator<iterator>;
	using const_reverse_iterator = typename MoperSTL::reverse_iterator<const_iterator>;
private:
	iterator __begin;  // 表示目前使用空间的头部
	iterator __end;    // 表示目前使用空间的尾部
	iterator __cap;    // 表示目前储存空间的尾部
	Allocator __allocator;
private: // 内部函数
	template<class InputIterator>
	void __assign(InputIterator first, InputIterator last, MoperSTL::input_iterator_tag) {
		iterator cur = __begin;
		while (first != last && cur != __end) {
			*cur++ = *first++;
		}
		if (first == last) erase(cur, __end);
		else insert(__end, first, last);
	}

	template<class ForwardIterator>
	void __assign(ForwardIterator first, ForwardIterator last, MoperSTL::forward_iterator_tag) {
		const size_type count = MoperSTL::distance(first, last);
		if (count > capacity()) {
			vector tmp(first, last);
			swap(tmp);
		} else if (count > size()) {
			ForwardIterator mid = MoperSTL::next(first, size());
			MoperSTL::copy(first, mid, __begin);
			iterator new_end = MoperSTL::uninitialized_copy(mid, last, __end);
			__end = new_end;
		} else {
			iterator new_end = MoperSTL::copy(first, last, __begin);
			erase(new_end, __end);
			__end = new_end;
		}
	}

public: // 构造、析构、copy构造函数
	vector() 
		: __begin(nullptr), __end(nullptr), __cap(nullptr), __allocator() 
	{}

	explicit vector(const Allocator& alloc) 
		: __begin(nullptr), __end(nullptr), __cap(nullptr), __allocator(alloc)
	{}

	vector(size_type count, const T& value, const Allocator& alloc = Allocator()) 
		: __begin(nullptr), __end(nullptr), __cap(nullptr), __allocator(alloc) 
	{
		__begin = __allocator.allocate(count * sizeof(T));
		MoperSTL::uninitialized_fill_n(__begin, count, value);
		__end = __begin + count;
		__cap = __end;
	}

	explicit vector(size_type count, const Allocator& alloc = Allocator())
		: __begin(nullptr), __end(nullptr), __cap(nullptr), __allocator(alloc) 
	{
		__begin = __allocator.allocate(count * sizeof(T));
		__end = MoperSTL::uninitialized_value_construct_n(__begin, count);
		__cap = __end;
	}


	template<class InputIt , typename std::enable_if<
				std::is_convertible_v<
					typename MoperSTL::iterator_traits<InputIt>::iterator_category, MoperSTL::input_iterator_tag>
				, bool>::type = true>
	vector(InputIt first, InputIt last, const Allocator& alloc = Allocator())
		: __begin(nullptr), __end(nullptr), __cap(nullptr), __allocator(alloc) 
	{
		const size_type count = static_cast<size_type>(MoperSTL::distance(first, last));
		__begin = __allocator.allocate(count * sizeof(T));
		__end = MoperSTL::uninitialized_copy(first, last, __begin);
		__cap = __end;
	}

	vector(const vector& other)
		: __begin(nullptr), __end(nullptr), __cap(nullptr), __allocator(other.__allocator) 
	{
		__begin = __allocator.allocate(other.capacity());
		__end = MoperSTL::uninitialized_copy(other.begin(), other.end(), __begin);
		__cap = __begin + other.capacity();
	}

	vector(const vector& other, const Allocator& alloc)
		: __begin(nullptr), __end(nullptr), __cap(nullptr), __allocator(alloc) 
	{
		__begin = __allocator.allocate(other.capacity());
		__end =  MoperSTL::uninitialized_copy(other.begin(), other.end(), __begin);
		__cap = __begin + other.capacity();
	}

	vector(vector&& other) noexcept
		: __begin(MoperSTL::move(other.__begin)),
		__end(MoperSTL::move(other.__end)),
		__cap(MoperSTL::move(other.__cap)),
		__allocator(other.__allocator) 
	{
		other.__begin = nullptr;
		other.__end = nullptr;
		other.__cap = nullptr;
	}

	vector(vector&& other, const Allocator& alloc)
		:__begin(MoperSTL::move(other.__begin)),
		__end(MoperSTL::move(other.__end)),
		__cap(MoperSTL::move(other.__cap)),
		__allocator(alloc) 
	{
		other.__begin = nullptr;
		other.__end = nullptr;
		other.__cap = nullptr;
	}

	vector(std::initializer_list<T> init, const Allocator& alloc = Allocator())
		: __begin(nullptr), __end(nullptr), __cap(nullptr), __allocator(alloc)
	{
		const size_type count = init.size();
		__begin = __allocator.allocate(count * sizeof(T));
		__end = MoperSTL::uninitialized_copy(init.begin(), init.end(), __begin);
		__cap = __end;
	}

	vector& operator=(const vector& other) {
		__allocator = other.__allocator;
		if (this != &other) {
			assign(other.begin(), other.end());
		}
		return *this;
	}

	vector& operator=(vector&& other) noexcept {
		MoperSTL::destory(__begin, __end);
		__allocator.deallocate(__begin, capacity());
		__begin = other.__begin;
		__end = other.__end;
		__cap = other.__cap;
		other.__begin = nullptr;
		other.__end = nullptr;
		other.__cap = nullptr;
		return *this;
	}

	vector& operator=(std::initializer_list<T> ilist) {
		assign(ilist);
		return *this;
	}

	~vector() {
		MoperSTL::destory(__begin, __end);
		__allocator.deallocate(__begin, capacity());
		__begin = nullptr;
		__end = nullptr;
		__cap = nullptr;
	}
public: // 迭代器接口
	iterator               begin()         noexcept { return __begin; }
	const_iterator         begin()   const noexcept { return __begin; }
	iterator               end()           noexcept { return __end; }
	const_iterator         end()     const noexcept { return __end; }
	reverse_iterator       rbegin()        noexcept { return reverse_iterator(end()); }
	const_reverse_iterator rbegin()  const noexcept { return const_reverse_iterator(end()); }
	reverse_iterator       rend()          noexcept { return reverse_iterator(begin()); }
	const_reverse_iterator rend()    const noexcept { return const_reverse_iterator(begin()); }
	const_iterator         cbegin()  const noexcept { return begin(); }
	const_iterator         cend()    const noexcept { return end(); }
	const_reverse_iterator crbegin() const noexcept { return rbegin(); }
	const_reverse_iterator crend()   const noexcept { return rend(); }
public: // 容量相关接口
	bool empty() const noexcept { 
		return __begin == __end; 
	}

	size_type size() const noexcept { 
		return static_cast<size_type>(MoperSTL::distance(begin(), end())); 
	}

	size_type max_size() const noexcept{ 
		return static_cast<size_type>(-1) / sizeof(T); 
	}

	size_type capacity() const noexcept { 
		return static_cast<size_type>(__cap - __begin); 
	}

	void reserve(size_type new_cap) {
		THROW_LENGTH_ERROR_IF(new_cap > max_size(), "vector reserve count > max_size()");
		else if (new_cap > capacity()) {
			const auto old_size = size();
			pointer __new_begin = __allocator.allocate(new_cap);
			MoperSTL::uninitialized_move(__begin, __end, __new_begin);
			__allocator.deallocate(__begin, capacity());
			__begin = __new_begin;
			__end = __new_begin + old_size;
			__cap = __new_begin + new_cap;
		}
	}

	void shrink_to_fit() {
		if (__end < __cap) {
			const auto __size = size();
			pointer __new_begin = __allocator.allocate(__size);
			MoperSTL::uninitialized_move(__begin, __end, __new_begin);
			__allocator.deallocate(__begin, capacity());
			__begin = __new_begin;
			__end = __new_begin + __size;
			__cap = __new_begin + __size;

		}
	}
public: // 元素访问接口
	reference       operator[](size_type pos) { 
		MYSTL_DEBUG(pos < size());
		return *(__begin + pos); 
	}
	const_reference operator[](size_type pos) const { 
		MYSTL_DEBUG(pos < size());
		return *(__begin + pos); 
	}
	reference       at(size_type pos) {
		THROW_OUT_OF_RANGE_IF(!(pos < size()), "vector at() out of range");
		if (pos < 0 ||  !(pos < size())) throw std::out_of_range;
		return *(__begin + pos);
	}
	const_reference at(size_type pos) const {
		THROW_OUT_OF_RANGE_IF(!(pos < size()), "vector at() out of range");
		if (pos < 0 || !(pos < size())) throw std::out_of_range;
		return *(__begin + pos);
	}
	reference front() {
		MYSTL_DEBUG(!empty());
		return *__begin;
	}
	const_reference front() const {
		MYSTL_DEBUG(!empty());
		return *__begin;
	}
	reference back() {
		MYSTL_DEBUG(!empty());
		return *(__begin + __end - 1);
	}
	const_reference back() const {
		MYSTL_DEBUG(!empty());
		return *(__begin + __end - 1);
	}
	T* data() noexcept {
		return __begin;
	}
	const T* data() const noexcept {
		return __begin;
	}
	allocator_type get_allocator() const {
		return allocator_type();
	}
public: // 修改操作接口
	void swap(vector& other) {
		MoperSTL::swap(__begin, other.__begin);
		MoperSTL::swap(__end, other.__end);
		MoperSTL::swap(__cap, other.__cap);
	}

	template< class... Args >
	iterator emplace(const_iterator pos, Args&&... args) {
		MYSTL_DEBUG(pos >= cbegin() && pos <= cend());

		iterator __first = begin() + (pos - cbegin());
		if (__cap == __end) reserve(1.5 * capacity());

		MoperSTL::uninitialized_move_backward(__first, __end, __end + 1);
		__allocator.construct(MoperSTL::addressof(*__first), MoperSTL::forward<Args>(args)...);
		++end;
		return __first;
	} 

	iterator erase(const_iterator first, const_iterator last) {
		MYSTL_DEBUG(first >= begin() && last <= end() && !(last < first));

		iterator __first = __begin + (first - begin());
		iterator __last = __first + (last - first);
		iterator __new_end =  MoperSTL::move(__last, __end, __first);
		MoperSTL::destory(__new_end, __end);
		__end = __new_end;
		return __first;
	}

	iterator erase(const_iterator pos) {
		erase(pos, pos + 1);
	}

	void clear() noexcept {
		erase(__begin, __end);
	}

	void assign(size_type count, const T& value) {
		if (capacity() < count) reserve(count);

		if (size() < count) {
			MoperSTL::fill(__begin, __end, value);
			MoperSTL::uninitialized_fill_n(__end, count - size(), value);
		} else {
			MoperSTL::fill_n(__begin, count, value);
		}
		__end = __begin + count;
	}

	template< class InputIt, typename std::enable_if<
				std::is_convertible_v<
					typename MoperSTL::iterator_traits<InputIt>::iterator_category, MoperSTL::input_iterator_tag>
				, bool>::type = true >
	void assign(InputIt first, InputIt last) {
		MYSTL_DEBUG(!(last < first));
		__assign(first, last, MoperSTL::__iterator_category<InputIt>());
	}

	void assign(std::initializer_list<T> ilist) {
		assign(ilist.begin(), ilist.end());
	}

	iterator insert(const_iterator pos, size_type count, const T& value) {
		MYSTL_DEBUG(pos >= cbegin() && pos <= cend());
		iterator __first = begin() + (pos - cbegin());
		if (count == 0) return __first;
		if (count > __cap - __end) reserve(count + size());

		MoperSTL::uninitialized_move_backward(__first, __end, __end + count);
		MoperSTL::uninitialized_fill_n(__first, count, value);
		__end += count;
		return __first;
	}

	iterator insert(const_iterator pos, const T& value) {
		return insert(pos, 1, value);
	}

	iterator insert(const_iterator pos, T&& value) {
		return emplace(pos, MoperSTL::move(value));
	}

	template< class InputIt >
	iterator insert(const_iterator pos, InputIt first, InputIt last) {
		MYSTL_DEBUG(pos >= cbegin() && pos <= cend() && first <= last);
		iterator __first = begin() + (pos - cbegin());
		if (first == last) return __first;
		const size_type count = static_cast<size_type>(MoperSTL::distance(first, last));
		if (count > __cap - __end) reserve(count + size());

		MoperSTL::uninitialized_move_backward(__first, __end, __end + count);
		MoperSTL::uninitialized_copy(first, last, __first);
		__end += count;
		return __first;
	}

	iterator insert(const_iterator pos, std::initializer_list<T> ilist) {
		insert(pos, ilist.begin(), ilist.end());
	}

	template< class... Args >
	void emplace_back(Args&&... args) {
		if (__end == __cap) reserve(1.5 * capacity());
		__allocator.construct(MoperSTL::addressof(*__end), MoperSTL::forward<Args>(args)...);
		++__end;
	}

	void push_back(const T& value) {
		if (__end == __cap) reserve(1.5 * capacity());
		
		__allocator.construct(MoperSTL::addressof(*__end), value);
		++__end;
	}

	void push_back(T&& value) {
		emplace_back(MoperSTL::move(value));
	}

	void pop_back() {
		MYSTL_DEBUG(!empty());
		__end;
		__allocator.destory(__end);
	}

	void resize(size_type count, const value_type& value) {
		if (count < size()) erase(__begin + count, __end);
		else insert(__end, count - size(), value);
	}

	void resize(size_type count) {
		resize(count, value_type());
	}

};

template< class T, class Alloc >
bool operator==(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs) {
	return lhs.size() == rhs.size() && MoperSTL::equal(lhs.begin(), lhs.end(), rhs.begin());
}

template< class T, class Alloc >
bool operator!=(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs) {
	return !(lhs == rhs);
}

template< class T, class Alloc >
bool operator<(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs) {
	return MoperSTL::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end());
}

template< class T, class Alloc >
bool operator<=(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs) {
	return !(rhs < lhs);
}

template< class T, class Alloc >
bool operator>(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs) {
	return rhs < lhs;
}

template< class T, class Alloc >
bool operator>=(const std::vector<T, Alloc>& lhs, const std::vector<T, Alloc>& rhs) {
	return !(lhs < rhs);
}

template< class T, class Alloc >
void swap(vector<T, Alloc>& lhs, vector<T, Alloc>& rhs) {
	lhs.swap(rhs);
}

}; /* MoperSTL */

#endif /* MOPER_STL_VECTOR_H */
