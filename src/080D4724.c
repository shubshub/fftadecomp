#include "ffta.h"

/* 0x080D4724..0x080D4754: 48 bytes, including the callback literal. */
typedef struct {
    u16 state;
    u8 unknown_02[2];
    const u8 *descriptor;
    u8 unknown_08[0xC];
    u16 flags;
} AnimationCommand;

typedef struct {
    const u8 *descriptor;
    u16 resource;
    u8 kind;
    u8 flags;
    u16 delay;
    u16 frame;
    u16 timer;
    u8 unknown_0E[2];
    void *handle;
    void *task;
} AnimationState;

typedef struct {
    AnimationCommand command;
    u32 unknown_18;
} AnimationRequest;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern u32 func_080D449C(void *context, AnimationCommand *command,
                         AnimationState *animation);
extern void *func_08005B6C(TaskCallback callback, u16 payload_size,
                          void *descriptor, void *parent);
extern void func_080D4820(u32 handle, u16 value);

void *func_080D4724(const u8 *descriptor, void *parent, u16 value)
{
    AnimationRequest request;
    void *task;

    request.command.flags = 0;
    request.command.descriptor = descriptor;
    task = func_08005B6C((TaskCallback)func_080D449C, sizeof(AnimationState),
                         &request, parent);
    func_080D4820((u32)task, value);
    return task;
}
