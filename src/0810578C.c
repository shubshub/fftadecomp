#include "ffta.h"

// Target: complete [0x0810578C, 0x08105930), 420 bytes, 210 instructions.
// These are offset views, not recovered original object declarations or
// extents.  Helper returns, storage effects and ABI preservation remain
// opaque; later phases and valid handles are independent premises.

typedef struct {
    u16 phase;
    u16 unknown_02;
    void *actor;
    u8 *done;
    u8 unknown_0c[8];
    u16 selector;
    u16 flag;
} Descriptor0810578C;

typedef struct {
    s32 unknown_00;
    s32 unknown_04;
} Rect0810578C;

typedef struct {
    u8 flag;
    u8 unknown_01;
    u16 counter;
    s16 x;
    s16 y;
    u8 selector;
    u8 unknown_09[3];
    u8 *done;
    void *actor;
    u32 coordinate_result;
    u8 unknown_18[8];
    void *coordinate_task;
    void *object_task;
    u8 unknown_28[2];
    u16 frame_2a;
    u8 unknown_2c[4];
    u8 enabled_30;
    u8 extra_31;
    u8 unknown_32[10];
    void *sound_task;
} Payload0810578C;

typedef void (*BufferCopier0810578C)(void *, const void *, u32);

/* Observed address bindings only; original asset extents are unknown. */
extern BufferCopier0810578C const data_0836D4BC[];
extern const u8 data_0839FD40[];
extern const u8 data_0839FD54[];
extern const u8 data_0839FD5C[];
extern const Rect0810578C data_08149E44;
extern const Rect0810578C data_08149E4C;
extern const u8 data_0839FDE8[];
extern const u8 data_0839FD10[];

extern void *func_080DD4C4(void *);
extern u8 func_080DBF90(void *, const Rect0810578C *, u8, const Rect0810578C *);
extern u8 func_080D8B4C(void);
extern u32 func_080DD748(void *, s16 *, s16 *, u32);
extern void *func_080DCFE4(void *, const void *, u8, u16, u16, void *, u16);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern u8 func_080DD580(void *);
extern void *func_080D6098(s16, s16, u16, u8, u16, void *, const void *, void *);
extern void *func_080D6134(void *);
extern void *func_080DBA5C(void *);

u32 func_0810578C(void *task, Descriptor0810578C *descriptor,
                  Payload0810578C *payload)
{
    Rect0810578C area;
    Rect0810578C adjustment;
    void *object;
    u16 mode;

    switch (descriptor->phase) {
    case 0:
        payload->selector = descriptor->selector;
        payload->flag = descriptor->flag;
        payload->actor = descriptor->actor;
        payload->done = descriptor->done;
        data_0836D4BC[0](payload->unknown_28, data_0839FD40, 0x14);
        payload->frame_2a = data_0839FD54[payload->selector];
        if (data_0839FD5C[payload->selector] != 0xFF) {
            payload->enabled_30 = 1;
            payload->extra_31 = data_0839FD5C[payload->selector];
        }
        object = func_080DD4C4(payload->actor);
        area = data_08149E44;
        adjustment = data_08149E4C;
        func_080DBF90(object, &area, 1, &adjustment);
        break;
    case 0x100:
        if (func_080D8B4C() != 0)
            break;
        payload->coordinate_result = func_080DD748(payload->actor,
            &payload->x, &payload->y, 0);
        descriptor->phase++;
        break;
    case 0x101:
        payload->counter = 0x28;
        mode = (payload->flag & 1) ? 2 : 4;
        payload->object_task = func_080DCFE4(payload->actor,
            payload->unknown_28, 12, 0x28, mode, task, 30);
        mode = (payload->flag & 1) ? 8 : 0x10;
        payload->sound_task = func_080DFD8C(data_0839FDE8, 1, mode | 4, 0,
            task);
        if (func_080DD580(payload->actor) != 0)
            payload->counter -= 10;
        payload->coordinate_task = func_080D6098(payload->x, payload->y,
            0, 1, 2, payload->unknown_18, data_0839FD10, task);
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->counter != 0) {
            if (--payload->counter == 0)
                *payload->done = 1;
        }
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task != 0)
            break;
        payload->object_task = func_080DBA5C(payload->object_task);
        if (payload->object_task == 0)
            descriptor->phase = 2;
        break;
    }
    return 0;
}
