#include "ffta.h"

/*
 * Complete target [0x08087B30, 0x08087C5C): 300 bytes, 114 instructions.
 *
 * Copies one 0x280-byte unit graphic per unit into OBJ VRAM: units 0-7 at
 * 0x06011000, units 8-23 at 0x06015300.  index 0xFF does all 24 units.
 */

typedef struct {
    u8 unknown_000[0xBCC];
    u8 palettes[24];
} State08087B30;

typedef struct {
    u8 unknown_00[4];
    u8 enabled;
    u8 unknown_05[0x108 - 5];
} Unit08087B30;

typedef struct {
    u8 unknown_00[0x80];
    Unit08087B30 units[24];
} GameState08087B30;

extern State08087B30 *data_03002818;
extern u8 data_02003CB0[];
extern const u8 data_083B5A5C[];
extern const u8 data_08393F0C[][2];
extern GameState08087B30 g_state_02000000;

/* src/08022238.c defines it returning u16.  This module uses the whole
 * return register (0x08087B86, 0x08087C20; 08087C5C at 0x08087D50), so it
 * saw a 32-bit declaration: with u16, agbcc extends again after each call
 * (304 bytes). */
extern u32 func_08022238(void *unit, u8 *palette);
extern u32 func_08005318(const u8 *archive, u8 *destination, u16 first, u16 count);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_08087B30(u8 index)
{
    s32 i;
    u8 *destination;
    u8 *buffer = data_02003CB0;

    if (index == 0xFF) {
        for (i = 0; i < 24; i++) {
            if (i < 8)
                destination = (u8 *)0x06011000 + i * 0x280;
            else
                destination = (u8 *)0x06015300 + (i - 8) * 0x280;
            if (g_state_02000000.units[i].enabled) {
                u8 palette;
                u32 sprite = func_08022238(&g_state_02000000.units[i], &palette);
                u8 entry;

                data_03002818->palettes[i] = palette;
                entry = data_08393F0C[sprite][0];
                func_08005318(data_083B5A5C, buffer, entry, 1);
                func_0814186C(buffer, destination, 0x140);
            }
        }
    } else {
        if (index < 8)
            destination = (u8 *)0x06011000 + index * 0x280;
        else
            destination = (u8 *)0x06015300 + (index - 8) * 0x280;
        if (g_state_02000000.units[index].enabled) {
            u8 palette;
            u32 sprite = func_08022238(&g_state_02000000.units[index], &palette);
            /* The table byte is loaded before the archive address
             * (0x08087C1E-0x08087C26). */
            u8 entry = data_08393F0C[sprite][0];

            func_08005318(data_083B5A5C, buffer, entry, 1);
            func_0814186C(buffer, destination, 0x140);
        }
    }
}
