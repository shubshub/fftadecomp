#include "ffta.h"

/* func_081263B0 [0x081263B0,0x081263DC) 44 bytes
 * raw: 00b587b0021c0906090e0020907101926846818204489368b4216a46fbf7defb07b001bc00470000e95d1208 */
typedef struct Object1263B0 {
    u8 unknown_00[6];
    u8 active;
    u8 unknown_07;
    void *parent;
} Object1263B0;

typedef struct Payload1263B0 {
    u32 unknown_00;
    Object1263B0 *object;
    u32 unknown_08[3];
    u16 value;
    u16 unknown_16;
    u32 unknown_18;
} Payload1263B0;

extern int func_08125DE8(void *, void *, void *);
extern void *func_08121B8C(int (*)(void *, void *, void *),
    unsigned short, const Payload1263B0 *, void *);

void func_081263B0(Object1263B0 *object, u8 value)
{
    Payload1263B0 payload;

    object->active = 0;
    payload.object = object;
    payload.value = value;
    func_08121B8C(func_08125DE8, 0xB4, &payload, object->parent);
}
