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
} State080A8FBC;

extern State080A8FBC data_0200FFC8;
extern void func_080A8FBC(State080A8FBC *state);

/* 080A9528..080A9538: 00 B5 02 48 FF F7 46 FD 01 BC 00 47 C8 FF 00 02. */
void func_080A9528(void)
{
    func_080A8FBC(&data_0200FFC8);
}
