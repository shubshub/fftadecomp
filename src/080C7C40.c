#include "ffta.h"

typedef struct {
    s32 key;
    void *value;
} Node080C7C40;

void func_080C7C40(Node080C7C40 *node, void *value, s32 key)
{
    node->value = value;
    node->key = key;
}
