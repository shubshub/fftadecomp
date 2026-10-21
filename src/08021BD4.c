/* func_08021BD4 - 0x08021BD4, 52 bytes - MATCH
 *
 * 70b5 041c 0e1c a568 6068 a6f009f8 011c 6068
 * a5f025ff a868 311c a6f001f8 011c a868 a5f01dff
 * 2868 311c e5f7b7fa 70bc 01bc 0047
 *
 * Takes an object out of the two lists it is registered in and releases it.
 * The child holds one of the lists at +0x04 and its parent at +0x08; the
 * parent holds the other list at +0x08 and the allocation block the object
 * came from at +0x00.
 *
 * func_080C7BF4 finds the node holding the object in a list and
 * func_080C7A34 unlinks and frees that node; func_08007170 releases the
 * object itself.
 */

#include "ffta.h"

typedef struct ListNode {
    void *value;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

typedef struct {
    void *owner;
    ListNode *head;
} ListContext;

ListNode *func_080C7BF4(ListContext *context, void *value);
void func_080C7A34(ListContext *context, ListNode *node);
void func_08007170(void *owner, u8 *object);

typedef struct Parent {
    void *owner;
    u32 unknown_04;
    ListContext *list;
} Parent;

typedef struct {
    u32 unknown_00;
    ListContext *list;
    Parent *parent;
} Child;

void func_08021BD4(Child *child, void *object)
{
    Parent *parent = child->parent;
    ListNode *node;

    node = func_080C7BF4(child->list, object);
    func_080C7A34(child->list, node);
    node = func_080C7BF4(parent->list, object);
    func_080C7A34(parent->list, node);
    func_08007170(parent->owner, object);
}
