#include "ffta.h"

typedef struct ListContext08021B9C ListContext08021B9C;
typedef struct ListNode08021B9C ListNode08021B9C;

typedef struct ListOwner08021B9C {
    void *allocator;
    ListContext08021B9C *first;
    ListContext08021B9C *second;
} ListOwner08021B9C;

typedef struct ListObject08021B9C {
    u32 unknown_00;
    ListContext08021B9C *children;
    ListOwner08021B9C *parent;
} ListObject08021B9C;

typedef struct Object08021B9C {
    u8 unknown_00[0x48];
} Object08021B9C;

typedef void (*BufferInitializer08021B9C)(void *destination, u32 size);

extern void *func_08007138(void *allocator, u32 size);
extern ListNode08021B9C *func_080C7A74(ListContext08021B9C *list, void *value);
extern BufferInitializer08021B9C const g_callbacks_0836D4B8[];

/* Complete [0x08021B9C, 0x08021BD4): 56 bytes, 22 instructions. */
Object08021B9C *func_08021B9C(ListObject08021B9C *context)
{
    ListOwner08021B9C *parent = context->parent;
    Object08021B9C *object =
        func_08007138(parent->allocator, sizeof(*object));

    g_callbacks_0836D4B8[0](object, sizeof(*object));
    func_080C7A74(parent->second, object);
    func_080C7A74(context->children, object);
    return object;
}
