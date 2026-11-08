#include "ffta.h"

/* func_08128898 [0x08128898,0x081288C8) 48 bytes
 * raw: 10b587b01b061b0e00248471019068468182c2820383054834216a460023f9f769f907b010bc01bc00470000c5871208 */

typedef struct Object128898 {
    u8 unknown_00[6];
    u8 active;
    u8 unknown_07;
    void *parent;
} Object128898;

typedef struct Payload128898 {
    u32 unknown_00;
    Object128898 *object;
    u32 unknown_08[3];
    u16 first;
    u16 second;
    u16 third;
    u16 unknown_1A;
} Payload128898;

extern int func_081287C4(void *, void *, void *);
extern void *func_08121B8C(int (*)(void *, void *, void *),
    unsigned short, const Payload128898 *, void *);

void func_08128898(Object128898 *object, u16 first, u16 second, u8 third)
{
    Payload128898 payload;

    object->active = 0;
    payload.object = object;
    payload.first = first;
    payload.second = second;
    payload.third = third;
    func_08121B8C(func_081287C4, 0x34, &payload, 0);
}
