#include "ffta.h"

typedef struct {
    u8 low : 4;
    u8 high : 4;
} Nibbles080BDB78;

void func_080BDB78(Nibbles080BDB78 *value, u8 low, u8 high)
{
    value->low = low;
    value->high = high;
}
