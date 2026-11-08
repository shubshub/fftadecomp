#include "ffta.h"

typedef struct {
    u16 unknown_00;
    u8 result;
    u8 phase;
    u8 unknown_04[0xC8];
} MenuSlot;

typedef struct {
    u8 unknown_00[0x11];
    u8 unknown_11;
    u8 unknown_12[8];
    u8 unknown_1A;
    u8 unknown_1B[0x71];
    u8 unknown_8C;
} MenuDetail;

typedef struct {
    void *owner;
    MenuDetail *detail;
    u8 unknown_08[0x97C];
    MenuSlot slots[3];
    u8 unknown_BE8[0x64];
    u8 text_state[1];
} MenuContext;

typedef struct {
    u8 operation;
    u8 unknown_01;
    u8 flags;
    u8 unknown_03[0x49];
} WindowCommand;

typedef struct {
    u16 unknown_00;
    u16 pressed;
} Input;

extern MenuContext *g_state_03002810;
extern WindowCommand data_030009E0[];
extern Input data_03000000;
extern u8 data_0201F48C;
extern u16 data_06009960[];
extern u16 data_06009F60[];
extern const u8 *const data_085668B0[];
extern const u8 *const g_table_08526680[];

extern void func_08141540(u16 song);
extern void func_0803DACC(u32 mode);
extern u16 func_08015110(void *drawing, const void *source,
    const u8 *text, u8 palette, u8 reset);
extern int func_0808A604(u32 window, u16 operation);

/* Complete 684-byte menu response handler. */
void func_0803D820(u32 index)
{
    MenuContext *context = g_state_03002810;
    u8 *record = (u8 *)context + index * sizeof(MenuSlot);
    u8 *phase = record + 0x987;

    switch (*phase) {
    case 0:
        if (data_030009E0[2].flags & 7)
            break;
        if (data_030009E0[3].flags & 7)
            break;
        switch (((MenuContext *)record)->slots[0].result) {
        case 0:
            func_08141540(0x65);
            func_0803DACC(2);
            func_08015110(g_state_03002810->text_state,
                data_06009960, data_085668B0[0x4C], 0, 1);
            func_08015110(g_state_03002810->text_state,
                data_06009F60,
                g_table_08526680[(g_state_03002810->detail->unknown_8C & 0x7F) + 0x2CD],
                0, 1);
            func_0808A604(4, 2);
            g_state_03002810->slots[index].phase = 1;
            break;
        case 1:
            func_08141540(0x6A);
            func_0803DACC(1);
            func_08015110(g_state_03002810->text_state,
                data_06009960, data_085668B0[0x4D], 0, 1);
            func_0808A604(4, 2);
            g_state_03002810->slots[index].phase = 2;
            break;
        }
        break;
    case 1:
        if (data_03000000.pressed & 3) {
            if (data_03000000.pressed & 1)
                func_08141540(0x64);
            else
                func_08141540(0x69);
            func_0808A604(4, 1);
            data_0201F48C = 3;
            g_state_03002810->slots[index].result = 3;
            g_state_03002810->slots[index].phase = 4;
        }
        break;
    case 2:
        if (data_03000000.pressed & 3) {
            if (data_03000000.pressed & 1)
                func_08141540(0x64);
            else
                func_08141540(0x69);
            func_0808A604(4, 1);
            data_0201F48C = 3;
            g_state_03002810->slots[index].result = 3;
            g_state_03002810->slots[index].phase = 4;
        }
        break;
    case 3:
        if (context->detail->unknown_1A && !context->detail->unknown_11) {
            if (data_03000000.pressed & 1)
                *phase = 0xFD;
        } else {
            if (data_03000000.pressed & 1)
                func_08141540(0x6A);
        }
        break;
    case 4:
        if (data_030009E0[4].operation == 0)
            *phase = data_0201F48C;
        break;
    case 0xFD:
        if (data_030009E0[4].operation == 0) {
            ((MenuContext *)record)->slots[0].result = 0xFF;
            g_state_03002810->slots[index].phase = 0xFF;
        }
        break;
    case 0xFF:
        break;
    }
}
