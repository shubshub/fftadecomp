#include "ffta.h"

/* func_0812640C [0x0812640C,0x08126430) 36 bytes
 * raw: 00b587b000218171019005498368081cb4216a46fbf7b4fb07b001bc0047000019611208 */
typedef struct Object12640C {
    u8 unknown_00[6];
    u8 active;
    u8 unknown_07;
    void *parent;
} Object12640C;

typedef struct Payload12640C {
    u32 unknown_00;
    Object12640C *object;
    u32 unknown_08[5];
} Payload12640C;

extern int func_08126118(void *, void *, void *);
extern void *func_08121B8C(int (*)(void *, void *, void *),
    unsigned short, const Payload12640C *, void *);

void func_0812640C(Object12640C *object)
{
    Payload12640C payload;

    object->active = 0;
    payload.object = object;
    func_08121B8C(func_08126118, 0xB4, &payload, object->parent);
}
