#include "ffta.h"
#include "control_flags.h"
// Target: 0x080EA938..0x080EAB32 (506 bytes).
// Sibling of func_080EA4A0 (same event phases).
typedef struct {
    u16 state;
    u16 unknown_2;
    void *value;
    u8 unknown_8[14];
    u16 mode;
} Event;
typedef struct {
    u16 timer;
    u8 mode;
    u8 unknown_3;
    void *object;
    void *first;
    void *third;
    void *value;
    void *pending;
    void *follow;
    void *effect;
    void *fade;
} State;
extern const u8 data_08398B10[], data_088F4CD4[], data_08398BA4[], data_08398B4C[], data_08398BB0[];
typedef void (*TaskCallback)(void);
extern void func_080EA6F4(void);
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void *func_080E05DC(void *);
extern void *func_080DFD68(int, int, void *);
extern void *func_080DFED8(void *);
extern void *func_080D3E9C(const void *, void *);
extern void *func_080D989C(int, int, int, const void *, void *);
extern void *func_08005B6C(TaskCallback, u16, void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080D3F08(void *);
extern u32 func_080035A8(u8);
extern u32 func_08005BB0(const void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080EDB98(void *, int, void *);
extern void *func_080EDBDC(void *);
extern void func_080D38B4(void);
extern void func_080D7220(const void *, u8, u8, s16, s16, u16);
extern void func_080EDB80(void *);
extern void func_080D9B38(void *);
extern void func_08005B58(void *);
extern void func_080D9B58(void *);

int func_080EA938(void *owner, Event *event, State *s)
{
    u32 buffer[7];

    switch (event->state) {
    case 0:
        s->mode = event->mode;
        s->value = event->value;
        if (!s->mode)
            s->pending = func_080E03F8(s->value, data_08398B10, 5, 4, 0, owner);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        if (s->mode) {
            s->pending = func_080E05DC(s->pending);
            if (!s->pending)
                event->state = 0x105;
        } else {
            s->fade = func_080DFD68(1, 30, owner);
            event->state++;
        }
        break;
    case 0x101:
        s->pending = func_080E05DC(s->pending);
        if (s->pending)
            break;
        s->fade = func_080DFED8(s->fade);
        if (s->fade)
            break;
        func_080D7220(data_088F4CD4, 1, 3, 0, 0, 0);
        s->first = func_080D3E9C(data_08398BA4, owner);
        s->third = func_080D989C(3, 0, 8, data_08398B4C, owner);
        s->object = func_08005B6C(func_080EA6F4, 0x54, buffer, owner);
        s->effect = func_080DFD8C(data_08398BB0, 1, 4, 0, owner);
        s->timer = 322;
        event->state++;
        break;
    case 0x102:
        s->timer--;
        s->first = func_080D3F08(s->first);
        if (!s->first)
            event->state++;
        break;
    case 0x103:
        if (!--s->timer) {
            g_control_flags_03000940.display &= ~func_080035A8(3);
            s->fade = func_080DFD68(0, 30, owner);
            func_080EDB80(s->value);
            func_080D9B38(s->third);
            event->state++;
        }
        break;
    case 0x104:
        s->fade = func_080DFED8(s->fade);
        if (!s->fade && func_08005BB0(s->object)) {
            func_08005B58(s->object);
            s->object = 0;
            func_080D9B58(s->third);
            if (func_080D8858(s->value, 0))
                event->state++;
            else
                event->state = 2;
        }
        break;
    case 0x105:
        s->follow = func_080EDB98(s->value, 1, owner);
        event->state++;
        break;
    case 0x106:
        s->follow = func_080EDBDC(s->follow);
        if (!s->follow)
            event->state = 2;
        break;
    }
    return 0;
}
