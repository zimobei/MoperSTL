#ifndef MOPER_STL_ITERATOR_H
#define MOPER_STL_ITERATOR_H

#include <cstddef> // std::ptrdiff_t
#include "type_traits.h"
#include "utility.h"

namespace MoperSTL {

//*******************************************************************
//
// 五种迭代器类型
// 
// 在iterator中以iterator_category类型表示
// C++中算法会根据迭代器类型自动选择对应实现方法，以提高算法效率
// 
//*******************************************************************

// 对应输入迭代器InputIterator
struct input_iterator_tag {};
// 对应输出迭代器OutputIterator
struct output_iterator_tag {};
// 对应向前迭代器ForwardIterator
struct forward_iterator_tag : public input_iterator_tag {};
// 对应双向迭代器BidirectionIterator
struct bidirectional_iterator_tag : public forward_iterator_tag {};
// 对应随机访问迭代器RandomAccessIterator
struct random_access_iterator_tag : public bidirectional_iterator_tag {};



//*******************************************************************
// 
//*******************************************************************

/* iterator<>
 * 
 * @brief
 * 迭代器模板类，是提供以简化迭代器所要求类型定义的基类
 * 
 * 
 * （已于C++17中弃用）
 */
template < class Category, class T, class Distance = std::ptrdiff_t, class Pointer = T*, class Reference = T& >
struct iterator {
	using iterator_category		=	Category;
	using value_type			=	T;
	using difference_type		=	Distance;
	using pointer				=	Pointer;
	using reference				=	Reference;
};



//*******************************************************************
// 
//*******************************************************************

/* iterator_traits<>
 * 
 * @brief
 * 为迭代器类型的属性提供统一的接口，使得能够仅针对迭代器实现算法
 */
template <class Iterator>
struct iterator_traits : public is_iterator<Iterator> {};

/* iterator_traits<>
 * 
 * @brief 
 */
template <class T>
struct iterator_traits<T*> {
	using iterator_category		=	random_access_iterator_tag;
	using value_type			=	T;
	using difference_type		=	std::ptrdiff_t;
	using pointer				=	T*;
	using reference				=	T&;
}; 

/* iterator_traits<>
 * 
 * @brief 
 */
template <class T>
struct iterator_traits<const T*> {
	using iterator_category		=	random_access_iterator_tag;
	using value_type			=	T;
	using difference_type		=	std::ptrdiff_t;
	using pointer				=	const T*;
	using reference				=	const T&;
};



//*******************************************************************
//
//   以下为五种迭代器适配器
//
//*******************************************************************

/* reverse_iterator<>
 * 
 * @brief
 * 反向迭代器，即反转给定迭代器方向的迭代器适配器
 *
 * 注意：
 * 由于正向迭代器的begin指向第一个元素，而end指向最后一个元素的下一个位置。
 * 所以，
 * 反向迭代器的begin指向正向迭代器end的前一个位置，即*(end - 1)；
 * 反向迭代器的end指向正向迭代器begin的前一个位置
 * （或者说反向迭代器的end的前一个位置指向正向迭代器的begin），即*(begin - 1)。
 */
template <class Iterator>
class reverse_iterator {
protected:
    Iterator current;

public:
    using iterator_type = Iterator;
    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
    using value_type = typename iterator_traits<Iterator>::value_type;
    using difference_type = typename iterator_traits<Iterator>::difference_type;
    using pointer = typename iterator_traits<Iterator>::pointer;
    using reference = typename iterator_traits<Iterator>::reference;

    constexpr reverse_iterator() : current() {}
    constexpr explicit reverse_iterator(Iterator x) : current(x){}
    template <class U> constexpr reverse_iterator(const reverse_iterator<U>& u) : current(u.base()){}
    template <class U> constexpr reverse_iterator& operator=(const reverse_iterator<U>& u) {
        this->current = u.base();
        return *this;
    }

    constexpr Iterator base() const { return current; }
    constexpr reference operator*() const {
        Iterator tmp = current;
        return *(--tmp);
    }
    constexpr pointer operator->() const {
        return &(operator*());
    }

