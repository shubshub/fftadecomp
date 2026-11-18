#include "ffta.h"

typedef struct {
    u8 group;
    u8 script;
    u8 unknown_02[2];
} EventEntry;

typedef struct {
    u16 state;
    u8 unknown_02[2];
    const u8 *script;
    u8 unknown_08[12];
    u16 first;
    u16 second;
    u8 unknown_18[4];
} Command;

typedef u32 (*TaskCallback)(void *task, void *descriptor, void *payload);

extern const u32 g_table_089A5D54[];
extern const EventEntry *func_08009A14(u16 event);
extern u32 func_08121FB8(void *task, void *descriptor, void *payload);
extern void *func_08121B8C(TaskCallback callback, u16 payload_size,
                           void *descriptor, void *parent);

/* Complete [0x0812237C, 0x081223C8), including the script table and callback literals. */
void *func_0812237C(u16 event)
{
    const EventEntry *entry = func_08009A14(event);
    const u8 *script = (const u8 *)g_table_089A5D54;
    Command command;

    /* Group numbers start at one. Each offset is relative to its directory. */
    script += *(const u32 *)(script + entry->group * 4 - 4);
    script += ((const u32 *)script)[entry->script];
    command.script = script;
    command.first = 0;
    command.second = 0xFF;
    return func_08121B8C(func_08121FB8, 0x10, &command, 0);
}
