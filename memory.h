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
// ����
// 
// 
//***************************************************************

// ��ȡ�����ַ
template <class Tp>
constexpr Tp* addressof(Tp& value) noexcept {
	return &value;
}

//***************************************************************
// 
// 
// δ��ʼ���洢
// 
// 
//***************************************************************


//***********************************************************************************************************
// destroy_at
// ���� p ��ָ�������������
//***********************************************************************************************************
template<class T>
void
destory_at(T* ptr) {
	ptr->~T();
}

//***********************************************************************************************************
// destroy
// ���ٷ�Χ [first, last) �еĶ���
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
// ���ٴ� first ��ʼ�ķ�Χ�е� n ������
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
// �������Է�Χ [first, last) ��Ԫ�ص�ʼ�� result ��δ��ʼ���ڴ�
// ��ʼ�������쳣��������Ч��
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
// ��ʼ�� first �ķ�Χ���� count ��Ԫ�ص�ʼ�� d_first ��δ��ʼ���ڴ�����
// ��ʼ�������쳣��������Ч��
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
// ���Ƹ����� value ���� [first, last) �����δ��ʼ���ڴ�����
// ��ʼ�������쳣��������Ч��
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
// ���Ƹ����� value ���� [first, last) �����δ��ʼ���ڴ�����
// ��ʼ�������쳣��������Ч��
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
// �ӷ�Χ [first, last) �ƶ�Ԫ�ص�ʼ�� result ��δ��ʼ���ڴ�����
// ��ʼ�������쳣��������Ч��
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
// ��ʼ�� first �ķ�Χ�ƶ� count ��ʼ�� result ��δ��ʼ���ڴ�����
// ��ʼ�������쳣��������Ч��
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
// �ӷ�Χ [first, last) �ƶ�Ԫ�ص���ֹ�� result ��δ��ʼ���ڴ�����
// ��ʼ�������쳣��������Ч��
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
// ����ֹ�� last �ķ�Χ�ƶ� count ����ֹ�� result ��δ��ʼ���ڴ�����
// ��ʼ�������쳣��������Ч��
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
// ��Ĭ�ϳ�ʼ���ڷ�Χ [first, last) ��ָ����δ��ʼ���洢�Ϲ��� typename iterator_traits<ForwardIt>::value_type ���Ͷ���
// ��ʼ�������쳣��������Ч��
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
// �� first ��ʼ�Ĵ洢����Ĭ�ϳ�ʼ������ n �� typename iterator_traits<ForwardIt>::value_type ���Ͷ���
// ��ʼ�������쳣��������Ч��
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
// �� [first, last) ��Χ��ָ����δ��ʼ���洢����ֵ��ʼ������ typename iterator_traits<ForwardIt>::value_type ���͵Ķ���
// ��ʼ�������쳣��������Ч��
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
// ��ʼ�� first ��δ��ʼ���洢����ֵ��ʼ������ n �� typename iterator_traits<ForwardIt>::value_type ���͵Ķ���
// ��ʼ�������쳣��������Ч��
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
// ����δ��ʼ������Ӵ洢����Ӧ���Դ洢���� count �� T ���͵����ڶ���
// Ҫ���Ƿǰ󶨵ģ���ʵ�ֿ��Է������ڻ���ڴ洢 count �����ڶ���������ڴ�
// ����pair(����ָ�򱻷���洢��ʼ��ָ�룬���ʺ���ʵ�ʷ���Ĵ洢�еĶ�����)
// ���޷������ڴ棬��������Ĵ洢�����Դ洢���� T ����Ԫ�أ������� first Ԫ��Ϊ��ָ���� second Ԫ��Ϊ��
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
// �������ǰ�� get_temporary_buffer ����Ĵ洢
//***********************************************************************************************************
template<class T>
void
return_temporary_buffer(T* ptr) {
	operator delete(ptr);
}


//***************************************************************
// 
// 
// ����ָ��
// 
// 
//***************************************************************


//***************************************************************
// 
// 
// ������
// 
// 
//***************************************************************

template<class T>
struct allocator {
	// ��������
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
	// ���졢��������
	allocator() noexcept{}
	allocator(const allocator& other) noexcept = default;
	template< class U >
	allocator(const allocator<U>& other) noexcept{}
	~allocator() = default;
	// �ӿ�

	/* address()
	 * 
	 * @brief ����ָ�� x ��ַ��ָ��
	 */
	pointer address(reference x) const noexcept {
		return addressof(x);
	}
	const_pointer address(const_reference x) const noexcept {
		return addressof(x);
	}

	/* max_size()
	 * 
	 * @brief ���ط��������ܷ�������� n ������
	 */
	size_type max_size() const noexcept {
		return std::numeric_limits<size_type>::max() / sizeof(value_type);
	}

	/* allocate()
	 *
	 * @brief ���� n * sizeof(T) ��С��δ��ʼ���洢�ռ�
	 * @return ����ָ�� T ���͵� n �������������Ԫ�ص�ָ�룬����Ԫ����δ����
	 */
	pointer allocate(size_type n, const void* hint = 0) {
		if (n == 0) return nullptr;
		return static_cast<pointer>(memory_pool.allocate(n * sizeof(T)));
	}

	/* deallocate()
	 *
	 * @brief ��ָ�� p �����õĴ洢�����
	 * @param ptr ������ͨ����ǰ�� allocate() ��õ�ָ��
	 * @param n ������ڶ�ԭ������ p �� allocate() ���õ��ײ���
	 */
	void deallocate(T* ptr, std::size_t n) {
		if (n == 0) return;
		memory_pool.deallocate(static_cast<void*>(ptr), sizeof(T) * n);
	}

	/* construct()
	 *
	 * @brief �� p ��ָ��δ��ʼ���洢�й������
	 * @param ptr ָ��δ��ʼ���洢��ָ��
	 * @param ...args ���õĹ��캯������
	 */
	template <class U, class... Args>
	void construct(U* ptr, Args&&... args) {
		new (ptr) U(std::forward<Args>(args)...);
	}

	/* destroy()
	 *
	 * @brief ���� p ��ָ�Ķ������������
	 * @param ptr ָ��Ҫ�����ٵĶ����ָ��
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