    constexpr reverse_iterator& operator++() {
        --current;
        return *this;
    }
    constexpr reverse_iterator  operator++(int) {
        reverse_iterator tmp = *this;
        --current;
        return tmp;
    }
    constexpr reverse_iterator& operator--() {
        ++current;
        return *this;
    }
    constexpr reverse_iterator  operator--(int) {
        reverse_iterator tmp = *this;
        ++current;
        return tmp;
    }

    constexpr reverse_iterator  operator+ (difference_type n) const {
        return reverse_iterator(current - n);
    }
    constexpr reverse_iterator& operator+=(difference_type n) {
        current -= n;
        return *this;
    }
    constexpr reverse_iterator  operator- (difference_type n) const {
        return reverse_iterator(current + n);
    }
    constexpr reverse_iterator& operator-=(difference_type n) {
        current += n;
        return *this;
    }

    constexpr reference operator[](difference_type n) const {
        return *(*this + n);
    }
};


/* back_insert_iterator<>
 * 
 * @brief 
 * @tparam Container 
 */
template<class Container>
class back_insert_iterator {
protected:
    Container* container;

public:
    using iterator_category = output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using container_type = Container;

    explicit back_insert_iterator(Container& x) : container(&x){}
    back_insert_iterator& operator=(const typename Container::value_type& value) {
        container->push_back(value);
        return *this;
    }
    back_insert_iterator& operator=(typename Container::value_type&& value) {
        container->push_back(MoperSTL::move(value));
        return *this;
    }

    back_insert_iterator& operator*() { return *this; }
    back_insert_iterator& operator++() { return *this; }
    back_insert_iterator operator++(int) { return *this; }
};


/* front_insert_iterator<>
 * 
 * @brief 
 * @tparam Container 
 */
template<class Container>
class front_insert_iterator {
protected:
    Container* container;

public:
    using iterator_category = output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using container_type = Container;

    explicit front_insert_iterator(Container& x) : container(&x) {}
    front_insert_iterator& operator=(const typename Container::value_type& value) {
        container->push_front(value);
        return *this;
    }
    front_insert_iterator& operator=(typename Container::value_type&& value) {
        container->push_front(MoperSTL::move(value));
        return *this;
    }

    front_insert_iterator& operator*() { return *this; }
    front_insert_iterator& operator++() { return *this; }
    front_insert_iterator operator++(int) { return *this; }
};


/* insert_iterator<>
 * 
 * @brief 
 * @tparam Container 
 */
template<class Container>
class insert_iterator {
protected:
    Container* container;
    typename Container::iterator iter;

public:
    using iterator_category = output_iterator_tag;
    using value_type = void;
    using difference_type = void;
    using pointer = void;
    using reference = void;
    using container_type = Container;

    insert_iterator(Container& x, typename Container::iterator i) : container(&x), iter(i) {}
    insert_iterator& operator=(const typename Container::value_type& value) {
        iter = container->insert(iter, value);
        ++iter;
        return *this;
    }
    insert_iterator& operator=(typename Container::value_type&& value) {
        iter = container->insert(iter, MoperSTL::move(value));
        ++iter;
        return *this;
    }

    insert_iterator& operator*() { return *this; }
    insert_iterator& operator++() { return *this; }
    insert_iterator& operator++(int) { return *this; }
};


/* move_iterator<>
 * 
 * @brief 
 * @tparam Iterator 
 */
template<class Iterator>
class move_iterator {
private:
    Iterator current;

public:
    using iterator_type = Iterator;
    using iterator_category = typename iterator_traits<Iterator>::iterator_category;
    using value_type = typename iterator_traits<Iterator>::value_type;
    using difference_type = typename iterator_traits<Iterator>::difference_type;
    using pointer = Iterator;
    using reference = std::conditional <
        // 判断iterator_traits<Iterator>::reference 是否为引用
        std::is_reference< typename iterator_traits<Iterator>::reference >::value,
        // 若是引用，则reference为iterator_traits<Iterator>::reference原类型的右值引用
        typename std::remove_reference< typename iterator_traits<Iterator>::reference >::type&&,
        // 若不是引用，则reference为iterator_traits<Iterator>::reference
        typename iterator_traits<Iterator>::reference
    >;

