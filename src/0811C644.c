#include "ffta.h"

/* Target: complete [0x0811C644, 0x0811C6AE), 106 bytes. */
typedef struct {
    void *object;
    u8 angle;
    u8 unknown_05[3];
} OrbitEntry0811C644;

extern s16 func_08007A60(u8);
extern s32 func_08007A4C(u8);
extern void func_080107D4(void *, s16, s16, u8);

void func_0811C644(OrbitEntry0811C644 *entries, u8 radius)
{
    u8 index;
    s16 x;
    s16 y;

    for (index = 0; index < 8; index++) {
        x = (s16)(func_08007A60(entries[index].angle) * radius) >> 8;
        y = (s16)((s16)func_08007A4C(entries[index].angle) * radius) >> 8;
        func_080107D4(entries[index].object, x + 120, y + 64, 0);
        entries[index].angle += 2;
    }
}
