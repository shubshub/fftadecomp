#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0A : 6;
} Resource;

typedef struct {
    u8 unknown_00[0x24];
    Resource *slots[16];
} ResourceSlots;

typedef struct {
    u8 unknown_00[4];
    ResourceSlots *resources;
} ResourceContext;

extern ResourceContext *g_state_03002810;

/* Complete target: [0x080301B0, 0x08030200), 80 bytes, 38 instructions. */
s32 func_080301B0(Resource *resource)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        if (g_state_03002810->resources->slots[i] == 0) {
            g_state_03002810->resources->slots[i] = resource;
            return i;
        }
        if (g_state_03002810->resources->slots[i]->id == 0
            || g_state_03002810->resources->slots[i]->id == resource->id) {
            g_state_03002810->resources->slots[i] = resource;
            return i;
        }
    }
    return -1;
}
