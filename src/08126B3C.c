#include "ffta.h"

/* Complete [0x08126B3C, 0x08126B6C): 48 bytes including callback literal.
 * Target: 00b587b00006000e0906090e1206120e6b4698826846c1820283044848216a460023fbf715f807b001bc004711691208
 */
typedef struct {
    u32 unknown_00[5];
    u16 first;
    u16 second;
    u16 third;
    u16 unknown_1a;
} Request126B3C;

typedef u32 (*TaskCallback126B3C)(void *, void *, void *);
extern u32 func_08126910(void *, void *, void *);
extern void *func_08121B8C(TaskCallback126B3C, u16, Request126B3C *, void *);

void func_08126B3C(u8 first, u8 second, u8 third)
{
    Request126B3C request;
    request.first = first;
    request.second = second;
    request.third = third;
    func_08121B8C(func_08126910, 0x48, &request, 0);
}
