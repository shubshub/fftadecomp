#include "ffta.h"
#include "control_flags.h"

/* Complete target [0x0804E9F0, 0x0804EBD0): 480 bytes. */
typedef void (*BufferCopier0804E9F0)(void *, const void *, u32);

typedef struct {
    u8 handle;
    s8 selected;
    s8 previous;
    u8 unknown_003;
    u8 saved[0x24c];
    u8 region[0x2c];
} Menu0804E9F0;

typedef struct {
    u8 unknown_00[0x10];
    u8 *tiles;
} Graphics0804E9F0;

typedef struct {
    u8 unknown_00[0x1a];
    u8 value;
} Panel0804E9F0;

typedef struct {
    void *unknown_00;
    Panel0804E9F0 *panel;
} MenuState0804E9F0;

extern Menu0804E9F0 *data_0201F54C;
extern BufferCopier0804E9F0 data_0836D4BC[];
extern u8 g_state_02002C10[];
extern u16 data_03003860[];
extern Graphics0804E9F0 data_03000990;
extern Table data_03002710;
extern Table data_03002720;
extern MenuState0804E9F0 *g_state_03002810;
extern u8 func_0804E008(void);
extern void func_0804E014(u8 enabled);
extern void *func_0804CA58(u32 bytes);
extern void func_0804CA6C(void *block);
extern void func_0814186C(const void *source, void *destination, u32 control);
extern void func_08013A88(void *destination, u16 count);
extern void func_0803172C(u8 index, u8 *phase);
extern void func_0804EBD0(void);
extern void func_0804EC74(void);
extern u8 func_080099A4(u32 handle);
extern void func_08017380(void *region, u16 tile, u8 palette);
extern u8 func_08036350(u8 value);

void func_0804E9F0(void *unused, u8 *state)
{
    /* The ROM lays the bodies out in the order the states run: case 2's,
     * at 0x0804EBB4, follows case 7's. */
    switch (*state) {
    case 0:
        data_0201F54C = func_0804CA58(0x69C);
        data_0201F54C->selected = 0;
        data_0201F54C->previous = -1;
        data_0836D4BC[0](data_0201F54C->saved, g_state_02002C10, 0x24c);
        func_0804E014(0);
        *state = 1;
        break;
    case 1:
        if (func_0804E008() == 9) {
            /* CpuFill16(0, ..., 0x200) of both halves of data_03003860:
             * the SDK's vu16 temporary, spelled through a pointer until
             * fftadecomp-kit#164, in the text of src/0807B858.c.  Each fill
             * has its own halfword (sp+0, sp+2) and takes its address before
             * the zero (mov r0, sp at 0x0804EA82 and 0x0804EA94). */
            {
                u16 zero;
                u16 *p = &zero;
                *p = 0;
                func_0814186C(p, data_03003860, 0x01000100);
            }
            {
                u16 zero;
                u16 *p = &zero;
                *p = 0;
                func_0814186C(p, data_03003860 + 0x100, 0x01000100);
            }
            func_08013A88(data_03000990.tiles + 0x2800, 0x2c);
            g_control_flags_03000940.bldcnt_lo = (g_control_flags_03000940.bldcnt_hi = 0);
            g_control_flags_03000940.bldalpha_lo = (g_control_flags_03000940.bldalpha_hi = 0);
            *state = 3;
        }
        break;
    case 3:
        func_08006ADC(&data_03002710, 4, (u32)func_0803172C);
        *state = 4;
        break;
    case 4:
        if (data_03002720.flags[0] == 0) {
            func_0804EBD0();
            *state = 5;
        }
        break;
    case 5:
        if (func_080099A4(data_0201F54C->handle)) {
            func_08017380(data_0201F54C->region, 0x140, 12);
            *state = 6;
        }
        break;
    case 6:
        if (data_03002710.flags[4] == 0xff) {
            *state = 7;
        } else {
            data_0201F54C->selected = func_08036350(g_state_03002810->panel->value);
            func_0804EC74();
        }
        break;
    case 7:
        data_0836D4BC[0](g_state_02002C10, data_0201F54C->saved, 0x24c);
        func_0804CA6C(data_0201F54C);
        func_0804E014(1);
        *state = 2;
        break;
    case 2:
        if (func_0804E008() == 9)
            *state = 8;
        break;
    case 8:
        *state = 9;
        break;
    case 9:
        /* The finished state: the jump table at 0x0804EA0C has ten entries
         * (cmp r0, #9 at 0x0804E9F8), the last one the return. */
        break;
    }
}
