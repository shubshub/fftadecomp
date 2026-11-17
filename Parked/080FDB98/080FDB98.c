#include "ffta.h"
#include "control_flags.h"

// Target: complete [0x080FDB98, 0x080FDE56), 702 bytes, including literal words.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 *result;
    u8 unknown_0c[8];
    u16 variant;
    u16 option;
} Descriptor080FDB98;

typedef struct {
    s16 x;
    s16 y;
    u16 timer;
    u8 variant;
    u8 option;
    u8 ready;
    u8 unknown_09[3];
    u8 *result;
    u8 saved[0x10];
    u8 unknown_20[0x10];
    void *object;
    void *position_task;
    void *flash_task;
    void *effects[2];
    void *intro_task;
    void *actor;
    void *motion_task;
    void *sound_task;
} Payload080FDB98;

typedef struct {
    s16 x;
    s16 y;
} Offset080FDB98;

typedef struct {
    Offset080FDB98 offsets[4];
} Offsets080FDB98;

extern u8 data_03003920[];
extern const u8 data_0839D7E4[];
extern const u8 data_0839D7FC[];
extern const u8 data_0839D800[];
extern const u8 data_0839D804[];
extern const u8 data_0839D80C[];
extern const Offsets080FDB98 data_08149D94;
extern const u8 data_088F58E0[];
extern const u8 data_0894A028[];
extern const u8 data_0894A050[];
extern const u8 data_0894BE84[];
extern const u8 data_0894BEAC[];
extern const u8 data_0894D69C[];

extern void func_0814186C(const void *source, void *destination, u32 control);
extern void *func_080E03F8(void *, const void *, int, int, int, void *);
extern void *func_080E05DC(void *);
extern void *func_080DDF68(void *, void **, int, int, u8 *, const void *, int, int, void *);
extern void func_080DBDC8(void *, s16 *, s16 *);
extern s8 func_080DBC88(void *);
extern void func_080D7220(const void *, int, int, int, int, int);
extern void *func_080D3E9C(const void *, void *);
extern void func_080D3F84(void *, u8, u8);
extern void *func_080D4704(const void *, void *);
extern void *func_080DFD8C(const void *, int, int, int, void *);
extern u8 func_080D48DC(void **, int);
extern void *func_080D3F08(void *);
extern u32 func_080035A8(int);
extern void func_080DE3BC(void *, u8);
extern void func_080DBA50(void *);
extern void *func_080DE4F4(void *, int, u8 *, const void *, int, int, void *);
extern void *func_080DD4A4(void *, int);
extern void *func_080DD748(void *, s16 *, s16 *, int);
extern void func_080DC0BC(void *, u8);
extern u8 func_080D8B4C(void);
extern u8 func_080D8858(void *, int);
extern u8 func_080DE1F0(void *);

s32 func_080FDB98(void *task, Descriptor080FDB98 *descriptor,
                  Payload080FDB98 *payload)
{
    switch (descriptor->phase) {
    case 0:
        payload->actor = descriptor->actor;
        payload->result = descriptor->result;
        payload->variant = descriptor->variant;
        payload->option = descriptor->option;
        func_0814186C(data_03003920, payload->saved, 0x10);
        payload->intro_task = func_080E03F8(payload->actor, data_0839D7E4,
                                            2, 7, 0, task);
        *payload->result = 0;
        break;
    case 1:
        break;
    case 0x100: {
        int flags;

        payload->intro_task = func_080E05DC(payload->intro_task);
        if (payload->intro_task)
            break;
        flags = 0x34;
        if (payload->variant == 6)
            flags = 0x54;
        payload->motion_task = func_080DDF68(payload->actor, &payload->object,
                                             flags, 1, &payload->ready,
                                             data_0839D7FC, 5, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x101: {
        Offsets080FDB98 table = data_08149D94;
        s16 x;
        s16 y;
        s8 index;
        const u8 *second;

        if (!payload->ready)
            break;
        func_080DBDC8(payload->object, &x, &y);
        index = func_080DBC88(payload->object);
        func_080D7220(data_088F58E0, 1, 3,
                      (s16)(x + table.offsets[index].x),
                      (s16)(y + table.offsets[index].y), 0);
        payload->flash_task = func_080D3E9C(data_0894D69C, task);
        func_080D3F84(payload->flash_task, 8, 0xff);
        if (payload->variant != 6) {
            payload->effects[0] = func_080D4704(data_0894A028, task);
            second = data_0894A050;
        } else {
            payload->effects[0] = func_080D4704(data_0894BE84, task);
            second = data_0894BEAC;
        }
        payload->effects[1] = func_080D4704(second, task);
        payload->sound_task = func_080DFD8C(data_0839D804, 1, 4, 0, task);
        descriptor->phase++;
        break;
    }
    case 0x102:
        if (!func_080D48DC(payload->effects, 2))
            break;
        payload->flash_task = func_080D3F08(payload->flash_task);
        if (payload->flash_task)
            break;
        g_control_flags_03000940.display &= ~func_080035A8(3);
        func_0814186C(payload->saved, data_03003920, 0x10);
        func_080DE3BC(payload->object, 0);
        func_080DBA50(payload->motion_task);
        payload->motion_task = func_080DE4F4(payload->object, 1,
                                             &payload->ready, data_0839D800,
                                             0, 0, task);
        descriptor->phase++;
        break;
    case 0x103:
        if (!payload->ready)
            break;
        payload->sound_task = func_080DFD8C(data_0839D80C, 1, 4, 0, task);
        payload->position_task = func_080DD748(func_080DD4A4(payload->actor, 0),
                                               &payload->x, &payload->y, 0);
        func_080DC0BC(payload->position_task, payload->option);
        payload->timer = 30;
        descriptor->phase++;
    case 0x104:
        if (payload->timer) {
            if (--payload->timer)
                break;
        }
        if (func_080D8B4C())
            break;
        if (!func_080D8858(payload->actor, 0))
            *payload->result = 2;
        else
            *payload->result = 1;
        descriptor->phase++;
        break;
    case 0x105:
        if (func_080DE1F0(payload->object))
            descriptor->phase = 2;
        break;
    }
    return 0;
}
