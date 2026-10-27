#include "ffta.h"

typedef struct ListContext08021B1C ListContext08021B1C;
typedef struct ListNode08021B1C ListNode08021B1C;

typedef struct ListOwner08021B1C {
    void *allocator;
    ListContext08021B1C *first;
    ListContext08021B1C *second;
} ListOwner08021B1C;

typedef struct ListObject08021B1C {
    u32 unknown_00;
    ListContext08021B1C *children;
    ListOwner08021B1C *parent;
    u32 unknown_0C;
} ListObject08021B1C;

typedef void (*BufferInitializer08021B1C)(void *destination, u32 size);

extern void *func_08007138(void *allocator, u32 size);
extern ListContext08021B1C *func_080C799C(void *allocator);
extern ListNode08021B1C *func_080C7A74(ListContext08021B1C *list, void *value);
extern BufferInitializer08021B1C const g_callbacks_0836D4B8[];

/* Complete [0x08021B1C, 0x08021B54): 56 bytes, 22 instructions. */
ListObject08021B1C *func_08021B1C(ListOwner08021B1C *parent)
{
    ListObject08021B1C *object =
        func_08007138(parent->allocator, sizeof(*object));

    g_callbacks_0836D4B8[0](object, sizeof(*object));
    object->children = func_080C799C(parent->allocator);
    object->parent = parent;
    func_080C7A74(parent->first, object);
    return object;
}
