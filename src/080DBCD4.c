#include "ffta.h"

/* Complete target [0x080DBCD4, 0x080DBD2E), 90 bytes:
 * 70b5464640b483b00e1c6a46023201a988466946434600f045f86c46063402aa6d460a35
 * 301c211c2b1c00f03bf8684600782178401a00060016424611782a78891a09060916c1f7
 * cffc0006000e03b008bc984670bc02bc0847
 */
void func_080DBD78(const Struct080DBD5C *source,
                   s16 *tile_x, s16 *tile_y, s16 *tile_z);
s32 func_0809D6BC(s8 x, s8 z);

u8 func_080DBCD4(const Struct080DBD5C *first, const Struct080DBD5C *second)
{
    s16 first_x, first_y, first_z;
    s16 second_x, second_y, second_z;

    func_080DBD78(first, &first_x, &first_y, &first_z);
    func_080DBD78(second, &second_x, &second_y, &second_z);
    return func_0809D6BC(first_x - second_x, first_z - second_z);
}
