#include "ffta.h"

// Complete [081223C8,08122404): 60 bytes.
// 00b587b009041206120ec36801936b46090c0088091899826846c282064810216a460023
// fff7cefb00f008f80006000e07b002bc08470000b91f1208

typedef struct {
    u16 base;
    u8 unknown_02[10];
    void *object;
} Source081223C8;

typedef struct {
    u16 state;
    u8 unknown_02[2];
    void *object;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u8 unknown_18[4];
} Command081223C8;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern u32 func_08121FB8(void *task, void *descriptor, void *payload);
extern void *func_08121B8C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);
extern u8 func_08122404(void *task);

u8 func_081223C8(Source081223C8 *source, u16 offset, u8 second)
{
    Command081223C8 command;

    command.object = source->object;
    command.first = offset + source->base;
    command.second = second;
    return func_08122404(func_08121B8C(func_08121FB8, 0x10, &command, 0));
}
