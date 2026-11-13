#include "ffta.h"

// Complete target: [0x08025A28, 0x08025B52), 298 bytes.

typedef struct {
    u16 id;
    u8 second;
    u8 first;
} PairRecord08025A28;

typedef struct {
    u8 unknown_00[2];
    u8 width;
    u8 unknown_03[0x11];
} PairLayout08025A28;

typedef struct {
    u8 unknown_00[0x80];
    PairLayout08025A28 layout;
    const u32 *entries;
    const u8 *enabled;
    u8 unknown_9c[4];
    u8 *resource;
} PairPanel08025A28;

typedef struct {
    u8 unknown_00[0x2c];
    u8 text[0];
} PairContext08025A28;

extern PairContext08025A28 *data_0200F438;

PairRecord08025A28 *func_080CB210(u32 identifier, s32 *count);
void func_080142DC(u8 *text, u32 value, u32 digits);
void func_08015110(void *context, s32 position, const u8 *text, u32 mode, u32 style);
void func_0814186C(void *source, s32 destination, u32 count);

void func_08025A28(PairPanel08025A28 *panel, void *context, s32 position, u16 index)
{
    PairLayout08025A28 *layout = &panel->layout;
    u32 id = panel->entries[index];
    u8 *glyph = panel->resource + 0x80;
    PairRecord08025A28 *record;
    s32 count;
    s32 i;
    u8 digits;

    record = func_080CB210(0, &count);
    for (i = 0; i < count && record->id != id; i++, record++)
        ;

    digits = record->first <= 9 ? 1 : 2;
    func_080142DC(data_0200F438->text, record->first, digits);
    position += (layout->width - 9) * 64;
    if (digits == 1)
        position += 0x40;
    if (panel->enabled[index] == 0)
        func_08015110(context, position, data_0200F438->text, 1, 1);
    else
        func_08015110(context, position, data_0200F438->text, 0, 1);
    position += 0x40;
    func_0814186C(glyph, position, 0x20);
    position += 0x40;

    digits = record->second <= 9 ? 1 : 2;
    func_080142DC(data_0200F438->text, record->second, digits);
    if (digits == 1)
        position += 0x40;
    if (panel->enabled[index] == 0)
        func_08015110(context, position, data_0200F438->text, 1, 1);
    else
        func_08015110(context, position, data_0200F438->text, 0, 1);
}
