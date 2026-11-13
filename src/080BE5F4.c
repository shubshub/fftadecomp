#include "ffta.h"

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

extern s32 func_0812F0D8(const void *object, u16 *entries);
extern int func_080B4A1C(RangeRequest *request, u8 direction, u8 mode,
                         struct Position080BE5F4 *output);
extern s16 func_080BDECC(struct Unit080BE5F4 *source,
                        struct Unit080BE5F4 *target,
                        u16 action, u16 parameter);

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

// Complete [0x080BE5F4, 0x080BE7AC): 440 bytes, 215 instructions.
s32 func_080BE5F4(struct Context080BE5F4 *context, u8 x, u8 y, s8 target_x,
                  s8 target_y, struct Position080BE5F4 *positions)
{
    RangeRequest request;
    u16 entries[2];
    s32 accepted;
    s32 count;
    s32 side;
    s32 i;
    struct Group080BE5F4 *group;

    func_0812F0D8(context->unit->actor, entries);
    request.unit = context->unit->actor;
    request.first = context->action;
    request.second = entries[0];
    request.x = x;
    request.y = y;
    request.end_x = x;
    request.end_y = y;
    count = func_080B4A1C(&request, 0, 1, positions);
    accepted = 0;

    for (side = 0; side < 2; side++) {
        group = context->groups[side];

        for (i = 0; i < count; i++) {
            struct Entry080BE5F4 *entry = find_position(group, positions[i].x,
                                                        positions[i].y);

            if (entry && entry->unit != context->unit) {
                struct Action080BE5F4 *record = find_action(entry, context->action);

                /* The ROM reads record->value without a NULL check. */
                if (record->value != 0) {
                    s32 value;

                    if (context->mode & 1)
                        return -1;
                    if ((context->mode & 2) && (record->flags & 2))
                        return -1;
                    value = func_080BDECC(context->unit, entry->unit,
                                          context->action, context->parameter);
                    if (value < 0)
                        value = -value;
                    if (record->value < 0)
                        value *= -100;
                    if (context->invert)
                        value = -value;
                    if (side)
                        value = -value;
                    if (value < 0)
                        return -1;
                    accepted++;
                }
            }
        }
    }
    return accepted;
}
