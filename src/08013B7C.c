#include "ffta.h"

typedef union {
    u16 value;
    struct {
        u8 first;
        u8 second;
    } count;
} BlockCounts08013B7C;

typedef struct {
    u8 unknown_00[0x0c];
    BlockCounts08013B7C blocks;
} BlockState08013B7C;

void func_08016E1C(void *destination, u8 first, u8 second);
void func_08016E4C(void *destination, const void *data, u32 first);

void func_08013B7C(const BlockState08013B7C *state, void *destination,
                   const u8 *source)
{
    if (state->blocks.value != 0) {
        const u8 *block = source;

        func_08016E1C(destination, state->blocks.count.first,
                      state->blocks.count.second);
        if (state->blocks.count.first != 0)
            func_08016E4C(destination, block, 1);
        if (state->blocks.count.second != 0) {
            block = source + 0xc0;
            func_08016E4C(destination, block, 0);
        }
    }
}
