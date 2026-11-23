/* Complete target [0x08070C94, 0x0807109A), 1030 bytes including pools,
 * 366 reachable instructions.  A task step called as (index, &phase):
 * phases 1 and 0 set the scene up and register its tasks (func_080802E4 in
 * slot 0), phase 0xFE clears four layers and stops in 0xFF or 0xFD. */
#include "ffta.h"
#include "control_flags.h"

typedef struct {
    u8 unknown_000[0x44C];
    u8 phase;
    u8 unknown_44D[2];
    u8 saved_phase;
    u8 unknown_450[0x960 - 0x450];
    u16 field_960;
    /* Bit 0 is cleared with `movs #2; rsbs; ands` (0x08070EA4) and tested
     * with `movs #1; ands` (0x08071052): a one-bit field, as the flag at
     * 0x95E is in src/08070414.c. */
    u8 field_962_0 : 1;
    u8 unknown_962_1 : 7;
    u8 unknown_963[0xC1E - 0x963];
    u8 enabled;
    u8 unknown_C1F[0x1D09 - 0xC1F];
    u8 field_1d09;
    u8 unknown_1D0A[2];
    u8 *unit;
} Context08070C94;

typedef struct {
    u8 unknown_00[0xC];
    u8 width;
    u8 height;
    u8 unknown_0E[6];
    u16 *map;
} Layer08070C94;

typedef struct {
    u8 unknown_00[4];
    void *entries;
} SharedResource08070C94;

extern Context08070C94 *data_03002818;
extern u8 data_030027A4;
extern u8 *data_030027F4;
extern const void *data_030027D4;
extern SharedResource08070C94 data_03000E30;
extern Table data_03002730, data_03000880;
extern u32 data_03000910[];
extern u8 data_03000EC0[];
extern Layer08070C94 data_030008B0, data_03000990, data_03000E60, data_03000E80;
extern void func_0807109C(u32);
extern void func_08087160(void);
extern void func_08087300(void);
extern void func_0807408C(void);
extern void func_0804C834(void *, s32);
extern void func_08006A7C(Table *, u32 *, u8 *, u8);
extern void func_08006AF8(Table *, u8, u32, u8);
extern void func_080802E4(u32 index, u8 *state);
extern void func_08071374(void);
extern void func_0807411C(u8, u8 *);
extern void func_080888B4(u32 unused, u8 *stage);
extern void func_08087FB8(u8, u8 *);
extern void func_08087F0C(void);
extern void func_0808B288(int unused, u8 *initialized);
extern void func_080069F4(Table *, u8);
extern void func_08006B5C(Table *);
extern void func_08006B8C(Table *, u8);
extern void func_08071234(u32);
extern void func_08003934(u8);
extern void func_0814186C(const void *source, void *destination, u32 control);

