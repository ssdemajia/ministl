#include <vector>

template<class RandomAccessIterator>
inline void push_heap(RandomAccessIterator first,
                      RandomAccessIterator last) {
    __push_heap_aux(first, last, RandomAccessIterator::distance_type, 
    RandomAccessIterator::value_type);
}

template<class RandomAccessIterator, class Distance, class T>
inline void __push_heap_aux(RandomAccessIterator first,
                            RandomAccessIterator last,
                            Distance*, T*) {
    __push_heap(first, Distance((last - first) - 1), Distance(0), T(*(last-1)));                            
}
