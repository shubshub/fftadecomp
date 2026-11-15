#include "ffta.h"

typedef struct {
    u16 identifier;
    u8 quantity;
    u8 unknown_03;
} InventoryRecord;

typedef struct {
    u8 unknown_0000[0x1940];
    InventoryRecord inventory[361];
} State080388C8;

extern State080388C8 g_state_02000000;

/* Complete target: [0x080388C8, 0x0803890A), 66 bytes, 28 instructions.
 * Target bytes: f0b50004030c0022074fca267601b4246400064d9000c11988190088984207d1481900780ae000000000000242190000501c0004020ca242ecd90020f0bc02bc0847
 */
u8 func_080388C8(u16 identifier)
{
    u16 i;

    for (i = 0; i < 361; i++) {
        if (g_state_02000000.inventory[i].identifier == identifier)
            return g_state_02000000.inventory[i].quantity;
    }
    return 0;
}
