#include "ffta.h"

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

/* The scheduler copies 28 bytes; only descriptor and flags are set here. */
typedef struct {
    AnimationCommand command;
    u32 unknown_18;
} AnimationRequest;

typedef struct {
    const u8 *descriptor;
    u16 delay;
    u8 unknown_06[2];
} AnimationEntry;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080D449C(void *context, AnimationCommand *command,
                  AnimationState *animation);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                   void *descriptor, void *parent);
void *func_08005BFC(void *task);

void func_080D4870(const AnimationEntry *entries, void **tasks,
                   u16 count, void *parent)
{
    u16 index;

    for (index = 0; index < count; index++) {
        const u8 *descriptor = entries[index].descriptor;
        AnimationRequest request;
        void *task;

        request.command.flags = 0;
        request.command.descriptor = descriptor;
        task = func_08005B6C((TaskCallback)func_080D449C,
                             sizeof(AnimationState), &request, parent);
        tasks[index] = task;
        if (entries[index].delay != 0) {
            u16 delay = entries[index].delay;
            AnimationState *animation = func_08005BFC(task);
            animation->delay = delay;
        }
    }
}
