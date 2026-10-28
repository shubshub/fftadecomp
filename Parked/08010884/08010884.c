#include "ffta.h"

typedef struct Object {
    u8 unknown_00[0x14];
    u16 flags;
    u8 unknown_16[6];
    u8 category;
    u8 state;
    u8 unknown_1E[26];
    struct Object *previous;
    struct Object *next;
} Object;

extern Object *data_02009178;
extern Object *data_0200917C;
extern Object *data_02009174;
extern Object *data_02009180;
extern void func_080105C4(Object *object);

static inline u8 is_hidden(Object *object)
{
    if (object->state == 0)
        return 1;
    if (object->state == 1)
        return 1;
    if (object->flags & 0x80)
        return 1;
    return 0;
}

void func_08010884(Object *object, u8 hidden)
{
    Object **head;
    Object *previous;
    Object *next;

    if (hidden) {
        if (is_hidden(object))
            return;
        object->flags |= 0x80;
    } else {
        if (!is_hidden(object))
            return;
        object->flags &= 0xFF7F;
    }
    head = 0;
    switch (object->category) {
    case 0:
        head = &data_02009178;
        break;
    case 1:
        head = &data_0200917C;
        break;
    case 2:
        head = &data_02009174;
        break;
    case 3:
        head = &data_02009180;
        break;
    }
    previous = object->previous;
    next = object->next;
    if (previous)
        previous->next = next;
    else
        *head = next;
    if (next)
        next->previous = previous;
    func_080105C4(object);
}