    constexpr move_iterator() : current(){}
    constexpr explicit move_iterator(Iterator i) : current(i){}
    template<class U> constexpr move_iterator(const move_iterator<U>& u) : current(u.base()){}
    template<class U> constexpr move_iterator& operator=(const move_iterator<U>& u) {
        this->current = u.base();
        return *this;
    }

    constexpr iterator_type base() const { return current; }
    constexpr reference operator*() const { return MoperSTL::move(*current); }
    constexpr pointer operator->() const { return current; }

    constexpr move_iterator& operator++() {
        ++current;
        return *this;
    }
    constexpr move_iterator operator++(int) {
        move_iterator tmp = *this;
        ++current;
        return tmp;
    }
    constexpr move_iterator& operator--() {
        --current;
        return *this;
    }
    constexpr move_iterator operator--(int) {
        move_iterator tmp = *this;
        --current;
        return *this;
    }

    constexpr move_iterator operator+(difference_type n) const {
        return move_iterator(current + n);
    }
    constexpr move_iterator& operator+=(difference_type n) {
        current += n;
        return *this;
    }
    constexpr move_iterator operator-(difference_type n) const {
        return move_iterator(current - n);
    }
    constexpr move_iterator& operator-=(difference_type n) {
        current -= n;
        return *this;
    }
    constexpr reference operator[](difference_type n) const {
        return MoperSTL::move(current[n]);
    }
};



//*******************************************************************
//
//   以下为适配器函数
// 
// 用于生成对应的迭代器适配器
//
//*******************************************************************

template < class Iterator >
inline reverse_iterator<Iterator> make_reverse_iterator(Iterator i) {
    return reverse_iterator<Iterator>(i);
}

template< class Iterator >
inline move_iterator<Iterator> make_move_iterator(Iterator i) {
    return move_iterator<Iterator>(i);
}

template< class Container >
inline front_insert_iterator<Container> front_inserter(Container& c) {
    return front_insert_iterator<Container>(c);
}

template< class Container >
inline back_insert_iterator<Container> back_inserter(Container& c) {
    return back_insert_iterator<Container>(c);
}

template< class Container >
inline insert_iterator<Container> inserter(Container& c, typename Container::iterator i) {
    return insert_iterator<Container>(c, i);
}



//*******************************************************************
//
//   以下为reverse_iterator非成员函数
//
//*******************************************************************

template< class Iterator1, class Iterator2 >
inline bool operator==(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return lhs.base() == rhs.base();
}

template< class Iterator1, class Iterator2 >
inline bool operator!=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return !(lhs == rhs);
}

template< class Iterator1, class Iterator2 >
inline bool operator<(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return lhs.base() < rhs.base();
}

template< class Iterator1, class Iterator2 >
inline bool operator<=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return !(rhs < lhs);
}

template< class Iterator1, class Iterator2 >
inline bool operator>(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return rhs < lhs;
}

template< class Iterator1, class Iterator2 >
inline bool operator>=(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) {
    return !(lhs < rhs);
}

template < class Iterator >
inline reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator>& it) {
    return reverse_iterator<Iterator>(it.base() - n);
}

template< class Iterator1, class Iterator2 >
inline auto operator-(const reverse_iterator<Iterator1>& lhs, const reverse_iterator<Iterator2>& rhs) -> decltype(rhs.base() - lhs.base()) {
    return rhs.base() - lhs.base();
}



//*******************************************************************
//
//   以下为move_iterator非成员函数
//
//*******************************************************************

template< class Iterator1, class Iterator2 >
inline bool operator==(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs) {
    return lhs.base() == rhs.base();
}

template< class Iterator1, class Iterator2 >
inline bool operator!=(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs) {
    return !(lhs.base() == rhs.base());
}

template< class Iterator1, class Iterator2 >
inline bool operator<(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs) {
    return lhs.base() < rhs.base();
}

template< class Iterator1, class Iterator2 >
inline bool operator<=(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs) {
    return !(rhs.base() < lhs.base());
}

template< class Iterator1, class Iterator2 >
inline bool operator>(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs) {
    return rhs.base() < lhs.base();
}

