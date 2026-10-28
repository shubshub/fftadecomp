#include "ffta.h"

struct PanelState {
    u8 unknown_00[0x0E];
    u8 flags;
};

extern struct PanelState *data_02009190;

/* 0x08018AA8 - 20 bytes: set the panel's update flag. */
void func_08018AA8(void)
{
    data_02009190->flags |= 1;
}
