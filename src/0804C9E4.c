#include "ffta.h"

typedef struct {
    u16 unknown_00;
} State0804C9E4;

extern Table data_03002710;
extern State0804C9E4 *data_0201F540;
extern void func_080069F4(Table *state, u8 count);

/* 0x0804C9E4..0x0804CA00: 28 complete bytes, including both mapped-data literals. */
u16 func_0804C9E4(void)
{
    func_080069F4(&data_03002710, 5);
    return data_0201F540->unknown_00;
}
