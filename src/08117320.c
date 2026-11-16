/* Target: complete [0x08117320, 0x081175D2), 690 bytes including literals. */
#include "ffta.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *object;
    u8 unknown_08[0x0E];
    u16 mode;
} Event08117320;

typedef struct {
    u8 unknown_00[4];
    u8 single;
    u8 count;
    u8 index;
    u8 timer;
    u16 delay;
    u8 unknown_0A[2];
    void *effect;
    void *task;
    void *children[4];
    void *link;
    void *object;
    void *sequence;
    void *sequences[4];
    void *intro;
} State08117320;

typedef struct {
    u16 state;
    u16 unknown_2;
    void *resource;
    u8 unknown_08[0x14];
} Descriptor08116F98;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    void *actor;
    void *source;
    u8 unknown_0C[8];
    u16 kind;
    u16 delay;
    u8 unknown_18[4];
} Descriptor081171CC;

extern const u8 data_083A506C[];
extern const u8 data_083A50C0[];
extern const u8 data_083A50D4[];

extern u32 func_08116F98(void *, void *, void *);
extern u32 func_081171CC(void *, void *, void *);
extern void *func_08005B6C(u32 (*callback)(void *, void *, void *), u32 size,
                           void *descriptor, void *parent);
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern u8 func_080DD494(void *object);
extern void *func_080DD47C(void *object);
extern void func_080DE10C(void *link, u16 value);
extern void func_080DE3BC(void *link, u8 mode);
extern void *func_080DFD8C(const void *record, u8 count, u16 flags, s16 delay,
                           void *parent);
extern void *func_080E051C(void *);
extern void *func_080F2E40(u8 kind, void *object, void *parent);
extern void *func_080F1210(void *task);
extern u8 func_080D8858(void *, int);
extern void func_080DE390(void *link);
extern void *func_080DD4A4(void *object, u8 index);
extern u8 func_080E0570(void **, int);
extern void func_080DBFFC(void *, u32);
extern u8 func_080D8B4C(void);
extern void *func_080DCFE4(void *object, const void *record, u8 mode, u16 duration,
                           u16 flags, void *parent, s16 fallback_duration);
extern u8 func_080DE1F0(void *);
extern void *func_080DBA5C(void *);

u32 func_08117320(void *owner, Event08117320 *event, State08117320 *state)
{
    Descriptor08116F98 intro;
    Descriptor081171CC child;
    u8 i;
    u16 delay;
    int odd;
    void *unit;
    u16 flags;
    u8 done;
    int mode;

    switch (event->phase) {
    case 0:
        state->single = event->mode;
        state->object = event->object;
        mode = 7;
        if (state->single)
            mode = 0;
        state->sequence = func_080E03F8(state->object, data_083A506C, mode, 0, 0,
                                        owner);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if ((state->sequence = func_080E05DC(state->sequence)))
            break;
        if (func_080D3B54(state->object)) {
            event->phase = 2;
            break;
        }
        if (state->single) {
            state->count = func_080DD494(state->object);
            state->timer = 1;
            event->phase = 0x103;
            break;
        }
        state->link = func_080DD47C(state->object);
        func_080DE10C(state->link, 0x24);
        func_080DE3BC(state->link, 1);
        intro.resource = state->link;
        state->task = func_08005B6C(func_08116F98, 0x34, &intro, owner);
        state->intro = func_080DFD8C(data_083A50D4, 1, 4, 0, owner);
        event->phase++;
        break;
    case 0x101:
        if ((state->task = func_080E051C(state->task)))
            break;
        state->effect = func_080F2E40(8, state->object, owner);
        event->phase++;
        break;
    case 0x102:
        if ((state->effect = func_080F1210(state->effect)))
            break;
        if (state->delay != 0 && --state->delay != 0)
            break;
        if (!(state->count = func_080D8858(state->object, 0))) {
            event->phase = 2;
            break;
        }
        func_080DE390(state->link);
        delay = 0;
        for (i = 0; i < state->count; i++) {
            child.kind = i;
            child.delay = delay;
            child.actor = func_080DD4A4(state->object, i);
            child.source = state->object;
            state->children[i] = func_08005B6C(func_081171CC, 0x1C, &child, owner);
            delay++;
        }
        event->phase++;
        break;
    case 0x103:
        if (func_080E0570(state->children, 4)) {
            state->timer = 1;
            event->phase++;
        }
        break;
    case 0x104:
        func_080DBFFC(state->object, state->index);
        event->phase++;
    case 0x105:
        if (func_080D8B4C())
            break;
        if (--state->timer)
            break;
        unit = func_080DD4A4(state->object, state->index);
        odd = state->index & 1;
        flags = 2;
        if (odd)
            flags = 4;
        state->sequences[state->index] = func_080DCFE4(unit, data_083A50C0, 12 - odd, 0,
                                                       flags | 8, owner, 0);
        state->timer = 0x28;
        state->index++;
        if (state->index != state->count)
            event->phase = 0x104;
        else
            event->phase++;
        break;
    case 0x106:
        if (!func_080DE1F0(state->link))
            break;
        done = 1;
        for (i = 0; i < 4; i++) {
            if ((state->sequences[i] = func_080DBA5C(state->sequences[i])))
                done = 0;
        }
        if (done)
            event->phase = 2;
        break;
    }
    return 0;
}
