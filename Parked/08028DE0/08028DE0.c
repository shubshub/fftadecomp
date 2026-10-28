#include "ffta.h"

typedef struct {
    u16 state;
    u8 unknown_02[0x12];
    u16 argument;
} MenuEvent;

typedef struct {
    u8 unknown_00[0x2c];
} MenuPanel;

typedef struct {
    u8 unknown_00[0x1a];
    u16 value;
    u8 unknown_1c[0x15];
    u8 selection;
    u8 unknown_32[2];
} MenuWidget;

typedef struct {
    u8 unknown_00[0x14];
} MenuCleanup;

typedef struct {
    u8 unknown_00[0x10];
    s16 current_id;
    u8 type;
    u8 unknown_13;
} MenuState;

typedef struct {
    void *owner;
    void *process;
    u8 slot;
    u8 unknown_09[3];
    MenuPanel panel;
    MenuWidget widget;
    MenuCleanup cleanup;
    MenuState menu;
    void **choices;
} MenuContext;

typedef struct {
    u16 value;
    u16 selection;
} SavedChoice;

typedef struct {
    s16 result;
    u8 unknown_02[2];
    u8 mode;
    u8 unknown_05[0x13];
    void *unit;
    u8 unknown_1c[0x444 - 0x1c];
    SavedChoice choices[1];
} BattleContext;

extern BattleContext *data_0200F438;
extern void *func_08005BF8(void *owner);
extern void func_08027DA0(MenuContext *context);
extern void func_080282D4(MenuContext *context);
extern u32 func_08028B20(MenuContext *context);
extern void func_0802800C(MenuContext *context);
extern u32 func_08017180(MenuPanel *panel);
extern void func_080253B0(u32 type, void *owner);
extern void func_080282A4(MenuContext *context);
extern u32 func_08028350(MenuContext *context);
extern u32 func_0802839C(MenuContext *context);
extern u32 func_08028D88(MenuContext *context);
extern u32 func_08028970(MenuContext *context);
extern void func_08028CA4(MenuContext *context);
extern void func_08016234(MenuPanel *panel);
extern void func_08017E28(MenuCleanup *cleanup);
extern u32 func_08017B68(MenuWidget *widget, s32 selection);

/* Complete target: [0x08028DE0, 0x08028FF4), 532 bytes. */
u32 func_08028DE0(void *owner, MenuEvent *event, MenuContext *context)
{
    switch (event->state) {
    case 0:
        context->owner = owner;
        context->process = func_08005BF8(owner);
        context->slot = event->argument;
        break;
    case 0x100:
        func_08027DA0(context);
        func_080282D4(context);
        if ((u8)func_08028B20(context))
            event->state = 0x106;
        else
            event->state = 0x101;
        break;
    case 0x104:
        func_0802800C(context);
        event->state = 3;
        break;
    case 0x105:
        if ((u8)func_08017180(&context->panel)) {
            MenuState *menu = &context->menu;
            func_080253B0(menu->type, context->owner);
            event->state = 0x106;
        }
        break;
    case 0x107:
        data_0200F438->mode = context->slot + 1;
        func_080282A4(context);
        event->state = 0x101;
        break;
    case 0x101:
        if ((u8)func_08028350(context))
            event->state = 0x102;
        break;
    case 0x103:
        if ((u8)func_0802839C(context))
            event->state = 0x104;
        break;
    case 0x108:
        if ((u8)func_08028D88(context))
            event->state = 0x102;
        /* Continue updating the panel after checking the result. */
    case 0x106:
        func_08016234(&context->panel);
        break;
    case 0x102:
        if ((u8)func_08028970(context)) {
            switch (data_0200F438->result) {
            case -1:
                event->state = 0x103;
                break;
            case -2:
                func_08028CA4(context);
                event->state = 0x108;
                break;
            case -3:
                event->state = 0x109;
                break;
            case 0:
                break;
            default:
                if (context->menu.current_id == data_0200F438->result) {
                    SavedChoice *choice = &data_0200F438->choices[context->slot];
                    choice->value = context->widget.value;
                    choice->selection = context->widget.selection;
                    event->state = 0x105;
                } else {
                    event->state = 0x103;
                }
                break;
            }
        }
        func_08016234(&context->panel);
        break;
    case 0x109:
        func_08017E28(&context->cleanup);
        func_08016234(&context->panel);
        if (data_0200F438->mode == 2) {
            u32 index = func_08017B68(&context->widget, (s8)context->widget.selection);
            data_0200F438->unit = context->choices[(u16)index];
        }
        event->state = 0x102;
        break;
    }
    return 0;
}
