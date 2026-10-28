#include "ffta.h"

/* 0x080DBFFC..0x080DC012: 22 bytes / 9 instructions. */
struct Group;

extern u32 func_080DD4B4(struct Group *group, u8 index);
extern u8 func_080DB838(u32 object);

u8 func_080DBFFC(struct Group *group, u8 index)
{
    return func_080DB838(func_080DD4B4(group, index));
}
