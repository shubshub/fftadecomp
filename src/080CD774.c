#include "080CD774.h"

void func_080CD774(u8 *data, u8 first, u8 second)
{
    if (first >= second) {
        first -= second;
        second = 0;
    } else {
        second -= first;
        first = 0;
    }

    data[0xDA] = first;
    if (first == 0)
        set_first_active(data, 0);
    else
        set_first_active(data, 1);

    data[0xDB] = second;
    if (second == 0)
        set_second_active(data, 0);
    else
        set_second_active(data, 1);
}
