#include <iostream>

#include "bits.h"

int main(void)
{
   using namespace std;

#ifdef USE_CONST_EXPR
   cout << "nr bits: " << count_nr_bits(0) << endl;
   cout << "nr bits: " << count_nr_bits(1) << endl;
   // 2015 == 0111 1101 1111
   cout << "nr bits: " << count_nr_bits(2015) << endl;
#else
   cout << "nr bits: " << count_nr_bits<0>() << endl;
   cout << "nr bits: " << count_nr_bits<1>() << endl;
   cout << "nr bits: " << count_nr_bits<2015>() << endl;

   cout << "nth bits from right: " << get_bit_pos<1 << 3, true>() << endl;
   cout << "nth bits from right: " << get_bit_pos<1 << 7, true>() << endl;
   cout << "nth bits from right: " << get_bit_pos<1 << 25, true>() << endl;

   cout << "nth bits from left: " << get_bit_pos<1 << 3, false>() << endl;
   cout << "nth bits from left: " << get_bit_pos<1 << 7, false>() << endl;
   cout << "nth bits from left: " << get_bit_pos<1 << 25, false>() << endl;

#endif

   return 0;
}
