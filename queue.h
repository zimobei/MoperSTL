#ifndef MOPER_STL_QUEUE_H
#define MOPER_STL_QUEUE_H

#include "deque.h"
#include "vector.h"
#include "functional.h"
#include "algorithm.h"

namespace MoperSTL {

// 模板类 queue
// 参数一代表数据类型，参数二代表底层容器类型，缺省使用 MoperSTL::deque 作为底层容器
template <class T, class Container = MoperSTL::deque<T>>
class queue {
public:
    typedef Container                           container_type;
    // 使用底层容器的型别
    typedef typename Container::value_type      value_type;
    typedef typename Container::size_type       size_type;
    typedef typename Container::reference       reference;
    typedef typename Container::const_reference const_reference;

    static_assert(std::is_same<T, value_type>::value,
                  "the value_type of Container should be same with T");
private:
    container_type c_;  // 用底层容器表现 queue

public:
  // 构造、复制、移动函数

    queue() = default;

    explicit queue(size_type n)
        :c_(n) {}
    queue(size_type n, const value_type& value)
        :c_(n, value) {}

    template <class IIter>
    queue(IIter first, IIter last)
        : c_(first, last) {}

    queue(std::initializer_list<T> ilist)
        :c_(ilist.begin(), ilist.end()) {}

    queue(const Container& c)
        :c_(c) {}
    queue(Container&& c) noexcept(std::is_nothrow_move_constructible<Container>::value)
        :c_(MoperSTL::move(c)) {}

    queue(const queue& rhs)
        :c_(rhs.c_) {}
    queue(queue&& rhs) noexcept(std::is_nothrow_move_constructible<Container>::value)
        :c_(MoperSTL::move(rhs.c_)) {}

    queue& operator=(const queue& rhs) {
        c_ = rhs.c_;
        return *this;
    }
    queue& operator=(queue&& rhs) noexcept(std::is_nothrow_move_assignable<Container>::value) {
        c_ = MoperSTL::move(rhs.c_);
        return *this;
    }

    queue& operator=(std::initializer_list<T> ilist) {
        c_ = ilist;
        return *this;
    }

    ~queue() = default;

    // 访问元素相关操作
    reference       front() { return c_.front(); }
    const_reference front() const { return c_.front(); }
    reference       back() { return c_.back(); }
    const_reference back()  const { return c_.back(); }

    // 容量相关操作
    bool      empty() const noexcept { return c_.empty(); }
    size_type size()  const noexcept { return c_.size(); }

    // 修改容器相关操作
    template <class ...Args>
    void emplace(Args&& ...args) {
        c_.emplace_back(MoperSTL::forward<Args>(args)...);
    }

    void push(const value_type& value) {
        c_.push_back(value);
    }
    void push(value_type&& value) {
        c_.emplace_back(MoperSTL::move(value));
    }

    void pop() {
        c_.pop_front();
    }

    void clear() {
        while (!empty())
            pop();
    }

    void swap(queue& rhs) noexcept(noexcept(MoperSTL::swap(c_, rhs.c_))) {
        MoperSTL::swap(c_, rhs.c_);
    }

public:
    friend bool operator==(const queue& lhs, const queue& rhs) { return lhs.c_ == rhs.c_; }
    friend bool operator< (const queue& lhs, const queue& rhs) { return lhs.c_ < rhs.c_; }
};

// 重载比较操作符
template <class T, class Container>
bool operator==(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
    return lhs == rhs;
}

template <class T, class Container>
bool operator!=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
    return !(lhs == rhs);
}

template <class T, class Container>
bool operator<(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
    return lhs < rhs;
}

template <class T, class Container>
bool operator>(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
    return rhs < lhs;
}

template <class T, class Container>
bool operator<=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
    return !(rhs < lhs);
}

template <class T, class Container>
bool operator>=(const queue<T, Container>& lhs, const queue<T, Container>& rhs) {
    return !(lhs < rhs);
}

