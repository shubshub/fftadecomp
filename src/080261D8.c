#include "ffta.h"

/* Complete [0x080261D8, 0x0802657E): 934 bytes, 418 instructions.
 * Target:
 *   f0b557464e464546e0b481b0071c3c1c803400260620824670f0c4fd084d2968
 *   896970f075ff00280cd0286880690321a1f04cfe0d2805d1a0880138a08028e0
 *   38f400020d4800689021c900401880190c2505700220a3f087f9000600280fd0
 *   a0780438a070207804302070381c94300168b00040180d21016007e038f40002
 *   381c94300168b00040180560701c0006060e0a488146006880692221a1f016fe
 *   051c0220a3f060f90006000e8046002806d0a0880138a08043e0000038f40002
 *   494608689021c900401880190d210170381c94300168b0004018697801600620
 *   fff790fe000600280fd06878fff762fe0006002809d00d20a3f06af90006000e
 *   012808d168781e2805d1381c983000688019414601700e4a687880000d494018
 *   0178407800020843800080180068eff759ff0004000c504500d98246701c0006
 *   060ea878002807d1a0880138a08046e0f067550844725208244800689021c900
 *   40188019002188460e210170381c94300168b0004018a97801600720fff742fe
 *   000600280fd0a878fff714fe0006002809d00d20a3f01cf90006000e012808d1
 *   a8781e2805d1381c983000688019414601700f4aa87880000e49401801784078
 *   00020843800080180068eff70bff0004000c504500d98246701c0006060ee878
 *   002809d1a0880138a08042e038f40002f067550844725208284800689021c900
 *   40188019002188460f210170381c94300168b0004018e9780160e878fff7cafd
 *   0006002809d00d20a3f0d2f80006000e012808d1e8781e2805d1381c98300068
 *   801941460170164ae8788000154940180178407800020843800080180068eff7
 *   c1fe0004000c504500d98246701c0006060e0a4d286880692621a1f027fd0006
 *   000e8046286880696946fff73dfe0006002809d1a0880138a08023e038f40002
 *   f06755084472520828689021c9004018801910210170381c94300168b0004018
 *   6946098801600020fff774fd0006010e002904d1381c9830006880190170701c
 *   0006060e0220a3f03ff80006002811d1404600280ed0094d28688069a1f0b4fe
 *   0006002806d128688069a6f0edff0006002805d1a0880138a0801be038f40002
 *   28689021c9004018801911210170381c94300168b00040180f2101600020fff7
 *   39fd0006010e002904d1381c9830006880190170a088011ce0700004000c0528
 *   05d80620401a40006178401860705046a0701c205146401a20700806000e0a28
 *   05d95046f530f97a4018f87203e0617aef200840607201b038bc9846a146aa46
 *   f0bc01bc0047
 *
 * Fills the command list of the mode 5 menu for func_08027DA0, its caller
 * when func_080CDA7C(unit) returns 0 (func_08026580 fills it otherwise).
 * The layout, item and order shapes are those of src/08027B2C.c, which
 * fills the mode 1 menu the same way.
 */
typedef struct {
    u8 x;
    u8 y;
    u8 width;
    u8 height;
    u16 count;
    u16 flags;
    u8 appearance;
    u8 unknown_09;
    u8 unknown_0A[0xA];
} MenuLayout;

typedef struct {
    u8 unknown_00[0xB];
    u8 unknown_0B;
    u8 unknown_0C[0x74];
    MenuLayout layout;
    u32 *items;
    u8 *enabled;
} MenuPanel;

typedef struct {
    u8 unknown_00[0x18];
    void *unit;
    u8 unknown_1C[0x480 - 0x1C];
    u8 order[6];
} MenuShared;

typedef struct __attribute__((packed)) {
    u16 name;
    u16 value;
} EncodedRecord;

extern MenuShared *data_0200F438;
extern const EncodedRecord data_08527244[];
extern const u8 *const g_table_085567F0[];

