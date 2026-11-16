#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u8 unknown_00[0x0c];
    u16 *large_second;
    u16 *large_first;
    u16 *small_second;
    u16 *small_first;
    u16 *buffer;
} ResourceContext;

typedef struct {
    u16 *large_tiles;
    u16 *small_tiles;
    u16 *regions[10];
} TileStorage;

extern ResourceContext *data_03002818;
extern TileStorage data_03002740;
extern u16 data_06007000[];
extern u16 data_06005800[];
extern u16 data_06006000[];
extern u16 data_06005000[];

/* Complete target [0x0808B984, 0x0808BA08): 132 bytes, 40 instructions. */
void func_0808B984(u32 mode)
{
    if (mode == 0) {
        u16 *buffer;

        data_03002740.regions[3] = buffer = data_03002818->buffer;
        data_03002740.regions[9] = data_03002740.regions[3];
        data_03002740.regions[4] = buffer + 0x444;
        data_03002740.regions[0] = buffer + 0x7ec;
        data_03002740.regions[7] = buffer + 0x9ac;
    } else {
        u16 *buffer;

        data_03002740.large_tiles = data_06007000;
        data_03002740.small_tiles = data_06005800;
        data_03002818->large_first = data_06007000;
        data_03002818->large_second = data_06006000;
        data_03002818->small_first = data_06005800;
        data_03002818->small_second = data_06005000;
        data_03002740.regions[3] = buffer = data_03002818->buffer;
        data_03002740.regions[9] = data_03002740.regions[3];
        data_03002740.regions[4] = buffer + 0x444;
        data_03002740.regions[0] = buffer + 0x7ec;
        data_03002740.regions[7] = buffer + 0x9ac;
    }
    g_control_flags_03000940.bg1cnt = 0xac09;
}
