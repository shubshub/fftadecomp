#include "ffta.h"

typedef struct Group Group;
typedef struct {
    u32 value;
} Child;

extern Child *func_080A8810(Group *group, s32 index);

/* 080DD4B4..080DD4C4: 16 bytes. */
u32 func_080DD4B4(Group *group, u8 index)
{
    return func_080A8810(group, index)->value;
}
