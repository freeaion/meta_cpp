#include <iostream>
#include <cstddef>
#include "util.h"

#ifdef CLASS_IMPL
#  include "bubble_sort_class.h"
#else
#  include "bubble_sort_func.h"
// function template partial specialization is not allowed
// so instantiate here for int
template<>
inline void bubble_sort_inner<int, 0, 0>(int * data) { }
template<>
inline void bubble_sort<int, 1>(int * data) { }
#endif

int main(void)
{
   constexpr std::size_t SIZE = 100;
   int data[SIZE];

   srand(time(nullptr));
   for(std::size_t i = 0; i < SIZE; i++) {
      data[i] = rand() % 1000;
   }

#ifdef CLASS_IMPL
   BubbleSort<int, SIZE>::sort(data);
#else
   bubble_sort<int, SIZE>(data);
#endif

   MetaPrtArray<int, SIZE>::print(data);

   return 0;
}
