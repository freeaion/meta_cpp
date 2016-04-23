/* -------------------------------------------------------------------------
* util.h: implements fast_ternary and meta_inc_sort_swap
*
* Copyright 2016 by Yonghyun Hwang <freeaion@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.  Some rights reserved.
* -------------------------------------------------------------------------*/
#ifndef UTIL_H
#define UTIL_H

#include <iostream>
#include <type_traits>

template<typename T>
inline T fast_ternary(bool cond, T val_cond_true, T val_cond_false)
{
   static_assert(std::is_integral<T>::value, "fast_ternary is only for integral type");

   return (((T)!(cond) - (T)1) & val_cond_true) +
      (((T)!!(cond) - (T)1) & val_cond_false);
}

template<typename T, int i, int j>
inline void meta_inc_sort_swap(T * data)
{
   static_assert(i < j, "i should be less than j\n");

   if (std::is_integral<T>::value) {
      T max = fast_ternary<T>(data[i] > data[j], data[i], data[j]);
      T min = fast_ternary<T>(data[i] < data[j], data[i], data[j]);

      data[i] = min;
      data[j] = max;
   }
   else {
      if(data[i] > data[j]) {
         T tmp = data[i];
         data[i] = data[j];
         data[j] = tmp;
      }
   }
}

// function template partial specialization is not allowed
// hence, use struct to implement meta print array
template<typename T, int N>
struct MetaPrtArray
{
   static void print(T * data)
   {
      std::cout << data[0] << " < ";
      MetaPrtArray<T, N-1>::print(data+1);
   }
};

template<typename T>
struct MetaPrtArray<T, 1>
{
   static void print(T * data)
   {
      std::cout << data[0] << std::endl;
   }
};

#endif // UTIL_H
