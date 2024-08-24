#ifndef MOPER_STL_FUNCTIONAL_H
#define MOPER_STL_FUNCTIONAL_H

#include "type_traits.h"

namespace MoperSTL {

// ����һԪ�����Ĳ����ͱ�ͷ���ֵ�ͱ�
template <class Arg, class Result>
struct unarg_function {
	typedef Arg       argument_type;
	typedef Result    result_type;
};

// �����Ԫ�����Ĳ����ͱ�ķ���ֵ�ͱ�
template <class Arg1, class Arg2, class Result>
struct binary_function {
	typedef Arg1      first_argument_type;
	typedef Arg2      second_argument_type;
	typedef Result    result_type;
};



//*******************************************************************
//
// ��������
// 
//*******************************************************************

// �������󣺼ӷ�
template <class T>
struct plus :public binary_function<T, T, T> {
	constexpr T operator()(const T& x, const T& y) const { return x + y; }
};

// �������󣺼���
template <class T>
struct minus :public binary_function<T, T, T> {
	constexpr T operator()(const T& x, const T& y) const { return x - y; }
};

// �������󣺳˷�
template <class T>
struct multiplies :public binary_function<T, T, T> {
	constexpr T operator()(const T& x, const T& y) const { return x * y; }
};

// �������󣺳���
template <class T>
struct divides :public binary_function<T, T, T> {
	constexpr T operator()(const T& x, const T& y) const { return x / y; }
};

// ��������ģȡ
template <class T>
struct modulus :public binary_function<T, T, T> {
	constexpr T operator()(const T& x, const T& y) const { return x % y; }
};

// �������󣺷�
template <class T>
struct negate :public unarg_function<T, T> {
	constexpr T operator()(const T& x) const { return -x; }
};



//*******************************************************************
//
// �Ƚ�
// 
//*******************************************************************

// �������󣺵���
template < class T>
struct equal_to : binary_function<T, T, bool> {
	constexpr bool operator() (const T& lhs, const T& rhs) const { return lhs == rhs; }
};

// �������󣺲�����
template <class T>
struct not_equal_to :public binary_function<T, T, bool> {
	constexpr bool operator()(const T& x, const T& y) const { return x != y; }
};

// �������󣺴���
template <class T>
struct greater :public binary_function<T, T, bool> {
	constexpr bool operator()(const T& x, const T& y) const { return x > y; }
};

// ��������С��
template <class T = void>
struct less :public binary_function<T, T, bool> {
	constexpr bool operator()(const T& x, const T& y) const { return x < y; }
};

// �������󣺴��ڵ���
template <class T>
struct greater_equal :public binary_function<T, T, bool> {
	constexpr bool operator()(const T& x, const T& y) const { return x >= y; }
};

// ��������С�ڵ���
template <class T>
struct less_equal :public binary_function<T, T, bool> {
	constexpr bool operator()(const T& x, const T& y) const { return x <= y; }
};



//*******************************************************************
//
// �߼�����
// 
//*******************************************************************

// ���������߼���
template <class T>
struct logical_and :public binary_function<T, T, bool> {
	constexpr bool operator()(const T& x, const T& y) const { return x && y; }
};

// ���������߼���
template <class T>
struct logical_or :public binary_function<T, T, bool> {
	constexpr bool operator()(const T& x, const T& y) const { return x || y; }
};

// ���������߼���
template <class T>
struct logical_not :public unarg_function<T, bool> {
	constexpr bool operator()(const T& x) const { return !x; }
};



//*******************************************************************
//
// ��λ����
// 
//*******************************************************************

// ����������λ��
template <class T>
struct bit_and : public binary_function<T, T, T> {
	constexpr T operator()(const T& lhs, const T& rhs) const { return lhs & rhs; }
};

// ����������λ��
template <class T>
struct bit_or : public binary_function<T, T, T> {
	constexpr T operator()(const T& lhs, const T& rhs) const { return lhs | rhs; }
};

// ����������λ���
template <class T>
struct bit_xor : public binary_function<T, T, T> {
	constexpr T operator()(const T& lhs, const T& rhs) const { return lhs ^ rhs; }
};

// ����������λ��
template <class T>
struct bit_not : public unarg_function<T, T> {
	constexpr T operator()(const T& arg) const { return ~arg; }
};


//*******************************************************************
//
// hash ��������
// 
//*******************************************************************

template <class Key>
struct hash {};

template <class T>
struct hash<T*> {
	std::size_t operator()(T* p) const noexcept {
		return reinterpret_cast<std::size_t>(p);
	}
};

template<>
struct hash<bool> {
	std::size_t operator()(bool val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<char> {
	std::size_t operator()(char val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<signed char> {
	std::size_t operator()(signed char val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<unsigned char> {
	std::size_t operator()(unsigned char val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<wchar_t> {
	std::size_t operator()(wchar_t val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<char16_t> {
	std::size_t operator()(char16_t val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<char32_t> {
	std::size_t operator()(char32_t val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<short> {
	std::size_t operator()(short val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<unsigned short> {
	std::size_t operator()(unsigned short val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<int> {
	std::size_t operator()(int val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<unsigned int> {
	std::size_t operator()(unsigned int val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<long> {
	std::size_t operator()(long val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<unsigned long> {
	std::size_t operator()(unsigned long val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<long long> {
	std::size_t operator()(long long val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

template<>
struct hash<unsigned long long> {
	std::size_t operator()(unsigned long long val) const noexcept {
		return static_cast<std::size_t>(val);
	}
};

// ���ڸ���������λ��ϣ
inline std::size_t bitwise_hash(const unsigned char* first, std::size_t count) {
	#if (_MSC_VER && _WIN64) || ((__GNUC__ || __clang__) &&__SIZEOF_POINTER__ == 8)
	const std::size_t fnv_offset = 14695981039346656037ull;
	const std::size_t fnv_prime = 1099511628211ull;
	#else
	const std::size_t fnv_offset = 2166136261u;
	const std::size_t fnv_prime = 16777619u;
	#endif
	std::size_t result = fnv_offset;
	for (std::size_t i = 0; i < count; ++i) {
		result ^= (std::size_t)first[i];
		result *= fnv_prime;
	}
	return result;
}

template <>
struct hash<float> {
	std::size_t operator()(const float& val) {
		return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(float));
	}
};

template <>
struct hash<double> {
	std::size_t operator()(const double& val) {
		return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(double));
	}
};

template <>
struct hash<long double> {
	std::size_t operator()(const long double& val) {
		return val == 0.0f ? 0 : bitwise_hash((const unsigned char*)&val, sizeof(long double));
	}
};

}; /* MoperSTL */

#endif /* MOPER_STL_FUNCTIONAL_H */
