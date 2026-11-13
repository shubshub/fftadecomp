#include "ffta.h"

// Complete [0x08127BC4, 0x08127C10): 76 bytes including callback literal.
// The eight-byte argument struct arrives by value in r1/r2.

typedef struct {
    u8 unknown_00[6];
    u8 complete;
    u8 unknown_07;
    void *parent;
} Owner08127BC4;

typedef struct {
    u8 first;
    u8 second;
    s16 unknown_02;
    s16 unknown_04;
    u16 third;
} Args08127BC4;

typedef struct {
    u32 unknown_00;
    Owner08127BC4 *owner;
    s32 unknown_08;
    s32 unknown_0C;
    u32 unknown_10;
    u16 first;
    u16 second;
    u16 third;
    u16 unknown_1A;
} Request08127BC4;

typedef u32 (*TaskCallback08127BC4)(void *, void *, void *);
extern u32 func_08127990(void *, void *, void *);
extern void *func_08121B8C(TaskCallback08127BC4, u16, void *, void *);

void func_08127BC4(Owner08127BC4 *owner, Args08127BC4 args)
{
    Request08127BC4 request;

    owner->complete = 0;
    request.owner = owner;
    request.unknown_08 = args.unknown_02;
    request.unknown_0C = args.unknown_04;
    request.first = args.first;
    request.second = args.second | 0x80;
    request.third = args.third;
    func_08121B8C(func_08127990, 0x140, &request, owner->parent);
}
