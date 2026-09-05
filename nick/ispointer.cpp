#include "ispointer.h"

int main()
{
    std::cout << std::boolalpha;
    std::cout << "is_pointer_v<int>  = " << is_pointer_v<int> << '\n';   // false
    std::cout << "is_pointer_v<int*> = " << is_pointer_v<int *> << '\n'; // true
    return 0;
}