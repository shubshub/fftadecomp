#include "movement_tile.h"

/* Complete [0x08099F58,0x08099FAE): 86 bytes.
 * The actual callback reads signed bytes4/5 and can store the pointer at8.
 * Other local fields remain unspecified. These are conditional transport
 * views, not initialization, effect, bounds or termination guarantees.
 */
s32 func_08099F58(Actor *object, s8 x, s8 z, u8 range)
{
    TileSearch search;
    Scene *lookup;
    s32 column = x;
    s32 row = z;

    if (!func_08097504(object, column, row, range))
        return 0;
    lookup = object->scene;
    search.match = 0;
    search.x = column;
    search.y = row;
    func_080C7CC0(lookup->objects, func_0809ABB0, &search);
    if (search.match != 0 && search.match != object)
        return 0;
    return 1;
}
