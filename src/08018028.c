#include "ffta.h"

// 0x08018028..0x080182CC: 676 bytes, 267 instructions.

struct Sprite08018028 {
    u8 unknown_00[0x0B];
    u8 unknown_0B;
    u16 unknown_0C;
    u8 unknown_0E;
    s8 unknown_0F;
    u8 unknown_10[0x06];
    u16 unknown_16;
    u16 unknown_18;
    u8 unknown_1A[0x03];
    u8 unknown_1D;
    u8 unknown_1E;
    u8 unknown_1F;
    u8 unknown_20[0x02];
    u16 unknown_22;
    u8 unknown_24[0x04];
    u8 unknown_28;
    u8 unknown_29[0x02];
    u8 unknown_2B;
    u8 unknown_2C[0x0E];
    u16 unknown_3A;
};

struct __attribute__((packed)) SelectedResource08018028 {
    u16 id : 10;
    u16 unknown_0A : 6;
};

struct Selection08018028 {
    const struct SelectedResource08018028 *current;
    u32 unknown_04;
    u32 unknown_08;
    u16 id;
    u8 unknown_0E[0x04];
    u8 unknown_12;
    u8 unknown_13[0xA1];
    u8 unknown_B4;
};

extern struct Selection08018028 g_state_020020D0;
extern u8 g_state_02000000[];
extern const u32 data_0836D678[];
extern u32 func_08009A24(u16 id);
extern u16 func_08009A90(u16 id);
extern u32 func_080CE4DC(u16 id, u8 selector);
extern u8 func_080C95A8(u16 index);
extern u8 func_080CED5C(u8 index);

u32 func_08018028(struct Sprite08018028 *sprite, u8 kind, u16 *id, u8 *out)
{
    u32 result = 0; /* the ROM stores *out = 0 from this register */
    u8 flag;

    *out = 0;
    result = data_0836D678[kind];
    switch (kind) {
    case 1:
    case 2:
        sprite->unknown_1D = 0x0D;
        sprite->unknown_1E = 3;
        sprite->unknown_0C = 0x800;
        sprite->unknown_0B = 0x10;
        sprite->unknown_1F = 0x0B;
        sprite->unknown_3A |= 6;
        if (kind == 2 || *id == 0x25)
            sprite->unknown_3A |= 0x40;
        break;
    case 3:
    case 4:
    case 5:
        if (kind == 3) {
            result = func_08009A24(*id);
            *id = func_08009A90(*id);
            sprite->unknown_0C = 0x20;
            sprite->unknown_0B = 0x80;
            sprite->unknown_2B = 1;
        } else if (kind == 5) {
            result = func_08009A24(*id);
            *id = func_08009A90(*id);
            sprite->unknown_0C = 0x1000;
        } else {
            sprite->unknown_0C = 0x30;
            sprite->unknown_0B = 0x82;
            sprite->unknown_2B = 2;
        }
        sprite->unknown_28 = 0;
        sprite->unknown_16 = 0x80;
        sprite->unknown_18 = 0x100;
        sprite->unknown_1D = 0x15;
        sprite->unknown_1E = 4;
        sprite->unknown_1F = 0x0B;
        if (sprite->unknown_0F == 0)
            sprite->unknown_0F = 1;
        break;
    case 8:
        sprite->unknown_0C = 0xC0;
        sprite->unknown_3A |= 0x60;
        sprite->unknown_22 = 2;
        break;
    case 9:
        sprite->unknown_0C = 0xC0;
        sprite->unknown_3A |= 0x10;
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
    case 16: case 17: case 18: case 19: case 20: case 21:
    case 22: case 23: case 24: case 25: case 26:
        sprite->unknown_1D = 0x0D;
        sprite->unknown_1E = 3;
        sprite->unknown_0C = 0x800;
        sprite->unknown_0B = 0x10;
        sprite->unknown_1F = 0x0B;
        sprite->unknown_3A |= 0x4A;
        break;
    case 6:
    case 7:
        sprite->unknown_0C = 0x1000;
        break;
    case 10:
    case 11:
    case 12:
    case 13:
    case 14:
    case 15:
        sprite->unknown_28 = 0;
        sprite->unknown_16 = 0x80;
        sprite->unknown_18 = 0x100;
        sprite->unknown_1D = 0x15;
        sprite->unknown_1E = 4;
        sprite->unknown_0C = 0x20;
        sprite->unknown_0B = 0x80;
        sprite->unknown_1F = 0x0B;
        sprite->unknown_2B = 1;
        if (sprite->unknown_0F == 0)
            sprite->unknown_0F = 1;
        break;
    }
    if ((g_state_02000000[0x2FC0] & 0x18) == 8) {
        sprite->unknown_16 = 0x1000;
        sprite->unknown_18 = 0x8000;
    }
    return result;
}
