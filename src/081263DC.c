#include "ffta.h"

/* Complete [0x081263DC, 0x0812640C): 48 bytes including callback literal.
 * Target: 00b587b0031c0906090e1206120e00209871019368468182c28204489b68b4216a46fbf7c5fb07b001bc0047a95f1208
 */
typedef struct {
    u8 unknown_00[6];
    u8 complete;
    u8 unknown_07;
    void *parent;
} Owner1263DC;

typedef struct {
    u32 unknown_00;
    Owner1263DC *owner;
    u32 unknown_08[3];
    u16 first;
    u16 second;
    u32 unknown_18;
} Request1263DC;

typedef u32 (*TaskCallback1263DC)(void *, void *, void *);
extern u32 func_08125FA8(void *, void *, void *);
extern void *func_08121B8C(TaskCallback1263DC, u16, Request1263DC *, void *);

void func_081263DC(Owner1263DC *owner, u8 first, u8 second)
{
    Request1263DC request;
    owner->complete = 0;
    request.owner = owner;
    request.first = first;
    request.second = second;
    func_08121B8C(func_08125FA8, 0xb4, &request, owner->parent);
}
