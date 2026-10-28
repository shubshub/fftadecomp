#include "ffta.h"

typedef struct {
    u32 unknown_00;
    u32 selection;
} ResourceSelection;

extern ResourceSelection g_state_020020D0;
extern const u8 *const g_table_08526680[];
extern u32 func_080CA7A4(u32 identifier, u32 field);
extern u32 func_080CB4A4(u8 code);
extern const u8 *func_080CB524(u32 identifier);
extern const u8 *func_080CB4E0(u32 identifier);
extern u16 func_08018C24(u8 *destination, const u8 *text);

/* Complete target: 0x080197BC..0x08019812, 86 bytes. */
u32 func_080197BC(u8 *destination)
{
    u32 selection = g_state_020020D0.selection;
    u16 kind = selection >> 16;
    u16 identifier = selection;
    const u8 *text;

    switch (kind) {
    case 1:
        text = func_080CB524((u16)func_080CB4A4((u8)identifier));
        break;
    case 2:
        text = func_080CB4E0(identifier);
        break;
    default:
        text = g_table_08526680[func_080CA7A4(identifier, 0)];
        break;
    }
    func_08018C24(destination, text);
    return 0;
}
