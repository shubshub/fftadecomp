#include "ffta.h"

// Target 0x080F41C8, complete [0x080F41C8, 0x080F444E), 646 bytes.

typedef struct Request080F41C8 {
    u16 phase;
    u16 unknown_02;
    void *object;
    u32 unknown_08[3];
    u16 kind;
    u16 argument;
    u32 unknown_18;
} Request080F41C8;

typedef struct Payload080F41C8 {
    u8 mode;
    u8 count;
    s16 x;
    s16 y;
    u8 index;
    u8 countdown;
    u8 ready;
    u8 unknown_09[3];
    void *resource;
    void *pairs[2];
    void *children[3];
    u32 output;
    u32 unknown_28;
    void *coordinate_task;
    void *timeline_task;
    void *initial_task;
    void *object;
    void *script_task;
    void *final_task;
} Payload080F41C8;

typedef u32 (*TaskCallback)(void *task, Request080F41C8 *request,
                            void *payload);

extern const u8 data_08149D10[];
extern const u8 data_0839AF60[];
extern const u8 data_0839B01C[];
extern const u8 data_0839AF90[];
extern const u8 data_08949F18[];
extern const u8 data_0839B024[];

extern void *func_081443FC(void *destination, const void *source, u32 bytes);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                           Request080F41C8 *request, void *parent);
extern void func_080D38B4(void);
extern void *func_080D4724(const void *, void *, u16);
extern void *func_080D4774(void *task);
extern void *func_080D6098(s16 x, s16 y, u16 depth, u8 mode, u16 count,
                           u32 *output, const void *entries, void *parent);
extern void *func_080D6134(void *task);
extern u8 func_080D8858(void *object, u16 index);
extern void func_080DBDC8(void *object, s16 *x, s16 *y);
extern void *func_080DD4A4(void *object, u8 index);
extern void *func_080DDF68(void *object, void **resource, u16 flags, u8 mode,
                           u8 *ready, const void *data, u16 options,
                           u16 value, void *parent);
extern u8 func_080DE1F0(void *object);
extern void *func_080DFD8C(const void *data, u8 mode, u16 flags, u16 delay,
                           void *parent);
extern void *func_080E03F8(void *object, const void *data, u8 mode, u8 kind,
                           const s16 *coordinates, void *parent);
extern u8 func_080E0570(void **children, u16 count);
extern void *func_080E05DC(void *task);
extern u32 func_080F3F7C(void *task, Request080F41C8 *request, void *payload);
extern u32 func_080F40DC(void *task, Request080F41C8 *request, void *payload);

u32 func_080F41C8(void *task, Request080F41C8 *request,
                  Payload080F41C8 *payload)
{
    Request080F41C8 child;
    u8 kinds[3];
    Request080F41C8 pair;
    u32 position;

    switch (request->phase) {
    case 0: {
        void *object;
        u8 mode;

        payload->mode = request->argument;
        object = request->object;
        payload->object = object;
        mode = 4;
        if (payload->mode)
            mode = 0;
        payload->initial_task = func_080E03F8(object, data_0839AF60,
                                              mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->initial_task = func_080E05DC(payload->initial_task);
        if (payload->initial_task)
            break;
        if (payload->mode) {
            payload->countdown = 1;
            payload->count = func_080D8858(payload->object, 0);
            if (payload->count == 0)
                request->phase = 0x104;
            else
                request->phase = 0x103;
        } else {
            payload->script_task = func_080DDF68(payload->object,
                &payload->resource, 0x3C, 2, &payload->ready,
                data_0839B01C, 0, 0, task);
            request->phase++;
        }
        break;
    case 0x101: {
        u8 i;

        func_081443FC(kinds, data_08149D10, sizeof(kinds));
        if (payload->ready == 0)
            break;
        func_080DBDC8(payload->resource, &payload->x, &payload->y);
        payload->coordinate_task = func_080D6098(payload->x,
            payload->y + 0x1C, 0, 1, 2, &payload->output, data_0839AF90,
            task);
        {
            u32 high = (u16)payload->y << 16;

            position = (u16)payload->x | high;
        }
        child.object = &position;
        for (i = 0; i < 3; i++) {
            child.kind = kinds[i];
            child.argument = i;
            payload->children[i] = func_08005B6C(func_080F3F7C, 0x1C,
                                                 &child, task);
        }
        payload->timeline_task = func_080D4724(data_08949F18, task, 0x10);
        payload->final_task = func_080DFD8C(data_0839B024, 1, 4, 0, task);
        request->phase++;
        break;
    }
    case 0x102:
        payload->timeline_task = func_080D4774(payload->timeline_task);
        if (payload->timeline_task)
            break;
        payload->coordinate_task = func_080D6134(payload->coordinate_task);
        if (payload->coordinate_task)
            break;
        if (!func_080E0570(payload->children, 3))
            break;
        payload->countdown = 1;
        payload->count = func_080D8858(payload->object, 0);
        if (payload->count == 0)
            request->phase = 0x104;
        else
            request->phase++;
        break;
    case 0x103:
        func_080E0570(payload->pairs, 2);
        if (--payload->countdown)
            break;
        {
            u8 slot = payload->pairs[0] != 0;

            pair.kind = payload->index;
            pair.object = func_080DD4A4(payload->object, payload->index);
            payload->pairs[slot] = func_08005B6C(func_080F40DC, 0x28,
                                                 &pair, task);
        }
        payload->countdown = 50;
        payload->index++;
        if (payload->index == payload->count)
            request->phase++;
        break;
    case 0x104:
        if (!func_080DE1F0(payload->resource))
            break;
        if (!func_080E0570(payload->pairs, 2))
            break;
        request->phase = 2;
        break;
    }
    return 0;
}
