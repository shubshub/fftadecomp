#include "ffta.h"

typedef struct {
    u8 first_layer;
    u8 second_layer;
    u8 first_mode;
    u8 second_mode;
    u8 unknown_04[0xC];
    u32 field_10;
    u32 field_14;
    u32 field_18;
    u8 field_1C;
    u8 field_1D;
    u16 field_1E;
} State0801E204;

extern State0801E204 g_state_02007F40;
extern void func_0801E098(u8 format);
extern u16 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);
extern void func_080034B8(u16 value, u8 layer);

/* Target bytes [0801E204, 0801E2A4):
 * 70 B5 56 46 4D 46 44 46 70 B4 01 20 21 4D 00 21
 * 89 46 28 70 48 46 68 70 02 20 03 21 A8 70 E9 70
 * 01 20 FF F7 37 FF 1C 49 8A 46 50 46 E5 F7 20 FC
 * 04 1C C0 26 F6 04 30 1C E5 F7 20 FC 04 43 02 20
 * 04 43 24 04 24 0C 20 1C 01 21 E5 F7 33 F9 13 48
 * 80 46 E5 F7 0D FC 04 1C 30 1C E5 F7 0F FC 04 43
 * 03 20 04 43 24 04 24 0C 20 1C 00 21 E5 F7 22 F9
 * 2E 61 51 46 69 61 40 46 A8 61 08 20 49 46 29 77
 * 68 77 48 46 E8 83 38 BC 98 46 A1 46 AA 46 70 BC
 * 01 BC 00 47 40 7F 00 02 00 70 00 06 00 60 00 06.
 */
void func_0801E204(void)
{
    u16 value;

    g_state_02007F40.first_layer = 1;
    g_state_02007F40.second_layer = 0;
    g_state_02007F40.first_mode = 2;
    g_state_02007F40.second_mode = 3;
    func_0801E098(1);
    value = func_08003A74(0x06007000);
    value |= func_08003A80(0x06000000);
    value |= 2;
    func_080034B8(value, 1);
    value = func_08003A74(0x06006000);
    value |= func_08003A80(0x06000000);
    value |= 3;
    func_080034B8(value, 0);
    g_state_02007F40.field_10 = 0x06000000;
    g_state_02007F40.field_14 = 0x06007000;
    g_state_02007F40.field_18 = 0x06006000;
    g_state_02007F40.field_1C = 0;
    g_state_02007F40.field_1D = 8;
    g_state_02007F40.field_1E = 0;
}
