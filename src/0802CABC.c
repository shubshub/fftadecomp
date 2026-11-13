#include "ffta.h"

// Complete [0x0802CABC, 0x0802CBD4): 280 bytes.
// f0b583b0041c0906090e0d1c04202840002809d0fef79aff0f4909680f4a89180f4a2823d3f7fcff201cfff7edfe02202840002865d08523db00e718e0689bf0cdfb000600280fd006480268381ccc2115f19efb43e0000040f400023c0b0000c09a0006b8d43608074808490368381ccc2215f18ffbe0689bf094fb0006002806d009200be00000bcd436087cd83b08e0689bf077fb0006002805d00b209ef093ff1a49c0890880e0689bf06bfb0006002805d1e0689bf075fb000600280ed0134eb0200002051c3a1c76231188301c0840401910800232013b002bf6dafef735ff0c4a0623e15e890152695218062100912221019140210291391c1123d3f7f7ff03b0f0bc01bc00470000ce390003ff0f000090090003

typedef struct {
    u8 unknown_00[6];
    s16 row;
    u8 unknown_08[4];
    const void *unit;
    u8 unknown_10[0x418];
    u16 tiles[0x77];
} Panel0802CABC;

typedef struct {
    u8 unknown_00[0xE];
    u16 value_0E;
} Record0802CABC;

typedef struct {
    u8 unknown_00[0x14];
    u8 *value_14;
} Display0802CABC;

typedef struct {
    u8 unknown_00[0x1C];
} Entry0802BA08;

typedef void (*BufferInitializer0802CABC)(void *buffer, u32 size);

extern u8 *data_0200F440;
extern Display0802CABC data_03000990;
extern u16 data_030039CE[];
extern BufferInitializer0802CABC const g_callbacks_0836D4B8[];
extern void (*const data_0836D4BC)(void *destination, const void *source,
                                   u32 size);
extern const u8 data_083BD87C[];

extern Entry0802BA08 *func_0802BA08(void);
extern void func_08000ADC(Entry0802BA08 *entry, const void *source,
                          void *destination, u16 words);
extern void func_08000BAC(Entry0802BA08 *entry, u16 *source, u8 *destination,
                          u16 count, u16 field_10, u16 field_12, u16 field_14);
extern void func_0802C8C4(Panel0802CABC *panel);
extern u8 func_080C8298(const void *unit);
extern u8 func_080C8260(const void *unit);
extern u8 func_080C8240(const void *unit);
extern Record0802CABC *func_080CBA84(u32 index);

void func_0802CABC(Panel0802CABC *panel, u8 flags)
{
    u16 *tiles;
    s32 i;

    if (flags & 4)
        func_08000ADC(func_0802BA08(), data_0200F440 + 0xB3C,
                      (void *)0x06009AC0, 0x28);
    func_0802C8C4(panel);
    if (flags & 2) {
        tiles = panel->tiles;
        if (func_080C8298(panel->unit)) {
            g_callbacks_0836D4B8[0](tiles, 0xCC);
        } else {
            data_0836D4BC(tiles, data_083BD87C, 0xCC);
            if (func_080C8260(panel->unit))
                data_030039CE[0] = func_080CBA84(9)->value_0E;
            else if (func_080C8240(panel->unit))
                data_030039CE[0] = func_080CBA84(11)->value_0E;
            if (func_080C8240(panel->unit) || func_080C8260(panel->unit)) {
                for (i = 0; i < 0x77; i++)
                    tiles[i] = (tiles[i] & 0x0FFF) + 0xB000;
            }
        }
        func_08000BAC(func_0802BA08(), tiles,
                      data_03000990.value_14 + panel->row * 64, 0x11, 6, 0x22,
                      0x40);
    }
}
