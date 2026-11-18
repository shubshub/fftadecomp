#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F3C];
    u16 entries[20];
} State08128E40;

extern State08128E40 g_state_02000000;
extern u32 func_08002804(void);
extern void func_08038678(u16 value);
extern void func_080CC2B4(void);

void func_08128E40(u8 count)
{
    u8 order[20];
    s32 total = 0;
    s32 index;
    s32 pass;

    for (index = 0; index < 20; index++) {
        if (g_state_02000000.entries[index] != 0)
            order[total++] = index;
    }
    if (total == 0)
        return;
    for (pass = 0; pass < 4; pass++) {
        for (index = 0; index < total; index++) {
            s32 other = (s16)func_08002804() % total;
            if (other != index) {
                u8 saved = order[index];
                order[index] = order[other];
                order[other] = saved;
            }
        }
    }
    if (total < count)
        count = total;
    for (index = 0; index < count; index++)
        func_08038678(order[index]);
    func_080CC2B4();
}
