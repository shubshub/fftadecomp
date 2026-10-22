#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    void *parent;
} TaskLinkPrefix;

void *func_08005BF8(const void *object)
{
    return ((const TaskLinkPrefix *)object)->parent;
}
