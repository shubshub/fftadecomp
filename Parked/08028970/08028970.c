#include "ffta.h"

/* 0x08028970..0x08028B1E: 430 bytes. */
typedef struct {
    u8 unknown_00[0x11];
    s8 row;
    u8 unknown_12[0x2A];
} Selector;

typedef struct {
    u8 unknown_00[0xA];
    u8 listIndex;
    u8 unknown_0B;
    u8 window[0x2C];
    u8 list[0x20];
    Selector selector;
    s32 *indices;
} MenuContext;

typedef struct {
    u16 choice;
    u8 unknown_02[2];
    u8 type;
    u8 navigation;
    u8 unknown_06[2];
    u16 backChoice;
    u8 unknown_0A[6];
    u16 selected;
    u8 unknown_12[2];
    u32 value;
    u32 source;
    u32 backup;
} MenuState;

typedef struct {
    u16 held;
    u16 pressed;
    u16 repeat;
} KeyState;

typedef struct {
    u8 unknown_00[4];
    u16 id;
    u8 unknown_06[2];
} ListEntry;

extern KeyState data_03000000;
extern MenuState *data_0200F438;
extern const ListEntry *g_table_0851BA84[];
extern s32 func_08017B68(void *list, s32 row);
extern u32 func_08028824(MenuContext *context, s32 index);
extern u32 func_080287F0(MenuContext *context);
extern void func_08141570(u32 channel, u32 sound);
extern void func_08016D64(void *window);
extern void func_08017D18(void *selector, u32 value);
extern u32 func_080287C4(MenuContext *context);
extern void func_08141540(u32 sound);
extern u32 func_08028708(MenuContext *context, u32 keys);
extern u32 func_08028584(MenuContext *context, u32 repeat, u32 held);

u8 func_08028970(MenuContext *context)
{
    void *window = context->window;
    Selector *selector = &context->selector;
    u16 pressed = data_03000000.pressed;
    u16 repeat = data_03000000.repeat;
    u16 held = data_03000000.held;

    if (pressed & 4) {
        u32 result = func_08028824(context, (s16)func_08017B68(context->list, selector->row));

        data_0200F438->backChoice = result;
        if ((u16)result) {
            data_0200F438->backChoice = result - 1;
            data_0200F438->choice = 0xFFFE;
            return 1;
        }
    }
    if (pressed & 2) {
        if ((u8)func_080287F0(context)) {
            func_08141570(1, 0x6B);
            return 0;
        }
        func_08141570(1, 0x69);
        func_08016D64(window);
        func_08017D18(selector, 0);
        data_0200F438->choice = 0xFFFF;
        return 1;
    }
    if (pressed & 1) {
        s32 choice = func_08017B68(context->list, selector->row);
        u16 selected;
        u8 type;

        data_0200F438->choice = choice + 1;
        selected = choice;
        if ((u8)func_080287C4(context)) {
            func_08141570(1, 0x6B);
            return 0;
        }
        type = data_0200F438->type;
        if (type == 5) {
            data_0200F438->selected = selected;
            data_0200F438->backup = data_0200F438->source;
        } else if ((type >= 6 && type <= 8) || type == 0xF) {
            const ListEntry *entries = g_table_0851BA84[context->listIndex];

            entries += context->indices[(s16)selected];
            data_0200F438->value = entries->id;
            if (type == 0xF)
                data_0200F438->selected = data_0200F438->value;
        } else if (type == 2) {
            data_0200F438->value = context->indices[(s16)selected];
            data_0200F438->source = data_0200F438->value;
        } else if (type >= 0xD && type <= 0xE) {
            data_0200F438->selected = context->indices[(s16)selected];
        }
        func_08141540(0x64);
        func_08016D64(window);
        func_08017D18(selector, 0);
        return 1;
    }
    {
        u8 result;

        if (data_0200F438->navigation)
            result = func_08028708(context, repeat);
        else
            result = func_08028584(context, repeat, held);
        return result;
    }
}
