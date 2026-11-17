#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1F3C];
    u16 entries[20];
} State08128E40;

extern State08128E40 g_state_02000000;
extern s16 func_08002804(void);
extern void func_08038678(u8 value);
extern void func_080CC2B4(void);

// 0x08128E40..0x08128EE0: 160 bytes.
// f0b5474680b485b00006070e002500242148224a81180888002803d06e4670190470013502310134
// 132cf4dd002d2cd00020002401308046ac4212dad9f6c2fc00040014291c19f063fda04206d06946
// 0a1913780918087810700b700134ac42ecdb40460328e4ddbd4201da2806070e0024bc4207da6a46
// 101900780ff7dcfb0134bc42f7dba3f7f5f905b008bc9846f0bc01bc0047
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
            s32 other = func_08002804() % total;
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
