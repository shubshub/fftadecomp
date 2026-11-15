#include "ffta.h"

typedef struct {
    u8 first_layer;
    u8 second_layer;
    u8 first_mode;
    u8 second_mode;
    u8 unknown_04[0xC];
    u32 source_a;
    u32 source_b;
    u32 source_c;
    u8 unknown_1C;
    u8 unknown_1D;
    u16 fill_tile;
} State0801E204;

extern State0801E204 g_state_02007F40;
extern void func_0801E098(u8 index);
extern u16 func_08003A74(u32 packed);
extern u16 func_08003A80(u32 packed);
extern void func_080034B8(u16 control, u8 layer);

/* Target bytes [0801E204, 0801E2A4), 160 bytes, 67 instructions:
 * 70 B5 56 46 4D 46 44 46 70 B4 01 20 21 4D 00 21
 * 89 46 28 70 48 46 68 70 02 20 03 21 A8 70 E9 70
 * 01 20 FF F7 37 FF 1C 49 8A 46 50 46 E5 F7 20 FC
 * 04 1C C0 26 F6 04 30 1C E5 F7 20 FC 04 43 02 20
 * 04 43 24 04 24 0C 20 1C 01 21 E5 F7 33 F9 13 48
 * 80 46 E5 F7 0D FC 04 1C 30 1C E5 F7 0F FC 04 43
 * 03 20 04 43 24 04 24 0C 20 1C 00 21 E5 F7 22 F9
 * 2E 61 51 46 69 61 40 46 A8 61 08 20 49 46 29 77
 * 68 77 48 46 E8 83 38 BC 98 46 A1 46 AA 46 70 BC
 * 01 BC 00 47 40 7F 00 02 00 70 00 06 00 60 00 06
 *
 * The five setters expanded here are also present out of line in the ROM, at
 * [0801E54C, 0801E58C), with no BL and no pointer to any of them.  Each
 * body below, compiled as an ordinary function, is byte-identical to its
 * out-of-line copy.
 */

/* An inlined copy of func_0801E54C ([0801E54C, 0801E558), not yet indexed). */
static inline void inlined_0801E54C(u8 first, u8 second)
{
    g_state_02007F40.first_layer = first;
    g_state_02007F40.second_layer = second;
}

/* An inlined copy of func_0801E558 ([0801E558, 0801E564), not yet indexed). */
static inline void inlined_0801E558(u8 first, u8 second)
{
    g_state_02007F40.first_mode = first;
    g_state_02007F40.second_mode = second;
}

/* An inlined copy of func_0801E564 ([0801E564, 0801E574), not yet indexed). */
static inline void inlined_0801E564(u32 a, u32 b, u32 c)
{
    g_state_02007F40.source_a = a;
    g_state_02007F40.source_b = b;
    g_state_02007F40.source_c = c;
}

/* An inlined copy of func_0801E574 ([0801E574, 0801E580), not yet indexed). */
static inline void inlined_0801E574(u8 first, u8 second)
{
    g_state_02007F40.unknown_1C = first;
    g_state_02007F40.unknown_1D = second;
}

/* An inlined copy of func_0801E580 ([0801E580, 0801E58C), not yet indexed). */
static inline void inlined_0801E580(u16 value)
{
    g_state_02007F40.fill_tile = value;
}

void func_0801E204(void)
{
    inlined_0801E54C(1, 0);
    inlined_0801E558(2, 3);
    func_0801E098(1);
    func_080034B8(func_08003A74(0x06007000) | func_08003A80(0x06000000) | 2, 1);
    func_080034B8(func_08003A74(0x06006000) | func_08003A80(0x06000000) | 3, 0);
    inlined_0801E564(0x06000000, 0x06007000, 0x06006000);
    inlined_0801E574(0, 8);
    inlined_0801E580(0);
}
