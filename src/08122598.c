#include "ffta.h"

struct CommandState;

typedef struct {
    u8 unknown_00[0xF6];
    s8 x;
    s8 z;
    u8 unknown_F8;
    s8 saved_x;
    s8 saved_z;
} TileRecord;

typedef struct {
    TileRecord *record;
    u32 unknown_04;
    s16 x;
    s16 height;
    s16 z;
} CommandActor;

extern void *func_081255C8(u8 selector);
extern void func_08099E68(void *object, s8 x, s8 z);

/* Command 47, [0x08122598, 0x0812260A). */
u32 func_08122598(struct CommandState *state, const u8 *command)
{
    CommandActor *actor = func_081255C8(command[1]);
    u8 x = command[2];
    u8 z;

    if (x == 0xFF)
        x = actor->x >> 5;
    z = command[3];
    if (z == 0xFF)
        z = actor->z >> 5;

    actor->record->x = x;
    actor->record->z = z;
    func_08099E68(actor, actor->record->x, actor->record->z);
    actor->record->saved_x = actor->record->x;
    actor->record->saved_z = actor->record->z;
    return 0x110;
}
