#include "ffta.h"

/* 0x08025F8C..0x08025FDA: 78 bytes, 34 instructions.
 * Target: 70b50006050e2e1c044c20688069a7f00bfe0006002803d0002015e038f40002
 *         20688069a7f0d4fc000600280bd0012d09d0152ef0d1206880691a21a7f0cafa
 *         0006000e00e0012070bc02bc0847 */
typedef struct {
    u8 unknown_00[0x18];
    void *unit;
} MenuContext;

extern MenuContext *data_0200F438;
extern u8 func_080CDBB4(const void *object);
extern u8 func_080CD95C(const void *object);
extern u8 func_080CD560(const void *object, u8 index);

u8 func_08025F8C(u8 kind)
{
    if (func_080CDBB4(data_0200F438->unit))
        return 0;
    if (func_080CD95C(data_0200F438->unit)) {
        if (kind == 1)
            return 1;
        if (kind == 21)
            return func_080CD560(data_0200F438->unit, 26);
        return 0;
    }
    return 1;
}
