#include "ffta.h"

struct Object {
    u8 unknown_00[4];
    u8 index;
};

struct NameEntry {
    u8 unknown_00[0xB];
    u8 name;
};

extern const u8 g_table_085273D8[][14];
extern u8 func_080C817C(void *object);
extern u32 func_080C92F0(void *object, u32 selector);

/* Target: complete [0x080CB78C, 0x080CB7C0), 52 bytes, including the
 * table literal.
 * 10b5041cfcf7f4fc0006002806d1201c0921fdf7a7fd0006000e06e02179c800
 * 401a400002494018c07a10bc02bc0847d8735208
 */
u8 func_080CB78C(struct Object *object)
{
    if (func_080C817C(object))
        return ((const struct NameEntry *)g_table_085273D8[object->index])->name;
    return func_080C92F0(object, 9);
}
