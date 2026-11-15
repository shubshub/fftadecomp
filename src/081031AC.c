#include "ffta.h"

/* 0x081031AC..0x0810350E, 866 bytes, phase handler for a moving sprite,
 * sha1 of the ROM bytes 66c07a33a08398c9cea9b2bdc95b23dc85b158a2.
 */

typedef struct {
    s16 x, y;
} Point;

typedef struct {
    u16 phase;
    u16 unknown_02;
    s16 *start;
    s16 *end;
    u8 *status;
    u8 unknown_10[4];
    u16 index;
    u8 delay;
} Descriptor;

typedef struct {
    u16 timer;
    u8 direction;
    u8 index;
    u8 count;
    u8 delay;
    u8 unknown_06[2];
    u8 *status;
    void *sprite;
    void *effects[4];
    s16 x_curve[60];
    s16 y_curve[60];
    Point from, to;
    void *task;
} State;

extern const u8 data_08502A10[];
extern const u16 data_0839F28C[];
extern const u8 data_08149DF0[];
extern const u8 data_08149DF3[];
extern const u8 data_08149DF6[];
extern const u8 data_08149DF9[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern u16 func_08141860(s16 horizontal, s16 vertical);
extern u32 func_08141898(u32 value);
extern void *func_080D5DD4(const void *header, int index, int x, int y,
                           int height, int mode, int palette);
extern void func_0801121C(void *object, int value);
extern void func_0801115C(void *object, u8 visible);
extern void func_080111A8(void *object, int value);
extern void func_08011198(void *object);
extern void func_08011428(void *object);
extern void *func_080D6334(void *object, s16 *start, s16 *end, u16 a, u16 b,
                           u16 count, s16 *x_values, s16 *y_values, u16 c,
                           u8 option_01, u8 option_00, void *parent);
extern u8 func_080D63C8(void *task);
extern u8 func_080D6478(void *task);
extern void func_080D5C20(void *task);
extern void *func_080D6530(void *task);
extern u8 func_080D5F24(void *objects, int count);

int func_081031AC(void *owner, Descriptor *d, State *s)
{
    u8 option_01[3], limit[3], base[3], cap[3];
    s16 px, py, pz;
    s16 *point;
    s16 dx, dy;
    int distance;
    s16 v;

    switch (d->phase) {
    case 0:
        point = d->start;
        s->from.x = point[0];
        s->from.y = point[1];
        point = d->end;
        s->to.x = point[0];
        s->to.y = point[1];
        s->status = d->status;
        s->index = d->index;
        s->delay = d->delay + 1;
        *s->status = 0;
        break;
    case 1:
        break;
    case 0x100:
        dx = s->to.x - s->from.x;
        dy = s->to.y - s->from.y;
        s->direction = func_08141860(dx, dy) >> 12;
        s->sprite = func_080D5DD4(data_08502A10, 0xd, s->from.x, s->from.y, 0x393, 6, 0);
        func_0801121C(s->sprite, -1);
        func_0801115C(s->sprite, 0);
        d->phase++;
        break;
    case 0x101:
        func_081443FC(option_01, data_08149DF0, sizeof(option_01));
        func_081443FC(limit, data_08149DF3, sizeof(limit));
        func_081443FC(base, data_08149DF6, sizeof(base));
        func_081443FC(cap, data_08149DF9, sizeof(cap));
        distance = (u16)func_08141898(((s->to.x - s->from.x) * (s->to.x - s->from.x) +
                                       (s->to.y - s->from.y) * (s->to.y - s->from.y)) << 8) >> 4;
        if (distance > limit[s->index])
            v = base[s->index];
        else
            v = limit[s->index] + base[s->index] - distance;
        if (v > cap[s->index])
            v = cap[s->index];
        s->task = func_080D6334(&s->sprite, &s->from.x, &s->to.x, 0, 0, 60,
                                s->x_curve, s->y_curve, 0, option_01[s->index],
                                v, owner);
        d->phase++;
        break;
    case 0x102:
        if (func_080D63C8(s->task)) {
            *s->status = 1;
            d->phase++;
        }
        break;
    case 0x103:
        if (*s->status == 2) {
            if (--s->delay == 0) {
                func_0801115C(s->sprite, 1);
                func_080D5C20(s->task);
                s->timer = 0;
                d->phase++;
            }
        }
        break;
    case 0x104:
        if (s->count <= 3 && s->timer == data_0839F28C[s->count]) {
            func_08011040(s->sprite, (u16 *)&px, (u16 *)&py, (u16 *)&pz);
            s->effects[s->count] = func_080D5DD4(data_08502A10, 0xd, px, py,
                                                 0x393, 6, 0);
            func_080111A8(s->effects[s->count], 1);
            func_08011198(s->effects[s->count]);
            s->count++;
        }
        s->timer++;
        if (func_080D6478(s->task)) {
            *s->status = 3;
            d->phase++;
        }
        break;
    case 0x105:
        if (s->timer != 0 && --s->timer != 0)
            break;
        s->task = func_080D6530(s->task);
        if (s->task == 0) {
            if (func_080D5F24(s->effects, 4)) {
                func_08011428(s->sprite);
                s->sprite = 0;
                *s->status = 4;
                d->phase = 2;
            }
        }
        break;
    }
    return 0;
}
