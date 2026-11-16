#include "ffta.h"

/* 0x080182CC..0x0801843C: 368 bytes, 139 instructions.
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

struct Sprite080182CC {
    u8 unknown_00[0x16];
    u16 unknown_16;
    u16 unknown_18;
    u8 unknown_1A[0x0E];
    u8 unknown_28;
};

struct __attribute__((packed)) SelectedResource080182CC {
    u16 id : 10;
    u16 unknown_0A : 6;
};

struct Selection080182CC {
    const struct SelectedResource080182CC *current;
    u32 unknown_04;
    u32 unknown_08;
    u16 id;
    u8 unknown_0E[0x04];
    u8 unknown_12;
    u8 unknown_13[0xA1];
    u8 unknown_B4;
};

extern struct Selection080182CC g_state_020020D0;
extern u8 g_state_02000000[];
extern const u32 data_0836D678[];
extern u32 func_080CE4DC(u16 id, u8 selector);
extern u8 func_080C95A8(u16 index);
extern u8 func_080CED5C(u8 index);

u32 func_080182CC(struct Sprite080182CC *sprite, u8 kind, u16 *id)
{
    u32 result = data_0836D678[kind];
    u8 flag;

    switch (kind) {
    case 1:
    case 2:
        sprite->unknown_16 = 0x1000;
        sprite->unknown_18 = 0x8000;
        break;
    case 9:
        sprite->unknown_16 = 0x1000;
        sprite->unknown_18 = 0x8000;
        if (func_080CE4DC(g_state_020020D0.current
                          ? g_state_020020D0.current->id
                          : g_state_020020D0.id, 2) == 3) {
            switch (*id) {
            case 1:
                *id = 10;
                break;
            case 2:
                *id = 11;
                break;
            }
        }
        if (g_state_020020D0.unknown_12 != 4)
            break;
        flag = func_080C95A8(0x0D) == 1;
        switch (*id) {
        case 0:
            if (g_state_020020D0.unknown_B4 == 0)
                break;
            if (func_080CED5C(1))
                *id = 0x0F;
            else
                *id = 0x0D;
            break;
        case 3:
            if (flag == 0)
                *id = 0x0C;
            else
                *id = 0x10;
            break;
        case 4:
            if (flag != 0)
                break;
            if (func_080CED5C(1))
                *id = 0x0F;
            else
                *id = 0x0D;
            break;
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
        sprite->unknown_28 = 0;
        sprite->unknown_16 = 0x80;
        sprite->unknown_18 = 0x100;
        break;
    }
    if ((g_state_02000000[0x2FC0] & 0x18) == 8) {
        sprite->unknown_16 = 0x1000;
        sprite->unknown_18 = 0x8000;
    }
    return result;
}
