#include "ffta.h"

/* 0x08017FC4..0x08017FE2: 30 bytes. */
typedef struct {
    u8 unknown_00[0x16];
    u8 value;
} State08017FC4;

typedef struct {
    u32 unknown_00;
    State08017FC4 *state;
    u16 unknown_08;
    u16 value;
} Record08017FC4;

extern u8 func_08017B48(const State08017FC4 *state);

u16 func_08017FC4(const Record08017FC4 *record)
{
    return func_08017B48(record->state) * 8 + 8 + record->value;
}
