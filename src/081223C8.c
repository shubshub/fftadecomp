#include "ffta.h"

/* Complete [0x081223C8, 0x08122404): 60 bytes, 25 instructions and one
 * callback literal.  Queues a func_08121FB8 command carrying state->object
 * and state->first + offset, and returns func_08122404's result for the new
 * task. */
typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u8 unknown_18[4];
} Command;

typedef struct {
    u16 first;
    u16 second;
    u16 timer;
    u8 ready;
    u8 filter;
    void *context;
    void *object;
} CommandState;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern u32 func_08121FB8(void *task, void *descriptor, void *payload);
extern void *func_08121B8C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);
extern int func_08122404(void *task);

u8 func_081223C8(CommandState *state, u16 offset, u8 second)
{
    Command command;

    command.object = state->object;
    command.first = offset + state->first;
    command.second = second;
    return func_08122404(func_08121B8C(func_08121FB8, 0x10, &command, 0));
}
