/* -------------------------------------------------------------------------
* obj_holder.h: implements object holder
*               depending on the size, ON_STACK_MAX, obj is allocated
*               in a stack or a heap
*
* Copyright 2016 by Yonghyun Hwang <freeaion@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.  Some rights reserved.
* -------------------------------------------------------------------------*/
#ifndef OBJ_HOLDER
#define OBJ_HOLDER

#include <cstddef>
#include <type_traits>

template<typename T>
struct OnHeap {
   OnHeap() : p {new T} { } // allocate
   ~OnHeap() { if (p) delete p; } // deallocate

   T & operator*() { return * p; }
   T * operator->() {return p; }

   // prevent copy
   OnHeap(const OnHeap &) = delete;
   OnHeap operator=(const OnHeap &) = delete;

   // allow move
   OnHeap(OnHeap && obj) : p{obj.p}
   {
      obj.p = nullptr;
   }
   OnHeap operator=(OnHeap && obj)
   {
      p = obj.p;
      obj.p = nullptr;
   }

private:
   T * p; // ptr to obj on free store
};

template<typename T>
struct OnStack {
   T & operator*() { return x; }
   T * operator->() { return &x; }

   // use default constructor, move, assignment, and so on

private:
   T x; // the obj
};

constexpr int ON_STACK_MAX = sizeof(double); // or whatever size here

template<typename T>
struct ObjHolder {
   using type = typename std::conditional<
      (sizeof(T) <= ON_STACK_MAX), OnStack<T>, OnHeap<T>
         >::type;
};

template<typename T>
void obj_copy(T* p, const T* q, std::size_t n)
{
   // std::is_pod<T>::value is computed at compile time
   // and is always true or false for a given T
   if(std::is_pod<T>::value) { // pod == plain old data, such as int, char, double ...
      memcpy(p, q, sizeof(T)*n); // use optimized copy
   }
   else {
      for (std::size_t i = 0; i != n; i++) {
         p[i] = q[i]; // copy individual values
      }
   }
}

#endif // OBJ_HOLDER
