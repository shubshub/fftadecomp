#include "ffta.h"

// func_080DE33C [0x080DE33C,0x080DE390) 84 bytes
// 70b581b0061c0c1c151c2406240e2d062d0e0f496846042266f052f868006844018824062416301c221c0023baf700f880225200301c0021bcf7fcf8002d03d1301c0121bcf7d6f801b070bc01bc0047709b1408

/* Two halfwords, 1 and 9: the func_0809836C mode for each selector. */
extern const u16 g_object_08149B70[];
extern void *func_081443FC(void *, const void *, u32);
extern void func_0809836C(void *object, u32 mode, s8 value, u32 option);
extern void func_0809A570(void *object, u32 clear, u32 set);
extern void func_0809A530(void *object, u32 value);

void func_080DE33C(void *object, s8 value, u8 selector)
{
    u16 values[2];

    func_081443FC(values, g_object_08149B70, sizeof(values));
    func_0809836C(object, values[selector], value, 0);
    func_0809A570(object, 0, 0x100);
    if (selector == 0) {
        func_0809A530(object, 1);
    }
}