template< class Iterator1, class Iterator2 >
inline bool operator>=(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs) {
    return !(lhs.base() < rhs.base());
}

template< class Iterator >
inline move_iterator<Iterator> operator+(typename move_iterator<Iterator>::difference_type n, const move_iterator<Iterator>& it) {
    return it + n;
}

template< class Iterator1, class Iterator2 >
inline auto operator-(const move_iterator<Iterator1>& lhs, const move_iterator<Iterator2>& rhs) -> decltype(lhs.base() - rhs.base()) {
    return lhs.base() - rhs.base();
}



//*******************************************************************
//
//   以下为迭代器操作
//
//*******************************************************************

/* __iterator_category()
 * 
 * @brief 萃取模板参数Iterator的iterator_category类型 
 * @tparam Iterator 迭代器类型
 */
template < typename Iterator>
inline typename iterator_traits<Iterator>::iterator_category 
__iterator_category(const Iterator&) {
    return typename iterator_traits<Iterator>::iterator_category();
}

template < typename Iterator>
inline typename iterator_traits<Iterator>::iterator_category
__iterator_category() {
    return typename iterator_traits<Iterator>::iterator_category();
}

// advance 的 input_iterator_tag 的版本
template < typename InputIterator, typename Distance>
void __advance(InputIterator& it, Distance n, input_iterator_tag) {
    while (n--) {
        ++it;
    }
}

template < typename InputIterator, typename Distance>
void __advance(InputIterator& it, Distance n, std::input_iterator_tag) {
    while (n--) {
        ++it;
    }
}

// advance 的 bidirectional_iterator_tag 的版本
template < typename BidirectionalIterator, typename Distance>
void __advance(BidirectionalIterator& it, Distance n, bidirectional_iterator_tag) {
    if (n > 0) {
        while (n--) ++it;
    } else {
        while (n++) --it;
    }
}

template < typename BidirectionalIterator, typename Distance>
void __advance(BidirectionalIterator& it, Distance n, std::bidirectional_iterator_tag) {
    if (n > 0) {
        while (n--) ++it;
    } else {
        while (n++) --it;
    }
}

// advance 的 random_access_iterator_tag 的版本
template < typename RandomIterator, typename Distance>
inline void __advance(RandomIterator& it, Distance n, random_access_iterator_tag) {
    it += n;
}

template < typename RandomIterator, typename Distance>
inline void __advance(RandomIterator& it, Distance n, std::random_access_iterator_tag) {
    it += n;
}

/* advance()
 * 
 * @brief 增加给定的迭代器 it 以 n 个元素的步长
 * @tparam InputIterator 必须满足 输入迭代器InputIterator 的要求。
 * @param it 迭代器
 * @param n 步长
 */
template< class InputIterator, class Distance >
inline void advance(InputIterator& it, Distance n) {
    typename iterator_traits<InputIterator>::difference_type dis = n;
    MoperSTL::__advance(it, dis, MoperSTL::__iterator_category(it));
}

// distance 的 input_iterator_tag 的版本
template < typename InputIterator >
typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last) {
        ++first;
        ++n;
    }
    return n;
}

template < typename InputIterator >
typename iterator_traits<InputIterator>::difference_type
__distance(InputIterator first, InputIterator last, std::input_iterator_tag) {
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while (first != last) {
        ++first;
        ++n;
    }
    return n;
}

// distance 的 random_access_iterator_tag 的版本
template < typename RandomIterator >
inline typename iterator_traits<RandomIterator>::difference_type
__distance(RandomIterator first, RandomIterator last, random_access_iterator_tag) {
    return last - first;
}

template < typename RandomIterator >
inline typename iterator_traits<RandomIterator>::difference_type
__distance(RandomIterator first, RandomIterator last, std::random_access_iterator_tag) {
    return last - first;
}

/* distance()
 * 
 * @brief 返回从 first 到 last 的路程
 * @tparam InputIt 迭代器类型
 * @param first 指向首元素的迭代器
 * @param last  指向范围尾的迭代器 
 * @return 从 first 走到 last 所需的自增数。若使用随机访问迭代器且 first 可从 last 抵达，则值可能为负。
 */
