#include "ffta.h"

/* 0x080DE2D0 - 88 bytes.
 * Target: f0b5041c0f1c151c2406240e60202cf7b9f9061c201c311c2a1cfef70dfd0006
 *         050e0024ac4211d2a100002f03d088190068b84205d0881900681f214156fff7
 *         b3ff601c0006040eac42edd3301c2cf7a3f9f0bc01bc0047
 */
typedef struct {
    u8 unknown_00[0x1F];
    s8 field_1f;
} Struct080DE2D0;

extern void *func_0800A654(u32 size);
extern void func_0800A668(void *pointer);
extern u32 func_080DCD08(u8 selector, void *list, void *argument);
extern void func_080DE278(Struct080DE2D0 *object, s8 value);

void func_080DE2D0(u8 selector, Struct080DE2D0 *skip, void *argument)
{
    Struct080DE2D0 **list = func_0800A654(0x60);
    u8 count = func_080DCD08(selector, list, argument);
    Struct080DE2D0 *object;
    u8 index;

    for (index = 0; index < count; index++) {
        if (skip != 0 && list[index] == skip)
            continue;
        object = list[index];
        func_080DE278(object, object->field_1f);
    }
    func_0800A668(list);
}
