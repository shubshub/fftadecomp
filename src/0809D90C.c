#include "ffta.h"

typedef struct {
    u32 field_00;
    u8 unknown_04[0x928];
} Object0809D90C;

typedef void (*BufferInitializer0809D90C)(void *destination, u32 size);

extern void *func_08022840(u32 size);
extern BufferInitializer0809D90C const g_callbacks_0836D4B8[];
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer0809D90C callback);

/* Target [0x0809D90C, 0x0809D938), 44 complete bytes:
 * 70b5061c074d281c84f794ff041c06480268201c291ca4f093fc
 * 2660201c70bc02bc08472c090000b8d43608
 */
Object0809D90C *func_0809D90C(u32 value)
{
    u32 size = sizeof(Object0809D90C);
    Object0809D90C *object = func_08022840(size);

    func_0814224C(object, size, g_callbacks_0836D4B8[0]);
    object->field_00 = value;
    return object;
}
