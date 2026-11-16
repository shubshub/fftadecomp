#include "ffta.h"

typedef struct Object {
    void *data;
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
    u16 current;
} RankedList;

typedef struct {
    Object *object;
    u8 unknown_04[12];
    u16 action;
} GroupInfo;

typedef struct {
    Object *object;
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
extern Group *func_080A88EC(Collection *collection, s32 index);
extern GroupInfo *func_080A880C(Group *group);
extern u8 func_081352CC(Collection *collection, u32 unused, u8 override_mode);
extern u8 func_080A88E0(Collection *collection);
extern u8 func_080C8280(const void *object);
extern s32 func_080A8830(Group *group);
extern Child *func_080A8810(Group *group, s32 index);
extern u8 func_080A8858(Child *child, u8 selector);

static inline u8 child_rank(GroupInfo *info, Child *child)
{
    if (info->object == 0 || info->object == child->object ||
        !func_080A8858(child, 3))
        return 0;
    if (info->action == 0xB8)
        return 10;
    return 1;
}

/* Complete [0x080BB5C4, 0x080BB7AC): 488 bytes, 223 instructions.
 * Does nothing when the global mode is 1.  Otherwise enters in the list the
 * object of every group whose children give a non-zero rank, keeping the
 * greatest rank per object, and finally stores 12 to list->current when bit 7
 * of the global flags is set.  With skip_first the first group's object is
 * left out; without it that object is entered with rank 1 when func_081352CC
 * returns non-zero. */
void func_080BB5C4(RankedList *list, Collection *collection,
                   u8 skip_first, u8 override_mode)
{
    Group *group;
    GroupInfo *info;
    GroupInfo *child_info;
    RankedObject *entry;
    u32 rank;
    s32 best;
    s32 children;
    s32 total;
    s32 i;
    s32 j;
    s32 k;
    Object *excluded;

    if (g_state_02000000.mode == 1)
        return;

    excluded = 0;
    if (skip_first) {
        group = func_080A88EC(collection, 0);
        info = func_080A880C(group);
        excluded = info->object;
    } else {
        u8 enabled;

        if (override_mode)
            enabled = func_081352CC(collection, 0, 1);
        else
            enabled = func_081352CC(collection, 0, 0);
        if (enabled) {
            rank = 1;
            group = func_080A88EC(collection, 0);
            info = func_080A880C(group);
            {
                Object *object = info->object;

                for (j = 0; j < list->count; j++) {
                    if (list->entries[j].object == object) {
                        entry = &list->entries[j];
                        goto found_first;
                    }
                }
            }
            entry = 0;
        found_first:
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
        group = func_080A88EC(collection, i);
        info = func_080A880C(group);
        if (info->object == 0 || info->object == excluded)
            continue;
        if (func_080C8280(info->object->data))
            continue;

        best = 0;
        children = func_080A8830(group);
        child_info = func_080A880C(group);
        for (k = 0; k < children; k++) {
            s32 value = child_rank(child_info, func_080A8810(group, k));

            if (value > best)
                best = value;
        }
        rank = best;
        if (rank == 0)
            continue;

        {
            Object *object = info->object;

            for (j = 0; j < list->count; j++) {
                if (list->entries[j].object == object) {
                    entry = &list->entries[j];
                    goto found;
                }
            }
        }
        entry = 0;
    found:
        if (entry == 0)
            entry = &list->entries[list->count++];
        if (entry->object == 0 || entry->rank < rank) {
            entry->object = info->object;
            entry->rank = rank;
        }
    }

    if (g_state_02000000.flags & 0x80)
        list->current = 12;
}
