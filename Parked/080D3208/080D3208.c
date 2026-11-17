#include "control_flags.h"

// Target complete [0x080D3208, 0x080D3506), 766 bytes, 383 instructions.

struct Task;

typedef struct {
    u8 busy;
    u8 unknown_01;
    u16 flags;
    u8 unknown_04[0x8CC];
    void *objects[16];
    struct Task *task;
    u8 unknown_914[0x1C4];
    u8 saved_control[0x50];
} State080D3208;

typedef void (*BufferCopier080D3208)(void *destination, const void *source,
                                     u32 size);

extern BufferCopier080D3208 const data_0836D4BC[];
extern void func_08142250(void *destination, const void *source, u32 size,
                          BufferCopier080D3208 callback);
extern u8 data_083947B4[];
extern u8 data_03003860[];
extern u8 data_0600FFC0[], data_06005800[], data_06005000[], data_0600C800[];
extern u16 func_080035A8(u8 index);
extern void *func_0808F79C(void);
extern void func_0808F7CC(void *resource);
extern struct Task *func_080D7A70(const void *data, u8 count,
                                  struct Task *parent);
extern u8 func_080D7A9C(struct Task *task);
extern void func_080D7AB0(struct Task *task);
extern void func_080D3994(void);
extern void func_080D39D4(void);
extern void *func_080D3AF8(void);
extern void func_08000B68(void *entry, u32 first, void *second, u16 count);
extern void func_08000B20(void *entry, u16 first, void *second, u16 count);
extern u16 func_0801AE00(void);
extern void func_08141868(const void *source, void *destination, u32 control);

static inline u8 is_wide_mode(void)
{
    switch (func_0801AE00()) {
    case 4:
    case 0x3F:
        return 1;
    }
    return 0;
}

int func_080D3208(struct Task *parent, u16 *phase, State080D3208 *state)
{
    u8 i;

    int next;

    switch (*phase) {
    case 0:
        g_control_flags_03000940.display &= ~func_080035A8(2);
        g_control_flags_03000940.display &= ~func_080035A8(3);
        func_08142250(state->saved_control, &g_control_flags_03000940.display,
                      0x50, data_0836D4BC[0]);
        for (i = 0; i < 16; i++)
            state->objects[i] = func_0808F79C();
        state->task = func_080D7A70(data_083947B4, 3, parent);
        state->busy = 1;
        break;
    case 1:
        break;
    case 0x100:
        if (!(state->flags & 4)) {
            int bank;
            int count;
            u32 zero;
            u32 zero2;

            func_08000B68(func_080D3AF8(), 0, data_0600FFC0, 16);
            bank = 6;
            count = 4;
            if (is_wide_mode()) {
                bank = 8;
                count = 2;
            }
            zero = 0;
            func_08141868(&zero, data_03003860 + bank * 32,
                          (((count << 5) / 4) & 0x1FFFFF) | 0x01000000);
            zero2 = 0;
            func_08141868(&zero2, data_03003860 + 0x2C0, 0x01000038);
        }
        state->flags &= ~4;
        (*phase)++;
        break;
    case 0x101:
        if (func_080D7A9C(state->task)) {
            func_080D7AB0(state->task);
            state->task = 0;
            func_080D3994();
            func_080D39D4();
            (*phase)++;
        }
        break;
    case 0x102:
        if (state->busy != 0)
            break;
        if (!(state->flags & 8)) {
            u16 bg1hofs, bg1vofs, bg0hofs, bg0vofs;
            u8 bldcnt_lo = 0, bldcnt_hi = 0, bldalpha_lo = 0;
            u8 bldalpha_hi = 0, bldy_lo = 0;

            bg1hofs = g_control_flags_03000940.bg1hofs;
            bg1vofs = g_control_flags_03000940.bg1vofs;
            bg0hofs = g_control_flags_03000940.bg0hofs;
            bg0vofs = g_control_flags_03000940.bg0vofs;

            if (state->flags & 0x10) {
                bldcnt_lo = g_control_flags_03000940.bldcnt_lo;
                bldcnt_hi = g_control_flags_03000940.bldcnt_hi;
                bldalpha_lo = g_control_flags_03000940.bldalpha_lo;
                bldalpha_hi = g_control_flags_03000940.bldalpha_hi;
                bldy_lo = g_control_flags_03000940.bldy_lo;
            }
            func_08142250(&g_control_flags_03000940.display, state->saved_control,
                          0x50, data_0836D4BC[0]);
            if (state->flags & 0x10) {
                g_control_flags_03000940.bldcnt_lo = bldcnt_lo;
                g_control_flags_03000940.bldcnt_hi = bldcnt_hi;
                g_control_flags_03000940.bldalpha_lo = bldalpha_lo;
                g_control_flags_03000940.bldalpha_hi = bldalpha_hi;
                g_control_flags_03000940.bldy_lo = bldy_lo;
            }
            g_control_flags_03000940.bg1hofs = bg1hofs;
            g_control_flags_03000940.bg1vofs = bg1vofs;
            g_control_flags_03000940.bg0hofs = bg0hofs;
            g_control_flags_03000940.bg0vofs = bg0vofs;
        }
        for (i = 0; i < 16; i++)
            func_0808F7CC(state->objects[i]);
        if (!(state->flags & 8)) {
            func_08000B20(func_080D3AF8(), 0, data_06005800, 0x400);
            (*phase)++;
        } else {
            next = 0x106;
            *phase = next;
        }
        break;
    case 0x103:
        func_08000B20(func_080D3AF8(), 0, data_06005000, 0x400);
        (*phase)++;
        break;
    case 0x104:
        func_08000B20(func_080D3AF8(), 0, data_0600C800, 0x1C00);
        (*phase)++;
        break;
    case 0x105:
        (*phase)++;
        break;
    case 0x106:
        *phase = 2;
        break;
    }
    return 0;
}
