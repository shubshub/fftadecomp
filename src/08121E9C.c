#include "ffta.h"

typedef struct {
    void *manager;
    void *allocation;
    void *task;
    u8 action;
    u8 unknown_0D[3];
    u32 saved_mode;
} State08121E9C;

typedef struct {
    u8 unknown_00[0xC];
    u8 mode;
} GlobalState08121E9C;

typedef void (*BufferInitializer08121E9C)(void *destination, u32 size);

extern State08121E9C *data_020159CC;
extern GlobalState08121E9C g_state_0200F390;
extern BufferInitializer08121E9C const g_callbacks_0836D4B8[];
extern void *func_08007138(void *owner, u32 size);
extern void *func_08005C14(void *storage, u32 byte_count);

/* An inlined copy of func_08121B64 (src/08121B64.c). */
static inline void *inlined_08121B64(u32 size)
{
    void **owner = (void **)0x020159C4;

    return func_08007138(*owner, size);
}

/* Complete [0x08121E9C, 0x08121EF0): 84 bytes, 28 instructions.
 * Target bytes:
 * 30 B5 0F 4C 0F 4D 28 68 0F 49 E5 F6 47 F9 20 60
 * 0E 4A 0D 49 12 68 20 F0 CB F9 28 68 80 21 49 01
 * E5 F6 3C F9 21 68 48 60 80 21 49 01 E3 F6 A4 FE
 * 21 68 08 60 06 48 00 7B 08 61 30 BC 01 BC 00 47
 * CC 59 01 02 C4 59 01 02 58 09 00 00 B8 D4 36 08
 * 90 F3 00 02.
 *
 * Both allocations are the body of func_08121B64, the allocator of the heap
 * at 0x020159C4 defined earlier in this module, expanded in place: each size
 * goes straight into r1 at the allocator call and is loaded again where it
 * is used the second time.
 */
void func_08121E9C(void)
{
    data_020159CC = inlined_08121B64(0x958);
    g_callbacks_0836D4B8[0](data_020159CC, 0x958);
    data_020159CC->allocation = inlined_08121B64(0x1000);
    data_020159CC->manager = func_08005C14(data_020159CC->allocation, 0x1000);
    data_020159CC->saved_mode = g_state_0200F390.mode;
}
