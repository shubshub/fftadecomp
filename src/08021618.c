#include "ffta.h"

// 0x08021618..0x080216F8: 224 bytes, 102 instructions, including the
// literal word for g_callbacks_0836D4B8.

typedef struct {
    u8 unknown_00[4];
} ResourceFrame08021618;

typedef struct {
    u16 length;
    u16 unknown_02;
    ResourceFrame08021618 frames[0];
} Resource08021618;

typedef struct {
    u32 flags;
    u16 unknown_04;
    u16 category;
    u16 selector;
    u16 position;
    s16 frame;
    u16 limit;
    u8 active;
    u8 unknown_11;
    u16 first;
    u16 unknown_14;
    u16 second;
    u8 unknown_18[8];
    s32 counter;
    u8 unknown_24[8];
    u32 unknown_2C;
    u8 unknown_30[4];
    const ResourceFrame08021618 *start;
    const ResourceFrame08021618 *cursor;
    u8 unknown_3C[0x0C];
} ResourceState08021618;

typedef struct {
    void *allocator;
    u8 unknown_04[4];
    void *list;
} Pool08021618;

typedef struct {
    u8 unknown_00[4];
    void *list;
    Pool08021618 *pool;
} Owner08021618;

typedef void (*BufferInitializer08021618)(void *destination, u32 size);

extern BufferInitializer08021618 const g_callbacks_0836D4B8[];
extern const u8 *func_08021004(u32 category, u32 selector);
extern void func_08021C84(ResourceState08021618 *state, u16 first, s32 second);
extern s32 func_08021C90(void *state, u32 alternate, s32 step);
extern void *func_08007138(void *owner, u32 byte_count);
struct ListNode;
extern struct ListNode *func_080C7A74(void *list, void *value);

static inline ResourceState08021618 *new_state(Owner08021618 *owner)
{
    Pool08021618 *pool = owner->pool;
    ResourceState08021618 *state = func_08007138(pool->allocator, sizeof(*state));

    g_callbacks_0836D4B8[0](state, sizeof(*state));
    func_080C7A74(pool->list, state);
    func_080C7A74(owner->list, state);
    return state;
}

ResourceState08021618 *func_08021618(Owner08021618 *owner,
                                     ResourceState08021618 *state,
                                     u32 alternate, s32 second,
                                     u32 category, u32 selector, u32 index)
{
    const Resource08021618 *const *resources =
        (const Resource08021618 *const *)func_08021004(category, selector);
    const Resource08021618 *resource;
    const ResourceFrame08021618 *frames;
    s32 first;
    s32 variant;

    if (resources[index] == 0)
        return (ResourceState08021618 *)-1;

    if (state != 0) {
        second = state->second;
        func_08021C84(state, state->first, second);
    } else {
        first = func_08021C90(owner->pool, alternate, second);
        if (first < 0)
            return 0;
        state = new_state(owner);
        func_08021C84(state, first, second);
    }

    resource = resources[index];
    state->flags = 0x45;
    state->position = 0;
    state->frame = 0;
    state->limit = resource->length;
    frames = resource->frames;
    state->start = frames;
    state->cursor = frames;
    state->counter = -1;
    state->active = 0;
    state->unknown_2C = 0;
    state->category = category;
    state->selector = selector;

    variant = selector & 3;
    switch (variant) {
    case 2:
    case 3:
        state->flags = 0x65;
        break;
    }
    return state;
}
