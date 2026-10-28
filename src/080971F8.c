#include "ffta.h"

typedef struct List List;
typedef struct ListEntry ListEntry;

typedef struct {
    u8 unknown_00[0x10];
    List *first;
    List *second;
    List *third;
} ListOwner;

typedef struct {
    u8 unknown_00[0x80];
    ListOwner *owner;
} Object;

extern ListEntry *func_080C7BF4(List *list, Object *object);
extern ListEntry *func_080C7C14(List *list, Object *object);
extern void func_080C7A34(List *list, ListEntry *entry);
extern void func_080C7A5C(List *list, ListEntry *entry);

void func_080971F8(Object *object)
{
    ListEntry *entry;

    entry = func_080C7BF4(object->owner->first, object);
    if (entry)
        func_080C7A34(object->owner->first, entry);
    entry = func_080C7C14(object->owner->first, object);
    if (entry)
        func_080C7A5C(object->owner->first, entry);

    entry = func_080C7BF4(object->owner->second, object);
    if (entry)
        func_080C7A34(object->owner->second, entry);
    entry = func_080C7C14(object->owner->second, object);
    if (entry)
        func_080C7A5C(object->owner->second, entry);

    entry = func_080C7BF4(object->owner->third, object);
    if (entry)
        func_080C7A34(object->owner->third, entry);
    entry = func_080C7C14(object->owner->third, object);
    if (entry)
        func_080C7A5C(object->owner->third, entry);
}
