#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u8 mode;
} CommandManager;

extern CommandManager *data_020159CC;

void func_08121BDC(u8 mode)
{
    data_020159CC->mode = mode;
}
