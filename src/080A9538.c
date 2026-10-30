#include "ffta.h"

typedef struct {
    u8 index;
    s8 selection;
    s8 previous_selection;
    u8 unknown_03;
    s16 x;
    s16 y;
    s16 target_x;
    s16 target_y;
    s16 previous_x;
    s16 previous_y;
    u8 flags;
} State080A8F60;

extern State080A8F60 data_0200FFC8;
extern void func_080A8F60(State080A8F60 *state);

/* 0x080A9538..0x080A9548: 16 bytes, including the named-object literal. */
void func_080A9538(void)
{
    func_080A8F60(&data_0200FFC8);
}
