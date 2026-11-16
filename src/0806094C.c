#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u16 selection;
    u8 unknown_1C[4];
} List0806094C;

typedef struct {
    u8 unknown_00[0x11];
    s8 selection;
    u8 unknown_12[2];
} Cursor0806094C;

typedef struct {
    u8 unknown_00[8];
    u8 appearance;
    u8 unknown_09;
    u8 unknown_0A[6];
} Layout0806094C;

typedef struct Context0806094C {
    u8 mode;
    u8 unknown_01;
    u8 flags;
    u8 unknown_03[2];
    u8 unknown_05;
    u8 unknown_06;
    u8 handle;
    u16 next_state;
    s16 row;
    void *task;
    u8 window[0x2C];
    List0806094C list;
    Cursor0806094C cursor;
    Cursor0806094C secondary;
    Layout0806094C layout;
} Context0806094C;

typedef struct {
    u16 state;
    u8 unknown_02[0x12];
    u16 mode;
    u16 unknown_16;
} Event0806094C;

typedef struct {
    u16 selection;
    u16 position;
} Tab0806094C;

typedef struct {
    u8 unknown_000[0x16];
    u8 kind;
    u8 unknown_017[9];
    void *records[66];
    Tab0806094C tabs[8];
    u8 unknown_148[0x410];
    u8 *backup_first;
    u8 *backup_second;
    u8 control_flags[0x50];
} Menu0806094C;

typedef struct {
    u8 unknown_00[0x10];
    void *first;
    void *second;
} Graphics0806094C;

typedef struct {
    u8 unknown_0000[0x1090];
    s8 status;
} TaskData0806094C;

typedef struct {
    u8 mode;
} Script0806094C;

extern Menu0806094C *data_0200F44C;
extern u8 g_control_flags_03000940[];
extern void *data_030027F4;
extern u32 data_030027D4;
extern Graphics0806094C data_03000990;
extern Script0806094C g_state_0200F390;
extern u8 func_080CECF4(void);
extern void func_0805FB9C(Context0806094C *);
extern void func_0805FD04(Context0806094C *);
extern u8 func_08060404(Context0806094C *);
extern u8 func_08060450(Context0806094C *);
extern u8 func_08060618(Context0806094C *);
extern void func_08060828(Context0806094C *);
extern u8 func_080608E0(Context0806094C *);
extern void func_0805F6EC(Context0806094C *);
extern void func_08017508(void *window, u8 appearance);
extern u8 func_080603F4(Context0806094C *);
extern u8 func_080098F4(u8 (*)(Context0806094C *), Context0806094C *);
extern void func_08017D18(Cursor0806094C *, u8);
extern void func_08017E28(Cursor0806094C *);
extern void *func_08005BFC(void *);
extern u32 func_08005BB0(const void *);
extern void func_08005B58(void *);
extern void func_080601D0(Context0806094C *, s16);
extern void func_080178A4(List0806094C *, s8);
extern void *func_081443FC(void *, const void *, u32);
extern u16 func_08017B68(List0806094C *, u32);
extern void *func_08022840(u32);
extern void func_08022854(u8 *);
extern void func_0814186C(const void *, void *, u32);
extern void func_08022E90(u16, u8);
extern void func_08016234(void *);

/* Complete target [0x0806094C, 0x08060DB8): 1132 bytes, 443 instructions,
   including the literal pools and the eight-entry jump table at 0x08060AA4. */
