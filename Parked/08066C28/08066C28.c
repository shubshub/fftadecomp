#include "ffta.h"

typedef struct {
    u16 state;
    u8 unknown_02[0x1A];
} Command08066C28;

typedef struct {
    u8 unknown_00[9];
    u8 flags;
} Task08066C28;

typedef struct {
    u8 unknown_00[0x108C];
    u32 value;
} Target08066C28;

typedef struct {
    u8 unknown_00[0x424];
    u32 entries[1];
} Table08066C28;

typedef struct {
    Table08066C28 *table;
    u8 unknown_04[4];
    u8 mode;
    u8 unknown_09[7];
    void *handle;
    u8 unknown_14[0x3C];
    u8 list[0x31];
    s8 row;
} Menu08066C28;

extern void *func_08005BFC(void *handle);
extern void func_08005C04(void *handle, Command08066C28 *command);
extern u16 func_08017B68(void *list, s8 row);
extern void func_080670B4(Task08066C28 *task);

// Complete target: [0x08066C28, 0x08066C98), 112 bytes including literal pool.
void func_08066C28(Menu08066C28 *menu)
{
    if (menu->mode == 4) {
        Task08066C28 *task = func_08005BFC(menu->handle);
        if (task->flags & 1)
            func_080670B4(task);
    } else {
        Table08066C28 *table = menu->table;
        u32 value = table->entries[func_08017B68(menu->list, menu->row)];
        Command08066C28 command;
        ((Target08066C28 *)func_08005BFC(menu->handle))->value = value;
        command.state = 0x102;
        func_08005C04(menu->handle, &command);
    }
}
