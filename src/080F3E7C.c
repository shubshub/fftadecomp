#include "ffta.h"

typedef struct TaskRequest {
    u16 state;
    u16 unknown_02;
    void *object;
    u32 unknown_08[3];
    s16 kind;
    u16 argument;
    u32 unknown_18;
} TaskRequest;

typedef struct TaskPayload {
    u8 flag;
    u8 ready;
    u8 unknown_02[2];
    void *resource;
    u32 unknown_08;
    void *object;
    void *pending;
    void *effect;
    void *task;
} TaskPayload;

typedef u32 (*TaskCallback)(void *task, TaskRequest *request, void *payload);

extern const u8 data_0839AF04[];
extern const u8 data_0839AF28[];
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                          TaskRequest *request, void *parent);
extern void func_080D38B4(void);
extern u8 func_080D3B54(void *object);
extern u8 func_080D8858(void *object, u16 flags);
extern void *func_080DDF68(void *object, void **resource, u16 flags, u8 mode,
                          u8 *ready, const void *data, u16 options,
                          u16 value, void *parent);
extern void *func_080E03F8(void *object, const void *data, u8 mode, u8 kind,
                          const s16 *coordinates, void *parent);
extern void *func_080E051C(void *effect);
extern void *func_080E05DC(void *pending);
extern u32 func_080E9E28(void *task, TaskRequest *request, void *payload);

u32 func_080F3E7C(void *task, TaskRequest *request, TaskPayload *payload)
{
    TaskRequest next;

    switch (request->state) {
    case 0: {
        void *object;
        u8 mode;

        payload->flag = request->argument;
        object = request->object;
        payload->object = object;
        mode = 3;
        if (payload->flag)
            mode = 0;
        payload->pending = func_080E03F8(object, data_0839AF04,
                                        mode, 0, 0, task);
        break;
    }
    case 1:
        func_080D38B4();
        break;
    case 0x100:
        payload->pending = func_080E05DC(payload->pending);
        if (payload->pending == 0) {
            if (func_080D3B54(payload->object)) {
                request->state = 2;
            } else {
                payload->task = func_080DDF68(payload->object, &payload->resource,
                                             0x8007, 2, &payload->ready,
                                             data_0839AF28, 5, 0, task);
                request->state++;
            }
        }
        break;
    case 0x101:
        if (payload->ready) {
            if (func_080D8858(payload->object, 0)) {
                next.kind = 0x54;
                next.argument = 1;
                next.object = payload->object;
                payload->effect = func_08005B6C(func_080E9E28, 0x44, &next, task);
                request->state++;
            } else {
                request->state = 2;
            }
        }
        break;
    case 0x102:
        payload->effect = func_080E051C(payload->effect);
        if (payload->effect == 0)
            request->state = 2;
        break;
    }
    return 0;
}
