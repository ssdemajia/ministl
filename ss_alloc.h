#ifndef __SS_ALLOC_H_
#define __SS_ALLOC_H_
#include <cstddef>
#include <cstdlib>
/*  
如果很小的空间，那么使用内存链分配，超过128字节的空间分配使用malloc，若小于128字节使用内存池中的内存块
*/


template<class T, class Alloc>
class simple_alloc{//对Alloc的简易包装，使得内存管理的单位从字节变为T的大小
public:
    static T* allocate(size_t n){
        return 0==n?0:(T*)Alloc::allocate(n*sizeof(T));//直接使用Alloc中的分配函数
    }
    static T* allocate(void){
        return (T*)allocate(sizeof(T));
    }
    static void deallocate(T* p, size_t n) {
        if (0!=n) Alloc::deallocate(p, n*sizeof(T));
    }
    static void deallocate(T* p){Alloc::deallocate(p, sizeof(T));}
};

#ifndef __THROW_BAD_ALLOC//定义出错时的处理方式
#include <iostream>
#define __THROW_BAD_ALLOC std::cerr << "Out Of Memory from ss" << std::endl; exit(1)
#endif


template<int inst>
class __malloc_alloc_template {//第一级内存配置器
private://用来处理内存不足的情况
    static void *oom_malloc(size_t);
    static void *oom_realloc(void*, size_t);//内存不足时的再分配
    static void (* __malloc_alloc_oom_handler)();//模仿set_new_handler，处理内存不足的情况

public:
    static void* allocate(size_t n) {
        void* result = malloc(n);//第一级配置器直接使用malloc分配内存
        if (result == 0) result = oom_malloc(n);//内存不足时，调用oom_malloc来处理
        return result;
    }
    static void deallocate(void* p, size_t /*n*/) {//n参数可以不用，因为这是对simple_alloc兼容才加入的
        free(p);
    }
    static void* reallocate(void *p, size_t /*old_sz*/, size_t new_sz) {
        void* result = realloc(p, new_sz);
        if (result == NULL) result = oom_realloc(p, new_sz);
        return result;
    }
    static void (*set_malloc_handler(void(*f)()))(){//这个函数设置自定义的malloc_handler
        void (*old)() = __malloc_alloc_oom_handler;//将类内的malloc_alloc_oom函数指针换为f
        __malloc_alloc_oom_handler = f;
        return old;
    }
};//end of __malloc_alloc_template
template<int inst>
void (* __malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;//静态变量初始化

template <int inst>
void * __malloc_alloc_template<inst>::oom_malloc(size_t n) {//定义oom_malloc
    void (* my_malloc_handler)();//申明一个处理分配内存问题的函数指针
    void *result;
    for (;;) {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (my_malloc_handler == 0) {__THROW_BAD_ALLOC;}//出错时调用32行的方法
        (*my_malloc_handler)();//调用自定义方法，释放内存
        result = malloc(n);
        if (result) return result;
    }
}

template <int inst>
void * __malloc_alloc_template<inst>::oom_realloc(void *p, size_t n) {
    void (*my_malloc_handler)();
    void *result;
    for (;;) {
        my_malloc_handler = __malloc_alloc_oom_handler;
        if (my_malloc_handler == 0) {__THROW_BAD_ALLOC;}//出错时调用32行的方法
        (*my_malloc_handler)();//调用自定义方法，释放内存
        result = realloc(p, n);
        if (result) return result;
    }
}
typedef __malloc_alloc_template<0> malloc_alloc;


enum {__ALIGN = 8};//小型区块的上调边界
enum {__MAX_BYTES = 128};//小型区块的上限
enum {__NFREELISTS = __MAX_BYTES/__ALIGN};//free list的个数
template <bool threads, int inst>
class __default_alloc_template {//二级内存配置器
private:
    static size_t ROUND_UP(size_t bytes) {
        return ((bytes + __ALIGN - 1) & ~(__ALIGN - 1));//将bytes换为8的倍数
    }
    union obj {
        union obj * free_list_link;//链表内部通过这个来指向下一个节点
        char client_data[1];//客户端访问这个，来访问内容
    };
    static obj* volatile free_lists[__NFREELISTS];//__NFREELISTS个链表
    static size_t FREELIST_INDEX(size_t bytes) {//各个链表的节点大小从8，16...直到 128
        return ((bytes + __ALIGN - 1) / __ALIGN - 1);
    }
    static void* refill(size_t n);//返回一个n字节的块,加入大小为n的块到链表中
    static char* chunk_alloc(size_t size, int &nobjs);//配置nobjs个大小为size的块，可能内存不够，则会修改nobjs

    static char* start_free;//内存池开始位置
    static char* end_free;//结束位置
    static size_t heap_size;//当前分配的堆大小
public:
    static void* allocate(size_t n) {
        obj* volatile *my_free_lsit;
        obj* result;
        if (n > (size_t) __MAX_BYTES) {
            return malloc_alloc::allocate(n);
        }
        my_free_lsit = free_lists+FREELIST_INDEX(n);//找到16个free lists中的一个
        result = *my_free_lsit;//result指向这个链表开始位置
        if (result == 0) {
            void* r = refill(ROUND_UP(n));
            return r;
        }
        *my_free_lsit = result->free_list_link;//将这个要返回的块丢出链表中
        return result;
    }
    static void  deallocate(void* p, size_t n) {
        obj* q = (obj*)p;
        obj* volatile * my_free_list;
        if (n > (size_t) __MAX_BYTES) {
            malloc_alloc::deallocate(p, n);
            return;
        }
        my_free_list = free_lists+FREELIST_INDEX(n);
        q->free_list_link = *my_free_list;
        *my_free_list = q;
    }
    static void* reallocate(void* p, size_t old_sz, size_t new_sz);
};
template<bool threads, int inst>//static member初始化
char* __default_alloc_template<threads, inst>::start_free = 0;

template<bool threads, int inst>//static member初始化
char* __default_alloc_template<threads, inst>::end_free = 0;

template<bool threads, int inst>//static member初始化
size_t __default_alloc_template<threads, inst>::heap_size = 0;

template<bool threads, int inst>//static member初始化
typename __default_alloc_template<threads, inst>::obj* volatile
__default_alloc_template<threads, inst>::free_lists[__NFREELISTS] = 
{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};

template<bool threads, int inst>
void * __default_alloc_template<threads, inst>::refill(size_t n) {
    int nobjs = 20;
    char * chunk = chunk_alloc(n, nobjs);
    obj* volatile * my_free_list;
    obj* result;
    obj * current_obj, * next_obj;
    if (nobjs == 1) {//如果从chunk_alloc只得到了1个块，那么分配给调用refill的调用者用
        return chunk;
    }
    my_free_list = free_lists+FREELIST_INDEX(n);
    result = (obj*)chunk;//chunk的第一块返回给调用者
    *my_free_list = next_obj = (obj*)(chunk + n);
    for (int i = 1;;i++) {//将剩下的块插入到链表中，等待以后使用
        current_obj = next_obj;
        next_obj = (obj*)((char*)next_obj + n);
        if (nobjs - 1 == i) {
            current_obj->free_list_link = 0;//最后一个节点指向NULL
            break;
        }
        else {
            current_obj->free_list_link = next_obj;
        }
    }
    return result;

}





#ifdef __USE_MALLOC//定义就使用一级配置器
typedef __malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc alloc; //定义alloc为malloc_alloc_template配置器
#else//没定义就使用二级配置器作为alloc，alloc在很多容器中使用
typedef __default_alloc_template<true,0> alloc;
#endif//end of use malloc

#endif//end of file