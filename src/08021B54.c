#include "ffta.h"

typedef struct ListNode08021B54 ListNode08021B54;
typedef struct ListContext08021B54 ListContext08021B54;
typedef u32 (*ListCallback08021B54)(ListNode08021B54 *node, void *payload);

typedef struct {
    void *allocator;
    ListContext08021B54 *first;
    ListContext08021B54 *second;
} ListOwner08021B54;

typedef struct {
    u32 unknown_00;
    ListContext08021B54 *children;
    ListOwner08021B54 *parent;
} ListObject08021B54;

u32 func_08022104(ListNode08021B54 *node, void *payload);
u32 func_080220CC(ListNode08021B54 *node, void *payload);
void func_080C7CC0(ListContext08021B54 *list, ListCallback08021B54 callback,
                  void *payload);
void *func_080C7908(ListContext08021B54 *list);
ListNode08021B54 *func_080C7BF4(ListContext08021B54 *list, void *value);
void func_080C7A34(ListContext08021B54 *list, ListNode08021B54 *node);
void func_08007170(void *allocator, void *allocation);

void func_08021B54(ListObject08021B54 *object)
{
    ListOwner08021B54 *parent = object->parent;
    ListNode08021B54 *node;
    void *payload;

    func_080C7CC0(object->children, func_08022104, parent->second);
    payload = parent->allocator;
    func_080C7CC0(object->children, func_080220CC, payload);
    func_080C7908(object->children);
    node = func_080C7BF4(parent->first, object);
    func_08007170(parent->allocator, object);
    func_080C7A34(parent->first, node);
}
