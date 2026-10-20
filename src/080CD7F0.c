#include "080CD7F0.h"

void func_080CD7F0(void *object)
{
    u8 *data = object;
    if (countdown_a_active(data)) {
        u8 value = data[0xDA];

        if (!(value & 0x80)) {
            if (value != 0)
                value--;
            if (value == 0)
                set_countdown_a_active(data, 0);
            data[0xDA] = value;
        }
    } else if (countdown_b_active(data)) {
        u8 value = data[0xDB];

        if (!(value & 0x80)) {
            if (value != 0)
                value--;
            if (value == 0)
                set_countdown_b_active(data, 0);
            data[0xDB] = value;
        }
    }
}
