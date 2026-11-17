#include "ffta.h"

// Complete target [0x08098CE8,0x08098E7A): 402 bytes, 201 instructions.
typedef struct ListNode08098CE8 ListNode08098CE8;
typedef struct List08098CE8 List08098CE8;
typedef struct Object08098CE8 Object08098CE8;

typedef struct {
    u32 count;
    void **cursor;
} State08098CE8;

typedef u32 (*ValueCallback08098CE8)(void *value, State08098CE8 *argument);

typedef struct {
    State08098CE8 *argument;
    ValueCallback08098CE8 callback;
} Closure08098CE8;

typedef struct {
    u8 unknown_00[0x10];
    List08098CE8 *first;
    List08098CE8 *second;
    List08098CE8 *third;
} ListOwner08098CE8;

typedef struct {
    u8 unknown_000[0x104];
    u8 order;
} Unit08098CE8;

struct Object08098CE8 {
    Unit08098CE8 *unit;
    u8 unknown_04[0x20];
    s32 key;
    u8 unknown_28[0x58];
    ListOwner08098CE8 *owner;
};

typedef struct {
    u8 unknown_00[0x10];
    List08098CE8 *list;
} Context08098CE8;

extern u32 func_0809ABE8(ListNode08098CE8 *node, Closure08098CE8 *closure);
extern u32 func_0809AC20(void *value, State08098CE8 *state);
extern void func_080C7CC0(List08098CE8 *list,
                          u32 (*callback)(ListNode08098CE8 *, Closure08098CE8 *),
                          Closure08098CE8 *closure);
extern void func_080971F8(Object08098CE8 *object);
extern u8 func_080C8298(const Unit08098CE8 *unit);
extern u8 func_080C8240(const Unit08098CE8 *unit);
extern ListNode08098CE8 *func_080C7BF4(List08098CE8 *list, Object08098CE8 *object);
extern ListNode08098CE8 *func_080C7A74(List08098CE8 *list, Object08098CE8 *object);
extern void *func_080C7AB4(List08098CE8 *list, Object08098CE8 *object, s32 key);

static inline u32 func_08098CE8_collect(Context08098CE8 *context, Object08098CE8 **out)
{
    State08098CE8 state;
    Closure08098CE8 closure;
    ValueCallback08098CE8 callback;

    state.count = 0;
    state.cursor = (void **)out;
    callback = func_0809AC20;
    closure.argument = &state;
    closure.callback = callback;
    func_080C7CC0(context->list, func_0809ABE8, &closure);
    return state.count;
}

void func_08098CE8(Context08098CE8 *context)
{
    Object08098CE8 *objects[13];
    s32 count;
    s32 i;
    s32 j;

    count = func_08098CE8_collect(context, objects);

    for (i = 0; i < count; i++)
        func_080971F8(objects[i]);

    for (i = 0; i < count - 1; i++) {
        for (j = i + 1; j < count; j++) {
            if (objects[i]->unit->order >= objects[j]->unit->order) {
                Object08098CE8 *swap = objects[i];
                objects[i] = objects[j];
                objects[j] = swap;
            }
        }
    }

    for (i = 0; i < count; i++) {
        Object08098CE8 *object;

        if (func_080C8298(objects[i]->unit)) {
            object = objects[i];
            if (!func_080C7BF4(object->owner->first, object)) {
                func_080C7A74(object->owner->first, object);
                func_080C7AB4(object->owner->first, object, object->key);
            }
        } else if (func_080C8240(objects[i]->unit)) {
            object = objects[i];
            if (!func_080C7BF4(object->owner->first, object)) {
                func_080C7A74(object->owner->first, object);
                func_080C7AB4(object->owner->first, object, object->key);
            }
            if (!func_080C7BF4(object->owner->third, object)) {
                func_080C7A74(object->owner->third, object);
                func_080C7AB4(object->owner->third, object, object->key);
            }
        } else {
            object = objects[i];
            if (!func_080C7BF4(object->owner->first, object)) {
                func_080C7A74(object->owner->first, object);
                func_080C7AB4(object->owner->first, object, object->key);
            }
            if (!func_080C7BF4(object->owner->second, object)) {
                func_080C7A74(object->owner->second, object);
                func_080C7AB4(object->owner->second, object, object->key);
            }
        }
    }
}
