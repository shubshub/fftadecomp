#include "ffta.h"

/* 0x080CCCA0..0x080CCCF0: 80 bytes, 37 instructions, including a pool. */
typedef struct {
    u8 unknown_00[4];
    u8 active;
    u8 unknown_05[0x23];
    u16 flags;
    u8 unknown_2A[0xC6];
    u8 busy;
    u8 unknown_F1[0x17];
} MenuRecord;

typedef struct {
    u8 unknown_00[0x80];
    MenuRecord records[24];
} MenuPool;

extern MenuPool g_state_02000000;
extern void func_080CC65C(MenuRecord *record);

void func_080CCCA0(void)
{
    u8 index = 0;
    MenuPool *pool = &g_state_02000000;
    MenuRecord *records = pool->records;

    do {
        if (pool->records[index].active && !pool->records[index].busy &&
            (pool->records[index].flags & 8)) {
            func_080CC65C(&records[index]);
        }
        index++;
    } while (index < 24);
}
