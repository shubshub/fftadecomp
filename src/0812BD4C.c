#include "ffta.h"
#include "control_flags.h"

// Complete [0x0812BD4C, 0x0812C030): 740 bytes, 318 instructions.

typedef void (*BufferCopier0812BD4C)(void *destination, const void *source,
                                    u32 size);

typedef struct {
    u8 unknown_00[6];
    u8 active;
} Target0812BD4C;

typedef struct {
    u16 phase;
    u8 unknown_02[2];
    Target0812BD4C *target;
    u8 *source;
} Descriptor0812BD4C;

typedef struct {
    u32 offset;
    u32 size;
    u32 source;
} Graphic0812BD4C;

typedef struct {
    u16 value;
    u8 unknown_02[0x16];
} Ramp0812BD4C;

typedef struct {
    u16 display;
    u8 unknown_02[0x48];
    u8 bldcnt_lo;
    u8 bldcnt_hi;
    u8 bldalpha_lo;
    u8 bldalpha_hi;
    u8 unknown_4E[2];
} Snapshot0812BD4C;

typedef struct {
    Target0812BD4C *target;
    const Graphic0812BD4C *graphic;
    u16 next_phase;
    u16 delay;
    u16 hold;
    u8 fade_in;
    u8 fade_out;
    u8 notify;
    u8 index;
    u8 unknown_12[2];
    Ramp0812BD4C ramp;
    u8 transfers[4][0x1C];
    u8 window[0x1C];
    Snapshot0812BD4C saved;
} Payload0812BD4C;

typedef struct {
    u8 unknown_00[0x14];
    void *screen;
} Background0812BD4C;

typedef struct {
    u16 held;
    u16 pressed;
} InputState;

extern const Graphic0812BD4C data_083A832C[];
extern const u8 data_08A1BEDC[];
extern u8 data_03003960[];
extern u8 data_06008A40[];
extern BufferCopier0812BD4C const data_0836D4BC[];
extern Background0812BD4C data_03000990;
extern InputState data_03000000;

extern const u8 *func_080CBABC(u32 index);
extern void func_08000ADC(void *entry, const void *source, void *destination,
                         u16 words);
extern void func_08000BAC(void *request, u32 source, void *destination,
                         u16 width, u16 height, u16 source_stride,
                         u16 destination_stride);
extern void func_08007620(Ramp0812BD4C *ramp, s16 first, s16 second,
                          s16 target, s16 duration);
extern void func_080076F4(Ramp0812BD4C *ramp);
extern u32 func_08007894(const Ramp0812BD4C *ramp);
extern void *func_081443FC(void *destination, const void *source, u32 size);
extern void func_0814186C(const void *source, void *destination, u32 control);

u32 func_0812BD4C(void *task, Descriptor0812BD4C *descriptor,
                  Payload0812BD4C *payload)
{
    switch (descriptor->phase) {
    case 0: {
        u8 *source;
        u32 delay;

        payload->target = descriptor->target;
        source = descriptor->source;
        payload->index = source[4];
        delay = source[1] | (source[2] << 8);
        payload->delay = delay;
        payload->fade_in = source[3];
        payload->hold = source[5] | (source[6] << 8);
        payload->fade_out = source[7];
        payload->notify = source[8];
        payload->graphic = &data_083A832C[payload->index];
        if (delay < 2)
            payload->delay = 2;
        if (payload->hold < 2)
            payload->hold = 2;
        func_081443FC(&payload->saved, &g_control_flags_03000940, 0x50);
        break;
    }
    case 1:
        break;
    case 0x100: {
        const u8 *graphic;
        u8 *destination;
        s32 step;
        s32 i;

        data_0836D4BC[0](data_03003960, func_080CBABC(0x19), 0x20);
        graphic = data_08A1BEDC + payload->graphic->offset;
        destination = data_06008A40;
        step = payload->graphic->size >> 2;
        for (i = 0; i < 4; i++) {
            func_08000ADC(payload->transfers[i], graphic, destination,
                          step >> 2);
            graphic += step;
            destination += step;
        }
        g_control_flags_03000940.display |= 0x800;
        g_control_flags_03000940.bldcnt_lo = 0x48;
        g_control_flags_03000940.bldcnt_hi = 0x33;
        g_control_flags_03000940.bldalpha_lo = 0;
        g_control_flags_03000940.bldalpha_hi = 0x10;
        descriptor->phase = 0x101;
        break;
    }
    case 0x101:
        if (payload->delay != 0)
            payload->delay--;
        if (payload->delay == 1)
            func_08000BAC(payload->window, payload->graphic->source,
                          data_03000990.screen, 0x1E, 0x14, 0x3C, 0x40);
        if (payload->delay == 0) {
            func_08007620(&payload->ramp, 0, 0, 0x10, payload->fade_in);
            payload->next_phase = 0x103;
            descriptor->phase = 0x102;
        }
        break;
    case 0x102:
    case 0x104:
        if (func_08007894(&payload->ramp)) {
            descriptor->phase = payload->next_phase;
        } else {
            func_080076F4(&payload->ramp);
            g_control_flags_03000940.bldalpha_lo = payload->ramp.value;
            g_control_flags_03000940.bldalpha_hi = 0x10 - payload->ramp.value;
        }
        break;
    case 0x105:
        if (data_03000000.pressed & 1)
            descriptor->phase = 0x104;
        break;
    case 0x103:
        if (payload->hold == 0 || --payload->hold == 0) {
            func_08007620(&payload->ramp, 0x10, 0, 0, payload->fade_out);
            payload->next_phase = 0x106;
            if (payload->index == 0x10)
                descriptor->phase = 0x105;
            else
                descriptor->phase = 0x104;
        }
        break;
    case 0x106: {
        /* CpuFill16(0, screen, 0x500), the SDK's fill written out: vu16
         * as volatile u16, CpuSet as func_0814186C and 0x01000280 as
         * CPU_SET_16BIT | CPU_SET_SRC_FIXED | 0x280.  The slot's address is
         * formed at 0x0812BFAE, before the zero at 0x0812BFB0, as for a
         * volatile temporary. */
        {
            volatile u16 tmp = 0;
            func_0814186C((void *)&tmp, data_03000990.screen, 0x01000280);
        }
        g_control_flags_03000940.display = payload->saved.display;
        g_control_flags_03000940.bldcnt_lo = payload->saved.bldcnt_lo;
        g_control_flags_03000940.bldcnt_hi = payload->saved.bldcnt_hi;
        g_control_flags_03000940.bldalpha_lo = payload->saved.bldalpha_lo;
        g_control_flags_03000940.bldalpha_hi = payload->saved.bldalpha_hi;
        if (payload->notify != 0)
            payload->target->active = 1;
        descriptor->phase = 3;
        break;
    }
    }
    return 0;
}
