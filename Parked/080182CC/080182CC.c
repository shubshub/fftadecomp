/* Target 0x080182CC..0x0801843C, 368 bytes:
 * f0b5051c141c0906090e064a880080180768481e0e2800d9
 * 95e08000024940180068874678d63608f882010834830108
 * 348301080284010802840108128401081284010812840108
 * 128401084083010802840108028401080284010802840108
 * 028401080284010880204001e8828020000267e080204001
 * e88280200002288305480268002a09d01078517803221140
 * 0902014303e00000d02000028189081c0221b6f0b5f80328
 * 09d12088012802d0022802d003e00a2000e00b2020800a4e
 * b07c04283fd10d20b1f008f900210006000e012800d10121
 * 2088032815d0032804dc002805d02ee0d0200002042814d0
 * 29e0301cb4300078002824d00120b6f0c7fc0006002810d1
 * 12e0002902d10c20208018e01020208015e0002913d10120
 * b6f0b6fc0006002802d00f2020800ae00d20208007e0291c
 * 2831002008708020e882803028830948bf21890140180178
 * 18200840082805d180204001e882802000022883381cf0bc
 * 02bc084700000002
 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x16];
    u16 field_16;
    u16 field_18;
    u8 unknown_1a[0x0e];
    u8 field_28;
} Record080182CC;

typedef struct {
    u8 field_00;
    u8 field_01;
} PackedRecord;

typedef struct {
    PackedRecord *record;
    u8 unknown_04[8];
    u16 field_0c;
    u8 unknown_0e[4];
    u8 field_12;
    u8 unknown_13[0xa1];
    u8 field_b4;
} State;

extern State g_state_020020D0;
extern u8 g_state_02000000[];
extern const u32 data_0836D678[];

u32 func_080CE4DC(u16 index, u8 selector);
u8 func_080C95A8(u16 index);
u8 func_080CED5C(u8 mode);

u32 func_080182CC(Record080182CC *record, u8 selector, u16 *value)
{
    u32 result = data_0836D678[selector];

    switch (selector) {
    case 1:
    case 2:
        record->field_16 = 0x1000;
        record->field_18 = 0x8000;
        break;
    case 9:
        {
            State *state;
            u16 index;
            s32 flag;

            record->field_16 = 0x1000;
            record->field_18 = 0x8000;
            state = &g_state_020020D0;
            if (state->record)
                index = state->record->field_00 |
                        ((state->record->field_01 & 3) << 8);
            else
                index = state->field_0c;
            if (func_080CE4DC(index, 2) == 3) {
                switch (*value) {
                case 1:
                    *value = 10;
                    break;
                case 2:
                    *value = 11;
                    break;
                }
            }
            state = &g_state_020020D0;
            if (state->field_12 != 4)
                break;
            flag = func_080C95A8(13) == 1;
            switch (*value) {
            case 0:
                if (state->field_b4) {
                    if (func_080CED5C(1))
                        *value = 15;
                    else
                        *value = 13;
                }
                break;
            case 3:
                if (!flag)
                    *value = 12;
                else
                    *value = 16;
                break;
            case 4:
                if (!flag) {
                    if (func_080CED5C(1))
                        *value = 15;
                    else
                        *value = 13;
                }
                break;
            }
        }
        break;
    case 3:
    case 4:
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        record->field_28 = 0;
        record->field_16 = 0x80;
        record->field_18 = 0x100;
        break;
    }
    if ((g_state_02000000[0x2fc0] & 0x18) == 8) {
        record->field_16 = 0x1000;
        record->field_18 = 0x8000;
    }
    return result;
}
