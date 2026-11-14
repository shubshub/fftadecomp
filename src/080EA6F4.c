#include "ffta.h"
#include "control_flags.h"
// Target: 0x080EA6F4..0x080EA936 (578 bytes).
// Sibling of func_080EA4A0 and func_080EA938 (same event phases).
typedef struct {
    u16 state;
} Event;
typedef struct LineState {
    s32 x;
    s32 y;
    s32 endX;
    s32 endY;
    s32 stepX;
    s32 stepY;
    s32 deltaX;
    s32 deltaY;
    s32 accumulator;
    s32 error;
    s32 remaining;
} LineState;
typedef struct {
    u16 timer;
    u16 unknown_2;
    void *first;
    u8 entries[24];
    void *window;
    LineState line;
    void *effect;
} State;
extern const u8 data_08398B8C[], data_088F491C[], data_0894914C[], data_08398BB8[], data_08948E44[], data_08398BD8[];
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void *func_080D9A24(u8 first, u8 second, u8 count, const void *entries, void *parent);
extern void func_0801E610(u8 *first, u8 *second);
extern u16 func_080035F8(u8 index);
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 end_x, s32 end_y);
extern void func_080076A0(LineState *state);
extern u32 func_08007880(const void *state);
extern void *func_080D4704(const void *, void *);
extern void *func_080D4774(void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D9A88(void *task, const void *entries, u16 count);
extern void func_080D9ADC(void *task, u8 first, u8 second);
extern void *func_080D9B64(void *task);
extern u16 func_080035A8(u8 index);

int func_080EA6F4(void *owner, Event *event, State *s)
{
    u8 first;
    u8 second;
    u8 old;

    switch (event->state) {
    case 0:
        func_0814186C(data_08398B8C, s->entries, 12);
        s->timer = 61;
        break;
    case 1:
        break;
    case 0x100:
        if (!--s->timer) {
            func_080D7220(data_088F491C, 0, 2, 0, 0, 0);
            s->window = func_080D9A24(16, 16, 3, s->entries, owner);
            func_0801E610(&first, &second);
            g_control_flags_03000940.bldcnt_lo = func_080035F8(2) | 0x40;
            g_control_flags_03000940.bldcnt_hi = func_080035F8(first) | func_080035F8(second) | func_080035F8(3) | 0x30;
            g_control_flags_03000940.bldalpha_lo = 16;
            g_control_flags_03000940.bldalpha_hi = 16;
            func_080075CC(&s->line, 16, 0, 10, 29);
            func_080076A0(&s->line);
            s->first = func_080D4704(data_0894914C, owner);
            s->effect = func_080DFD8C(data_08398BB8, 4, 4, 0, owner);
            event->state++;
        }
        break;
    case 0x101:
        event->state++;
        break;
    case 0x102:
        if (!func_08007880(&s->line)) {
            old = s->entries[5];
            s->entries[5] = s->line.x;
            s->entries[11] = s->line.x;
            s->entries[13] = s->line.x;
            s->entries[19] = s->line.x;
            if ((u8)s->line.x != old)
                func_080D9A88(s->window, s->entries, 3);
            func_080076A0(&s->line);
        }
        s->first = func_080D4774(s->first);
        if (!s->first) {
            s->first = func_080D4704(data_08948E44, owner);
            s->effect = func_080DFD8C(data_08398BD8, 3, 4, 0, owner);
            s->timer = 20;
            event->state++;
        }
        break;
    case 0x103:
        if (!--s->timer) {
            s->timer = 98;
            event->state++;
        }
        break;
    case 0x104:
        if (s->timer && !--s->timer)
            func_080D9ADC(s->window, 16, 16);
        s->first = func_080D4774(s->first);
        if (!s->first) {
            g_control_flags_03000940.display &= ~func_080035A8(2);
            event->state++;
        }
        break;
    case 0x105:
        s->window = func_080D9B64(s->window);
        if (!s->window)
            event->state = 2;
        break;
    }
    return 0;
}
