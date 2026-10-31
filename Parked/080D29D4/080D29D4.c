#include "ffta.h"

typedef struct {
    u16 id : 10;
    u16 field_0A : 8;
    u8 status : 3;
    u8 unknown_15 : 3;
    u8 field_03;
    u8 unknown_04[2];
    u16 field_06 : 16;
    u8 unknown_08[8];
} __attribute__((packed)) Record080D29D4;

typedef struct {
    u8 unknown_00[2];
    u8 unknown_02_low : 3;
    u8 kind : 3;
    u8 unknown_02_high : 2;
    u8 unknown_03[0xB];
    u16 unknown_0E_low : 3;
    u16 field_0E : 8;
    u16 unknown_0F_high : 5;
    u16 unknown_10_low : 6;
    u16 field_10 : 8;
    u16 unknown_11_high : 2;
    u8 unknown_12[0x34];
} __attribute__((packed)) Metadata080D29D4;

typedef void (*BufferInitializer080D29D4)(void *destination, u32 size);

extern const Metadata080D29D4 g_table_0855AE4C[];
extern BufferInitializer080D29D4 const g_callbacks_0836D4B8[];
extern u8 func_080C9540(u16 bit_index);
extern u32 func_08002804(void);
extern s32 func_08142950(s32 first, s32 second);

/* Complete [0x080D29D4, 0x080D2AD0): 252 bytes, 114 instructions.
 * f0b557464e464546e0b48046374d00208246012603218946a978382008401828
 * 57d13620f6f7a2fd0006002803d1304ab01802284dd901239a44444610200019
 * 80462c480268201c10216ff015fc3004ff272670000e49460840617804225242
 * 0a4002436270287c8009697c3f23194089000143081c184080004b461a400243
 * 627089091940a27804204042104008431d225242111c084008210843a070aa7b
 * d208e87b0721084040011043ff21002800d0011ce1702ff7bbfe000400149b21
 * 49006ff05bff0004010c3940a171000ee07101364635084886429ddd504638bc
 * 9846a146aa46f0bc02bc084792ae55088dfeffffb8d43608ff010000
 */
u32 func_080D29D4(void *destination)
{
    Record080D29D4 *output = destination;
    const Metadata080D29D4 *metadata = &g_table_0855AE4C[1];
    u32 count = 0;
    s32 id;

    for (id = 1; id <= 511; id++, metadata++) {
        if (metadata->kind == 3 &&
            (func_080C9540(0x36) || (u32)(id - 0x173) > 2)) {
            Record080D29D4 *record;
            u8 field;

            count++;
            record = output++;
            g_callbacks_0836D4B8[0](record, sizeof(*record));
            record->id = id;
            record->field_0A = metadata->field_10;
            record->status = 2;
            field = metadata->field_0E;
            record->field_03 = field ? field : 0xFF;
            record->field_06 = (u16)func_08142950((s16)func_08002804(), 310);
        }
    }
    return count;
}
