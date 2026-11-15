/* Target 0x0813FD78, complete [0x0813FD78, 0x0813FEC8), 336 bytes, 142 instructions. */

#include "control_flags.h"

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0c;
    u8 unknown_0d;
    u8 *tiles;
    u16 *destination;
} Display0813FD78;

typedef void (*BufferInitializer0813FD78)(void *destination, u32 size);

extern Display0813FD78 data_03000E60;
extern Display0813FD78 data_03000E80;
extern Display0813FD78 data_030008B0;
extern Display0813FD78 data_03000990;
extern BufferInitializer0813FD78 g_callbacks_0836D4B8[];

extern void func_0800323C(void);

/* Target bytes: 70b54e46454660b4c3f65cfa464b588800210026454858809a889880d8884448d88018898020400118811a1c4a3210781170013210781170181c4c30027801701a1c4d3210781170013210781170181c4430027801701a1c453210781170033a10781170013210781170083a10781170013a10781170053210781170013a10781170181c3c30027801701a1c3d3210781170181c4030027801701a1c413210781170e220400118802249c023db040b612148486120224a730a73204989460b6148614a730a731e4d2b611e4969616a732a731d4c236160616273227361680e80a1680e8069680e80a9680e80174e802109018846326802f0edf9494648693268414602f0e7f968693268414602f0e2f960693268414602f0ddf918bc9846a14670bc01bc00470000400900030310000001120000600e000300800006800e0003b00800030090000690090003b8d43608 */
void func_0813FD78(void)
{
    func_0800323C();
    g_control_flags_03000940.bg0cnt = 0x1003;
    g_control_flags_03000940.bg1cnt = 0x1003;
    g_control_flags_03000940.bg2cnt = 0x1201;
    g_control_flags_03000940.bg3cnt = 0x1000;
    g_control_flags_03000940.bldcnt_lo = 0;
    g_control_flags_03000940.bldcnt_hi = 0;
    g_control_flags_03000940.bldalpha_lo = 0;
    g_control_flags_03000940.bldalpha_hi = 0;
    g_control_flags_03000940.bldy_lo = 0;
    g_control_flags_03000940.winout_lo = 0;
    g_control_flags_03000940.winout_hi = 0;
    g_control_flags_03000940.winin_lo = 0;
    g_control_flags_03000940.winin_hi = 0;
    g_control_flags_03000940.win0h_hi = 0;
    g_control_flags_03000940.win0h_lo = 0;
    g_control_flags_03000940.win0v_hi = 0;
    g_control_flags_03000940.win0v_lo = 0;
    g_control_flags_03000940.win1h_lo = 0;
    g_control_flags_03000940.win1h_hi = 0;
    g_control_flags_03000940.win1v_lo = 0;
    g_control_flags_03000940.win1v_hi = 0;
    g_control_flags_03000940.display = 0x1c40;
    data_03000E60.tiles = (u8 *)0x06000000;
    data_03000E60.destination = (u16 *)0x06008000;
    data_03000E60.unknown_0d = 0x20;
    data_03000E60.unknown_0c = 0x20;
    data_03000E80.tiles = (u8 *)0x06000000;
    data_03000E80.destination = (u16 *)0x06008000;
    data_03000E80.unknown_0d = 0x20;
    data_03000E80.unknown_0c = 0x20;
    data_030008B0.tiles = (u8 *)0x06000000;
    data_030008B0.destination = (u16 *)0x06009000;
    data_030008B0.unknown_0d = 0x20;
    data_030008B0.unknown_0c = 0x20;
    data_03000990.tiles = (u8 *)0x06000000;
    data_03000990.destination = (u16 *)0x06008000;
    data_03000990.unknown_0d = 0x20;
    data_03000990.unknown_0c = 0x20;
    *data_03000990.horizontal_offset = 0;
    *data_03000990.vertical_offset = 0;
    *data_030008B0.horizontal_offset = 0;
    *data_030008B0.vertical_offset = 0;
    g_callbacks_0836D4B8[0](data_03000E60.destination, 0x800);
    g_callbacks_0836D4B8[0](data_03000E80.destination, 0x800);
    g_callbacks_0836D4B8[0](data_030008B0.destination, 0x800);
    g_callbacks_0836D4B8[0](data_03000990.destination, 0x800);
}
