#include "ffta.h"

/* 0x080A8810..0x080A8830: 32 bytes. */
typedef struct {
    u8 unknown_00[0x2C];
} Child;

typedef struct {
    u8 unknown_00[0x20];
    Child children[15];
    u8 unknown_2B4[0xC];
    u8 child_count;
} Group;

Child *func_080A8810(Group *group, s32 index)
{
    if (group->child_count < index)
        return 0;
    return &group->children[index];
}
