#include "ffta.h"

/* Complete [0x08123860, 0x08123898): 56 bytes, 19 instructions, two literal
 * words.
 * 10b50b4c211cb431002008700af762f809f7d8ffaff75afb06482418201c182177f766f8
 * 8820400010bc02bc08470000d0200002b0dfffff
 */

/* The 0x108-byte record of src/0809A950.c, which this function passes it to. */
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
} ResetRecord;

/* The request at 0x020020D0 as src/08023AF4.c declares it. */
typedef struct {
    const void *current;
    void *source;
    u8 unknown_08[4];
    u16 id;
    u8 unknown_0E[2];
    u8 unknown_10;
    u8 kind;
    u8 unknown_12;
    u8 unknown_13[0xB4 - 0x13];
    u8 slot;
} Request;

/* The 0x02000000 block: the records of src/080230BC.c at +0x80 and the
 * request of src/08023AF4.c at +0x20D0.  The ROM keeps 0x020020D0 in r4 and
 * reaches the records by adding -0x2050, so both are members of one object. */
typedef struct {
    u8 unknown_0000[0x80];
    ResetRecord records[24];
    u8 unknown_1940[0x20D0 - 0x1940];
    Request request;
} GlobalState;

extern GlobalState g_state_02000000;

extern void func_0802D934(void);
extern void func_0802D824(void);
extern void func_080D2F2C(void);
extern void func_0809A950(ResetRecord *record, s32 count);

u32 func_08123860(void *context, const u8 *script)
{
    Request *request = &g_state_02000000.request;

    request->slot = 0;
    func_0802D934();
    func_0802D824();
    func_080D2F2C();
    func_0809A950(g_state_02000000.records, 24);
    return 0x110;
}
