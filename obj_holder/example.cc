#include <array>
#include "obj_holder.h"

int main(void)
{
   typename ObjHolder<double>::type v1; // v1 on stack
   typename ObjHolder<std::array<double,200>>::type v2; //v2 on free store (meaning heap)
   //...

   *v1 = 7.7;
   (*v2)[77] = 9.9;

   return 0;
}
