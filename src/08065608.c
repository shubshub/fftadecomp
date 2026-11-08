#include "ffta.h"

typedef struct { u8 unknown_00[9]; u8 flags; } Root;
typedef struct { u16 state; u8 unknown_02[0x12]; u16 mode; } Command;
typedef struct { u8 unknown_00[0x12]; u8 appearance; u8 unknown_13[2]; u8 saved_appearance; } Window;
typedef struct {
    Root *root;
    u16 flags;
    s16 selection;
    u8 mode;
    u8 unknown_09[2];
    u8 root_flags;
    u8 unknown_0c[4];
    void *child;
    u8 unknown_14[0x3c];
    Window window;
} Context;
typedef struct { u8 unknown_00[0x10]; u8 *tiles; } Graphics;

extern Root *data_0200F454;
extern u8 data_02003CB0[], data_03003980[], data_06010000[];
extern const u8 data_083B4214[], data_083A9CA4[], data_0894ECFC[];
extern Graphics data_030008B0;
extern void (*const data_0836D4BC)(void *, const void *, u32);
extern void func_0806617C(Context *);
extern u8 *func_0800543C(void *, const void *);
extern void func_0814186C(const void *, void *, u32);
extern void func_08005318(const void *, void *, u32, u32);
extern void func_080CB9B0(void *, u8);
extern u8 func_080664E0(Context *), func_08068810(Context *), func_08066694(Context *), func_080667E4(Context *), func_08066570(Context *);
extern void func_08061390(void), func_0806149C(u8);
extern Root *func_08005BFC(void *);
extern void func_08005BA8(void *, u16);
extern u16 func_08005BAC(void *);
extern u32 func_08005BB0(void *);
extern void func_08005B58(void *);
extern void func_080665B0(Context *), func_08068820(Context *), func_08068848(Context *), func_080664C4(Context *), func_080687D8(Context *), func_08068864(Context *);
extern void func_080651C8(void *);

/* Complete target [0x08065608, 0x080659AC): 932 bytes including pools. */
s32 func_08065608(void *owner, Command *command, Context *context)
{
    u16 state = command->state;
    u16 idle = 0x106;
    switch (state) {
    case 0:
        context->mode = command->mode;
        context->root = data_0200F454;
        context->flags |= 4;
        context->root_flags = context->root->flags;
        break;
    case 1:
        break;
    case 0x100:
        func_0806617C(context);
        command->state = 0x101;
        break;
    case 0x101: {
        u8 *scratch = data_02003CB0;
        s32 i;
        func_0800543C(scratch, data_083B4214);
        func_0814186C(scratch + 0xd40, data_030008B0.tiles + 0x6000, 0x4e0);
        func_08005318(data_083A9CA4, scratch, 0, 0);
        func_0814186C(scratch + 0x240, data_06010000 + 0x2800, 0x140);
        for (i = 31; i <= 36; scratch += 0x80, i++)
            func_080CB9B0(scratch, i);
        func_0814186C(data_02003CB0, data_030008B0.tiles + 0x1400, 0x180);
        data_0836D4BC(data_03003980, data_0894ECFC, 32);
        command->state = 0x102;
        break;
    }
    case 0x102:
        if (func_080664E0(context)) {
            func_08061390();
            if (func_08068810(context)) command->state = 0x10b;
            else command->state = 0x104;
        }
        break;
    case 0x111:
        if (func_08066694(context)) command->state = 0x104;
        break;
    case 0x104:
        if (func_080667E4(context)) {
            switch (context->selection) {
            case -3:
                context->selection = 0;
                command->state = 0x107;
                break;
            case -5:
                context->selection = 0;
                command->state = 0x108;
                break;
            case -4: {
                Root *child = func_08005BFC(context->child);
                Window *window = &context->window;
                context->selection = 0;
                command->state = 0x10d;
                if (child->flags & 1) {
                    func_08005BA8(context->child, state);
                    window->appearance = window->saved_appearance;
                } else {
                    func_0806149C(1);
                    func_08005BA8(context->child, 0x102);
                    window->appearance = 13;
                }
                break;
            }
            case -6:
                func_080665B0(context);
                context->selection = 0;
                command->state = 0x111;
                break;
            default:
                command->state = 0x106;
                if (context->selection != -1 && context->child && context->mode == 4 &&
                    (func_08005BFC(context->child)->flags & 4)) {
                    Window *window = &context->window;
                    func_08005BA8(context->child, 0x104);
                    window->appearance = window->saved_appearance;
                    command->state = 0x112;
                }
                break;
            }
        }
        break;
    case 0x107:
        func_08068820(context);
        command->state = 0x104;
        break;
    case 0x108:
        func_08068848(context);
        command->state = 0x104;
        break;
    case 0x106:
        if (context->flags & 0x80) {
            func_080664C4(context);
            context->flags &= ~0x80;
            command->state = 3;
        } else if (context->flags & 0x40) {
            if (context->child) {
                func_080651C8(owner);
                command->state = 0x10c;
            } else {
                context->flags &= ~0x40;
                func_080687D8(context);
                func_0806149C(1);
                command->state = 0x103;
            }
        } else if (context->flags & 0x20) {
            context->flags &= ~0x20;
            command->state = 0x104;
        }
        break;
    case 0x103:
        if (func_08066570(context)) {
            context->selection = -2;
            command->state = idle;
        }
        break;
    case 0x10b:
    case 0x10d:
        if (func_08005BAC(context->child) == 0x101) command->state = 0x104;
        break;
    case 0x112:
        if (func_08005BAC(context->child) == 0x101) command->state = idle;
        break;
    case 0x10c:
        if (func_08005BB0(context->child)) {
            func_08005B58(context->child);
            context->child = 0;
            context->flags &= ~0x40;
            func_080687D8(context);
            func_0806149C(1);
            command->state = 0x103;
        }
        break;
    }
    if (command->state > 0x101) func_08068864(context);
    return 0;
}
