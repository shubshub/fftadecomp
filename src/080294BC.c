#include "ffta.h"

typedef struct {
    u16 active;
    u8 unknown_02[2];
    u8 mode;
} State080294BC;

extern State080294BC *data_0200F438;
extern void func_080294E4(u32 value);

void func_080294BC(u32 value)
{
    func_080294E4(value);
    data_0200F438->mode = 10;
    data_0200F438->active = 1;
}
