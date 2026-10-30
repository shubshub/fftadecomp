#include "ffta.h"

typedef struct {
    u16 current;
    u16 count;
    u16 entries[32];
    void *context;
    u8 unknown_48[6];
    u16 field_4E;
    u8 mode;
    u8 timer;
    u8 unknown_52[2];
    u32 flags;
    s32 saved_result;
    s32 result;
    u32 unknown_60;
    u16 field_64;
    u16 field_66;
} CommandState08062E1C;

typedef struct {
    u8 unknown_0000[0x219E];
    u16 field_219E;
} Root08062E1C;

extern CommandState08062E1C *data_0200F450;
extern Root08062E1C g_state_02000000;
extern s16 func_08065050(const void *object);
extern void func_08066018(void *object);
extern u32 func_08066114(void);

/* Target [0x08062E1C, 0x08062FD8), 444 complete bytes:
 * 30b5364d2868406c02f014f900040414002c00d1c7e02868406c03f0eff80120
 * 4042844260d12968cc650a1c4e32ad201080486d022210434865503103200870
 * 2d68ac4661466431254808800231254808803023604603804088411c62465180
 * 0004c00b043210180380392463461c805888411c59800004c00b101804803b23
 * 2b806888411c69800004c00b1018038034232b806888411c69800004c00b1018
 * 038033232b806888411c69800004c00b1018038029232b806888411c69800004
 * c00b1018038028232b806888411c69800004c00b121813802c8064e050f40002
 * 019000003412000029680120c8650a1c4e32b0201080486d0222104348655131
 * 10200870286850300324047029680a1c64322648108066312548088003f0ecf8
 * 244902784078204000021043224a891808802a68112414805088411c51800004
 * c00b131d18180480372414805088411c51800004c00b18180480342414805088
 * 411c51800004c00b18180480332414805088411c51800004c00b181804802924
 * 14805088411c51800004c00b18180480282414805088411c51800004c00b1b18
 * 1c803920108030bc01bc00470190000034120000000000029e210000
 */
void func_08062E1C(void)
{
    s16 result = func_08065050(data_0200F450->context);

    if (result == 0)
        return;
    func_08066018(data_0200F450->context);
    if (result == -1) {
        CommandState08062E1C *head = data_0200F450;
        CommandState08062E1C *state;

        head->result = -1;
        head->field_4E = 0xAD;
        head->flags |= 2;
        head->mode = 3;
        state = data_0200F450;
        state->field_64 = 0x9001;
        state->field_66 = 0x1234;
        state->current = 0x30;
        state->entries[state->count++] = state->current;
        state->current = 0x39;
        state->entries[state->count++] = state->current;
        state->current = 0x3B;
        state->entries[state->count++] = state->current;
        state->current = 0x34;
        state->entries[state->count++] = state->current;
        state->current = 0x33;
        state->entries[state->count++] = state->current;
        state->current = 0x29;
        state->entries[state->count++] = state->current;
        state->current = 0x28;
        state->entries[state->count++] = state->current;
        state->current = 0x39;
    } else {
        CommandState08062E1C *head = data_0200F450;
        CommandState08062E1C *state;
        const u8 *record;

        head->result = 1;
        head->field_4E = 0xB0;
        head->flags |= 2;
        head->timer = 0x10;
        data_0200F450->mode = 3;
        {
            CommandState08062E1C *metadata = data_0200F450;

            metadata->field_64 = 0x9001;
            metadata->field_66 = 0x1234;
        }
        record = (const u8 *)func_08066114();
        g_state_02000000.field_219E = ((record[1] & 3) << 8) | record[0];
        state = data_0200F450;
        state->current = 0x11;
        state->entries[state->count++] = state->current;
        state->current = 0x37;
        state->entries[state->count++] = state->current;
        state->current = 0x34;
        state->entries[state->count++] = state->current;
        state->current = 0x33;
        state->entries[state->count++] = state->current;
        state->current = 0x29;
        state->entries[state->count++] = state->current;
        state->current = 0x28;
        state->entries[state->count++] = state->current;
        state->current = 0x39;
    }
}
