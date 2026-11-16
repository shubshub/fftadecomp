#include "ffta.h"

/* Complete [0x0809D938, 0x0809D96A): 50 bytes, 23 instructions.
 * 70b5061c0025b420291c4143301c0c3044182068002803d084f780ff0020206001350c2d
 * efdd301c84f778ff70bc01bc0047
 * Frees the resource held by each of the thirteen 0xB4-byte entries at +8
 * (the entry array of func_0809D2F8, func_0809D96C, func_0809D98C and
 * func_0809D9D8), clears the pointer, then frees the object itself.
 */
typedef struct {
    void *object;
    void *resource;
    u8 unknown_08[0xAC];
} Entry0809D938;

typedef struct {
    u8 unknown_00[8];
    Entry0809D938 entries[13];
} Object0809D938;

extern void func_08022854(void *resource);

void func_0809D938(Object0809D938 *object)
{
    s32 index;

    for (index = 0; index <= 12; ++index) {
        if (object->entries[index].resource) {
            func_08022854(object->entries[index].resource);
            object->entries[index].resource = 0;
        }
    }
    func_08022854(object);
}
