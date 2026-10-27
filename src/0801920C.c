#include "ffta.h"

typedef struct __attribute__((packed)) SelectedResource {
    u16 id : 10;
    u16 unknown_0a : 6;
    u8 flags;
    u8 value;
} SelectedResource;

typedef struct ResourceSelection {
    const SelectedResource *current;
} ResourceSelection;

extern ResourceSelection g_state_020020D0;
extern const u8 *const g_table_08526680[];
extern u32 func_080CE4DC(u16 id, u32 field);
extern u16 func_08018ABC(u8 *destination, u32 value);
extern u16 func_08018C24(u8 *destination, const u8 *text);

/* 0801920C..08019268: 92 bytes, 38 instructions. */
u32 func_0801920C(u8 *destination)
{
    const SelectedResource *resource = g_state_020020D0.current;
    u8 value = resource->value;

    if (resource->flags & 0x1c) {
        value = func_080CE4DC(resource->id, 0x10);
        if (value == 0)
            value = 0xff;
    }

    if (value == 0xff) {
        func_08018C24(destination, g_table_08526680[0]);
        return 8;
    } else {
        func_08018ABC(destination, value);
        return 0;
    }
}
