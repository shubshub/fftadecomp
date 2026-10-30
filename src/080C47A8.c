#include "ffta.h"

typedef struct {
    u8 unknown_00[8];
    u8 unknown_08[0x50];
    u16 field_58;
    u8 unknown_5a[0x521C];
    u8 field_5276[8];
    u8 field_527e;
    u8 unknown_527f[0x405];
} Object080C47A8;

typedef void (*BufferInitializer080C47A8)(void *destination, u32 size);

extern void *func_08022840(u32 size);
extern BufferInitializer080C47A8 const g_callbacks_0836D4B8[];
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer080C47A8 callback);
extern void func_080C1EB4(Object080C47A8 *object, u32 value);
extern u32 func_080C1C38(void *region, u16 value, u8 *output);

/* Complete target: [0x080C47A8, 0x080C47FC), 84 bytes. */
Object080C47A8 *func_080C47A8(u32 value)
{
    u32 size = sizeof(Object080C47A8);
    Object080C47A8 *object = func_08022840(size);

    func_0814224C(object, size, g_callbacks_0836D4B8[0]);
    func_080C1EB4(object, value);
    object->field_527e = func_080C1C38(object->unknown_08,
                                      object->field_58,
                                      object->field_5276);
    return object;
}
