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
    u32 (*callback)(void *, void *);
} Visitor;

/* Two words per frame, a duration and a graphics pointer; func_0809A48C
 * reads the second word of each pair. */
typedef union {
    u32 duration;
    const void *graphics;
} FrameWord;

extern const FrameWord data_083915CC[8];
extern u32 func_08097A04(void *, void *);
extern u32 func_0809ABE8(ListNode *, void *);
extern void func_08021E7C(struct State08021E7C *display);

/* Advances one animation slot by a tick; past the last of its four frames
 * the slot goes inactive.  The slot pointer is formed per call, scene plus
 * scaled index and then the 0x394 array offset (0x0809A42A-0x0809A432);
 * func_08097A04's start_slot is the matching helper that starts one. */
static inline void advance_slot(AnimationSlot *slot)
{
    if (slot->flags & 1) {
        slot->elapsed++;
        if (slot->elapsed > data_083915CC[slot->frame * 2].duration) {
            slot->elapsed = 0;
            if (++slot->frame > 3)
                slot->flags &= ~1;
        }
    }
}

/* Complete [0x0809A3F4, 0x0809A48C): 152 bytes, 67 instructions.
 * Target:
 * f0b582b0041c211c28310878013808700006002805dc10200870606a04214840
 * 60621a4800940190206919496a462df04dfc0026174f30010219e52080001218
 * 937a01201840002815d0d07a01300025d072d17a107bc000c019006881420ad9
 * d572107b013010730006000e032802d9fe20184090720136012edcdda06887f7
 * 03fd02b0f0bc01bc00470000057a0908e9ab0908cc153908
 */
void func_0809A3F4(void *context)
{
    Scene *scene = context;
    int i;
    Visitor visitor;
    u32 (*callback)(void *, void *);

    if (--scene->timer <= 0) {
        scene->timer = 16;
        scene->flags ^= 4;
    }
    callback = func_08097A04;
    visitor.argument = scene;
    visitor.callback = callback;
    func_080C7CC0(scene->objects, func_0809ABE8, &visitor);
    for (i = 0; i < 2; i++)
        advance_slot(&scene->slots[i]);
    func_08021E7C(scene->display);
}
