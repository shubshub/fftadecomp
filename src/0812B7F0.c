#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
} Owner0812B7F0;

typedef struct {
    u8 unknown_00[8];
    s16 x;
    s16 y;
    s16 z;
    u8 unknown_0e[0x22];
    u32 flags;
} Entity0812B7F0;

typedef struct {
    u16 event;
    u8 unknown_02[2];
    Owner0812B7F0 *owner;
    u8 unknown_08[0x0C];
    u8 selector;
} Descriptor0812B7F0;

typedef struct {
    Owner0812B7F0 *owner;
    Entity0812B7F0 *entries[13];
    Entity0812B7F0 *current;
    void *child;
    u8 frame;
    u8 count;
    u8 index;
} Payload0812B7F0;

extern void *func_081255C8(u8 selector);
extern void *func_080D3508(u16 resource, void *context, u32 variant);
extern u8 func_080E2BDC(void *object);
extern void func_08141520(u16 value);
extern void func_080E2C00(void *object, s16 x, s16 y, s16 z,
                        u8 effect, u8 argument);
extern u8 func_080D3878(const void *object);
extern void func_080D3864(void *object);

/* Complete [0812B7F0,0812B980): 400 bytes, including middle literals. */
u32 func_0812B7F0(void *task, Descriptor0812B7F0 *descriptor,
                  Payload0812B7F0 *payload)
{
    switch (descriptor->event) {
    case 0:
        payload->owner = descriptor->owner;
        payload->current = func_081255C8(descriptor->selector);
        payload->count = 1;
        payload->index = 0;
        payload->child = func_080D3508(0x15B, 0, 0);
        break;
    case 1:
        break;
    case 0x100:
        if (func_080E2BDC(payload->child))
            descriptor->event = 0x101;
        break;
    case 0x101:
        func_08141520(0xDD);
        payload->frame = 0;
        descriptor->event = 0x102;
        break;
    case 0x102:
        {
            s8 effect = -1;

            payload->current->flags ^= 1;
            switch (payload->frame) {
            case 0:
                effect = 6;
                break;
            case 10:
                effect = 5;
                break;
            case 20:
                effect = 4;
                break;
            }
            if (effect >= 0)
                func_080E2C00(payload->child, payload->current->x,
                              payload->current->y, payload->current->z,
                              effect, 2);
            if (++payload->frame > 31) {
                payload->current->flags |= 1;
                descriptor->event = 0x103;
            }
        }
        break;
    case 0x103:
        if (payload->count == 1)
            descriptor->event = 0x104;
        else if (++payload->index == payload->count)
            descriptor->event = 0x104;
        else {
            payload->current = payload->entries[payload->index];
            descriptor->event = 0x101;
        }
        break;
    case 0x104:
        if (func_080D3878(payload->child)) {
            func_080D3864(payload->child);
            payload->child = 0;
            descriptor->event = 0x105;
        }
        break;
    case 0x105:
        payload->owner->complete = 1;
        descriptor->event = 3;
        break;
    }
    return 0;
}
