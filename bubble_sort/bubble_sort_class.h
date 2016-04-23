/* -------------------------------------------------------------------------
* bubble_sort_class.h: implements bubble sort using meta programming
*                      this is based on class. compare this w/ bubble_sort_func.h
*
* Copyright 2016 by Yonghyun Hwang <freeaion@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.  Some rights reserved.
* -------------------------------------------------------------------------*/
#ifndef BUBBLE_SORT_CLASS_H
#define BUBBLE_SORT_CLASS_H

#include "util.h"

template<typename T, int i, int n>
class BubbleSortInner
{
   enum { cont = (i < n - 2) };

public:
   static void sort(T * data)
   {
      meta_inc_sort_swap<T, i, i + 1>(data);
      // bubble up to n from i+1
      BubbleSortInner<T, cont ? i + 1 : 0, cont ? n : 0>::sort(data);
   }
};

// class template allows partial specialization
template<typename T>
class BubbleSortInner<T, 0, 0> {
public:
   static void sort(T * data) { }
};

template<typename T, int n>
struct BubbleSort
{
   static void sort(T * data)
   {
      // put max val in data[n-1]
      BubbleSortInner<T, 0, n>::sort(data);
      // do recursision w/ n-1
      BubbleSort<T, n - 1>::sort(data);
   }
};

// class template allows partial specialization
template<typename T>
struct BubbleSort<T, 1>
{
   static void sort(T * data) { }
};

#endif // BUBBLE_SORT_CLASS_H
