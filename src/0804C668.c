#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u32 value;
    u8 unknown_08[4];
    u8 type;
    u8 active;
    u8 unknown_0E[2];
    u8 first;
    u8 second;
    u8 third;
    u8 fourth;
    u8 unknown_14[8];
} Entry0804C668;

void func_0804C668(Entry0804C668 *entries, u16 index, u32 value,
                   u8 first, u8 second, u8 third, u8 fourth)
{
    entries[index].value = value;
    entries[index].active = 1;
    entries[index].first = first;
    entries[index].second = second;
    entries[index].third = third;
    entries[index].type = 3;
    entries[index].fourth = fourth;
}
