#include "ffta.h"

/* Complete [0x0812A440, 0x0812A52C): 236 bytes, 96 instructions. */
typedef struct {
    u8 unknown_000[0x298];
    const void *image;
    u8 unknown_29c[0x5a];
    s8 selection;
} State0812A440;

extern const u8 data_083A8295[];
extern const u8 data_083A8298[];
extern const u8 data_083A82AC[];
extern const u8 data_083A82BA[];
extern const u8 data_083A82C8[];
extern const u8 data_083A82EC[];
extern void func_08001F34(const void *, s32, s32, u32, u32, u32, u32,
                         u32, u32, u32, u32);
extern void func_08001CF0(const void *, s32, s32, u32, u32, u32, u32,
                         u32, u32, u32, u32);
extern void func_0812ADDC(State0812A440 *, s32, s32);

void func_0812A440(State0812A440 *state)
{
    func_08001F34(data_083A8298, 80, 128, 0, 0, 0, 0, 0, 0, 0, 0);
    func_0812ADDC(state, 92, 136);
    func_08001F34(state->image, 240, 154, 0, 0, 1, 0, 0, 0x240, 0, 0);
    func_08001F34(data_083A82AC, 192, 16, 0, 0, 0, 0, 0, 0, 0, 0);
    func_08001F34(data_083A82BA, 192, 32, 0, 0, 0, 0, 0, 0, 0, 0);
    func_08001CF0(data_083A82C8, 192, 48, 0, 0, 0, 0, 0, 0, 0, 0);
    func_08001F34(data_083A82EC, data_083A8295[state->selection], 8,
                  0, 0, 0, 0, 0, 0, 0, 0);
}
