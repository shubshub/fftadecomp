#include "control_flags.h"

// Complete target [0x0813FCF0, 0x0813FD78): 136 bytes, 41 instructions.
// Target bytes: 70b581b01549c88900261548c881088a14480882144805681448154c15490368201c602202f09cfac03c26801249281cc5f68cfb021c11495202d20a281c01f09bfd0f480f4949690096d2220f23fff7e5fe01b070bc01bc004700004009000378ff0000f0ff0000b0f30002bcd436082039000340819908ecbd96080024000634919908800e0003

typedef struct {
    u16 *control;
    u16 *horizontal_offset;
    u16 *vertical_offset;
    u8 unknown_0C;
    u8 unknown_0D;
    u8 *tiles;
    u16 *destination;
} DisplayRecord;

typedef void (*BufferCopier)(void *, const void *, u32);
extern u8 *data_0200F3B0;
extern u16 data_03003860[];
extern DisplayRecord data_03000E80;
extern BufferCopier const data_0836D4BC[];
extern const u16 data_08998140[];
extern const u8 data_0896BDEC[];
extern u8 data_06002400[];
extern const u16 data_08999134[];
extern u32 func_0800543C(void *destination, const void *source);
extern void func_08141868(const void *, void *, u32);
extern void func_0813FB0C(const u16 *, u16 *, u16, u8, u16);

void func_0813FCF0(void)
{
    u8 *buffer;
    u32 size;

    g_control_flags_03000940.bg1hofs = -136;
    g_control_flags_03000940.bg1vofs = -16;
    buffer = data_0200F3B0;
    data_0836D4BC[0](data_03003860 + 0x60, data_08998140, 0x60);
    data_03003860[0] = 0;
    size = func_0800543C(buffer, data_0896BDEC);
    func_08141868(buffer, data_06002400, (size & 0x7FFFFF) >> 2);
    func_0813FB0C(data_08999134, data_03000E80.destination, 210, 15, 0);
}
