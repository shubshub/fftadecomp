#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *context;
    u8 unknown_48[6];
    u16 field_4e;
    u8 unknown_50[8];
    s32 result_58;
    u8 unknown_5c[0xea - 0x5c];
    u16 result_ea;
} CommandState08062248;

typedef struct {
    u8 unknown_0000[0x219e];
    u16 field_219e;
} GlobalState08062248;

extern CommandState08062248 *data_0200F450;
extern GlobalState08062248 g_state_02000000;
extern s16 func_08065050(const void *context);
extern void func_08066028(void *context);

/* Complete target [0x08062248, 0x08062344): 252 bytes, 92 instructions.
 * 70b50b4c2068406c02f0fefe0004050c0014261c00286cd00424013000040014
 * 05283fd880000349401800688746000050f400028022060898220608ec220608
 * c0220608d0220608e02206089822060806480749401800210180064a10684e30
 * 522101800124161c1ce00000000000029e21000050f40002024801684e31a722
 * 0ee0000050f40002024801684e31b52206e0000050f40002174801684e31bd22
 * 0a80061c3068406c03f09afe326814805088411c51800004c00b131d18180480
 * 342414805088411c51800004c00b18180480352414805088411c51800004c00b
 * 1b181c8032201080280400149065ea32108070bc01bc004750f40002
 */
void func_08062248(void)
{
    s16 result = func_08065050(data_0200F450->context);
    u16 command;
    CommandState08062248 *state;

    if (result == 0)
        return;

    command = 4;
    switch (result) {
    case -1:
    case 4:
        g_state_02000000.field_219e = 0;
        data_0200F450->field_4e = 0x52;
        command = 1;
        break;
    case 1:
        data_0200F450->field_4e = 0xa7;
        break;
    case 2:
        data_0200F450->field_4e = 0xb5;
        break;
    case 3:
        data_0200F450->field_4e = 0xbd;
        break;
    }

    func_08066028(data_0200F450->context);
    state = data_0200F450;
    state->current = command;
    state->entries[state->count++] = command;
    state->current = 0x34;
    state->entries[state->count++] = 0x34;
    state->current = 0x35;
    state->entries[state->count++] = 0x35;
    state->current = 0x32;
    state->result_58 = result;
    state->result_ea = result;
}
