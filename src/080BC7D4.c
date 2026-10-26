#include "ffta.h"

/* 0x080BC7D4: 40 bytes. */
extern u8 data_020100C8[];
void func_080BACF0(void *context, void *first, void *second,
                   void *third, u8 mode);

void func_080BC7D4(void *first, void *second, void *third, u8 mode)
{
    func_080BACF0(data_020100C8, first, second, third, mode);
}
