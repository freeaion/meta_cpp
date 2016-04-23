/* -------------------------------------------------------------------------
* bits.h: bit manipulations using metaprogramming
*
* Copyright 2016 by Yonghyun Hwang <freeaion@gmail.com>
*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.  Some rights reserved.
* -------------------------------------------------------------------------*/
#ifndef CNT_NR_BITS_H
#define CNT_NR_BITS_H

#include <cstddef>

// count number of bits
constexpr std::size_t count_nr_bits(size_t num)
{
   return num ? 1 + count_nr_bits(num & (num - 1)) : 0;
}

template <std::size_t num>
std::size_t count_nr_bits(void)
{
   return 1 + count_nr_bits<num & (num - 1)>();
}

template <>
std::size_t count_nr_bits<0>(void)
{
   return 0;
}

// get bit position
template <std::size_t num>
std::size_t get_bit_pos_inner(void)
{
   return num == 1 ? 1 : 1 + get_bit_pos_inner<(num >> 1)>();
}

template <std::size_t num, bool fromRight>
std::size_t get_bit_pos(void)
{
   static_assert(num != 0 && count_nr_bits(num) == 1,
                 "only 2^n can be input for get_bit_pos");
   if (fromRight) {
      return get_bit_pos_inner<num>();
   }
   else {
      return (sizeof(std::size_t)*8 - get_bit_pos_inner<num>());
   }
}

#endif // CNT_NR_BITS_H
