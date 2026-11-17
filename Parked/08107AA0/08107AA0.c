#include "control_flags.h"

// Target: complete [0x08107AA0, 0x08107DA6), 774 bytes, 387 halfwords.
typedef struct Descriptor { u16 phase, unknown_2; u32 argument; void *data; u32 flags; u32 unknown_10; u16 mode, unknown_16; u32 unknown_18; } Descriptor;
typedef struct Part { s16 x; u8 unknown_2[10]; } Part;
typedef struct State {
    s16 x1, y1, x2, y2;
    u8 option, mode;
    u16 timer;
    u32 actor, unknown_10, resource, loader, unknown_1c, unknown_20, transition, task;
    Part first;
    Part second;
    u32 unknown_44;
} State;
extern u8 data_083A0D60[], data_083A0D9C[], data_083A0DA4[], data_0894DC5C[], data_0600F860[], data_06005000[], data_06008000[];
extern u32 func_080E03F8(u32, const void *, u32, u32, u32, u32);
extern u32 func_080E05DC(u32);
extern u32 func_080DFD8C(const void *, u32, u32, u32, u32);
typedef void (*Callback)(void);
extern u32 func_08005B6C(Callback callback, u32, Descriptor *, u32);
extern u32 func_080035A8(u32 index);
extern u32 func_08003A74(u32);
extern u32 func_08003A80(u32);
extern void func_080034B8(u16, u8);
extern void func_08003508(s16, u8);
extern void func_08003558(s16, u8);
extern u32 func_080D3E9C(const void *, u32);
extern u32 func_080D3F08(u32);
extern u32 func_080E051C(u32);
extern u32 func_080DBA5C(u32);
extern u8 func_080D3B54(u32);
extern u8 func_080D8858(u32, u32);
extern u8 func_080DE1F0(u32);
extern void func_080D38B4(void);
extern u32 func_080DD47C(u32);
extern void func_080DE10C(u32, u32);
extern u32 func_080DC1E8(u32, u32, u32, u32, const void *, const void *, u32);
extern u32 func_080DD4B4(u32, u32);
extern void func_080DBDC8(u32, s16 *, s16 *);
extern void func_080DC224(u32, s16, s16, s16 *, s16 *);
extern void func_080E0608(Part *, s16, s16, u32);
extern void func_080E064C(Part *);
extern u32 func_080DF8E8(u32, u32, u32, u32);
extern void func_080E4054(void);
u32 func_08107AA0(u32 owner, Descriptor *event, State *s)
{
    switch (event->phase) {
    case 0: {
        u32 size;
        u16 option = event->unknown_16;
        s->option = option;
        s->resource = event->argument;
        size = 5;
        if ((u8)option) size = 0;
        if (event->flags & 2) s->mode = 1;
        s->loader = func_080E03F8(s->resource, data_083A0D60, size, 0, 0, owner);
        break;
    }
    case 1: func_080D38B4(); break;
    case 0x100:
        s->loader = func_080E05DC(s->loader);
        if (s->loader) break;
        if (func_080D3B54(s->resource)) { event->phase = 2; break; }
        s->actor = func_080DD47C(s->resource);
        if (!s->mode) func_080DE10C(s->actor, 0x58);
        else func_080DE10C(s->actor, 0x20);
        s->unknown_44 = func_080DFD8C(data_083A0D9C, 1, 4, 0, owner);
        event->phase++;
        break;
    case 0x101:
        if (!func_080DE1F0(s->actor)) break;
        s->unknown_1c = func_080DC1E8(s->actor, 0, 0, 7, data_0600F860, data_06005000, owner);
        event->phase++;
        break;
    case 0x102: {
        s16 ax, ay, bx, by;
        s->unknown_1c = func_080DBA5C(s->unknown_1c);
        if (s->unknown_1c) break;
        func_080034B8(func_08003A74((u32)data_06005000) | func_08003A80((u32)data_06008000), 3);
        { u32 mask = func_080035A8(3); u32 flags = g_control_flags_03000940.display; flags |= mask; g_control_flags_03000940.display = flags; }
        s->unknown_10 = func_080DD4B4(s->resource, 0);
        func_080DBDC8(s->actor, &s->x1, &s->y1);
        func_080DBDC8(s->unknown_10, &s->x2, &s->y2);
        func_080DC224(s->actor, s->x1, s->y1, &ax, &ay);
        func_080DC224(s->unknown_10, s->x2, s->y2, &bx, &by);
        func_08003508(ax, 3);
        func_08003558(ay, 3);
        func_080E0608(&s->first, ax, bx, 0x28);
        func_080E0608(&s->second, ay, by, 0x28);
        s->transition = func_080D3E9C(data_0894DC5C, owner);
        s->unknown_44 = func_080DFD8C(data_083A0DA4, 1, 4, 0, owner);
        s->timer = 0x14;
        event->phase++;
        break;
    }
    case 0x103:
        if (s->timer && --s->timer) break;
        func_080E064C(&s->first);
        func_080E064C(&s->second);
        func_08003508(s->first.x, 3);
        func_08003558(s->second.x, 3);
        s->transition = func_080D3F08(s->transition);
        if (s->transition) break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        event->phase++;
        break;
    case 0x104: {
        Descriptor d;
        if (!func_080D8858(s->resource, 0)) { event->phase = 2; break; }
        d.mode = 0x109;
        d.unknown_16 = 1;
        d.argument = s->resource;
        s->task = func_08005B6C(func_080E4054, 0x1c, &d, owner);
        event->phase++;
        break;
    }
    case 0x105:
        s->task = func_080E051C(s->task);
        if (s->task) break;
        s->unknown_20 = func_080DF8E8(s->actor, 2, 0x14, owner);
        event->phase++;
        break;
    case 0x106:
        s->unknown_20 = func_080DBA5C(s->unknown_20);
        if (s->unknown_20) break;
        event->phase = 2;
        break;
    }
    return 0;
}