template< class InputIterator >
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last) {
    return MoperSTL::__distance(first, last, MoperSTL::__iterator_category(first));
}

/* next()
 * 
 * @brief 返回迭代器 it 的第 n 个后继。
 * @tparam ForwardIterator 必须满足 向前迭代器ForwardIterator 的要求
 * @param it 迭代器 
 * @param n 要前进的元素数
 * @return 
 */
template< class ForwardIterator >
inline ForwardIterator next(ForwardIterator it, typename iterator_traits<ForwardIterator>::difference_type n = 1) {
    MoperSTL::advance(it, n);
    return it;
}

/* prev()
 * 
 * @brief 返回迭代器 it 的第 n 个前驱。
 * @tparam BidirectionalIterator 必须满足 双向迭代器BidirectionalIterator 的要求
 * @param it 迭代器
 * @param n 要后退的元素数
 * @return 
 */
template< class BidirectionalIterator >
inline BidirectionalIterator prev(BidirectionalIterator it, typename iterator_traits<BidirectionalIterator>::difference_type n = 1) {
    MoperSTL::advance(it, -n);
    return it;
}



//*******************************************************************
//
//   以下为迭代器范围函数
//
//*******************************************************************

template< class C >
inline auto begin(C& c) -> decltype(c.begin()) { return c.begin(); }

template< class C >
inline auto begin(const C& c) -> decltype(c.begin()) { return c.begin(); }

template< class T, std::size_t N >
inline constexpr T* begin(T(&array)[N]) noexcept { return array; }

template< class C >
inline constexpr auto cbegin(const C& c) noexcept(noexcept(begin(c)))-> decltype(begin(c)) { return begin(c); }

template< class C >
inline auto end(C& c) -> decltype(c.end()) { return c.end(); }

template< class C >
inline auto end(const C& c) -> decltype(c.end()) { return c.end(); }

template< class T, std::size_t N >
inline constexpr T* end(T(&array)[N]) noexcept { return array + N; }

template< class C >
inline constexpr auto cend(const C& c) noexcept(noexcept(end(c)))-> decltype(end(c)) { return end(c); }

template< class C >
inline auto rbegin(C& c) -> decltype(c.rbegin()) { return c.rbegin(); }

template< class C >
inline auto rbegin(const C& c) -> decltype(c.rbegin()) { return c.rbegin(); }

template< class T, size_t N >
inline reverse_iterator<T*> rbegin(T(&array)[N]) { return reverse_iterator<T*>(array + N); }

template< class C >
inline auto crbegin(const C& c) -> decltype(rbegin(c)) { return rbegin(c); }

template< class C >
inline auto rend(C& c) -> decltype(c.rend()) { return c.rend(); }

template< class C >
inline auto rend(const C& c) -> decltype(c.rend()) { return c.rend(); }

template< class T, size_t N >
inline reverse_iterator<T*> rend(T(&array)[N]) { return reverse_iterator<T*>(array); }

template< class C >
inline auto crend(const C& c) -> decltype(rend(c)) { return rend(c); }

template < class C >
inline constexpr auto size(const C& c) -> decltype(c.size()) { return c.size(); }

template < class T, std::size_t N >
inline constexpr std::size_t size(const T(&array)[N]) noexcept { return N; }

template <class C>
inline constexpr auto empty(const C& c) -> decltype(c.empty()) { return c.empty(); }

template <class T, std::size_t N>
inline constexpr bool empty(const T(&array)[N]) noexcept { return false; }

template <class E>
inline constexpr bool empty(std::initializer_list<E> il) noexcept { return il.size() == 0; }

template <class C>
inline constexpr auto data(C& c) -> decltype(c.data()) { return c.data(); }

template <class C>
inline constexpr auto data(const C& c) -> decltype(c.data()) { return c.data(); }

template <class T, std::size_t N>
inline constexpr T* data(T(&array)[N]) noexcept { return array; }

template <class E>
inline constexpr const E* data(std::initializer_list<E> il) noexcept { return il.begin(); }

}; /* MoperSTL */

#endif /* MOPER_STL_ITERATOR_H */
