#include "ffta.h"

typedef struct {
    u8 unknown_00[0xf1];
    u8 count;
} Parent08132A98;

typedef struct {
    u8 unknown_00[0x18];
    u16 field_18;
    u8 unknown_1a[0xd8];
    u8 count;
} Child08132A98;

typedef struct {
    Parent08132A98 *parent;
    u32 unknown_04;
    Child08132A98 *child;
    u8 unknown_0c[0x1a];
    u16 flags;
} Object08132A98;

typedef struct {
    u8 unknown_0000[0x3c2b];
    u8 count;
} Global08132A98;

extern Global08132A98 g_state_02000000;
extern u8 func_080CD8FC(const void *);
extern u8 func_080CD8CC(const void *);
extern u8 func_080C8240(const void *);
extern void func_080CDD88(void *, u8);
extern void func_08097298(void *);
extern void func_08131DD4(void *, s32);

/* Complete [0x08132A98, 0x08132B44): 172 bytes, 75 instructions. */
void func_08132A98(Object08132A98 *object)
{
    u32 count;
    u16 blocked;

    if (object->flags & 0x10)
        return;

    if (func_080CD8FC(object->child)) {
        if (!(object->flags & 0x10)) {
            func_080CDD88(object->child, 0);
            object->flags |= 0x100;
        }
    } else {
        func_08131DD4(object, 0);
        blocked = object->flags & 0x10;
        if (!blocked) {
            object->child->field_18 = 0;
            count = object->parent->count;
            if (count < 255)
                count++;
            object->parent->count = count;

            if (!func_080CD8CC(object->child)) {
                count = object->child->count;
                if (count < 255)
                    count++;
                object->child->count = count;
                if (func_080C8240(object->child))
                    g_state_02000000.count++;
            }
            func_08097298(object->child);
        }
    }
}
