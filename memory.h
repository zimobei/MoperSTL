#ifndef MOPER_STL_MEMORY_H
#define MOPER_STL_MEMORY_H

#include <new>
#include <cstddef> // std::ptrdiff_t
#include <limits>

#include "type_traits.h"
#include "iterator.h"
#include "utility.h"
#include "memory_pool.h"

namespace MoperSTL {


//***************************************************************
// 
// 
// 杂项
// 
// 
//***************************************************************

// 获取对象地址
template <class Tp>
constexpr Tp* addressof(Tp& value) noexcept {
	return &value;
}

//***************************************************************
// 
// 
// 未初始化存储
// 
// 
//***************************************************************


//***********************************************************************************************************
// destroy_at
// 调用 p 所指对象的析构函数
//***********************************************************************************************************
template<class T>
void
destory_at(T* ptr) {
	ptr->~T();
}

//***********************************************************************************************************
// destroy
// 销毁范围 [first, last) 中的对象
//***********************************************************************************************************
template<class ForwardIterator>
void
destory(ForwardIterator first, ForwardIterator last) {
	for (; first != last; ++first) {
		MoperSTL::destory_at(MoperSTL::addressof(*first));
	}
}

//***********************************************************************************************************
// destroy_n
// 销毁从 first 开始的范围中的 n 个对象
//***********************************************************************************************************
template<class ForwardIterator, class Size>
ForwardIterator
destory_n(ForwardIterator first, Size n) {
	for (; n > 0; (void)++first, --n) {
		MoperSTL::destory_at(MoperSTL::addressof(*first));
	}
	return first;
}

//***********************************************************************************************************
// uninitialized_copy
// 复制来自范围 [first, last) 的元素到始于 result 的未初始化内存
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class InputIterator, class ForwardIterator>
ForwardIterator
uninitialized_copy(InputIterator first, InputIterator last,
				   ForwardIterator result) {
	using value_type = typename MoperSTL::iterator_traits<ForwardIterator>::value_type;
	ForwardIterator current = result;
	try {
		for (; first != last; ++first, (void)++current) {
			new(static_cast<void*>(MoperSTL::addressof(*current))) value_type(*first);
		}
	} catch (...) {
		for (; result != current; ++result) {
			result->~value_type();
		}
		throw;
	}
	return current;
}

//***********************************************************************************************************
// uninitialized_copy_n
// 从始于 first 的范围复制 count 个元素到始于 d_first 的未初始化内存区域
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class InputIterator, class Size, class ForwardIterator>
ForwardIterator
uninitialized_copy_n(InputIterator first, Size count,
					 ForwardIterator result) {
	using value_type = typename MoperSTL::iterator_traits<ForwardIterator>::value_type;
	ForwardIterator current = result;
	try {
		for (; count > 0; ++first, (void)++current, --count) {
			new(static_cast<void*>(MoperSTL::addressof(*current))) value_type(*first);
		}
	} catch (...) {
		for (; result != current; ++result) {
			result->~value_type();
		}
		throw;
	}
	return current;
}

//***********************************************************************************************************
// uninitialized_fill
// 复制给定的 value 到以 [first, last) 定义的未初始化内存区域
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class ForwardIterator, class T>
void
uninitialized_fill(ForwardIterator first, ForwardIterator last,
				   const T& value) {
	using value_type = typename MoperSTL::iterator_traits<ForwardIterator>::value_type;
	ForwardIterator current = first;
	try {
		for (; current != last; ++current) {
			new(static_cast<void*>(MoperSTL::addressof(*current))) value_type(value);
		}
	} catch (...) {
		for (; first != current; ++first) {
			first->~value_type();
		}
		throw;
	}
}

//***********************************************************************************************************
// uninitialized_fill_n
// 复制给定的 value 到以 [first, last) 定义的未初始化内存区域
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class ForwardIterator, class Size, class T>
void
uninitialized_fill_n(ForwardIterator first, Size count,
					 const T& value) {
	using value_type = typename MoperSTL::iterator_traits<ForwardIterator>::value_type;
	ForwardIterator current = first;
	try {
		for (; count > 0; ++current, (void)--count) {
			new(static_cast<void*>(MoperSTL::addressof(*current))) value_type(value);
		}
	} catch (...) {
		for (; first != current; ++first) {
			first->~value_type();
		}
		throw;
	}
}

//***********************************************************************************************************
// uninitialized_move
// 从范围 [first, last) 移动元素到始于 result 的未初始化内存区域
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class InputIterator, class ForwardIterator>
ForwardIterator
uninitialized_move(InputIterator first, InputIterator last,
				   ForwardIterator result) {
	using value_type = typename MoperSTL::iterator_traits<ForwardIterator>::value_type;
	ForwardIterator current = result;
	try {
		for (; first != last; ++first, (void)++current) {
			new(static_cast<void*>(MoperSTL::addressof(*current))) value_type(MoperSTL::move(*first));
		}
	} catch (...) {
		for (; result != current; ++result) {
			result->~value_type();
		}
		throw;
	}
	return current;
}

//***********************************************************************************************************
// uninitialized_move_n
// 从始于 first 的范围移动 count 到始于 result 的未初始化内存区域
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class InputIterator, class Size, class ForwardIterator>
pair<InputIterator, ForwardIterator>
uninitialized_move_n(InputIterator first, Size count,
					 ForwardIterator result) {
	using value_type = typename MoperSTL::iterator_traits<ForwardIterator>::value_type;
	ForwardIterator current = result;
	try {
		for (; count > 0; ++first, (void)++current, --count) {
			new(static_cast<void*>(MoperSTL::addressof(*current))) value_type(MoperSTL::move(*first));
		}
	} catch (...) {
		for (; result != current; ++result) {
			result->~value_type();
		}
		throw;
	}
	return pair<InputIterator, ForwardIterator>(first, current);
}

//***********************************************************************************************************
// uninitialized_move_backward
// 从范围 [first, last) 移动元素到终止于 result 的未初始化内存区域
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class BidirectionalIterator1, class BidirectionalIterator2>
BidirectionalIterator2
uninitialized_move_backward(BidirectionalIterator1 first, BidirectionalIterator1 last,
							BidirectionalIterator2 result) {
	using value_type = typename MoperSTL::iterator_traits<BidirectionalIterator2>::value_type;
	BidirectionalIterator2 current = result;
	try {
		while (first != last) {
			new(static_cast<void*>(MoperSTL::addressof(*--current))) value_type(MoperSTL::move(*--last));
		}
	} catch (...) {
		for (; result != current; --result) {
			result->~value_type();
		}
		throw;
	}
	return current;
}

//***********************************************************************************************************
// uninitialized_move_backward_n
// 从终止于 last 的范围移动 count 到终止于 result 的未初始化内存区域
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class BidirectionalIterator1, class BidirectionalIterator2, class Size>
BidirectionalIterator2
uninitialized_move_backward_n(BidirectionalIterator1 last, Size count,
							BidirectionalIterator2 result) {
	using value_type = typename MoperSTL::iterator_traits<BidirectionalIterator2>::value_type;
	BidirectionalIterator2 current = result;
	try {
		while (count--) {
			new(static_cast<void*>(MoperSTL::addressof(*--current))) value_type(MoperSTL::move(*--last));
		}
	} catch (...) {
		for (; result != current; --result) {
			result->~value_type();
		}
		throw;
	}
	return current;
}

//***********************************************************************************************************
// uninitialized_default_construct
// 以默认初始化在范围 [first, last) 所指代的未初始化存储上构造 typename iterator_traits<ForwardIt>::value_type 类型对象
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class ForwardIterator>
void
uninitialized_default_construct(ForwardIterator first, ForwardIterator last) {
	using value_type = typename MoperSTL::iterator_traits<ForwardIterator>::value_type;
	ForwardIterator current = first;
	try {
		for (; current != last; ++current) {
			new(static_cast<void*>(MoperSTL::addressof(*current))) value_type;
		}
	} catch (...) {
		MoperSTL::destory(first, current);
		throw;
	}
}

//***********************************************************************************************************
// uninitialized_default_construct_n
// 在 first 起始的存储中以默认初始化构造 n 个 typename iterator_traits<ForwardIt>::value_type 类型对象
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class ForwardIterator, class Size>
ForwardIterator
uninitialized_default_construct_n(ForwardIterator first, Size n) {
	using value_type = typename MoperSTL::iterator_traits<ForwardIterator>::value_type;
	ForwardIterator current = first;
	try {
		for (; n > 0; (void)++current, --n) {
			new(static_cast<void*>(MoperSTL::addressof(*current))) value_type;
		}
	} catch (...) {
		MoperSTL::destory(first, current);
		throw;
	}
	return current;
}

//***********************************************************************************************************
// uninitialized_value_construct
// 在 [first, last) 范围所指代的未初始化存储中以值初始化构造 typename iterator_traits<ForwardIt>::value_type 类型的对象
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class ForwardIterator>
void
uninitialized_value_construct(ForwardIterator first, ForwardIterator last) {
	using value_type = typename MoperSTL::iterator_traits<ForwardIterator>::value_type;
	ForwardIterator current = first;
	try {
		for (; current != last; ++current) {
			new(static_cast<void*>(MoperSTL::addressof(*current))) value_type();
		}
	} catch (...) {
		MoperSTL::destory(first, current);
		throw;
	}
}

//***********************************************************************************************************
// uninitialized_value_construct_n
// 在始于 first 的未初始化存储中以值初始化构造 n 个 typename iterator_traits<ForwardIt>::value_type 类型的对象
// 初始化中抛异常，则函数无效果
//***********************************************************************************************************
template<class ForwardIterator, class Size>
ForwardIterator
uninitialized_value_construct_n(ForwardIterator first, Size n) {
	using value_type = typename MoperSTL::iterator_traits<ForwardIterator>::value_type;
	ForwardIterator current = first;
	try {
		for (; n > 0; (void)++current, --n) {
			new(static_cast<void*>(MoperSTL::addressof(*current))) value_type();
		}
	} catch (...) {
		MoperSTL::destory(first, current);
		throw;
	}
	return current;
}

//***********************************************************************************************************
// get_temporary_buffer
// 分配未初始化的相接存储，它应足以存储至多 count 个 T 类型的相邻对象
// 要求是非绑定的，且实现可以分配少于或多于存储 count 个相邻对象所需的内存
// 返回pair(保有指向被分配存储起始的指针，和适合在实际分配的存储中的对象数)
// 若无法分配内存，或若分配的存储不足以存储单个 T 类型元素，则结果的 first 元素为空指针且 second 元素为零
//***********************************************************************************************************
template<class T>
pair<T*, std::ptrdiff_t>
get_temporary_buffer(std::ptrdiff_t count) {
	if (static_cast<std::size_t>(count) <= static_cast<std::size_t>(-1) / sizeof(T)) {
		while (count > 0) {
			const auto size = static_cast<std::size_t>(count) * sizeof(T);
			void* tmp = operator new(size, std::nothrow);
			if (tmp) return pair<T*, std::ptrdiff_t>(static_cast<T*>(tmp), count);
			else count /= 2;
		}
	}
	return pair<T*, std::ptrdiff_t>(nullptr, 0);
}

//***********************************************************************************************************
// return_temporary_buffer
// 解分配先前以 get_temporary_buffer 分配的存储
//***********************************************************************************************************
template<class T>
void
return_temporary_buffer(T* ptr) {
	operator delete(ptr);
}


//***************************************************************
// 
// 
// 智能指针
// 
// 
//***************************************************************


//***************************************************************
// 
// 
// 分配器
// 
// 
//***************************************************************

template<class T>
struct allocator {
	// 声明类型
	using value_type = typename T;
	using pointer = typename T*;
	using const_pointer = typename const T*;
	using reference = typename T&;
	using const_reference = typename const T&;
	using size_type = std::size_t;
	using difference_type = std::ptrdiff_t;
	using propagate_on_container_move_assignment = std::true_type;
	using is_always_equal = std::true_type;
	template<class U> 
	struct rebind { using other = allocator<U>; };
	// 构造、析构函数
	allocator() noexcept{}
	allocator(const allocator& other) noexcept = default;
	template< class U >
	allocator(const allocator<U>& other) noexcept{}
	~allocator() = default;
	// 接口

