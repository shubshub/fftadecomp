/* func_08080EB8 [0x08080EB8, 0x08080EF8), 64 bytes.
 * 30b581b0051c0024ac4214da2004000c05490968054a891809686a46f8f774fd002805d0
 * 012007e018280003502d00000134ac42eadb002001b030bc02bc0847
 */
#include "ffta.h"

struct State {
    u8 unknown_00[0x2D50];
    void *resource_2d50;
};

extern struct State *data_03002818;
extern int func_080799C0(u16 index, void *context, int *result);

int func_08080EB8(int count)
{
    int index;
    int result;

    for (index = 0; index < count; index++) {
        if (func_080799C0(index, data_03002818->resource_2d50, &result))
            return 1;
    }

    return 0;
}
