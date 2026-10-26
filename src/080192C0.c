#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 id : 10;
    u16 unknown_0A : 6;
} SelectedResource;

typedef struct {
    SelectedResource *current;
} ResourceSelection;

extern ResourceSelection g_state_020020D0;
extern const u8 *const g_table_08526680[];
extern const u8 *const g_table_085567F0[];

extern u32 func_080CB4A4(u8 code);
extern const u8 *func_080CB524(u32 identifier);
extern u32 func_080CE4DC(u16 identifier, u32 field);
extern u16 func_08018C24(u8 *destination, const u8 *text);
extern u16 func_08018C94(u8 *destination, u32 format);

/* Complete target: [0x080192C0, 0x08019398), 216 bytes. */
u32 func_080192C0(u8 *destination, u8 field)
{
    SelectedResource *record = g_state_020020D0.current;
    u8 *cursor = destination;
    u16 identifier = func_080CB4A4(*((const u8 *)record + field - 30));
    u32 property;
    u16 formatted;

    if (identifier == 0)
    {
        func_08018C24(cursor, g_table_08526680[0]);
        return 0;
    }

    property = 0;
    switch (field)
    {
    case 0x22:
        property = 0x2A;
        break;
    case 0x23:
        property = 0x2C;
        break;
    }

    formatted = func_080CE4DC(record->id, property);
    if (formatted)
        cursor += func_08018C94(cursor, 3);

    cursor += func_08018C24(cursor, func_080CB524(identifier));
    if (func_080CE4DC(record->id, property + 1))
        cursor += func_08018C24(cursor, g_table_085567F0[0x42]);

    if (formatted)
        func_08018C94(cursor, 0);
    return 0;
}
