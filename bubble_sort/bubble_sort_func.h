/* -------------------------------------------------------------------------
* bubble_sort_func.h: implements bubble sort using meta programming
*                     this is based on func. compare this w/ bubble_sort_class.h
*
* Copyright 2016 by Yonghyun Hwang <freeaion@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.  Some rights reserved.
* -------------------------------------------------------------------------*/
#ifndef BUBBLE_SORT_FUNC_H
#define BUBBLE_SORT_FUNC_H

#include "util.h"

template<typename T, int i, int n>
inline void bubble_sort_inner(T * data)
{
   meta_inc_sort_swap<T, i, i + 1>(data);
   // bubble up to n from i+1
   bubble_sort_inner<T, (i < n - 2) ? i + 1 : 0, (i < n - 2) ? n : 0>(data);
}

template<typename T, int n>
inline void bubble_sort(T * data)
{
   bubble_sort_inner<T, 0, n>(data);
   bubble_sort<T, n-1>(data);
}

#endif // BUBBLE_SORT_FUNC_H