extern void *func_08096D7C(void);
extern s32 func_080970E8(void *context, void *unit);
extern s32 func_080C7EA4(const void *object, u32 selector);
extern u8 func_080C9540(u16 bit_index);
extern u8 func_080C95A8(u16 index);
extern u8 func_080C8240(void *object);
extern u8 func_080CD4C0(void *object);
extern u8 func_08025FDC(u8 mode);
extern u8 func_08025F8C(u8 kind);
extern u8 func_080260E0(void *object, u16 *entry);
extern u16 func_080161BC(const u8 *text);

void func_080261D8(MenuPanel *panel)
{
    MenuLayout *layout = &panel->layout;
    u8 index = 0;
    u16 width = 6;
    u16 text_width;
    const u8 *sets;
    u8 value;
    u16 entry;

    if (func_080970E8(func_08096D7C(), data_0200F438->unit)
        && func_080C7EA4(data_0200F438->unit, 3) == 13) {
        layout->count--;
    } else {
        data_0200F438->order[index] = 12;
        if (func_080C9540(2)) {
            layout->width -= 4;
            layout->x += 4;
            panel->items[index] = 13;
        } else {
            panel->items[index] = 12;
        }
        index++;
    }

    sets = (const u8 *)func_080C7EA4(data_0200F438->unit, 0x22);
    if (func_080C9540(2)) {
        layout->count--;
    } else {
        data_0200F438->order[index] = 13;
        panel->items[index] = sets[1];
        if (!func_08025FDC(6) || !func_08025F8C(sets[1]))
            panel->enabled[index] = 0;
        else if (func_080C95A8(13) == 1 && sets[1] == 30)
            panel->enabled[index] = 0;
        text_width = func_080161BC(g_table_085567F0[(data_08527244 + sets[1])->name]);
        if (text_width > width)
            width = text_width;
        index++;
    }

    if (sets[2] == 0) {
        layout->count--;
    } else {
        data_0200F438->order[index] = 14;
        panel->items[index] = sets[2];
        if (!func_08025FDC(7) || !func_08025F8C(sets[2]))
            panel->enabled[index] = 0;
        else if (func_080C95A8(13) == 1 && sets[2] == 30)
            panel->enabled[index] = 0;
        text_width = func_080161BC(g_table_085567F0[(data_08527244 + sets[2])->name]);
        if (text_width > width)
            width = text_width;
        index++;
    }

    if (sets[3] == 0) {
        layout->count--;
    } else {
        data_0200F438->order[index] = 15;
        panel->items[index] = sets[3];
        if (!func_08025F8C(sets[3]))
            panel->enabled[index] = 0;
        else if (func_080C95A8(13) == 1 && sets[3] == 30)
            panel->enabled[index] = 0;
        text_width = func_080161BC(g_table_085567F0[(data_08527244 + sets[3])->name]);
        if (text_width > width)
            width = text_width;
        index++;
    }

    value = func_080C7EA4(data_0200F438->unit, 0x26);
    if (!func_080260E0(data_0200F438->unit, &entry)) {
        layout->count--;
    } else {
        data_0200F438->order[index] = 16;
        panel->items[index] = entry;
        if (!func_08025F8C(0))
            panel->enabled[index] = 0;
        index++;
    }

    if (func_080C9540(2) || !value || func_080C8240(data_0200F438->unit)
        || !func_080CD4C0(data_0200F438->unit)) {
        layout->count--;
    } else {
        data_0200F438->order[index] = 17;
        panel->items[index] = 15;
        if (!func_08025F8C(0))
            panel->enabled[index] = 0;
    }

    layout->height = layout->count;
    if (layout->count <= 5)
        layout->y += (6 - layout->count) << 1;
    layout->width = width;
    layout->x = 28 - width;
    if (layout->width > 10)
        panel->unknown_0B += (u8)(width - 11);
    else
        layout->unknown_09 &= ~0x10;
}
