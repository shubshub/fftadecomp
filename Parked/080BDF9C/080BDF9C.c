#include "ffta.h"

/* 0x080BDF9C: 216 bytes. */
typedef struct {
    u16 id;
    u8 unknown_02[0xA];
    s16 value;
    u8 unknown_0E[6];
} Action;

typedef struct {
    void *object;
    Action actions[40];
    u16 count;
    u16 unknown_326;
} Group;

typedef struct {
    Group groups[13];
    u16 count;
} Collection;

typedef struct {
    void *source;
    void *target;
    u16 action_id;
    u16 unknown_0A;
    Collection *first;
    Collection *second;
    u8 unknown_14[0x14];
    u8 direction;
} ActionContext;

s32 func_080CCD50(u16 action_id, u32 selector);

s32 func_080BDF9C(ActionContext *context)
{
    Collection *collection;
    Group *group;
    Action *action;
    void *object;
    u16 action_id;


    if (context->action_id == 0 || !func_080CCD50(context->action_id, 11)) {
        if (context->source == context->target)
            return 0;
    }

    collection = context->first;
    object = context->target;
    group = 0;
    action_id = context->action_id;
    {
        s32 i;
        s32 count = collection->count;
        Group *cursor = collection->groups;

        for (i = 0; i < count; i++, cursor++) {
            if (cursor->object == object) {
                group = cursor;
                break;
            }
        }
    }
    if (group == 0) {
        collection = context->second;
        {
            s32 i;
            s32 count = collection->count;
            Group *cursor = collection->groups;

            for (i = 0; i < count; i++, cursor++) {
                if (cursor->object == object) {
                    group = cursor;
                    break;
                }
            }
        }
    }

    action = 0;
    {
        s32 i;
        s32 count = group->count;

        for (i = 0; i < count; i++) {
            if (group->actions[i].id == action_id) {
                action = &group->actions[i];
                break;
            }
        }
    }
    if (action == 0)
        return 0;

    if (context->direction) {
        if (action->value > 0)
            return 0;
    } else {
        if (action->value < 0)
            return 0;
    }
    return 1;
}
