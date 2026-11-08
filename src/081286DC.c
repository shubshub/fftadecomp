#include "ffta.h"

/* func_081286DC [0x081286DC,0x08128708) 44 bytes
 * raw: 00b587b00906090e0022827101906846818205488221c9006a460023f9f748fa07b001bc004700003d801208 */

typedef struct Object1286DC {
    u8 unknown_00[6];
    u8 active;
    u8 unknown_07;
    void *parent;
} Object1286DC;

typedef struct Payload1286DC {
    u32 unknown_00;
    Object1286DC *object;
    u32 unknown_08[3];
    u16 value;
    u16 unknown_16;
    u32 unknown_18;
} Payload1286DC;

extern int func_0812803C(void *, void *, void *);
extern void *func_08121B8C(int (*)(void *, void *, void *),
    unsigned short, const Payload1286DC *, void *);

void func_081286DC(Object1286DC *object, u8 value)
{
    Payload1286DC payload;

    object->active = 0;
    payload.object = object;
    payload.value = value;
    func_08121B8C(func_0812803C, 0x410, &payload, 0);
}
