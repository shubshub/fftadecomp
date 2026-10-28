#include "ffta.h"

typedef struct TableEntry {
    u16 base;
    u8 unknown_02[4];
} __attribute__((packed)) TableEntry;

extern const TableEntry data_083A7EE4[];
extern void func_081223C8(void *state, u16 value, u8 option);

static inline u16 read_u16(const u8 *source)
{
    return source[0] | (source[1] << 8);
}

/* 08122B14..08122B50: 60 bytes, 26 instructions. */
u32 func_08122B14(void *state, const u8 *command)
{
    const TableEntry *table = data_083A7EE4;
    u16 base = table[command[0]].base;
    u16 offset = read_u16(command + 2);

    func_081223C8(state, base + offset, command[1]);
    return 0x110;
}
