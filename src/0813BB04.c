#include "ffta.h"

typedef struct {
    u8 unknown_00[0x1A];
    u8 first_copy[20];
    u8 value_2E;
    u8 unknown_2F;
    u16 lower : 10;
    u16 upper : 6;
    u16 enabled;
    u8 unknown_34[2];
    u16 result_low;
    u16 result_high;
    u8 unknown_3A[0x18];
    u8 second_copy[20];
    u8 unknown_66[0xE];
    u16 value_74;
    u16 count;
    u8 unknown_78[0x11];
    u8 source_89;
    u8 unknown_8A[0x1E92];
    u8 first_source[20];
    u8 unknown_1F30[0x252];
    u8 selector;
    u8 unknown_2183[0x1D];
    u8 second_source[20];
    u8 source_21B4;
    u8 unknown_21B5[0xE07];
    u16 source_lower;
    u8 source_upper;
} Context0813BB04;

typedef void (*BufferCopier0813BB04)(void *destination, const void *source,
                                    u32 size);

extern BufferCopier0813BB04 const data_0836D4BC[];
extern void func_08142250(void *destination, const void *source, u32 size,
                          BufferCopier0813BB04 callback);
extern u16 func_0813B9F8(void *context);
extern u32 func_0813BA5C(void *context, u8 selector);

/* Target: complete [0x0813BB04, 0x0813BBB8), 180 bytes.
 * 30b50c1c224d201c1a30224aa1182b68142206f09bfb201c89300078211c2e310870
 * 1d49601800881c490140228e1c481040084320861b4aa018231c3133017889001a78
 * 0320104008431870201c5230154aa1182b68142206f078fb134960180178201c7430
 * 0180201cfff743ff211c76310880012060860d4aa0180178201cfff76affe086000c
 * 208730bc01bc0047bcd436081c1f0000bc2f0000ff03000000fcffffbe2f0000a021
 * 0000b421000082210000
 */
void func_0813BB04(u8 mode, void *context)
{
    Context0813BB04 *state = context;
    BufferCopier0813BB04 const *copy = data_0836D4BC;
    u32 result;

    func_08142250(state->first_copy, state->first_source,
                  sizeof(state->first_copy), copy[0]);
    state->value_2E = state->source_89;
    state->lower = state->source_lower;
    state->upper = state->source_upper;
    func_08142250(state->second_copy, state->second_source,
                  sizeof(state->second_copy), copy[0]);
    state->value_74 = state->source_21B4;
    state->count = func_0813B9F8(state);
    state->enabled = 1;
    result = func_0813BA5C(state, state->selector);
    state->result_low = result;
    state->result_high = result >> 16;
}
