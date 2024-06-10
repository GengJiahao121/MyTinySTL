#ifndef MYTINYSTL_ITERATOR_H_
#define MYTINYSTL_ITERATOR_H_

#include <cstddef> // ptrdiff_t
#include "type_traits.h"

namespace mystl{

// 五种迭代器类型
struct input_iterator_tag {}; // 只读
struct output_iterator_tag {}; // 只写
struct forward_iterator_tag : public input_iterator_tag {}; // 读写
struct bidirectional_iterator_tag : public forward_iterator_tag {}; // 双向
struct random_access_iterator_tag : public bidirectional_iterator_tag {}; // 随机访问

/**
 * 五种迭代器类型的关系
 * input_iterator_tag <- forward_iterator_tag <- bidirectional_iterator_tag <- random_access_iterator_tag
 * output_iterator_tag
*/

// iterator 模板
template <class Category, class T, class Distance = ptrdiff_t,
  class Pointer = T*, class Reference = T&>
struct iterator
{
    typedef Category                             iterator_category;
    typedef T                                    value_type;
    typedef Pointer                              pointer;
    typedef Reference                            reference;
    typedef Distance                             difference_type;
};

// iterator traits
//  
template <class Iterator>
struct iterator_traits{
    typedef typename Iterator::iterator_category iterator_category;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
    typedef typename Iterator::difference_type   difference_type;
};

// 针对原生指针而设计的偏特化版本
template <class T>
struct iterator_traits<T*>{
    typedef random_access_iterator_tag iterator_category; // 
    typedef T                          value_type;
    typedef T*                         pointer;
    typedef T&                         reference;
    typedef ptrdiff_t                  difference_type;
};

// 针对常量原生指针而设计的偏特化版本
template <class T>
struct iterator_traits<const T*>{
    typedef random_access_iterator_tag iterator_category;
    typedef T                          value_type;
    typedef T*                         pointer; // const T* -> T*
    typedef T&                         reference;
    typedef ptrdiff_t                  difference_type;
};



// 返回迭代器的类型
template <class Iterator>
inline typename iterator_traits<Iterator>::iterator_category
iterator_category(const Iterator&){
    typedef typename iterator_traits<Iterator>::iterator_category category;
    return category();
}

// 返回迭代器的 distance type
template <class Iterator>
inline typename iterator_traits<Iterator>::difference_type*
distance_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
}

// 返回迭代器的 value type
template <class Iterator>
inline typename iterator_traits<Iterator>::value_type*
value_type(const Iterator&){
    return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
}

// 整组的 distance 函数
template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
_distance(InputIterator first, InputIterator last, input_iterator_tag){
    typename iterator_traits<InputIterator>::difference_type n = 0;
    while(first != last){
        ++first;
        ++n;
    }
    return n;
}

template <class RandomAccessIterator>
inline typename iterator_traits<RandomAccessIterator>::difference_type
_distance(RandomAccessIterator first, RandomAccessIterator last, random_access_iterator_tag){
    return last - first;
}

template <class InputIterator>
inline typename iterator_traits<InputIterator>::difference_type
distance(InputIterator first, InputIterator last){
    return _distance(first, last, iterator_category(first));
}

// 整组的 advance 函数
template <class InputIterator, class Distance>
inline void _advance(InputIterator& it, Distance n, input_iterator_tag){
    while(n--) ++it;
}

template <class BidirectionalIterator, class Distance>
inline void _advance(BidirectionalIterator& it, Distance n, bidirectional_iterator_tag){
    if(n >= 0){
        while(n--) ++it;
    }else{
        while(n++) --it;
    }
}

template <class RandomAccessIterator, class Distance>
inline void _advance(RandomAccessIterator& it, Distance n, random_access_iterator_tag){
    it += n;
}

template <class InputIterator, class Distance>
inline void advance(InputIterator& it, Distance n){
    _advance(it, n, iterator_category(it));
}

} // namespace mystl

#endif // !MYTINYSTL_ITERATOR_H_