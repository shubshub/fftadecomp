/* Target 0x080DC414..0x080DC498, 132 bytes including the literal at 0x080DC494:
 * 70b581b0041c0d1c1206160e00f096ff69466a460132bdf7ebfb011c281c34f783ff
 * 68460178281c34f76cfe684601300178281c34f76afe201c00f07fffbdf7cffb011c
 * 09040914281c34f777fe201cbdf7d4fb0006000eff2e08d04001084a801871018918
 * 102265f0f6f9301c01060916281c34f75afe01b070bc01bc0047603a0003
 */
#include "ffta.h"

struct ValueOwner;

extern u16 data_03003A60[][16];

extern void *func_080DD350(void *object);
extern u32 func_08099C04(const struct ValueOwner *owner, u8 *first, u8 *second);
extern u16 func_08099BF4(void *object);
extern void func_0801133C(void *object, u32 value);
extern void func_08011118(void *object, u8 value);
extern void func_08011120(void *object, u8 value);
extern void func_08011150(void *object, s16 value);
extern u8 func_08099C10(const void *object);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08011140(void *object, s8 value);

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

void func_080DC414(void *source, void *destination, u8 palette)
{
    u8 first;
    u8 second;
    u8 current;

    func_0801133C(destination, inlined_080DBD30(source, &first, &second));
    func_08011118(destination, first);
    func_08011120(destination, second);
    func_08011150(destination, inlined_080DBD48(source));
    current = func_08099C10(source);
    if (palette != 0xFF) {
        func_0814186C(data_03003A60[current], data_03003A60[palette], 16);
        current = palette;
    }
    func_08011140(destination, current);
}
