#include "ffta.h"

typedef struct {
    const u8 *current;
} ResourceSelection;

extern ResourceSelection g_state_020020D0;
extern const u8 *const g_table_085567F0[];

extern u32 func_080CB4A4(u8 code);
extern const u8 *func_080CB524(u32 identifier);
extern u16 func_08018C24(u8 *destination, const u8 *text);
extern u32 func_08014778(const u8 *text);
extern void func_08018CB8(u8 *destination, s8 width);

/* Complete target: 0x080199EC..0x08019A50, 100 bytes. */
u32 func_080199EC(u8 *destination, u8 field)
{
    const u8 *record = g_state_020020D0.current;
    u8 *cursor = destination;
    u16 identifier = func_080CB4A4(*(record + field - 0x34));
    const u8 *text;

    if (identifier == 0) {
        text = g_table_085567F0[0x4B];
    } else {
        text = func_080CB524(identifier);
    }
    cursor += func_08018C24(cursor, text);
    func_08018CB8(cursor, (s8)(88 - func_08014778(text)));
    return 0;
}
