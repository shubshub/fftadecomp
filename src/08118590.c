#include "ffta.h"

/* Target: complete [0x08118590, 0x0811872A), 410 bytes, including two
 * literal words. */
typedef struct {
    s16 current;
    s16 remaining;
    s16 error;
    s16 step;
    s16 period;
    s16 distance;
} InterpolationState;

typedef struct { u16 phase; u16 unknown_2; const u8 *text; } Event;
typedef struct {
    s16 x;
    s16 y;
    u16 timer;
    u16 unknown_6;
    void *object[3];
    InterpolationState motion[3];
    const void *unknown_38;
} State;

extern const u8 data_08501200[];
extern void func_080D8C58(const u8 *, s16 *, s16 *);
extern void *func_080D5CC0(const void *, u16, s16, s16, u16, u8, u8, u32);
extern void func_0801115C(void *, u8);
extern void func_080111A8(void *, u8);
extern void func_080E0608(InterpolationState *, s16, s16, s16);
extern void func_080E064C(InterpolationState *);
extern u8 func_080E0690(InterpolationState *);
extern void func_080107D4(void *, s16, s16, s16);
extern void func_080D5F74(void **, u16);

int func_08118590(void *owner, Event *event, State *s)
{
    u8 i;
    u8 j;

    switch (event->phase) {
    case 0:
        s->unknown_38 = event->text;
        func_080D8C58(event->text, &s->x, &s->y);
        break;
    case 1:
        for (j = 0; j < 3; j++) {
            /* An object still set: the ROM spins here (b . at 0x081185E0). */
            if (s->object[j] != 0)
                for (;;)
                    ;
        }
        break;
    case 0x100:
        for (i = 0; i < 3; i++) {
            s->object[i] = func_080D5CC0(data_08501200, i, s->x, s->y,
                                         0x3E3, 6, 0, 0);
            func_0801115C(s->object[i], 0);
            func_080111A8(s->object[i], 1);
        }
        func_080E0608(&s->motion[0], 0, 0x54, 0x78);
        func_080E0608(&s->motion[1], 0, 0x3B, 0x78);
        func_080E0608(&s->motion[2], 0, 0x2A, 0x78);
        event->phase++;
        break;
    case 0x101:
        for (i = 0; i < 3; i++) {
            func_080E064C(&s->motion[i]);
            func_080107D4(s->object[i], s->x, s->y - s->motion[i].current, 0);
        }
        s->timer++;
        if (s->timer == 0x2C) {
            for (i = 0; i < 3; i++)
                func_0801115C(s->object[i], 1);
        } else if (s->timer == 0x34) {
            for (i = 0; i < 3; i++)
                func_080111A8(s->object[i], 0);
        }
        if (func_080E0690(&s->motion[0])) {
            func_080D5F74(s->object, 3);
            event->phase = 2;
        }
        break;
    }
    return 0;
}
