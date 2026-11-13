#include "ffta.h"

/* Complete [0x08127C54, 0x08127C94): 64 bytes including callback literal.
 * The eight-byte argument arrives by value in r1/r2. */
typedef struct {
    u8 unknown_00[6];
    u8 complete;
    u8 unknown_07;
    void *parent;
} Owner08127C54;

typedef struct {
    u8 first;
    u8 second;
    s16 value;
    u16 unknown_04;
    u16 third;
} Args08127C54;

typedef struct {
    u32 unknown_00;
    Owner08127C54 *owner;
    s32 value;
    u8 unknown_0C[8];
    u16 first;
    u16 second;
    u16 third;
    u16 unknown_1A;
} Request08127C54;

typedef u32 (*TaskCallback08127C54)(void *, void *, void *);
extern u32 func_08127A1C(void *, void *, void *);
extern void *func_08121B8C(TaskCallback08127C54, u16, void *, void *);

void func_08127C54(Owner08127C54 *owner, Args08127C54 args)
{
    Request08127C54 request;

    owner->complete = 0;
    request.owner = owner;
    request.value = args.value;
    request.first = args.first;
    request.second = args.second;
    request.third = args.third;
    func_08121B8C(func_08127A1C, 0x140, &request, owner->parent);
}
