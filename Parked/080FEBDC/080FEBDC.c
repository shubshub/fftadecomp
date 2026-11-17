#include "ffta.h"

// 0x080FEBDC .. 0x080FEE60: 644 bytes, 322 instructions.
// Offset views describe the accesses in this callback, not original layouts.

typedef struct {
    s16 x;
    s16 y;
} Point080FEBDC;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *first;
    void *second;
    void *third;
    u8 unknown_10[4];
    u16 flag;
} Descriptor080FEBDC;

typedef struct {
    s16 counter;
    u8 flag;
    u8 unknown_03;
    s16 x[60];
    s16 y[60];
    void *path;
    void *first;
    void *second;
    void *third;
    void *marker;
    void *markers[3];
    void *unknown_114[3];
    void *coordinate_task;
    void *child;
    void *effect;
} Payload080FEBDC;

// Only the observed reads are typed; extents are unknown.
extern const u8 data_084FBA40[];
extern const u8 data_08149DCC[];
extern const u8 data_08949ADC[];
extern const u8 data_0839E0FC[];
extern const u8 data_0839E194[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void func_080DBDA0(void *entity, s16 *x, s16 *y, s16 *z);
extern void *func_080D62CC(void **, const Point080FEBDC *, const Point080FEBDC *, s16, s16, u16,
    const s16 *, const s16 *, u16, void *);
extern void *func_080D5DD4(const void *, u8, s16, s16, u16, u8, u8);
extern void func_0801121C(void *, s16);
extern void *func_080D4704(const void *, void *);
extern void func_080D5C20(void *);
extern void *func_080D6530(void *);
extern void func_08011428(void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080D4774(void *);
extern u8 func_080D5F24(void **, u16);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_080FEBDC(void *task, Descriptor080FEBDC *descriptor, Payload080FEBDC *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->first = descriptor->first;
        payload->second = descriptor->second;
        payload->third = descriptor->third;
        payload->flag = descriptor->flag;
        payload->counter = 62;
        break;
    case 1:
        break;
    case 0x100:
    {
        Point080FEBDC from, to;
        s16 from_z, to_z;

        func_080DBDA0(payload->first, &from.x, &from.y, &from_z);
        func_080DBDA0(payload->second, &to.x, &to.y, &to_z);
        payload->path = func_080D62CC(&payload->marker, &from, &to, -28, -28, 60,
            payload->x, payload->y, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x101:
        if (--payload->counter != 0)
            break;
        payload->marker = func_080D5DD4(data_084FBA40, 2, payload->x[0], payload->y[0], 0x3a1, 6, 0);
        func_0801121C(payload->marker, 1);
        payload->child = func_080D4704(data_08949ADC, task);
        func_080D5C20(payload->path);
        payload->counter = 0;
        descriptor->phase++;
        break;
    case 0x102:
    {
        u8 steps[3];
        u8 i;
        s16 x, y;

        func_081443FC(steps, data_08149DCC, sizeof(steps));
        for (i = 0; i < 3; i++) {
            if (payload->counter == steps[i])
                payload->markers[i] = func_080D5DD4(data_084FBA40, 3,
                    payload->x[payload->counter], payload->y[payload->counter], 0x3a1, 6, 0);
        }
        payload->counter++;
        payload->path = func_080D6530(payload->path);
        if (payload->path != 0)
            break;
        func_08011428(payload->marker);
        payload->marker = 0;
        func_080DBDC8(payload->second, &x, &y);
        payload->coordinate_task = func_080D6098(x, y, 0, 1, 3, payload->unknown_114,
            data_0839E0FC, task);
        if (payload->flag == 1)
            payload->effect = func_080DCFE4(payload->third, data_0839E194, 12, 30, 4, task, 30);
        descriptor->phase++;
        break;
    }
    case 0x103:
        payload->child = func_080D4774(payload->child);
        if (payload->child != 0)
            break;
        if (!func_080D5F24(payload->markers, 3))
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->effect = func_080DBA5C(payload->effect);
        if (payload->effect == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
