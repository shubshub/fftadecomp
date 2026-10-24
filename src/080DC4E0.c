/* 0x080DC4E0 target: 70b5041c0e1c307a01300006000e012830d900252ae00022301c093040190078002806d1a18901200840002804d0e28b07e0012817d1a18902200840002800d0228c10040014002814dc002809da201c0521ccf791f90006002804d00120404209e0002007e0681c0006050e082030568542d0db012070bc02bc0847 */
#include "ffta.h"

typedef struct {
    u8 unknown_00[0x0C];
    u16 flags;
    u8 unknown_0e[0x10];
    s16 value_1e;
    s16 value_20;
} Object080DC4E0;

typedef struct {
    u8 unknown_00[8];
    s8 count;
    u8 selectors[0];
} Selection080DC4E0;

extern u8 func_080A8858(const Object080DC4E0 *object, u8 selector);

s8 func_080DC4E0(const Object080DC4E0 *object,
                 const Selection080DC4E0 *selection)
{
    u8 index;

    if ((u8)(selection->count + 1) <= 1)
        return 1;

    for (index = 0; index < selection->count; index++) {
        s16 value = 0;

        if (selection->selectors[index] == 0) {
            if (object->flags & 1)
                value = object->value_1e;
            else if (object->flags & 2)
                value = object->value_20;
        } else if (selection->selectors[index] == 1) {
            if (object->flags & 2)
                value = object->value_20;
        } else {
            continue;
        }

        if (value > 0)
            return 1;
        if (value < 0) {
            if (func_080A8858(object, 5))
                return -1;
        } else {
            return 0;
        }
    }
    return 1;
}
