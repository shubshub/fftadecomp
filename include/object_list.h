#ifndef GUARD_OBJECT_LIST_H
#define GUARD_OBJECT_LIST_H

#include "ffta.h"

typedef struct {
    void *value;
} ListValue;

typedef struct ListNode {
    ListValue object;
    struct ListNode *prev;
    struct ListNode *next;
} ListNode;

typedef struct ListContext {
    void *owner;
    ListNode *head;
} ListContext;

typedef u32 (*ListCallback)(ListNode *node, void *payload);

void *func_080C7B74(const ListValue *object);
void func_080C7CC0(ListContext *context, ListCallback callback, void *payload);

#endif
