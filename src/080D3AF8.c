#include "ffta.h"

typedef struct {
    u8 unknown_00[28];
} Record080D3AF8;

typedef struct {
    u8 unknown_000[0x914];
    u8 index;
    u8 unknown_915[3];
    Record080D3AF8 records[16];
} State080D3AF8;

extern void *data_020159C0;
extern void *func_08005BFC(void *task);

/* Target [0x080D3AF8, 0x080D3B38), 64 complete bytes:
 * 00b50c48006832f77df8021c0a4811180878013008700006000e
 * 0f2801d9002008700978c800401a800004494018101802bc0847
 * c05901021409000018090000
 */
Record080D3AF8 *func_080D3AF8(void)
{
    State080D3AF8 *state = func_08005BFC(data_020159C0);

    state->index++;
    if (state->index > 15)
        state->index = 0;
    return &state->records[state->index];
}
