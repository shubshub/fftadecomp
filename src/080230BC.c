#include "ffta.h"

typedef struct {
    u8 unknown_00[0x18];
    u16 first;
    u8 unknown_1A[2];
    u16 second;
    u8 unknown_1E[0xB2];
    s16 counters[3];
    u16 unknown_D6;
    u8 buffer_D8[16];
    u8 buffer_E8[8];
    u8 unknown_F0[0x18];
} ResetRecord080230BC;

typedef struct {
    u8 unknown_0000[0x80];
    ResetRecord080230BC records[24];
    u8 unknown_1940[0x219E - 0x1940];
    u16 field_219E;
    u8 unknown_21A0[0x3C24 - 0x21A0];
    u32 field_3C24;
    u16 field_3C28;
    u8 field_3C2A;
} State080230BC;

extern State080230BC g_state_02000000;
extern void func_0802D934(void);
extern void func_0802D824(void);
extern void func_080C95C0(u16 index, u32 value);
extern void func_080C9574(u16 bitIndex, u16 enabled);
extern void func_0809A950(ResetRecord080230BC *record, s32 count);
extern void func_08004C40(void);
extern void func_08009AFC(u16 event);
extern void func_08009FD0(void);

/* Target [0x080230BC, 0x08023130), 116 complete bytes:
 * 10b5174c1749601800210160164aa01800220180154be0180180154960180270
 * 0af02afc0af0a0fb0d200021a6f06afa08200021a6f066fa40200021a6f03cfa
 * 8034201c182177f025fce1f79bfda720e6f7f6fce6f75eff10bc01bc00470000
 * 00000002243c00009e210000283c00002a3c0000
 */
void func_080230BC(void)
{
    State080230BC *state = &g_state_02000000;

    state->field_3C24 = 0;
    state->field_219E = 0;
    state->field_3C28 = 0;
    state->field_3C2A = 0;
    func_0802D934();
    func_0802D824();
    func_080C95C0(13, 0);
    func_080C95C0(8, 0);
    func_080C9574(0x40, 0);
    func_0809A950(state->records, 24);
    func_08004C40();
    func_08009AFC(0xA7);
    func_08009FD0();
}
