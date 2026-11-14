// 0x0810EA78: complete 396-byte function, including the literal pool.
#include "control_flags.h"

typedef struct {
    u16 phase;
    u16 unknown_02;
} Event;

typedef struct {
    u8 unknown_00[8];
    void *script;
    void *top;
    void *record_child;
} State;

extern const u8 data_083A2E00[];
extern const u8 data_088F46CC[];
extern const u8 data_0894DBA4[];
extern u16 data_03003860[];
extern u8 data_0600CC00[];
extern u8 data_06007000[];
extern u8 data_06007800[];
extern void func_0801E6F0(s16 *first, s16 *second);
extern void func_0801E610(u8 *first, u8 *second);
extern u16 func_0801BA20(s16 x, s16 y, u16 speed);
extern u8 func_0801BDB0(void);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u32 func_080035A8(u8);
extern void func_080DBED4(int, int, int, int);
extern void func_080D72C8(const void *, u8, u8, s16, s16, u16, u8);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D89D0(int, int, int, int, int, int, void *, void *, int, int, int, int, int, void *);
extern void *func_080D3F08(void *);
extern void *func_080D8AEC(void *);
extern void *func_080D3AF8(void);
extern void func_08000B20(void *, int, void *, unsigned);

int func_0810EA78(void *owner, Event *event, State *s)
{
    s16 first;
    s16 second;
    u8 a, b;
    u8 busy;
    int y;

    switch (event->phase) {
    case 0:
    case 1:
        break;
    case 0x100:
        func_0801E6F0(&first, &second);
        y = -0xC0;
        second = y;
        func_0801BA20(first, y, 8);
        s->record_child = func_080DFD8C(data_083A2E00, 1, 4, 0, owner);
        event->phase++;
        break;
    case 0x101:
        busy = func_0801BDB0();
        if (busy == 0) {
            func_0801E610(&a, &b);
            g_control_flags_03000940.display &= ~func_080035A8(a);
            g_control_flags_03000940.display &= ~func_080035A8(b);
            func_080DBED4(0, 0, 0, 0);
            data_03003860[0x71] = 0x65C9;
            func_080D72C8(data_088F46CC, 1, 3, 0, 0, 0, 3);
            s->script = func_080D3E9C(data_0894DBA4, owner);
            s->top = func_080D89D0(0, 0, 0, 0, 0x260, 0x100, data_0600CC00, data_06007000, 0x3FF, 0, 0, 0x40, 0x40, owner);
            event->phase++;
        }
        break;
    case 0x102:
        if (!(s->script = func_080D3F08(s->script)) &&
            !(s->top = func_080D8AEC(s->top))) {
            func_08000B20(func_080D3AF8(), 0x3FF, data_06007800, 0x400);
            event->phase++;
        }
        break;
    case 0x103:
        event->phase = 2;
        break;
    }
    return 0;
}
