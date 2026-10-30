#include "ffta.h"

typedef struct {
    u16 first;
    u16 current;
} Position08066120;

typedef struct {
    u8 unknown_00[9];
    u8 value;
    u8 unknown_0A[0x9FA];
    Position08066120 positions[8];
    u8 alternate[0x18];
} State08066120;

typedef void (*BufferInitializer08066120)(void *destination, u32 size);

extern State08066120 *data_0200F454;
extern BufferInitializer08066120 const g_callbacks_0836D4B8[];

/* 08066120..08066168: 72 bytes, including the state, callback, and field-offset literals. */
void func_08066120(u8 index)
{
    Position08066120 *position = &data_0200F454->positions[index];

    position->first = 0;
    position->current = 0;
    if (index == 4) {
        data_0200F454->value = 0;
        g_callbacks_0836D4B8[0](data_0200F454->alternate, 0x18);
    }
}
