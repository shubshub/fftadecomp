#include "ffta.h"

/* 0x080BB5C4: 488 bytes. */
typedef struct Object {
    void *state;
} Object;

typedef struct {
    Object *object;
    u8 rank;
    u8 unknown_05[3];
} RankedObject;

typedef struct {
    RankedObject entries[13];
    u8 unknown_68[6];
    u8 count;
    u8 unknown_6F[9];
    u16 mode;
} RankedList;

typedef struct {
    Object *object;
    u8 unknown_04[12];
    u16 action;
} GroupInfo;

typedef struct {
    Object *object;
    u8 unknown_04[0x28];
} Child;

typedef struct Group Group;
typedef struct Collection Collection;

typedef struct {
    u8 unknown_0000[0x2190];
    u8 mode;
    u8 unknown_2191[0xE2F];
    u8 flags;
} GlobalState;

extern GlobalState g_state_02000000;
Group *func_080A88EC(Collection *collection, s32 index);
GroupInfo *func_080A880C(Group *group);
u8 func_081352CC(Collection *collection, s32 index, u8 mode);
u8 func_080A88E0(Collection *collection);
u8 func_080C8280(void *state);
s32 func_080A8830(Group *group);
Child *func_080A8810(Group *group, s32 index);
u8 func_080A8858(Child *child, u32 selector);

void func_080BB5C4(RankedList *list, Collection *collection,
                   u8 skip_first, u8 mode)
{
    GlobalState *state = &g_state_02000000;
    Object *excluded;
    Group *group;
    GroupInfo *info;
    Object *object;
    RankedObject *entry;
    u32 rank;
    s32 best, total, children, i, j;
    u8 enabled;

    if (state->mode == 1)
        return;

    excluded = 0;
    if (skip_first) {
        group = func_080A88EC(collection, 0);
        excluded = func_080A880C(group)->object;
    } else {
        if (mode)
            enabled = func_081352CC(collection, 0, 1);
        else
            enabled = func_081352CC(collection, 0, 0);
        if (enabled) {
            rank = 1;
            group = func_080A88EC(collection, 0);
            info = func_080A880C(group);
            object = info->object;
            {
                s32 count = list->count;
                entry = list->entries;
                for (j = 0; j < count; j++, entry++) {
                    if (entry->object == object)
                        break;
                }
                if (j >= count)
                    entry = 0;
            }
            if (entry == 0)
                entry = &list->entries[list->count++];
            if (entry->object != 0 && entry->rank >= rank)
                rank = entry->rank;
            entry->object = info->object;
            entry->rank = rank;
        }
    }

    total = func_080A88E0(collection);
    for (i = 0; i < total; i++) {
        GroupInfo *group_info;

        group = func_080A88EC(collection, i);
        info = func_080A880C(group);
        if (info->object == 0 || info->object == excluded)
            continue;
        if (func_080C8280(info->object->state))
            continue;

        best = 0;
        children = func_080A8830(group);
        group_info = func_080A880C(group);
        for (j = 0; j < children; j++) {
            Child *child = func_080A8810(group, j);
            s32 value;

            if (group_info->object == 0 ||
                group_info->object == child->object ||
                !func_080A8858(child, 3))
                value = 0;
            else if (group_info->action == 0xB8)
                value = 10;
            else
                value = 1;
            if (value > best)
                best = value;
        }
        rank = best;
        if (rank == 0)
            continue;

        object = info->object;
        {
            s32 count = list->count;
            entry = list->entries;
            for (j = 0; j < count; j++, entry++) {
                if (entry->object == object)
                    break;
            }
            if (j >= count)
                entry = 0;
        }
        if (entry == 0)
            entry = &list->entries[list->count++];
        if (entry->object == 0 || entry->rank < rank) {
            entry->object = info->object;
            entry->rank = rank;
        }
    }

    if (state->flags & 0x80)
        list->mode = 12;
}
