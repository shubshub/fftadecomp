#include "ffta.h"

/* Target: complete [0x0810BEA0, 0x0810C244), 932 bytes including literal
 * pools.  The three-byte initialiser of delays is the ROM at 0x08149F20. */

typedef struct {
    s16 x, y;
} Point;

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u32 unknown_08;
    u32 flags;
    u8 unknown_10[6];
    u16 flag;
} Descriptor;

typedef struct {
    u8 flag;
    u8 mode;
    u16 countdown;
    s16 x, y;
    u8 unknown_08;
    u8 status[3];
    u8 ready;
    u8 unknown_0d[3];
    Point from, to;
    void *children[3];
    u8 unknown_24[8];
    void *position_child;
    void *actor;
    void *output;
    void *coordinate_result;
    void *object;
    void *initial_child;
    void *effect;
    void *preparation;
    void *record_child;
} Payload;

/* The scheduler copies this 28-byte descriptor (0x080059F2..0x080059FC). */
typedef struct {
    u16 phase;
    u16 unknown_02;
    s16 *start;
    s16 *end;
    u8 *status;
    u8 unknown_10[4];
    u16 index;
    u16 delay;
    u32 unknown_18;
} Child;

extern const u8 data_083A2218[];
extern const u8 data_083A22C0[];
extern const u8 data_083A2290[];
extern const u8 data_083A22C8[];
extern const u8 data_083A22C4[];
extern const u8 data_083A22D0[];
extern const u8 data_083A2260[];
extern const u8 data_083A22D8[];

extern void *memcpy(void *, const void *, unsigned long);
extern u32 func_0810BB70();
extern void *func_080E03F8(void *, const void *, u8, u8, u32, void *);
extern void func_080D38B4(void);
extern void *func_080E05DC(void *);
extern u8 func_080D3B54(void *);
extern void *func_080DDF68(void *, void **, u16, u8, u8 *, const void *,
                           u16, u16, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern void func_080DBDA0(void *entity, s16 *x, s16 *y, s16 *z);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void *func_080DD4A4(void *, u8);
extern void *func_080DD4C4(void *);
extern void *func_08005B6C(u32 (*)(), u32, void *, void *);
extern void func_080DE3BC(void *, u8);
extern void func_080DBA50(void *);
extern void *func_080DE4F4(void *, u8, u8 *, const void *, u16, u16, void *);
extern u16 func_0801BB0C(s16, s16, u16);
extern void *func_080D6134(void *);
extern u8 func_080D8858(void *, u16);
extern void *func_080DD748(void *, s16 *, s16 *, s16 *);
extern u8 func_080DD580(void *);
extern void *func_080DC498(void *, int, int, int, void *);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern u8 func_080E0570(void **, int);
extern u8 func_080DE244(void *);
extern void *func_080DBA5C(void *);

u32 func_0810BEA0(void *task, Descriptor *descriptor, Payload *payload)
{
    u8 animation;
    u16 output_mode;

    switch (descriptor->phase) {
    case 0:
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        animation = 6;
        if (payload->flag != 0)
            animation = 0;
        if (descriptor->flags & 2)
            payload->mode = 1;
        payload->initial_child = func_080E03F8(payload->actor, data_083A2218,
            animation, 0, 0, task);
        break;
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_child = func_080E05DC(payload->initial_child);
        if (payload->initial_child != 0)
            break;
        if (func_080D3B54(payload->actor)) {
            descriptor->phase = 2;
            break;
        }
        output_mode = 92;
        if (payload->mode != 0)
            output_mode = 52;
        payload->preparation = func_080DDF68(payload->actor, &payload->output,
            output_mode, 1, &payload->ready, data_083A22C0, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x101: {
        Child child;
        u8 delays[3] = {6, 0, 12};
        s16 x, y, z;
        u8 i;

        if (payload->ready == 0)
            break;
        func_080DBDC8(payload->output, &x, &y);
        payload->position_child = func_080D6098(x, y, 0, 1, 2,
            payload->unknown_24, data_083A2290, task);
        payload->record_child = func_080DFD8C(data_083A22C8, 1, 4, 0, task);
        func_080DBDA0(payload->output, &x, &y, &z);
        payload->from.x = x;
        payload->from.y = y - 12;
        payload->object = func_080DD4A4(payload->actor, 0);
        payload->coordinate_result = func_080DD4C4(payload->object);
        func_080DBDA0(payload->coordinate_result, &x, &y, &z);
        payload->to.x = x;
        payload->to.y = y - 12;
        child.start = &payload->from.x;
        child.end = &payload->to.x;
        for (i = 0; i <= 2; i++) {
            child.status = &payload->status[i];
            child.index = i;
            child.delay = delays[i];
            payload->children[i] = func_08005B6C(func_0810BB70, 0xcc, &child,
                task);
            payload->countdown = 10;
        }
        descriptor->phase++;
        break;
    }
    case 0x102:
        payload->countdown--;
        if (payload->countdown != 0)
            break;
        func_080DE3BC(payload->output, 0);
        func_080DBA50(payload->preparation);
        payload->preparation = func_080DE4F4(payload->output, 1,
            &payload->ready, data_083A22C4, 0, 0, task);
        descriptor->phase++;
        break;
    case 0x103: {
        u8 i;

        if (payload->ready == 0)
            break;
        if (payload->status[0] == 0)
            break;
        if (payload->status[1] == 0)
            break;
        if (payload->status[2] == 0)
            break;
        payload->record_child = func_080DFD8C(data_083A22D0, 1, 4, 0, task);
        for (i = 0; i <= 2; i++)
            payload->status[i] = 2;
        func_0801BB0C(payload->to.x - 120, payload->to.y - 96, 40);
        descriptor->phase++;
        break;
    }
    case 0x104:
        payload->position_child = func_080D6134(payload->position_child);
        if (payload->position_child != 0)
            break;
        if (payload->status[0] != 3)
            break;
        func_080DE3BC(payload->output, 0);
        if (func_080D8858(payload->actor, 0) == 0) {
            descriptor->phase = 0x105;
            break;
        }
        payload->coordinate_result = func_080DD748(payload->object,
            &payload->x, &payload->y, 0);
        payload->position_child = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_24, data_083A2260, task);
        if (func_080DD580(payload->object)) {
            payload->effect = func_080DC498(payload->coordinate_result,
                16, 12, 0, task);
        } else {
            payload->effect = func_080DCFE4(payload->object, 0, 12, 20, 4,
                task, 20);
        }
        payload->record_child = func_080DFD8C(data_083A22D8, 1, 4, 0, task);
        descriptor->phase++;
        break;
    case 0x105:
        if (!func_080E0570(payload->children, 3))
            break;
        payload->position_child = func_080D6134(payload->position_child);
        if (payload->position_child != 0)
            break;
        if (func_080DE244(payload->output) == 0)
            break;
        payload->effect = func_080DBA5C(payload->effect);
        if (payload->effect != 0)
            break;
        descriptor->phase = 2;
        break;
    }
    return 0;
}
