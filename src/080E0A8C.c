#include "ffta.h"
#include "control_flags.h"

/* Complete target [0x080E0A8C, 0x080E0C88), 508 bytes, 208 instructions:
 * f0b581b00f1c151c398880204000814226d0814202dc00290ad0e8e00348814238d00130814200d1a4e0e0e001010000
 * f2f798ff0006002804d0f2f71dff291ccc3109e001204042291c0a3139f7a8fc291ccc31281c0c300860b8682871c6e0
 * f3f704f801214942074a082320f736f8064cf2f7fbff064a8023db00211c20f709f838880130b1e0a0ff0006fd630000
 * 005800060020e880082028726872281ccc30036801205f21142267f0f9f828602879012852d12b48e988de3001800020
 * 22f768fd284822f78fff041c274822f791ff0443032004432404240c201c022122f7a4fc0020022122f7c8fc00200221
 * 22f7ecfc022022f739fd1d4c40210143221c4a321078002001431170211c4b31087820200870297a201c4c3002780170
 * 687a221c4d3211781070022022f7f6fc218801432180281cd030297a142400940022002326f7fcfc281cfc30697a0094
 * 0022102326f7f4fc3df70ef83888013044e0000060380003005800060080000640090003287901281dd12c1cd034201c
 * 26f748fd2e1cfc36301c26f743fd1a482268011c4c310b780a7031684d3002780170201c26f726fe002820d0301c26f7
 * 21fe00281bd0286867f0c6fc002816d0286867f023fc00222a60287901280ad1094c211c4a3108780a70022022f79efc
 * 218881432180f2f7ddfe02203880002001b0f0bc02bc084740090003
 * Incoming R0 is unused; R1 and R2 carry the descriptor and payload.
 */

typedef struct RequestNode {
    u8 status;
    u8 kind;
    u8 unknown_02[2];
    u32 first;
    u32 second;
    u32 control;
    u8 unknown_10[8];
    struct RequestNode *next;
} RequestNode;

typedef struct LineState {
    s32 x;
    s32 y;
    s32 endX;
    s32 endY;
    s32 stepX;
    s32 stepY;
    s32 deltaX;
    s32 deltaY;
    s32 accumulator;
    s32 error;
    s32 remaining;
} LineState;

typedef struct {
    u16 phase;
    u8 unknown_02[6];
    u32 mode;
} Descriptor;

typedef struct {
    void *handle;
    u8 mode;
    u8 unknown_05;
    u16 offset;
    u8 first_alpha;
    u8 second_alpha;
    u16 palette[0x61];
    const u16 *colors;
    LineState first;
    LineState second;
} Payload;

extern u16 data_03003860[];
extern u8 data_06005800[], data_0600FFA0[];

extern void func_08000B20(RequestNode *entry, u16 first, u32 second, u16 count);
extern void func_08000B68(RequestNode *entry, u32 first, u32 second, u16 count);
extern void func_080034B8(u16 control, u8 layer);
extern void func_08003508(s16 value, u8 layer);
extern void func_08003558(s16 value, u8 layer);
extern u16 func_080035A8(u8 layer);
extern u16 func_080035F8(u8 layer);
extern void func_08003620(u8 value);
extern u32 func_08003A74(u32 packed);
extern u32 func_08003A80(u32 packed);
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 end_x, s32 end_y);
extern void func_080076A0(LineState *state);
extern u32 func_08007880(const void *state);
extern void func_0801A42C(s16 index, void *destination);
extern void func_0801DC04(void);
extern void *func_080D3904(void);
extern u8 func_080D39F0(void);
extern void func_080D3A30(void);
extern RequestNode *func_080D3AF8(void);
extern void *func_08147D2C(u16 first, u16 count, u16 duration, const u16 *colors);
extern void func_08148498(void *handle);
extern u32 func_081485D4(void *handle);

u32 func_080E0A8C(void *task, Descriptor *descriptor, Payload *payload)
{
    switch (descriptor->phase) {
    case 0:
        if (func_080D39F0()) {
            payload->colors = func_080D3904();
        } else {
            func_0801A42C(-1, payload->palette);
            payload->colors = &payload->palette[1];
        }
        payload->mode = descriptor->mode;
        break;
    case 0x100: {
        u16 entry;

        func_08000B68(func_080D3AF8(), -1, (u32)data_0600FFA0, 8);
        /* Map entry: palette 6, tile 0x3FD (the tile filled above).  The ROM
         * loads it into r4 between the two func_080D3AF8 calls (0x080E0AFC)
         * and copies it to r1 after the second (0x080E0B08); 080E0824
         * (0x080E088C, 0x080E0898) and 081104DC (0x08110536, 0x08110542)
         * hold the same 0x63FD the same way. */
        entry = 0x63FD;
        func_08000B20(func_080D3AF8(), entry, (u32)data_06005800, 0x400);
        descriptor->phase++;
        break;
    }
    case 0x101:
        payload->offset = 0;
        payload->first_alpha = 8;
        payload->second_alpha = 8;
        payload->handle = func_08147D2C(1, 0x5F, 20, payload->colors);
        if (payload->mode == 1) {
            data_03003860[0x6F] = payload->offset;
            func_08003620(0);
            func_080034B8(func_08003A74(0x06005800) | func_08003A80(0x06008000) | 3, 2);
            func_08003508(0, 2);
            func_08003558(0, 2);
            g_control_flags_03000940.bldcnt_lo = func_080035F8(2) | 0x40;
            g_control_flags_03000940.bldcnt_hi = 0x20;
            g_control_flags_03000940.bldalpha_lo = payload->first_alpha;
            g_control_flags_03000940.bldalpha_hi = payload->second_alpha;
            g_control_flags_03000940.display |= func_080035A8(2);
            func_080075CC(&payload->first, payload->first_alpha, 0, 0, 20);
            func_080075CC(&payload->second, payload->second_alpha, 0, 16, 20);
            func_0801DC04();
        }
        descriptor->phase++;
        break;
    case 0x102:
        if (payload->mode == 1) {
            func_080076A0(&payload->first);
            func_080076A0(&payload->second);
            g_control_flags_03000940.bldalpha_lo = payload->first.x;
            g_control_flags_03000940.bldalpha_hi = payload->second.x;
            if (!func_08007880(&payload->first))
                break;
            if (!func_08007880(&payload->second))
                break;
        }
        if (!func_081485D4(payload->handle))
            break;
        func_08148498(payload->handle);
        payload->handle = 0;
        if (payload->mode == 1) {
            g_control_flags_03000940.bldcnt_lo = 0;
            g_control_flags_03000940.display &= ~func_080035A8(2);
        }
        func_080D3A30();
        descriptor->phase = 2;
        break;
    }
    return 0;
}
