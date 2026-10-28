#include "ffta.h"

/* Target: complete [0x0808B984, 0x0808BA08), 132 bytes, 40 instructions. */
typedef struct {
    u8 unknown_00[0x0c];
    u16 *large_second;
    u16 *large_first;
    u16 *small_second;
    u16 *small_first;
    u8 *workspace;
} ResourceContext;

typedef struct {
    u16 *large_tiles;
    u16 *small_tiles;
    u8 *tile_workspace;
    u8 unknown_0c[8];
    u8 *primary_workspace;
    u8 *secondary_workspace;
    u8 unknown_1c[8];
    u8 *final_workspace;
    u8 unknown_28[4];
    u8 *shared_workspace;
} TileStorage;

typedef struct {
    u16 display_control;
    u16 display_status;
    u16 bg0_control;
} DisplayRegisters;

extern ResourceContext *data_03002818;
extern TileStorage data_03002740;
extern u16 data_06005000[];
extern u16 data_06005800[];
extern u16 data_06006000[];
extern u16 data_06007000[];
extern DisplayRegisters g_control_flags_03000940;

void func_0808B984(u32 initialize)
{
    u8 *workspace;

    if (initialize == 0) {
        workspace = data_03002818->workspace;
    } else {
        data_03002740.large_tiles = data_06007000;
        data_03002740.small_tiles = data_06005800;
        data_03002818->large_first = data_06007000;
        data_03002818->large_second = data_06006000;
        data_03002818->small_first = data_06005800;
        data_03002818->small_second = data_06005000;
        workspace = data_03002818->workspace;
    }
    data_03002740.primary_workspace = workspace;
    data_03002740.shared_workspace = workspace;
    data_03002740.secondary_workspace = workspace + 0x888;
    data_03002740.tile_workspace = workspace + 0xfd8;
    data_03002740.final_workspace = workspace + 0x1358;
    g_control_flags_03000940.bg0_control = 0xac09;
}
