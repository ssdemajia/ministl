#ifndef __SS_ALLOC_H_
#define __SS_ALLOC_H_

/*  
如果很小的空间，那么使用内存链分配，超过128字节的空间分配使用malloc，若小于128字节使用内存池中的内存块
*/
#ifdef __USE_MALLOC
typedef __malloc_alloc_template<0> malloc_alloc;
typedef malloc_alloc alloc; //定义alloc为malloc_alloc_template配置器
#else
typedef __default_alloc_template<__NODE_ALLOCATOR_THREADS,0> alloc;
#endif//end of use malloc
#endif//end of file