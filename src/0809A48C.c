#include "object_list.h"

typedef struct {
    void *sprite;
    s16 x;
    s16 y;
    s16 z;
    u8 flags;
    u8 elapsed;
    u8 frame;
    u8 unknown_0D[3];
} AnimationSlot;

typedef struct {
    u8 unknown_00[0x10];
    ListContext *objects;
    u8 unknown_14[0x10];
    u32 flags;
    u8 unknown_28[0x394 - 0x28];
    AnimationSlot slots[2];
} Scene;

typedef struct {
    void *argument;
    u32 (*callback)(void *, void *);
} Visitor;

typedef union {
    u32 duration;
    const void *graphics;
} FrameWord;

extern const FrameWord data_083915CC[8];
extern const u8 *(*data_08394038[])(void *, const void *);
extern void (*data_08394040[])(void *, s32);
extern void func_0808EFCC(void *, s16, s16, s16);
extern u32 func_08097F04(void *, void *);
extern u32 func_0809ABE8(ListNode *, void *);

void func_0809A48C(void *context)
{
    Scene *scene = context;
    int i;
    Visitor visitor;
    u32 mask;
    u32 (*callback)(void *, void *);

    for (i = 0; i < 2; i++) {
        AnimationSlot *slot = &scene->slots[i];

        if (slot->flags & 1) {
            data_08394038[0](slot->sprite, data_083915CC[slot->frame * 2 + 1].graphics);
            data_08394040[0](slot->sprite, 1);
            func_0808EFCC(slot->sprite, slot->x, slot->y, slot->z);
        }
    }
    mask = 2;
    if (!(mask & scene->flags)) {
        scene->flags ^= 0x40;
        callback = func_08097F04;
        visitor.argument = scene;
        visitor.callback = callback;
        func_080C7CC0(scene->objects, func_0809ABE8, &visitor);
    }
}
