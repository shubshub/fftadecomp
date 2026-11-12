#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
    u8 unknown_07;
    void *parent;
} Owner08126AA8;

typedef struct {
    u32 unknown_00;
    Owner08126AA8 *owner;
    u32 unknown_08;
    u32 unknown_0C;
    u32 unknown_10;
    s16 first;
    u16 second;
    u16 third;
    u16 unknown_1A;
} Request08126AA8;

typedef u32 (*TaskCallback08126AA8)(void *, void *, void *);
extern u32 func_08126B9C(void *, void *, void *);
extern u32 func_081264B8(void *, void *, void *);
extern void *func_08121B8C(TaskCallback08126AA8, u16, void *, void *);

/* Complete [0x08126AA8, 0x08126B08): 96 bytes including two callback literals. */
void func_08126AA8(Owner08126AA8 *owner, const u8 *values, u8 mode)
{
    Request08126AA8 request;

    owner->complete = 0;
    if (values) {
        s32 upper = values[1] >> 4;
        s32 lower = values[1] & 15;
        request.owner = owner;
        request.first = upper - lower;
        request.second = values[2];
        request.third = values[3];
    } else {
        request.owner = owner;
    }
    if (mode)
        func_08121B8C(func_08126B9C, 8, &request, owner->parent);
    else
        func_08121B8C(func_081264B8, 8, &request, owner->parent);
}
