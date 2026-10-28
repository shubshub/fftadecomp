#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0a : 6;
} SelectedResource;

typedef struct {
    const SelectedResource *current;
    u32 unknown_04;
    u32 unknown_08;
    u16 id;
} ResourceSelection;

extern ResourceSelection g_state_020020D0;
extern const u8 *const g_table_085567F0[];
extern u32 func_080CE4DC(u16 id, u32 field);
extern u16 func_08018ABC(u8 *destination, u32 value);
extern u16 func_08018C24(u8 *destination, const u8 *text);

#define CURRENT_RESOURCE_ID \
    (g_state_020020D0.current \
        ? g_state_020020D0.current->id : g_state_020020D0.id)

/* 080190A8..08019120: 120 bytes, 47 instructions. */
u32 func_080190A8(u8 *destination)
{
    u16 present = func_080CE4DC(CURRENT_RESOURCE_ID, 0x2e);

    if (present != 0) {
        func_08018ABC(destination, func_080CE4DC(CURRENT_RESOURCE_ID, 0x2f));
    } else {
        func_08018C24(destination, g_table_085567F0[0]);
    }
    return 0;
}
