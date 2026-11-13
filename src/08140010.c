// Target 0x08140010, complete [0x08140010, 0x0814011C), 268 bytes, 113 instructions.

#include "control_flags.h"

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0c;
    u8 unknown_0d;
    u8 *tiles;
    u16 *destination;
} Display08140010;

typedef void (*BufferInitializer08140010)(void *destination, u32 size);

extern Display08140010 data_03000E60;
extern Display08140010 data_03000E80;
extern BufferInitializer08140010 g_callbacks_0836D4B8[];

extern void func_0800323C(void);
extern void func_0814224C(void *destination, u32 size,
                          BufferInitializer08140010 callback);

// Target bytes: 70b5c3f613f9384bd88800210025dd8018891d815888354858809888344898801a1c4a3210781170013210781170181c4c30027801701a1c4d3210781170013210781170181c4430027801701a1c453210781170033a10781170013210781170083a10781170013a10781170053210781170013a10781170181c3c30027801701a1c3d3210781170181c4030027801701a1c41321078117016481880164bc021c90419611548586120225a731a73144c2161144961616273227361680d80a1680d8059680d8099680d800f4d802636012a68311c02f0b2f860692a68311c02f0adf870bc01bc004740090003821000008312000041030000600e000300800006800e000300900006b8d43608
void func_08140010(void)
{
    func_0800323C();
    g_control_flags_03000940.bg2cnt = 0;
    g_control_flags_03000940.bg3cnt = 0;
    g_control_flags_03000940.bg0cnt = 0x1082;
    g_control_flags_03000940.bg1cnt = 0x1283;
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
    g_control_flags_03000940.display = 0x341;
    data_03000E60.tiles = (u8 *)0x06000000;
    data_03000E60.destination = (u16 *)0x06008000;
    data_03000E60.unknown_0d = 0x20;
    data_03000E60.unknown_0c = 0x20;
    data_03000E80.tiles = (u8 *)0x06000000;
    data_03000E80.destination = (u16 *)0x06009000;
    data_03000E80.unknown_0d = 0x20;
    data_03000E80.unknown_0c = 0x20;
    *data_03000E80.horizontal_offset = 0;
    *data_03000E80.vertical_offset = 0;
    *data_03000E60.horizontal_offset = 0;
    *data_03000E60.vertical_offset = 0;
    {
        BufferInitializer08140010 *callbacks = g_callbacks_0836D4B8;

        func_0814224C(data_03000E60.destination, 0x800, callbacks[0]);
        func_0814224C(data_03000E80.destination, 0x800, callbacks[0]);
    }
}
