#include "ffta.h"
#include "control_flags.h"

/* Complete target [0x080868D4, 0x08087000), 1836 bytes, 686 instructions. */

typedef struct {
    u8 unknown_00[4];
    u8 kind;
    u8 unknown_05;
    u8 unknown_06;
    u8 unknown_07;
    u8 unknown_08[0x100];
} Character;

typedef struct {
    u32 unknown_00;
    Character *record;
    u8 unknown_08[0xc];
    u8 unknown_14;
} SharedState;

typedef struct {
    u8 unknown_00;
    u8 unknown_01[0x4b];
} Window;

typedef struct {
    u8 unknown_0000[0x25];
    u8 timer;
    u8 unknown_0026[0x412];
    u16 unknown_438;
    u8 mode;
    u8 saved_mode;
    u8 unknown_43c[0x1c];
    s16 scroll;
    u8 unknown_45a[0x504];
    u8 active : 1;
    u8 unknown_95e_1 : 7;
    u8 unknown_95f[0x27];
    u8 unknown_986;
    u8 selection;
    u8 unknown_988[0x32];
    u8 availability[24];
    u8 unknown_9d2[0x223];
    u8 unknown_bf5;
    u8 unknown_bf6[0x676];
    u16 counter;
    u8 unknown_126e[0xa96];
    u8 unknown_1d04;
    u8 unknown_1d05[7];
    Character *record;
    u8 window[1];
} DisplayState;

extern DisplayState *data_03002818;
extern SharedState g_state_020020D0;
extern Window data_030009E0[];
extern u16 data_03000000[];
extern u8 data_02003CB0[];
extern u8 data_03000990[];
extern u8 data_03000E80[];
extern u8 data_030008B0[];
extern u16 data_030027F0;
extern u8 data_030027A4;
extern u8 data_0200F28E;
extern u8 data_0200F28F;

extern void func_08141540(u16 sound);
extern void func_08141520(u16 sound);
extern void func_0801174C(void *window, u8 x, u8 y, void *first,
                          void *second, s32 index, u32 flags,
                          u32 width, u32 height, u32 tile);
extern void func_08013210(Character *character, u32 flags, u32 tile);
extern u16 func_08011860(void);
extern void func_08013364(void);
extern s8 func_08013380(void);
extern u8 func_080C8194(const void *object, u8 category);
extern u32 func_08002804(void);
extern void func_080C9574(u16 bitIndex, u16 enabled);
extern void func_080C8C24(Character *record, u8 selector);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08072130(int selection, u8 *availability);
extern void func_08087B30(u8 index);
extern void func_08076420(s32 selected);
extern void func_08011C60(void);

/* An inlined copy of func_08087000 (src/08087000.c), the function that
   follows this one in the ROM and that nothing calls or points to.  Here the
   character records at 0x02000080 are addressed from g_state_020020D0, as
   src/080CEA80.c does: every copy forms the base as r8 + 0xFFFFDFB0 with
   r8 = &g_state_020020D0 (0x08086A80, 0x08086AF8, 0x08086B62, 0x08086BC6,
   0x08086C2A, 0x08086C9A, 0x08086D1C). */
static inline void show_character(u8 x, u8 y, u16 selection)
{
    Character *character =
        (Character *)((u8 *)&g_state_020020D0 - 0x2050) + selection;

    func_0801174C(data_03002818->window, x, y,
                  data_03000990, data_030008B0, -1, 0, 22, 6, 0x157);
    func_08013210(character, 0, 0x4300);
}

