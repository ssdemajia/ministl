#ifndef __SS_CONSTRUCT_H_
#define __SS_CONSTRUCT_H_

#include <new>//添加new是为了placement new,placement new允许你在一个已经分配好的内存中（栈或堆中）构造一个新的对象
/*
这个文件主要是构造和析构的方法,2017/8/22 ss
*/
namespace SS{
    template<class T1, class T2>
    inline void construct(T1* p, const T2 & value) {
        new(p) T1(value);
    }
    
    template <class T>//第一个版本的destroy
    inline void destroy(T* pointer) {//接受一个指针
        pointer->~T();//直接调用指向目标的析构函数
    }
    
    template <class ForwardIterator>//第二个版本的destroy，ForwardIterator是向前的迭代器
    inline void destroy(ForwardIterator first, ForwardIterator last) {//接受两个向前的迭代器
        __destroy(first, last, value_type(first));//使用value_type()提取类型，根据类型编译器选择特定重载方法
    }
    
    template <class ForwardIterator, class T>//通过类型T，来使用T的type_traits，了解T是否有默认构造函数和析构函数，拷贝函数
    inline void __destroy(ForwardIterator first, ForwardIterator last, T*) {
        typedef typename __type_traits<T>::has_trivial_destructor trivial_destructor;//特性提取提取出是否有编译器默认的构造函数
        __destroy_aux(first, last, trivial_destructor());
    }
    
    template <class ForwardIterator>//如果没有默认构造函数，那么需要一个一个调用对象的析构函数
    inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __false_type) {
        for (;first != last; first++) destroy(&(*first));//先用迭代器的*符号方法，取得对象，在对其求地址
    }
    
    template <class ForwardIterator>//如果有默认构造函数，那么直接不用管，能够默认析构，构造
    inline void __destroy_aux(ForwardIterator first, ForwardIterator last, __true_type) {}
    
    inline void destroy(char*, char*) {}//针对char*的特化版本
    inline void destroy(wchar_t*, wchar_t*) {}//针对wchar_t*的特化版本, wchar_t一般是32位的
    
    
}

#endif