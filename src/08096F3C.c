#include "ffta.h"

typedef struct Effect Effect;
extern Effect data_0200F4C0;
extern void func_080922CC(Effect *effect, s16 x, s16 y, s16 z,
                          s32 first, s32 second, s32 mode, s32 duration);

void func_08096F3C(s16 x, s16 y, s16 z)
{
    func_080922CC(&data_0200F4C0, x, y, z, -120, -86, 4, 100);
}
