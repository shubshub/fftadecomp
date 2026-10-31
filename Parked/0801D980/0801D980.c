#include "ffta.h"

typedef struct ParameterState0801D980 {
    u16 unknown_00;
    u16 selector;
    u16 first;
    u8 enabled;
    u8 unknown_07;
    const u16 *source;
    u16 second;
    u16 third;
    u32 fourth;
    u32 derived;
} ParameterState0801D980;

extern ParameterState0801D980 data_02007F20;
extern const u16 data_08425104[];
extern u16 data_02008390[];
extern void func_0814186C(const void *source, void *destination, u32 count);

/* Complete target [0x0801D980, 0x0801DA10), 144 bytes:
 * f0b5474680b40004000c804609060a0e024e7088ff2803d100202fe0207f00020648
 * 43465900091809880d18af1d002a06d00120b071b7600de0000004514208114c381c
 * 211ca12223f150ff2088a0214900641820802888b080a888b0816888ad8840190138
 * f0813761b08840003818064bc018706140467080388808bc9846f0bc02bc08470000
 * 90830002c0feffff
 */
u16 func_0801D980(u16 index, u8 mode)
{
    ParameterState0801D980 *state = &data_02007F20;
    const u16 *offsets;
    const u16 *header;
    const u16 *payload;

    if (state->selector == 0xFF)
        return 0;

    offsets = data_08425104;
    header = (const u16 *)((const u8 *)offsets + offsets[index]);
    payload = header + 3;
    if (mode != 0) {
        state->enabled = 1;
        state->source = payload;
    } else {
        u16 *buffer = data_02008390;

        func_0814186C(payload, buffer, 0xA1);
        buffer[160] = buffer[0];
    }
    state->first = header[0];
    state->second = header[2];
    state->third = header[1] + header[2] - 1;
    state->fourth = (u32)payload;
    state->derived = (u32)(payload + state->first - 160);
    state->selector = index;
    return payload[0];
}
