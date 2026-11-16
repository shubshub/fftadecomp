#include "ffta.h"

/* Complete target [0x080BE1F4, 0x080BE3B8): 452 bytes, 216 instructions.
 * f0 b5 57 46 4e 46 45 46 e0 b4 89 b0 80 46 89 46
 * 14 1c 11 9a 12 98 13 99 00 04 00 0c 82 46 09 06
 * 09 0e 08 91 1b 06 12 06 1b 0e 17 0e 00 25 10 49
 * 60 18 00 88 85 42 16 da 06 1c 22 1c ca 20 80 00
 * 84 46 14 1c 20 68 01 68 08 1c f6 30 00 78 98 42
 * 04 d1 08 1c f7 30 00 78 b8 42 0b d0 61 46 62 18
 * 01 35 b5 42 ed db 00 26 00 2e 05 d1 00 20 a1 e0
 * 08 29 00 00 16 1c f7 e7 42 46 10 68 00 68 31 68
 * 09 68 12 89 06 f0 14 fb 00 06 00 28 ee d0 43 46
 * 18 68 00 68 05 90 05 a9 18 89 08 81 08 1c 55 46
 * 45 81 30 68 00 68 f6 30 00 78 08 71 30 68 00 68
 * f7 30 00 78 48 71 08 1c 00 79 88 71 08 1c 40 79
 * c8 71 08 1c 00 21 01 22 14 9b f6 f7 ad fb 05 1c
 * 30 68 00 68 01 1c f6 31 00 22 8a 56 f7 30 00 23
 * c3 56 14 98 29 1c f9 f7 e1 fd 00 28 0d d1 a9 00
 * 14 98 09 18 30 68 00 68 f6 30 00 78 08 70 30 68
 * 00 68 f7 30 00 78 48 70 01 35 00 2d 03 dc ad e7
 * 18 1d 30 18 14 e0 41 46 0f 89 00 22 c9 23 9b 00
 * f0 18 00 88 82 42 0a da 04 1c 31 1c 00 23 88 88
 * b8 42 ed d0 14 31 14 33 01 32 a2 42 f7 db 00 20
 * 12 4a 00 28 13 d0 82 89 41 7c 01 20 08 40 00 28
 * 8c d1 40 46 28 30 00 78 00 28 02 d0 10 04 40 42
 * 02 0c 08 98 01 28 02 d1 10 04 40 42 02 0c 00 2d
 * 1f dd 10 04 07 14 00 26 14 9c 00 2f 08 da 21 78
 * 62 78 48 46 ff f7 8e fc 0f e0 00 00 ff ff 00 00
 * 21 78 62 78 00 96 ff 20 01 90 01 20 02 90 03 96
 * 04 96 48 46 00 23 ff f7 ef fc 04 34 01 3d 00 2d
 * e3 d1 01 20 09 b0 38 bc 98 46 a1 46 aa 46 f0 bc
 * 02 bc 08 47 */

struct Actor080BE5F4 {
    u8 unknown00[0xF6];
    u8 x;
    u8 y;
};

struct Unit080BE5F4 {
    struct Actor080BE5F4 *actor;
};

struct Action080BE5F4 {
    u16 action;
    u8 unknown02[10];
    s16 value;
    u8 unknown0E[3];
    u8 flags;
    u8 unknown12[2];
};

struct Entry080BE5F4 {
    struct Unit080BE5F4 *unit;
    struct Action080BE5F4 actions[40];
    u16 count;
    u8 unknown326[2];
};

struct Group080BE5F4 {
    struct Entry080BE5F4 entries[13];
    u16 count;
};

struct Context080BE5F4 {
    struct Unit080BE5F4 *unit;
    u8 unknown04[4];
    u16 action;
    u8 unknown0A[2];
    struct Group080BE5F4 *groups[2];
    u8 unknown14[6];
    u16 parameter;
    u8 unknown1C[12];
    u8 invert;
    u8 unknown29[0x1EF];
    u8 mode;
};

typedef struct {
    struct Actor080BE5F4 *unit;
    u8 x;
    u8 y;
    u8 end_x;
    u8 end_y;
    u16 first;
    u16 second;
} RangeRequest;

struct Position080BE5F4 {
    u8 x;
    u8 y;
    u8 height;
    u8 unknown03;
};

extern u8 func_080C48A4(struct Actor080BE5F4 *first,
                        struct Actor080BE5F4 *second, u16 action);
extern int func_080B4A1C(RangeRequest *request, u8 direction, u8 mode,
                         struct Position080BE5F4 *output);
extern s32 func_080B7EA0(const struct Position080BE5F4 *positions, s32 count,
                         s8 x, s8 y);
extern void func_080BDC98(s32 *grid, u8 column, u8 row);
extern s32 func_080BDD7C(void *grid, u8 x, u8 y, u8 low, u8 high, u8 type,
                         s16 amount, u8 replace, u8 matchNibbles);

/* find_position and find_action are character-for-character copies of the
 * helpers in src/080BE5F4.c.  Inlined at 0x080BE220-0x080BE26A and
 * 0x080BE304-0x080BE332. */
static inline struct Entry080BE5F4 *find_position(struct Group080BE5F4 *group,
                                                  u8 x, u8 y)
{
    s32 i;

    for (i = 0; i < group->count; i++) {
        if (group->entries[i].unit->actor->x == x &&
            group->entries[i].unit->actor->y == y)
            return &group->entries[i];
    }
    return 0;
}

static inline struct Action080BE5F4 *find_action(struct Entry080BE5F4 *entry,
                                                 u16 action)
{
    s32 i;

    for (i = 0; i < entry->count; i++) {
        if (entry->actions[i].action == action)
            return &entry->actions[i];
    }
    return 0;
}

/* x and y are not narrowed on entry: the caller passes plain ldrb values
 * (0x080BEB3E, 0x080BEB42) and the u8 narrowing comes at find_position's
 * parameters (0x080BE218-0x080BE21E), after second and side. */
s32 func_080BE1F4(struct Context080BE5F4 *context, s32 *grid,
                  struct Group080BE5F4 *group, s32 x, s32 y, u16 second,
                  u8 side, struct Position080BE5F4 *positions)
{
    RangeRequest request;
    struct Entry080BE5F4 *entry;
    struct Action080BE5F4 *record;
    s32 count;
    s32 i;
    s16 value;

    entry = find_position(group, x, y);
    if (entry == 0)
        return 0;
    if (!func_080C48A4(context->unit->actor, entry->unit->actor,
                       context->action))
        return 0;

    request.unit = context->unit->actor;
    request.first = context->action;
    request.second = second;
    request.x = entry->unit->actor->x;
    request.y = entry->unit->actor->y;
    request.end_x = request.x;
    request.end_y = request.y;
    count = func_080B4A1C(&request, 0, 1, positions);
    if (!func_080B7EA0(positions, count, entry->unit->actor->x,
                       entry->unit->actor->y)) {
        positions[count].x = entry->unit->actor->x;
        positions[count].y = entry->unit->actor->y;
        count++;
    }
    if (count <= 0)
        return 0;

    record = find_action(entry, context->action);
    value = -1;
    if (record) {
        value = record->value;
        if (record->flags & 1)
            return 0;
        if (context->invert)
            value = -value;
        if (side == 1)
            value = -value;
    }

    for (i = 0; i < count; i++) {
        if (value < 0)
            func_080BDC98(grid, positions[i].x, positions[i].y);
        else
            func_080BDD7C(grid, positions[i].x, positions[i].y, 0, 0, 0xFF, 1,
                          0, 0);
    }
    return 1;
}
