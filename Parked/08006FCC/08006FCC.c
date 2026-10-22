/* 0x08006FCC - 252 bytes
 * Target: f0b54f464646c0b4061c0d1ca846a979e879000208430338a871000ae8717020287173206871014a03e0000070730000251c2978687800020843002802d08000311800e000210c1c002c05d021796079000208439042ebd0454503d0301c291cfff7b8fe01488146ff2720e070730000444503d0301c211cfff7acfea879e979090201430331a279e0790002104309180904080c3840a871090ee971a078e17809020143081c3840a870090ae970a978e87800020843002802d08000311800e000210c1c002c0fd021796079000208434845cdd0002d03d0a81b8003000c00e000202070000a6070301c291cfff7b6fe18bc9846a146f0bc01bc0047
 */
#include "ffta.h"

void func_08006DA0(u8 *owner, u8 *block);
void func_08006E28(u8 *owner, u8 *block);

static inline u16 read_offset(const u8 *encoded)
{
    return encoded[0] | (encoded[1] << 8);
}

static inline void write_offset(u8 *encoded, u16 offset)
{
    encoded[0] = offset & 0xFF;
    encoded[1] = offset >> 8;
}

static inline u8 *decode_owner_link(u8 *owner, u16 offset)
{
    return offset != 0 ? owner + offset * 4 : 0;
}

void func_08006FCC(u8 *owner, u8 *block)
{
    u8 *original = block;
    u8 *neighbor;

    write_offset(block + 6, read_offset(block + 6) - 3);
    write_offset(block + 4, 0x7370);
    while ((neighbor = decode_owner_link(owner, read_offset(block))) != 0 &&
           read_offset(neighbor + 4) == 0x7370) {
        block = neighbor;
    }
    if (block != original) {
        func_08006DA0(owner, block);
    }
    while ((neighbor = decode_owner_link(owner, read_offset(block + 2))) != 0 &&
           read_offset(neighbor + 4) == 0x7370) {
        if (neighbor != original) {
            func_08006DA0(owner, neighbor);
        }
        write_offset(block + 6, read_offset(block + 6) + 3 + read_offset(neighbor + 6));
        write_offset(block + 2, read_offset(neighbor + 2));
    }
    if (neighbor != 0) {
        u16 offset = block != 0 ? (u16)((u32)(block - owner) >> 2) : 0;

        write_offset(neighbor, offset);
    }
    func_08006E28(owner, block);
}
