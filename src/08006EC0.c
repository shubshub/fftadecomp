#include "ffta.h"

// Complete target [0x08006EC0, 0x08006FCA): 266 bytes, 127 instructions.
// Target bytes: f0b5474680b482b0804609040d0c01ab291c6a46fff7d8fe019c002c01d100206de04046211cfff75bffa179e07900020843401b0004070ce81cff26a071000ae0716c20207161206071032f4bd9a179e07900020843800025181a480268281c0c213bf193f97020287173206871f91e0904080c3040a871090ee9714046211a8903090c081c30402870090a6970a078e17809020143081c3040a870090ae9704146681a8003000c0640a670000ae070a978e87800020843002805d080004246111802e0b8d436080021002906d04246a81a8003000c0870000a48704046291cfff742ff0ae0a079e1790902014379180904080c3040a071090ee171201c02b008bc9846f0bc02bc0847

typedef struct {
    u16 previous, next, marker, size;
    u16 free_previous, free_next;
} __attribute__((packed)) Block08006EC0;

typedef void (*BufferInitializer08006EC0)(void *destination, u32 size);

extern BufferInitializer08006EC0 const g_callbacks_0836D4B8[];

extern void func_08006C88(u8 *owner, u16 size, Block08006EC0 **before,
                          Block08006EC0 **selected);
extern void func_08006DA0(void *owner, void *block);
extern void func_08006E28(void *owner, void *block);

static inline Block08006EC0 *decode_offset08006EC0(u8 *owner, u16 value)
{
    return value ? (Block08006EC0 *)(owner + value * 4) : 0;
}

static inline u32 encode_offset08006EC0(u8 *owner, Block08006EC0 *block)
{
    return (u16)((u32)((u8 *)block - owner) >> 2);
}

Block08006EC0 *func_08006EC0(u8 *owner, u16 size)
{
    Block08006EC0 *before;
    Block08006EC0 *found;
    Block08006EC0 *block;
    Block08006EC0 *split;
    Block08006EC0 *next;
    u16 remain;

    func_08006C88(owner, size, &before, &found);
    block = found;
    if (block == 0)
        return 0;
    func_08006DA0(owner, block);
    remain = block->size - size;
    block->size = size + 3;
    block->marker = 0x616C;
    if (remain > 3) {
        split = (Block08006EC0 *)((u8 *)block + block->size * 4);
        g_callbacks_0836D4B8[0](split, sizeof(*split));
        split->marker = 0x7370;
        split->size = remain - 3;
        split->previous = encode_offset08006EC0(owner, block);
        split->next = block->next;
        block->next = encode_offset08006EC0(owner, split);
        next = decode_offset08006EC0(owner, split->next);
        if (next)
            next->previous = encode_offset08006EC0(owner, split);
        func_08006E28(owner, split);
    } else {
        block->size += remain;
    }
    return block;
}
