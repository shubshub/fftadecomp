#include "ffta.h"

/* 0x08133758 - 154 bytes. */
typedef struct {
    u8 unknown_00[0x28];
    u16 flags;
    u8 unknown_2a[0xd9];
    u8 count;
    u8 kind;
} ScriptObject;

typedef struct {
    u32 unknown_00;
    ScriptObject *object;
    u8 unknown_08[0x1e];
    u16 flags;
} Task;

typedef struct {
    u8 kind : 4;
    u8 unknown_00 : 4;
    u8 unknown_01[3];
} EventEntry;

typedef struct {
    u8 unknown_0000[0x3c3c];
    EventEntry entries[24];
} GlobalState;

typedef void (*BufferInitializer)(void *, u32);
extern GlobalState g_state_02000000;
extern BufferInitializer g_callbacks_0836D4B8[];
extern u8 func_080C832C(const ScriptObject *object);
extern u8 func_080C95A8(u16 index);

void func_08133758(Task *task)
{
    GlobalState *state;
    s32 index;

    if (task->flags & 0x10)
        return;
    if (!func_080C832C(task->object))
        return;
    task->object->flags &= ~0x40;
    index = 0;
    state = &g_state_02000000;
    for (; index < 24; index++) {
        if (state->entries[index].kind == task->object->kind) {
            g_callbacks_0836D4B8[0](&state->entries[index], sizeof(EventEntry));
            if (task->object->count != 0 && func_080C95A8(13) != 1)
                task->object->count--;
            return;
        }
    }
}
