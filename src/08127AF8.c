#include "ffta.h"

typedef struct {
    u8 unknown_00[6];
    u8 complete;
    u8 unknown_07;
    void *parent;
} Owner08127AF8;

typedef struct {
    u32 unknown_00;
    Owner08127AF8 *owner;
    u32 count;
    u32 mode;
    u32 unknown_10;
    u16 first;
    u16 second;
    u16 third;
    u16 unknown_1A;
} Request08127AF8;

typedef u32 (*TaskCallback08127AF8)(void *, void *, void *);
extern u32 func_08126FCC(void *, void *, void *);
extern void *func_08121B8C(TaskCallback08127AF8, u16, void *, void *);

/* Complete actual scheduler entry copies a 28-byte request; fields that the
 * target does not initialize remain unspecified here. The ordinary callback
 * interface is conditional, without external memory or effect claims.
 * Complete [0x08127AF8, 0x08127B40): 72 bytes including callback literal. */
void func_08127AF8(Owner08127AF8 *owner, u8 first, u8 second, u8 count,
                   u8 third, u8 mode)
{
    Request08127AF8 request;

    owner->complete = 0;
    request.owner = owner;
    request.count = count;
    request.mode = mode;
    request.first = first;
    request.second = second;
    request.third = third;
    func_08121B8C(func_08126FCC, 16, &request, owner->parent);
}
