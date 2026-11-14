#include "ffta.h"

// Complete [0x0802C034, 0x0802C0E0): 172 bytes.
// 70b582b0051cc0208000f6f7fffb061c01a9002008800e4a081c311c15f10cfc298a0220
// 0840002818d00a4ce86803219bf01eff800000190168e8683a300078c0000918044a0888
// 8000801802680ae08001000184ba5108f0675508e86800219bf006ff021c0f480068f321
// 8900401801210091311c0023e9f730f82c1c2834201c311cfff71efd301cf6f7c9fbfff7
// a1fc054a211cc023d4f706fd02b070bc01bc004740f4000200450106

typedef struct TransferRecord TransferRecord;

typedef struct {
    u8 unknown_00[0x3A];
    u8 index;
} Unit;

typedef struct {
    u16 name;
    u8 unknown_02[6];
} NameEntry;

typedef struct {
    u8 unknown_00[0xC];
    Unit *unit;
    u16 flags;
    u8 unknown_12[0x16];
    u8 tiles[0x300];
} NamePanel;

extern u8 *data_0200F440;
extern u8 data_06014500[];
extern const NameEntry *const g_table_0851BA84[];
extern const u8 *const g_table_085567F0[];
extern void *func_08022840(u32 size);
extern void func_08022854(void *allocation);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern s32 func_080C7EA4(const void *unit, u32 selector);
extern void func_08015110(void *context, void *tiles, const u8 *text,
                          u32 mode, u32 spacing);
extern void func_0802BAF8(void *destination, const void *source);
extern TransferRecord *func_0802BA08(void);
extern void func_08000ADC(TransferRecord *entry, const void *source,
                          void *destination, u16 words);

void func_0802C034(NamePanel *panel)
{
    u8 *tiles = func_08022840(0x300);
    u16 fill;
    u16 *fill_source = &fill;
    const NameEntry *entry;
    const u8 *text;

    /* CpuFill16(0, tiles, 0x300): the SDK's vu16 temporary,
     * spelled through a pointer until fftadecomp-kit#164. */
    *fill_source = 0;
    func_0814186C(fill_source, tiles, 0x01000180);
    if (panel->flags & 2) {
        entry = g_table_0851BA84[func_080C7EA4(panel->unit, 3)];
        entry += panel->unit->index;
        text = g_table_085567F0[entry->name];
    } else {
        text = (const u8 *)func_080C7EA4(panel->unit, 0);
    }

    func_08015110(data_0200F440 + 0x3CC, tiles, text, 0, 1);
    func_0802BAF8(panel->tiles, tiles);
    func_08022854(tiles);
    func_08000ADC(func_0802BA08(), panel->tiles, data_06014500, 0xC0);
}