u32 func_0806094C(void *task, Event0806094C *event, Context0806094C *context)
{
    switch (event->state) {
    case 0:
        context->mode = event->mode;
        context->unknown_06 = event->unknown_16;
        context->flags = 0;
        if (context->mode == 3)
            context->unknown_05 = func_080CECF4();
        break;
    case 1:
        break;
    case 0x100:
        func_0805FB9C(context);
        event->state = 0x102;
        break;
    case 0x101:
        func_0805FD04(context);
        event->state = 3;
        break;
    case 0x102:
        if (func_08060404(context)) {
            if (context->task) {
                event->state = 0x109;
            } else {
                Layout0806094C *layout = &context->layout;

                if (layout->unknown_09 & 0x10) {
                    context->flags = 1;
                    func_08017D18(&context->cursor, 1);
                    event->state = 0x105;
                } else {
                    event->state = 0x104;
                }
            }
        }
        break;
    case 0x103:
        if (func_08060450(context))
            event->state = 0x101;
        break;
    case 0x104: {
        Layout0806094C *layout = &context->layout;

        if (func_08060618(context)) {
            Tab0806094C *tab;

            switch (data_0200F44C->kind) {
            case 8:
                func_08060828(context);
                event->state = 0x107;
                break;
            case 1:
            case 3:
                if (context->task) {
                    func_0805F6EC(context);
                    event->state = 0x10A;
                } else {
                    func_08017508(context->window, layout->appearance);
                    context->handle = func_080098F4(func_080603F4, context);
                    event->state = 0x103;
                }
                break;
            case 2:
            case 4:
                context->flags = 1;
                func_08017D18(&context->cursor, 1);
                event->state = 0x105;
                break;
            case 5:
                event->state = 0x108;
                break;
            case 6:
                context->flags = 2;
                event->state = 0x105;
                break;
            case 7:
                event->state = 0x10C;
                break;
            }
            tab = &data_0200F44C->tabs[context->mode];
            tab->selection = context->list.selection;
            tab->position = (u8)context->cursor.selection;
        }
        break;
    }
    case 0x108:
        func_08017E28(&context->secondary);
        event->state = 0x104;
        break;
    case 0x107:
        if (func_080608E0(context))
            event->state = 0x104;
        break;
    case 0x105:
        if (context->flags & 2) {
            Layout0806094C *layout = &context->layout;

            if (context->flags & 4) {
                func_08017508(context->window, layout->appearance);
                context->handle = func_080098F4(func_080603F4, context);
                event->state = 0x103;
            } else {
                func_08017D18(&context->cursor, 3);
                event->state = 0x104;
            }
            context->flags = 0;
        }
        break;
    case 0x109:
        if (((TaskData0806094C *)func_08005BFC(context->task))->status == 1)
            event->state = 0x104;
        break;
    case 0x10A:
        if (func_08005BB0(context->task)) {
            Layout0806094C *layout = &context->layout;

            func_08005B58(context->task);
            context->task = 0;
            func_08017508(context->window, layout->appearance);
            context->handle = func_080098F4(func_080603F4, context);
            event->state = 0x103;
        }
        break;
    case 0x10B: {
        List0806094C *list = &context->list;

        func_080601D0(context, context->row);
        func_080178A4(list, context->row);
        event->state = context->next_state;
        break;
    }
    case 0x10C:
        func_081443FC(data_0200F44C->control_flags, g_control_flags_03000940, 0x50);
        data_030027F4 = data_0200F44C->records[func_08017B68(&context->list, context->cursor.selection)];
        data_030027D4 = 0;
        data_0200F44C->backup_first = func_08022840(0x6C00);
        data_0200F44C->backup_second = func_08022840(0x1000);
        func_0814186C(data_03000990.first, data_0200F44C->backup_first, 0x3600);
        func_0814186C(data_03000990.second, data_0200F44C->backup_second, 0x800);
        func_08022E90(4, 16);
        g_state_0200F390.mode = 0x1B;
        event->state = 0x10D;
        break;
    case 0x10D:
        if (g_state_0200F390.mode == 0x20) {
            func_0814186C(data_0200F44C->backup_first, data_03000990.first, 0x3600);
            func_0814186C(data_0200F44C->backup_second, data_03000990.second, 0x800);
            func_08022854(data_0200F44C->backup_first);
            func_08022854(data_0200F44C->backup_second);
            func_081443FC(g_control_flags_03000940, data_0200F44C->control_flags, 0x50);
            event->state = 0x10E;
        }
        break;
    case 0x10E:
        if (g_state_0200F390.mode == 0)
            event->state = 0x104;
        break;
    }
    if (event->state > 0x103)
        func_08016234(context->window);
    return 0;
}