	/* address()
	 * 
	 * @brief 返回指向 x 地址的指针
	 */
	pointer address(reference x) const noexcept {
		return addressof(x);
	}
	const_pointer address(const_reference x) const noexcept {
		return addressof(x);
	}

	/* max_size()
	 * 
	 * @brief 返回分配器所能分配的最大的 n 的数量
	 */
	size_type max_size() const noexcept {
		return std::numeric_limits<size_type>::max() / sizeof(value_type);
	}

	/* allocate()
	 *
	 * @brief 分配 n * sizeof(T) 大小的未初始化存储空间
	 * @return 返回指向 T 类型的 n 个对象的数组首元素的指针，数组元素尚未构造
	 */
	pointer allocate(size_type n, const void* hint = 0) {
		if (n == 0) return nullptr;
		return static_cast<pointer>(memory_pool.allocate(n * sizeof(T)));
	}

	/* deallocate()
	 *
	 * @brief 从指针 p 所引用的存储解分配
	 * @param ptr 必须是通过先前对 allocate() 获得的指针
	 * @param n 必须等于对原先生成 p 的 allocate() 调用的首参数
	 */
	void deallocate(T* ptr, std::size_t n) {
		if (n == 0) return;
		memory_pool.deallocate(static_cast<void*>(ptr), sizeof(T) * n);
	}

	/* construct()
	 *
	 * @brief 在 p 所指的未初始化存储中构造对象
	 * @param ptr 指向未初始化存储的指针
	 * @param ...args 所用的构造函数参数
	 */
	template <class U, class... Args>
	void construct(U* ptr, Args&&... args) {
		new (ptr) U(std::forward<Args>(args)...);
	}

	/* destroy()
	 *
	 * @brief 调用 p 所指的对象的析构函数
	 * @param ptr 指向要被销毁的对象的指针
	 */
	template <class U>
	void destroy(U* ptr) {
		ptr->~U();
	}
};

template< class T1, class T2 >
bool operator==(const allocator<T1>& lhs, const allocator<T2>& rhs) noexcept {
	return true;
}

template< class T1, class T2 >
bool operator!=(const allocator<T1>& lhs, const allocator<T2>& rhs) noexcept {
	return false;
}

}; /* MoperSTL */

#endif /* MOPER_STL_MEMORY_H */
