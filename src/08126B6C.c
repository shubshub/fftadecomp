#include "ffta.h"

typedef struct {
    u32 unknown_00;
    void *owner;
    u32 unknown_08;
    u32 unknown_0c;
    u32 unknown_10;
    u16 first;
    u16 second;
    u16 third;
    u16 unknown_1a;
} Request08126B6C;

typedef u32 (*TaskCallback08126B6C)(void *, void *, void *);
extern u32 func_081269E4(void *, void *, void *);
extern void *func_08121B8C(TaskCallback08126B6C, u16, void *, void *);

/* Complete body 0x08126B6C..0x08126B9C: 48 bytes including callback literal. */
void func_08126B6C(void *owner, u8 first, u8 second, u8 third)
{
    Request08126B6C request;
    request.owner = owner;
    request.first = first;
    request.second = second;
    request.third = third;
    func_08121B8C(func_081269E4, 52, &request, 0);
}
