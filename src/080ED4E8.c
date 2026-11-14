#include "ffta.h"
#include "control_flags.h"

// 0x080ED4E8..0x080ED7AE: 710 bytes, 355 instructions plus literal pools.

typedef struct {
    u16 step;
    u16 unknown_02;
    u16 *samples;
} Command080ED4E8;

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
    u8 active;
    u8 unknown_01;
    u16 timer;
    s16 base;
    s16 offsets[160];
    u8 phase_a;
    u8 phase_b;
    u16 phase_c;
    u8 unknown_14A[2];
    u16 *samples;
    LineState fade;
    LineState first;
    LineState second;
    void *scanline_task;
    void *window;
    void *effect;
    void *closing;
} Wave080ED4E8;

/* data_08149CE8 holds &g_control_flags_03000940.bg0hofs .. .bg3vofs. */
typedef struct {
    u16 *registers[8];
} ScrollRegisters;

extern const ScrollRegisters data_08149CE8;
extern const u8 data_083993AC[];
extern const u8 data_083993B4[];
extern void *func_080D9914(u8 first, u8 second, void *parent);
extern void func_080D9BA8(void *task, u8 value);
extern void *func_080D9A24(u8 first, u8 second, u8 count, const void *entries, void *parent);
extern void func_0801E610(u8 *first, u8 *second);
extern u16 func_080035F8(u8 layer);
extern u16 func_080035A8(u8 layer);
extern void func_080075CC(LineState *state, s32 x, s32 y, s32 endX, s32 endY);
extern void func_080076A0(LineState *state);
extern u32 func_08007880(const void *state);
extern void *func_080DFD8C(const void *, u8, u16, u16, void *);
extern void func_080D9B38(void *);
extern void func_080ED308(Wave080ED4E8 *);
extern void func_080ED3B8(Wave080ED4E8 *);

static inline void set_blend_targets(void)
{
    u8 first;
    u8 second;

    func_0801E610(&first, &second);
    g_control_flags_03000940.bldcnt_lo = 0x40 | func_080035F8(2);
    g_control_flags_03000940.bldcnt_hi =
        func_080035F8(first) | func_080035F8(second) | 0x30;
}

u32 func_080ED4E8(void *owner, Command080ED4E8 *command, Wave080ED4E8 *wave)
{
    ScrollRegisters registers;
    u16 offset;
    u16 i;
    u16 line;
    void *task;
    void *window;

    switch (command->step) {
    case 0:
        registers = data_08149CE8;
        wave->base = *registers.registers[4];
        task = func_080D9914(2, 0, owner);
        func_080D9BA8(task, 1);
        wave->scanline_task = task;
        window = func_080D9A24(0, 16, 0, 0, owner);
        set_blend_targets();
        g_control_flags_03000940.bldalpha_lo = 0;
        g_control_flags_03000940.bldalpha_hi = 16;
        wave->window = window;
        func_080075CC(&wave->fade, 160, 0, -31, 30);
        wave->active = 1;
        offset = 0;
        for (i = 0; i < 160; i++) {
            wave->offsets[i] = offset;
            if (i & 1)
                offset--;
        }
        wave->samples = command->samples;
        wave->effect = func_080DFD8C(data_083993AC, 1, 4, 0, owner);
        break;
    case 1:
        break;
    case 0x100:
        func_080076A0(&wave->fade);
        func_080ED308(wave);
        if (func_08007880(&wave->fade)) {
            wave->timer = 210;
            func_080D9B38(wave->window);
            command->step++;
        }
        break;
    case 0x101:
        g_control_flags_03000940.bldalpha_lo = 16;
        g_control_flags_03000940.bldalpha_hi = 16;
        command->step++;
        break;
    case 0x102:
        if (--wave->timer == 0) {
            wave->timer = 10;
            func_080075CC(&wave->first, 16, 0, 0, 15);
            func_080075CC(&wave->second, 16, 0, 16, 15);
            wave->closing = func_080DFD8C(data_083993B4, 3, 4, 0, owner);
            command->step++;
        }
        break;
    case 0x103:
        for (line = 0; line < 160; line++)
            wave->offsets[line] += 4;
        if (wave->timer == 0 || --wave->timer == 0) {
            func_080076A0(&wave->first);
            func_080076A0(&wave->second);
        }
        g_control_flags_03000940.bldalpha_lo = wave->first.x;
        g_control_flags_03000940.bldalpha_hi = wave->second.x;
        if (func_08007880(&wave->first)) {
            g_control_flags_03000940.display &= ~func_080035A8(2);
            command->step++;
        }
        break;
    case 0x104:
        wave->active = 0;
        func_080D9B38(wave->scanline_task);
        command->step = 2;
        break;
    }
    if (wave->active)
        func_080ED3B8(wave);
    return 0;
}