void func_08070C94(u8 index, u8 *phase)
{
    data_03002818->saved_phase = *phase;
    /* Case 1's body (0x08070CE8) precedes case 0's (0x08070E30) in the ROM.
     * The two set-up bodies are the same text apart from the bit at 0x962;
     * the ROM keeps both copies and cross-jumps only their shared tail
     * (0x08070F78-0x08070F96). */
    switch (*phase) {
    case 1:
        data_030027A4 = 0xFF;
        func_0807109C(1);
        func_08087160();
        func_08087300();
        func_0807408C();
        g_control_flags_03000940.bg0vofs = g_control_flags_03000940.bg1vofs = 0;
        g_control_flags_03000940.bg0hofs = g_control_flags_03000940.bg1hofs = 0;
        data_03002818->unit = data_030027F4;
        data_03002818->field_1d09 = 0;
        data_03002818->enabled |= 0xFF;
        func_08006A7C(&data_03002730, data_03000910, data_03000EC0, 8);
        data_030027D4 = 0;
        data_03002818->field_962_0 = 1;
        func_08006ADC(&data_03002730, 0, (u32)func_080802E4);
        func_08006ADC(&data_03002730, 1, (u32)func_08071374);
        func_08006ADC(&data_03002730, 2, (u32)func_08071374);
        func_08006ADC(&data_03002730, 3, (u32)func_08071374);
        func_08006AF8(&data_03002730, 4, (u32)func_0807411C, 3);
        func_08006ADC(&data_03002730, 7, (u32)func_08071374);
        func_08006ADC(&data_03002730, 5, (u32)func_080888B4);
        func_08006ADC(&data_03002730, 6, (u32)func_08087FB8);
        func_08006ADC(&data_03000880, 0, (u32)func_08087F0C);
        func_08006ADC(&data_03000880, 1, (u32)func_0808B288);
        if (*phase == 0)
            data_03002818->field_960 = 1;
        else
            data_03002818->field_960 = 0;
        data_03002818->phase = 4;
        *phase = 5;
        break;
    case 0:
        data_030027A4 = 0xFF;
        func_0807109C(1);
        func_08087160();
        func_08087300();
        func_0807408C();
        g_control_flags_03000940.bg0vofs = g_control_flags_03000940.bg1vofs = 0;
        g_control_flags_03000940.bg0hofs = g_control_flags_03000940.bg1hofs = 0;
        data_03002818->unit = data_030027F4;
        data_03002818->field_1d09 = 0;
        data_03002818->enabled |= 0xFF;
        func_08006A7C(&data_03002730, data_03000910, data_03000EC0, 8);
        data_030027D4 = 0;
        data_03002818->field_962_0 = 0;
        func_08006ADC(&data_03002730, 0, (u32)func_080802E4);
        func_08006ADC(&data_03002730, 1, (u32)func_08071374);
        func_08006ADC(&data_03002730, 2, (u32)func_08071374);
        func_08006ADC(&data_03002730, 3, (u32)func_08071374);
        func_08006AF8(&data_03002730, 4, (u32)func_0807411C, 3);
        func_08006ADC(&data_03002730, 7, (u32)func_08071374);
        func_08006ADC(&data_03002730, 5, (u32)func_080888B4);
        func_08006ADC(&data_03002730, 6, (u32)func_08087FB8);
        func_08006ADC(&data_03000880, 0, (u32)func_08087F0C);
        func_08006ADC(&data_03000880, 1, (u32)func_0808B288);
        if (*phase == 0)
            data_03002818->field_960 = 1;
        else
            data_03002818->field_960 = 0;
        data_03002818->phase = 4;
        *phase = 5;
        break;
    case 5:
        func_080069F4(&data_03002730, 8);
        *phase = data_03002818->saved_phase;
        break;
    case 0xFD:
        /* Phase 0xFE leaves this phase below.  Its node is what makes the
         * dispatch test `cmp r6, #0xFE; bgt` (0x08070CDA-0x08070CDC) ahead of
         * the 0xFF test; its own compare branched to the exit and was
         * folded away. */
        break;
    case 0xFE:
        /* CpuFill16 of the four layers src/08087300.c clears, in the text of
         * src/0807B858.c: the SDK's vu16 temporary, spelled through a pointer
         * until fftadecomp-kit#164.  The four halfwords are sp+0..sp+6; the
         * first takes its address before the 1 is stored
         * (mov r0, sp at 0x08070FC0). */
        {
            u16 fill;
            u16 *p = &fill;
            *p = 1;
            func_0814186C(p, data_030008B0.map,
                          (data_030008B0.width * data_030008B0.height) | 0x01000000);
        }
        {
            u16 fill;
            u16 *p = &fill;
            *p = 1;
            func_0814186C(p, data_03000990.map,
                          (data_03000990.width * data_03000990.height) | 0x01000000);
        }
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, data_03000E60.map,
                          (data_03000E60.width * data_03000E60.height) | 0x01000000);
        }
        {
            u16 zero;
            u16 *p = &zero;
            *p = 0;
            func_0814186C(p, data_03000E80.map,
                          (data_03000E80.width * data_03000E80.height) | 0x01000000);
        }
        func_0804C834(data_03000E30.entries, 0x40);
        func_08006B5C(&data_03002730);
        func_08006B8C(&data_03000880, 0);
        func_08006B8C(&data_03000880, 1);
        func_08071234(1);
        if (data_03002818->field_962_0)
            *phase = 0xFF;
        else
            *phase = 0xFD;
        break;
    case 0xFF:
        func_08003934(6);
        break;
    }
}
