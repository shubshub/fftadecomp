#include "ffta.h"

/* 0x0804C7EC..0x0804C832: 70 bytes / 35 instructions. */
struct Record0804C7EC {
    u8 unknown_00[8];
    u16 position;
    u16 mode;
    u8 type;
    u8 active;
    u8 count;
    u8 unknown_0F[13];
};

void func_0804C7EC(struct Record0804C7EC *records, u16 index)
{
    if (records[index].active != 0 && records[index].type == 6) {
        ++records[index].position;
        if (records[index].mode == 1) {
            if (records[index].position + 1 >= records[index].count)
                records[index].position = 0;
        } else {
            if (records[index].position + 1 >= records[index].count)
                records[index].position = records[index].count - 1;
        }
    }
}