// 重载 mystl 的 swap
template <class T, class Container>
void swap(queue<T, Container>& lhs, queue<T, Container>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

/*****************************************************************************************/

// 模板类 priority_queue
// 参数一代表数据类型，参数二代表容器类型，缺省使用 MoperSTL::vector 作为底层容器
// 参数三代表比较权值的方式，缺省使用 MoperSTL::less 作为比较方式
template <class T, class Container = MoperSTL::vector<T>,
    class Compare = MoperSTL::less<typename Container::value_type>>
    class priority_queue {
    public:
        typedef Container                           container_type;
        typedef Compare                             value_compare;
        // 使用底层容器的型别
        typedef typename Container::value_type      value_type;
        typedef typename Container::size_type       size_type;
        typedef typename Container::reference       reference;
        typedef typename Container::const_reference const_reference;

        static_assert(std::is_same<T, value_type>::value,
                      "the value_type of Container should be same with T");

    private:
        container_type c_;     // 用底层容器来表现 priority_queue
        value_compare  comp_;  // 权值比较的标准

    public:
      // 构造、复制、移动函数
        priority_queue() = default;

        priority_queue(const Compare& c)
            :c_(), comp_(c) {}

        explicit priority_queue(size_type n)
            :c_(n) {
            MoperSTL::make_heap(c_.begin(), c_.end(), comp_);
        }
        priority_queue(size_type n, const value_type& value)
            :c_(n, value) {
            MoperSTL::make_heap(c_.begin(), c_.end(), comp_);
        }

        template <class IIter>
        priority_queue(IIter first, IIter last)
            : c_(first, last) {
            MoperSTL::make_heap(c_.begin(), c_.end(), comp_);
        }

        priority_queue(std::initializer_list<T> ilist)
            :c_(ilist) {
            MoperSTL::make_heap(c_.begin(), c_.end(), comp_);
        }

        priority_queue(const Container& s)
            :c_(s) {
            MoperSTL::make_heap(c_.begin(), c_.end(), comp_);
        }
        priority_queue(Container&& s)
            :c_(MoperSTL::move(s)) {
            MoperSTL::make_heap(c_.begin(), c_.end(), comp_);
        }

        priority_queue(const priority_queue& rhs)
            :c_(rhs.c_), comp_(rhs.comp_) {
            MoperSTL::make_heap(c_.begin(), c_.end(), comp_);
        }
        priority_queue(priority_queue&& rhs)
            :c_(MoperSTL::move(rhs.c_)), comp_(rhs.comp_) {
            MoperSTL::make_heap(c_.begin(), c_.end(), comp_);
        }

        priority_queue& operator=(const priority_queue& rhs) {
            c_ = rhs.c_;
            comp_ = rhs.comp_;
            MoperSTL::make_heap(c_.begin(), c_.end(), comp_);
            return *this;
        }
        priority_queue& operator=(priority_queue&& rhs) {
            c_ = MoperSTL::move(rhs.c_);
            comp_ = rhs.comp_;
            MoperSTL::make_heap(c_.begin(), c_.end(), comp_);
            return *this;
        }
        priority_queue& operator=(std::initializer_list<T> ilist) {
            c_ = ilist;
            comp_ = value_compare();
            MoperSTL::make_heap(c_.begin(), c_.end(), comp_);
            return *this;
        }

        ~priority_queue() = default;

    public:

      // 访问元素相关操作
        const_reference top() const { return c_.front(); }

        // 容量相关操作
        bool      empty() const noexcept { return c_.empty(); }
        size_type size()  const noexcept { return c_.size(); }

        // 修改容器相关操作
        template <class... Args>
        void emplace(Args&& ...args) {
            c_.emplace_back(MoperSTL::forward<Args>(args)...);
            MoperSTL::push_heap(c_.begin(), c_.end(), comp_);
        }

        void push(const value_type& value) {
            c_.push_back(value);
            MoperSTL::push_heap(c_.begin(), c_.end(), comp_);
        }
        void push(value_type&& value) {
            c_.push_back(MoperSTL::move(value));
            MoperSTL::push_heap(c_.begin(), c_.end(), comp_);
        }

        void pop() {
            MoperSTL::pop_heap(c_.begin(), c_.end(), comp_);
            c_.pop_back();
        }

        void clear() {
            while (!empty())
                pop();
        }

        void swap(priority_queue& rhs) noexcept(noexcept(MoperSTL::swap(c_, rhs.c_)) &&
                                                noexcept(MoperSTL::swap(comp_, rhs.comp_))) {
            MoperSTL::swap(c_, rhs.c_);
            MoperSTL::swap(comp_, rhs.comp_);
        }

    public:
        friend bool operator==(const priority_queue& lhs, const priority_queue& rhs) {
            return lhs.c_ == rhs.c_;
        }
        friend bool operator!=(const priority_queue& lhs, const priority_queue& rhs) {
            return lhs.c_ != rhs.c_;
        }
};

// 重载比较操作符
template <class T, class Container, class Compare>
bool operator==(priority_queue<T, Container, Compare>& lhs,
                priority_queue<T, Container, Compare>& rhs) {
    return lhs == rhs;
}

template <class T, class Container, class Compare>
bool operator!=(priority_queue<T, Container, Compare>& lhs,
                priority_queue<T, Container, Compare>& rhs) {
    return lhs != rhs;
}

// 重载 mystl 的 swap
template <class T, class Container, class Compare>
void swap(priority_queue<T, Container, Compare>& lhs,
          priority_queue<T, Container, Compare>& rhs) noexcept(noexcept(lhs.swap(rhs))) {
    lhs.swap(rhs);
}

}; /* MoperSTL */

#endif
