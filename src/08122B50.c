#include "ffta.h"

typedef struct __attribute__((packed)) {
    u16 base;
    u8 unknown_02[4];
} BaseRecord;

extern const BaseRecord data_083A7EE4[];
extern void func_081223C8(void *state, u16 value, u8 option);

static inline u16 read_u16(const u8 *source)
{
    return source[0] | (source[1] << 8);
}

/* 08122B50..08122B8C: 60 bytes, 26 instructions. */
u32 func_08122B50(void *state, const u8 *command)
{
    u16 base = data_083A7EE4[command[0]].base;
    u16 offset = read_u16(command + 1);

    func_081223C8(state, base + offset, 0x80);
    return 0x110;
}
