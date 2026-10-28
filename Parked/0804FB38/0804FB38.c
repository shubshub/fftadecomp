#include "ffta.h"

/* 0x0804FB38..0x0804FB84: 76 bytes / 31 instructions. */
struct Entry0804FB38 {
    u8 id;
};

struct State0804FB38 {
    u8 unknown_00[0x424];
    struct Entry0804FB38 *entries[0];
};

struct Object0804FB38 {
    struct State0804FB38 *state;
};

struct Definition0804FB38 {
    u8 unknown_00[2];
    u8 resource;
    u8 unknown_03[13];
};

extern const struct Definition0804FB38 g_table_08521214[];
extern u8 func_080CB99C(u32 resource);

u32 func_0804FB38(struct Object0804FB38 *object, u32 index)
{
    struct Entry0804FB38 *entry = object->state->entries[index];
    const struct Definition0804FB38 *definition;
    u32 resource;

    if (entry == 0)
        return 0;
    definition = &g_table_08521214[entry->id];
    if (definition->resource != 0)
        resource = definition->resource + 0x18A;
    else
        resource = 0;
    return func_080CB99C(resource) + 13;
}
