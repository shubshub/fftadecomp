#include "ffta.h"

typedef struct ListContext ListContext;
typedef struct ListNode ListNode;
typedef u32 (*ListCallback)(ListNode *node, void *payload);

typedef struct {
    void *allocator;
    ListContext *first;
    ListContext *second;
} ListOwner;

extern u32 func_080220B4(ListNode *node, void *payload);
extern u32 func_080220CC(ListNode *node, void *payload);
extern void func_080C7CC0(ListContext *list, ListCallback callback, void *payload);
extern void *func_080C7908(ListContext *list);
extern void func_08007170(void *allocator, void *allocation);

/* 08021AD0..08021B1C: 76 bytes. */
void *func_08021AD0(ListOwner *object)
{
    void *allocator;
    void *payload;

    func_080C7CC0(object->first, func_080220B4, 0);
    payload = object->allocator;
    func_080C7CC0(object->first, func_080220CC, payload);
    payload = object->allocator;
    func_080C7CC0(object->second, func_080220CC, payload);
    func_080C7908(object->second);
    func_080C7908(object->first);
    allocator = object->allocator;
    func_08007170(allocator, object);
    return allocator;
}
