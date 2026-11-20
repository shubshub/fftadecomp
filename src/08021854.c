#include "object_list.h"

typedef struct {
    u16 lower, upper;
} TileRange;

typedef struct Node080C7E68 TreeNode;

typedef struct {
    ListContext list;
    TreeNode *root;
} SpriteCollection;

typedef struct {
    void *allocator;
    SpriteCollection *first;
    SpriteCollection *sprites;
    TileRange primary;
    TileRange alternate;
} SpriteOwner;

typedef struct {
    u32 key, value;
} TreePair;

struct Node080C7E68 {
    TreePair pair;
    TreeNode *parent, *left, *right;
    u32 flags;
};

typedef struct {
    u8 unknown_00[0x12];
    u16 tile;
    u16 saved_tile;
} Sprite;

/* Each slot starts as a tree node pointer and is replaced with its sprite value. */
typedef union {
    TreeNode **nodes;
    u32 *values;
} SpriteEntries;

typedef struct {
    TileRange range;
    SpriteEntries entries;
    u32 *cursor;
    s32 processed;
    s32 count;
    u8 flags;
    u8 unknown_15[3];
    SpriteOwner *owner;
} SpriteSelection;

typedef struct {
    const TileRange *range;
    SpriteCollection *destination;
} RangeFilter;

typedef void (*BufferInitializer)(void *, u32);

extern BufferInitializer const g_callbacks_0836D4B8[];
extern void *func_08007138(void *allocator, u32 bytes);
extern void func_08007170(void *allocator, u8 *object);
extern void func_080C79E0(SpriteCollection *context);
extern u32 func_080C7B08(ListContext *context);
extern s32 func_080C7B20(SpriteCollection *context);
extern u32 func_080C7B9C(SpriteCollection *context, TreeNode **nodes);
extern void func_080C7B78(const TreePair *source, u32 *value, u32 *key);
extern u32 func_08022164(ListNode *node, void *payload);

/* [0x08021854, 0x0802192C), 216 bytes. Collect active sprites in tile order. */
void *func_08021854(void *object, u32 alternate)
{
    SpriteOwner *owner = object;
    SpriteSelection *selection;
    RangeFilter filter;
    u32 key;
    s32 count, i;
    u32 *cursor;

    func_080C79E0(owner->sprites);
    count = func_080C7B08(&owner->sprites->list);
    if (count == 0)
        return 0;

    selection = func_08007138(owner->allocator, sizeof(*selection));
    g_callbacks_0836D4B8[0](selection, sizeof(*selection));
    selection->owner = owner;
    if (alternate) {
        selection->range.lower = owner->alternate.lower;
        selection->range.upper = owner->alternate.upper;
    } else {
        selection->range.lower = owner->primary.lower;
        selection->range.upper = owner->primary.upper;
    }
    filter.range = &selection->range;
    filter.destination = owner->sprites;
    func_080C7CC0(&owner->sprites->list, func_08022164, &filter);

    count = func_080C7B20(owner->sprites);
    selection->count = count;
    if (count <= 0) {
        func_080C79E0(owner->sprites);
        func_08007170(owner->allocator, (u8 *)selection);
        return 0;
    }

    selection->entries.nodes = func_08007138(owner->allocator,
                                             count * sizeof(TreeNode *));
    func_080C7B9C(owner->sprites, selection->entries.nodes);
    for (i = 0; i < count; i++) {
        func_080C7B78(&selection->entries.nodes[i]->pair,
                      &selection->entries.values[i], &key);
    }
    func_080C79E0(owner->sprites);
    selection->cursor = selection->entries.values;
    cursor = selection->entries.values;
    for (i = 0; i < selection->count; i++) {
        Sprite *sprite = (Sprite *)*cursor++;
        sprite->saved_tile = sprite->tile;
    }
    return selection;
}
