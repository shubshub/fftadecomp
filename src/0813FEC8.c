// Target 0x0813FEC8, complete [0x0813FEC8, 0x08140010), 328 bytes, 147 instructions.

#include "control_flags.h"

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0c;
    u8 unknown_0d;
    u8 *tiles;
    u16 *destination;
} Display0813FEC8;

typedef void (*BufferInitializer0813FEC8)(void *destination, u32 size);

extern Display0813FEC8 data_030008B0;
extern Display0813FEC8 data_03000990;
extern BufferInitializer0813FEC8 g_callbacks_0836D4B8[];

extern void func_0800323C(void);
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer0813FEC8 callback);

// Target bytes: 70b5c3f6b7f9494b9888002100259d8058885d8018891d81d888a120c001d8801a1c4a3210781170013210781170181c4c30027801701a1c4d3210781170013210781170181c4430027801701a1c453210781170033a10781170013210781170083a10781170013a10781170053210781170013a10781170181c3c30027801701a1c3d3210781170181c4030027801701a1c413210781170588b802040005883998b9d83d98bdd83198c1884598c5d84998c9d84d98cdd84198d1d85598d5885998d9d85d98ddd85198e1886588e5d86988e9d86d88edd86188f1d8714481880144bc021c90419611348586120225a731a73124c2161124961616273227361680d80a1680d8059680d8099680d800d4d802636012a68311c02f034f960692a68311c02f02ff970bc01bc00474009000341140000b0080003008000069009000300880006b8d43608
void func_0813FEC8(void)
{
    func_0800323C();
    g_control_flags_03000940.bg1cnt = 0;
    g_control_flags_03000940.bg0cnt = 0;
    g_control_flags_03000940.bg3cnt = 0;
    g_control_flags_03000940.bg2cnt = 0x5080;
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
    g_control_flags_03000940.bg2pa = 0x100;
    g_control_flags_03000940.bg2pb = 0;
    g_control_flags_03000940.bg2pc = 0;
    g_control_flags_03000940.bg2pd = 0x100;
    g_control_flags_03000940.bg2x_l = 0;
    g_control_flags_03000940.bg2x_h = 0;
    g_control_flags_03000940.bg2y_l = 0;
    g_control_flags_03000940.bg2y_h = 0;
    g_control_flags_03000940.bg3pa = 0x100;
    g_control_flags_03000940.bg3pb = 0;
    g_control_flags_03000940.bg3pc = 0;
    g_control_flags_03000940.bg3pd = 0x100;
    g_control_flags_03000940.bg3x_l = 0;
    g_control_flags_03000940.bg3x_h = 0;
    g_control_flags_03000940.bg3y_l = 0;
    g_control_flags_03000940.bg3y_h = 0;
    g_control_flags_03000940.display = 0x1441;
    data_030008B0.tiles = (u8 *)0x06000000;
    data_030008B0.destination = (u16 *)0x06008000;
    data_030008B0.unknown_0d = 0x20;
    data_030008B0.unknown_0c = 0x20;
    data_03000990.tiles = (u8 *)0x06000000;
    data_03000990.destination = (u16 *)0x06008800;
    data_03000990.unknown_0d = 0x20;
    data_03000990.unknown_0c = 0x20;
    *data_03000990.horizontal_offset = 0;
    *data_03000990.vertical_offset = 0;
    *data_030008B0.horizontal_offset = 0;
    *data_030008B0.vertical_offset = 0;
    {
        BufferInitializer0813FEC8 *callbacks = g_callbacks_0836D4B8;

        func_0814224C(data_030008B0.destination, 0x800, callbacks[0]);
        func_0814224C(data_03000990.destination, 0x800, callbacks[0]);
    }
}
