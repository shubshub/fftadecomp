#include "ffta.h"

/* Target: complete [0x080194E4, 0x08019574), 144 bytes. */
typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0a : 6;
    u8 unknown_02[6];
    u16 identifiers[2];
} SelectedResource;

typedef struct {
    SelectedResource *current;
} ResourceSelection;

extern ResourceSelection g_state_020020D0;
extern const u8 *const g_table_08526680[];
extern const u8 *const g_table_085567F0[];
extern u32 func_080CE4DC(u16 identifier, u32 field);
extern u32 func_080CA7A4(u32 identifier, u32 mode);
extern u16 func_08018C24(u8 *destination, const u8 *text);

u32 func_080194E4(u8 *destination, u8 field)
{
    SelectedResource *record = g_state_020020D0.current;
    u32 index;
    u32 property;

    if (field == 0x82) {
        index = 0;
        property = 0x3d;
    } else {
        index = 1;
        property = 0x3e;
    }
    if (func_080CE4DC(record->id, property)) {
        func_08018C24(destination, g_table_085567F0[0x26]);
    } else {
        u16 identifier = record->identifiers[index];
        u16 text_index;

        if (identifier == 0)
            text_index = 0;
        else if (identifier <= 0x177)
            text_index = func_080CA7A4(identifier, 0);
        else
            text_index = identifier + 0x7b;
        func_08018C24(destination, g_table_08526680[text_index]);
    }
    return 0;
}
