#include "ffta.h"

/* 0x080301B0..0x08030200: 80 bytes. */
typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0A : 6;
} Resource;

typedef struct {
    u8 unknown_00[0x24];
    Resource *slots[16];
} ResourceSlots;

typedef struct {
    u32 unknown_00;
    ResourceSlots *resources;
} ResourceContext;

extern ResourceContext *g_state_03002810;

s32 func_080301B0(Resource *resource)
{
    s32 i;

    for (i = 0; i < 16; i++) {
        Resource **slots = g_state_03002810->resources->slots;
        Resource **slot = slots + i;
        Resource *current = *slot;

        if (current == 0 || current->id == 0 || current->id == resource->id) {
            *slot = resource;
            return i;
        }
    }
    return -1;
}
