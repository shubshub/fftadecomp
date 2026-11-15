/* Target 0x080DC34C..0x080DC414, 200 bytes including the literal at 0x080DC410:
 * f0b557464e464546e0b488b0051c1098119c0906090e07911204120c90461b041b0c
 * 99460004000c82462406240e281c00f0e8ff06a96a461932bdf73dfc071c281c00f0
 * dfffbdf72ffc0604281cbdf739fc0006010eff2c08d04801194a8018610189181022
 * 65f05bfa211c42461004001400904a46100400140190524610040014029030140390
 * 049106200590381c00210022079b34f7b1ff041c06a80178201c34f793fe68461930
 * 0178201c34f791fe201c08b038bc9846a146aa46f0bc02bc0847603a0003
 */
#include "ffta.h"

struct ValueOwner;

extern u16 data_03003A60[][16];

extern void *func_080DD350(void *object);
extern u32 func_08099C04(const struct ValueOwner *owner, u8 *first, u8 *second);
extern u16 func_08099BF4(void *object);
extern u8 func_08099C10(const void *object);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern u32 func_08011348(u32, u32, u16, u8, s16, s16, s16, s16, s16, u16);
extern void func_08011118(void *object, u8 value);
extern void func_08011120(void *object, u8 value);

/* An inlined copy of func_080DBD30 (src/080DBD30.c). */
static inline u32 inlined_080DBD30(void *object, u8 *first, u8 *second)
{
    return func_08099C04(func_080DD350(object), first, second);
}

/* An inlined copy of func_080DBD48 (src/080DBD48.c). */
static inline u16 inlined_080DBD48(void *object)
{
    return func_08099BF4(func_080DD350(object));
}

void *func_080DC34C(void *source, u8 layer, s16 x, s16 y, s16 z, u8 palette)
{
    u8 first;
    u8 second;
    u32 resource;
    u16 frame;
    u8 current;
    void *object;

    resource = inlined_080DBD30(source, &first, &second);
    frame = inlined_080DBD48(source);
    current = func_08099C10(source);
    if (palette != 0xFF) {
        func_0814186C(data_03003A60[current], data_03003A60[palette], 16);
        current = palette;
    }
    object = (void *)func_08011348(resource, 0, 0, layer, x, y, z, (s16)frame,
                                   current, 6);
    func_08011118(object, first);
    func_08011120(object, second);
    return object;
}
