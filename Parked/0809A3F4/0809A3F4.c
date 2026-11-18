#include "ffta.h"

typedef struct {
    u32 duration;
    const void *graphics;
} AnimationFrame;

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

typedef struct ListNode ListNode;
typedef struct {
    u8 unknown_00[4];
    ListNode *head;
} ListContext;
struct State08021E7C;

typedef struct {
    u8 unknown_00[8];
    struct State08021E7C *display;
    u8 unknown_0C[4];
    ListContext *objects;
    u8 unknown_14[0x10];
    u32 flags;
    s8 timer;
    u8 unknown_29[0x394 - 0x29];
    AnimationSlot slots[2];
} Scene;

typedef struct {
    void *argument;
    u32 (*callback)(void *value, void *argument);
} CallbackContext;

extern const AnimationFrame data_083915CC[];
extern u32 func_08097A04(void *object, void *scene);
extern u32 func_0809ABE8(ListNode *node, void *descriptor);
extern void func_080C7CC0(ListContext *list,
                          u32 (*callback)(ListNode *, void *), void *descriptor);
extern void func_08021E7C(struct State08021E7C *display);

void func_0809A3F4(void *context)
{
    Scene *scene = context;
    CallbackContext visitor;
    u32 (*callback)(void *, void *);
    int i;

    if (--scene->timer <= 0) {
        scene->timer = 16;
        scene->flags ^= 4;
    }
    callback = func_08097A04;
    visitor.argument = scene;
    visitor.callback = callback;
    func_080C7CC0(scene->objects, func_0809ABE8, &visitor);
    for (i = 0; i < 2; i++) {
        AnimationSlot *slot = &scene->slots[i];

        if (slot->flags & 1) {
            slot->elapsed++;
            if (slot->elapsed > data_083915CC[slot->frame].duration) {
                slot->elapsed = 0;
                if (++slot->frame > 3)
                    slot->flags &= ~1;
            }
        }
    }
    func_08021E7C(scene->display);
}
