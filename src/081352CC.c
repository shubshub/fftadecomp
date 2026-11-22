#include "ffta.h"

/* func_081352CC: complete target [0x081352CC, 0x0813554E), 642 bytes,
 * 300 instructions, including the literal 0x149 at 0x08135470.
 * Returns 1 as soon as func_0813522C accepts one of the collection's
 * children.  First every group's leading child is offered with the running
 * total of the amounts seen so far; then the first group's action decides
 * between offering its children paired with the second group's (actions 0
 * and 0xDF) and offering the children of every group that shares its base
 * object. */

typedef struct {
    void *data;
} Object;

typedef struct {
    Object *object;
    u16 flags;
    u8 unknown_06[3];
    u8 kind;
    u8 unknown_0A[6];
    u16 action;
} GroupInfo;

typedef struct {
    Object *object;
    u8 unknown_04[8];
    u16 flags;
    u8 unknown_0E[6];
    u8 options[10];
    s16 amount;
} Child;

typedef struct Group Group;
typedef struct Collection Collection;

extern u8 func_080A88E0(Collection *collection);
extern Group *func_080A88EC(Collection *collection, s32 index);
extern GroupInfo *func_080A880C(Group *group);
extern Child *func_080A8810(Group *group, s32 index);
extern s32 func_080A8830(Group *group);
/* The amount is passed sign-extended at all three calls (0x08135332,
 * 0x08135444, 0x0813550E), so this caller saw a signed halfword. */
extern u8 func_0813522C(void *source, void *target, u16 entry, u8 mode,
                        s16 amount, const void *options);

u8 func_081352CC(Collection *collection, u32 unused, u8 override_mode)
{
    u8 count;
    u16 action;
    void *base;
    Group *paired;
    Group *group;
    GroupInfo *info;
    Child *child;
    Child *paired_child;
    void *target;
    s16 amount;
    s32 i;

    count = func_080A88E0(collection);
    amount = 0;
    for (i = 0; i < count; i++) {
        group = func_080A88EC(collection, i);
        info = func_080A880C(group);
        child = func_080A8810(group, 0);
        if (child->flags & 1)
            amount += child->amount;
        if (info->kind == 2) {
            base = info->object->data;
            target = child->object->data;
            if (func_0813522C(base, target, 0, 1, amount, child->options))
                return 1;
        }
    }

    group = func_080A88EC(collection, 0);
    info = func_080A880C(group);
    base = info->object->data;
    if (info->flags & 0x2000)
        action = 0xE9;
    else if (info->flags & 0x4000)
        action = 0x149;
    else
        action = info->action;

    paired = 0;
    if ((action == 0 || action == 0xDF) && count > 1) {
        paired = func_080A88EC(collection, 1);
        if (func_080A880C(paired)->object->data != base)
            paired = 0;
    }

    /* Kept at 0x081353C4: the paired loop's entry test compares
     * children against this zero (0x081353DC). */
    amount = 0;
    if (action == 0 || action == 0xDF) {
        s32 children;
        s32 j;
        u8 active;

        children = func_080A8830(group);
        for (j = 0; j < children; j++) {
            active = 0;
            child = func_080A8810(group, j);
            amount = 0;
            target = 0;
            if (child->flags & 0x40)
                continue;
            if (child->flags & 1) {
                active = 1;
                amount = child->amount;
                target = child->object->data;
            }
            if (paired) {
                paired_child = func_080A8810(paired, j);
                if (paired_child->flags & 1) {
                    active = 1;
                    amount += paired_child->amount;
                    target = child->object->data;
                }
            }
            if (active && func_0813522C(base, target, action, 0, amount,
                                        child->options))
                return 1;
        }
    } else {
        s32 children;
        s32 j;
        s32 k;

        for (j = 0; j < count; j++) {
            group = func_080A88EC(collection, j);
            children = func_080A8830(group);
            info = func_080A880C(group);
            if (!(info->flags & 0x6000) && info->action != action)
                continue;
            if (info->object == 0)
                continue;
            if (info->object->data != base)
                continue;
            if (info->kind == 9)
                continue;
            if (info->kind == 11 || info->kind == 12)
                continue;
            if (override_mode)
                action = 0x21;
            for (k = 0; k < children; k++) {
                child = func_080A8810(group, k);
                if (child->object == 0)
                    continue;
                target = child->object->data;
                if (child->flags & 0x40)
                    continue;
                if (!(child->flags & 0x80))
                    continue;
                amount = 0;
                if (child->flags & 1)
                    amount = child->amount;
                if (func_0813522C(base, target, action, 0, amount,
                                  child->options))
                    return 1;
            }
        }
    }
    return 0;
}
