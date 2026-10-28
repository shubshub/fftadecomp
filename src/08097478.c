#include "ffta.h"

typedef struct {
    u8 unknown_00[0x44];
    void *primary;
    u8 unknown_48[4];
    void *children[2];
} Group08097478;

extern u32 func_08021C3C(void *object);
extern u16 func_08021DE0(const void *object);
extern void func_08021DE4(void *object, u16 clear_flags, u16 set_flags);

/* 0x08097478..0x08097504: 140 bytes, 64 instructions. */
s32 func_08097478(Group08097478 *group, u32 identifier)
{
    s32 ready = 1;
    s32 i;

    for (i = 0; i < 2; i++) {
        if (group->children[i]) {
            if (func_08021C3C(group->children[i]) == identifier) {
                func_08021DE4(group->children[i], 0, 0x100);
            } else if (!(func_08021DE0(group->children[i]) & 0x100)) {
                ready = 0;
            }
        }
    }
    if (group->primary) {
        if (func_08021C3C(group->primary) == identifier) {
            func_08021DE4(group->primary, 0, 0x100);
        } else if (!(func_08021DE0(group->primary) & 0x100)) {
            ready = 0;
        }
    }
    return ready;
}
