/* 0x080D9A24: complete 56-byte scheduler caller. */
#include "ffta.h"

typedef struct ObjectEntry ObjectEntry;
typedef struct ObjectCommand {
    u16 state;
    u16 unknown_02;
    const ObjectEntry *entries;
    u8 unknown_08[0xC];
    u16 first;
    u16 second;
    u16 count;
} ObjectCommand;

typedef struct ObjectState ObjectState;
typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

u32 func_080D96F0(void *task, ObjectCommand *command, ObjectState *state);
void *func_08005B6C(TaskCallback callback, u16 payload_size,
                  void *descriptor, void *parent);

void *func_080D9A24(u8 first, u8 second, u8 count,
                   const ObjectEntry *entries, void *parent)
{
    ObjectCommand command;

    command.first = first;
    command.second = second;
    command.count = count;
    command.entries = entries;
    return func_08005B6C((TaskCallback)func_080D96F0, 8, &command, parent);
}