void func_080868D4(void *unused, u8 *state)
{
    u8 *buffer;
    u8 selector;

    switch (*state) {
    case 0:
        func_08141540(0x65);
        data_03002818->unknown_bf5 = 5;
        data_03002818->unknown_1d04 = 0;
        data_03002818->active = 0;
        data_0200F28E = 3;
        *state = 0xc;
        break;
    case 0xc:
        /* The buffer is loaded at 0x08086980, ahead of the two mode stores
           (0x08086990, 0x08086998); 0x08077C30 and 0x08085FB8 open the
           same prompt in the same order. */
        buffer = data_02003CB0;
        data_03002818->saved_mode = data_03002818->mode;
        data_03002818->mode = 3;
        func_0801174C(buffer, 1, 0x13, data_03000990, data_03000E80,
                      2, 7, 24, 4, 0x3a0);
        *state = 0xd;
        break;
    case 0xd:
        if (func_08011860() != 0) {
            if (func_08013380() == 0) {
                func_08013364();
                data_0200F28E = 0x10;
                *state = 0x13;
            } else {
                func_08013364();
                data_03002818->mode = data_03002818->saved_mode;
                data_0200F28E = 0xfd;
                *state = 0x13;
            }
        }
        break;
    case 0x10:
        g_state_020020D0.record = data_03002818->record;
        data_03002818->timer = 0;
        data_03002818->active = 1;
        if (func_080C8194(data_03002818->record, 0x5e)) {
            show_character(15, 27, data_03002818->selection);
        } else if (func_080C8194(data_03002818->record, 10)) {
            show_character(15, 15, data_03002818->selection);
        } else if (func_080C8194(data_03002818->record, 9)) {
            show_character(15, 18, data_03002818->selection);
        } else if (func_080C8194(data_03002818->record, 4)) {
            show_character(15, 21, data_03002818->selection);
        } else if (func_080C8194(data_03002818->record, 12)) {
            show_character(15, 24, data_03002818->selection);
        } else if (data_03002818->record->kind == 2) {
            show_character(15, (s16)func_08002804() % 3,
                           data_03002818->selection);
        } else {
            show_character(15, (data_03002818->record->unknown_06 - 1) * 3
                               + (s16)func_08002804() % 3,
                           data_03002818->selection);
        }
        *state = 0x11;
        break;
    case 0x11:
        if (data_03002818->timer == 5) {
            g_control_flags_03000940.bg2cnt = 0x2b09;
            data_030027F0 = 0;
            data_030027A4 = 0xfd;
        }
        if (data_03002818->timer < 50) {
            if (data_03002818->scroll > -0x40)
                data_03002818->scroll -= 4;
        } else {
            data_03002818->timer = 0;
            *state = 0x12;
        }
        data_03002818->timer++;
        func_08011860();
        break;
    case 0x12:
        if ((data_03000000[1] & 1) || data_03002818->timer > 70) {
            func_08141520(0x71);
            func_08013364();
            data_03002818->mode = data_03002818->saved_mode;
            data_03002818->counter = 0;
            data_03002818->mode = data_03002818->saved_mode;
            *state = 6;
        }
        func_08011860();
        data_03002818->timer++;
        break;
    case 6:
        if (data_03002818->counter < 30) {
            if (data_03002818->scroll > -0x40)
                data_03002818->scroll -= 4;
        } else if (data_03002818->counter > 30) {
            *state = 5;
        }
        data_03002818->counter++;
        break;
    case 5:
        selector = data_03002818->record->unknown_07;
        switch (data_03002818->record->kind) {
        case 10:
            func_080C9574(0x258, 0);
            break;
        case 9:
            func_080C9574(0x259, 0);
            break;
        case 4:
            func_080C9574(0x25a, 0);
            break;
        case 12:
            func_080C9574(0x25b, 0);
            break;
        case 0x5e:
            func_080C9574(0x25c, 0);
            break;
        }
        func_080C8C24(data_03002818->record, selector);
        {
            /* CpuFill16(0, record, sizeof(Character)): the SDK's vu16
             * temporary, spelled through a pointer until fftadecomp-kit#164. */
            u16 zero;
            u16 *source = &zero;

            *source = 0;
            func_0814186C(source, data_03002818->record, 0x01000084);
        }
        func_08072130(g_state_020020D0.unknown_14,
                      data_03002818->availability);
        data_03002818->unknown_438 = 200;
        *state = 0xfe;
        break;
    case 0x13:
        if (func_08011860() != 0)
            *state = data_0200F28E;
        break;
    case 0xb:
        if (data_030009E0[data_0200F28F].unknown_00 == 0)
            *state = data_0200F28E;
        break;
    case 0xfd:
        func_08087B30(0xff);
        data_03002818->unknown_1d04 = 0;
        func_08076420(data_03002818->unknown_986);
        *state = 0xff;
        break;
    /* The two terminal states this handler sets.  They leave no code, but
       the compare tree is balanced for them: its root is 0x10 (0x080868E2)
       and the upper half's is 0x13 (0x08086918), which eleven cases would
       put at 0x0d and 0x12. */
    case 0xfe:
    case 0xff:
        break;
    }
    if (data_03002818->active)
        func_08011C60();
}
