#include "ffta.h"

// 0x0801B5D4..0x0801B630: 92 bytes, 46 instructions.
// Target: 30b58eb0041c02a9a07808712089c88060890881a08948812078087060784870
//         a0880885e08848850b48c08bc8830020fff78afb051c0120fff786fb21696269
//         00900120019002a82b1c00f0ebf80eb030bc01bc00470000407f0002

struct Request0801B5D4 {
    u8 unknown_00;
    u8 unknown_01;
    u8 unknown_02;
    u8 unknown_03;
    u16 unknown_04;
    u16 unknown_06;
    u16 unknown_08;
    u16 unknown_0A;
    u16 unknown_0C;
    u16 unknown_0E;
    void *first;
    void *second;
};

struct State0801B5D4 {
    u8 unknown_00;
    u8 unknown_01;
    u8 unknown_02[2];
    u8 unknown_04;
    u8 unknown_05;
    u16 unknown_06;
    u16 unknown_08;
    u16 unknown_0A;
    u8 unknown_0C[0x12];
    u16 unknown_1E;
    u8 unknown_20[8];
    u16 unknown_28;
    u16 unknown_2A;
    u8 unknown_2C[4];
};

extern struct State0801B5D4 g_state_02007F40;
extern void *func_0801AD1C(u8 selector);
extern void func_0801B7F8(struct State0801B5D4 *state, void *first, void *second,
                          void *buffer, void *secondary_buffer, u8 enabled);

void func_0801B5D4(const struct Request0801B5D4 *request)
{
    struct State0801B5D4 state;
    void *buffer;

    state.unknown_04 = request->unknown_02;
    state.unknown_06 = request->unknown_08;
    state.unknown_08 = request->unknown_0A;
    state.unknown_0A = request->unknown_0C;
    state.unknown_00 = request->unknown_00;
    state.unknown_01 = request->unknown_01;
    state.unknown_28 = request->unknown_04;
    state.unknown_2A = request->unknown_06;
    state.unknown_1E = g_state_02007F40.unknown_1E;
    buffer = func_0801AD1C(0);
    func_0801B7F8(&state, request->first, request->second,
                  buffer, func_0801AD1C(1), 1);
}
